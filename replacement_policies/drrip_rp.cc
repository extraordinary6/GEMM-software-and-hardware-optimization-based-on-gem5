#include "mem/cache/replacement_policies/drrip_rp.hh"

#include <cassert>
#include <memory>

#include "params/DRRIPRP.hh"
#include "sim/cur_tick.hh"

namespace gem5
{

namespace replacement_policy
{

DRRIP::DRRIP(const Params &p)
    : Base(p), mode(0), threshold(p.threshold), srrip_hits(0), brrip_hits(0)
{
}

void
DRRIP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
{
    // Set RRPV to maximum (least likely to be reused)
    std::static_pointer_cast<DRRIPReplData>(replacement_data)->rrpv = 3;
}

void
DRRIP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<DRRIPReplData>(replacement_data);
    // Decrease RRPV (indicating recent use), but do not go below 0
    if (data->rrpv > 0)
        --data->rrpv;
}

void
DRRIP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<DRRIPReplData>(replacement_data);

    // SRRIP: RRPV = 1; BRRIP: RRPV = 3 (with probability p)
    if (mode == 0) {
        data->rrpv = 1; // SRRIP mode
    } else {
        data->rrpv = (rand() % 100 < 5) ? 1 : 3; // BRRIP mode (5% insertion as re-reference)
    }
}

ReplaceableEntry*
DRRIP::getVictim(const ReplacementCandidates& candidates) const
{
    // There must be at least one replacement candidate
    assert(candidates.size() > 0);

    // Search for a candidate with maximum RRPV (3)
    for (int rrpv = 3; rrpv >= 0; --rrpv) {
        for (const auto& candidate : candidates) {
            auto data = std::static_pointer_cast<DRRIPReplData>(candidate->replacementData);
            if (data->rrpv == rrpv) {
                return candidate;
            }
        }
    }

    // Fallback: return the first candidate (shouldn't happen)
    return candidates[0];
}

std::shared_ptr<ReplacementData>
DRRIP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new DRRIPReplData());
}

void
DRRIP::updateMode() const
{
    // Update mode based on hit statistics
    if (srrip_hits > brrip_hits + threshold) {
        mode = 0; // SRRIP
    } else if (brrip_hits > srrip_hits + threshold) {
        mode = 1; // BRRIP
    }
}

} // namespace replacement_policy
} // namespace gem5
