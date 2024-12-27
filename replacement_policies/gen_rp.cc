#include "mem/cache/replacement_policies/gen_rp.hh"
#include "params/GenRP.hh"
#include "sim/cur_tick.hh"

namespace gem5
{

namespace replacement_policy
{

GenRP::GenRP(const Params &p)
    : Base(p)
{
}

void
GenRP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
{
    auto data = std::static_pointer_cast<GenReplData>(replacement_data);
    // Reset generation and access count when invalidating
    data->generation = 0;
    data->accessCount = 0;
}

void
GenRP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<GenReplData>(replacement_data);
    // Increment access count for each touch
    data->accessCount++;

    // If access count exceeds threshold, move to next generation
    if (data->accessCount > 5) {
        data->generation++;
        data->accessCount = 0; // Reset access count after generation change
    }
}

void
GenRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<GenReplData>(replacement_data);
    // Initialize generation and access count
    data->generation = 0;
    data->accessCount = 0;
}

ReplaceableEntry*
GenRP::getVictim(const ReplacementCandidates& candidates) const
{
    // Find the candidate with the smallest generation number
    ReplaceableEntry* victim = candidates[0];
    for (const auto& candidate : candidates) {
        auto data = std::static_pointer_cast<GenReplData>(candidate->replacementData);
        auto victimData = std::static_pointer_cast<GenReplData>(victim->replacementData);

        // Select the entry with the smallest generation (oldest entry)
        if (data->generation < victimData->generation) {
            victim = candidate;
        }
    }

    return victim;
}

std::shared_ptr<ReplacementData>
GenRP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new GenReplData());
}

} // namespace replacement_policy
} // namespace gem5
