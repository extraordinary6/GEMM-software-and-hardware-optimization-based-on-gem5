#include "mem/cache/replacement_policies/hawkeye_rp.hh"
#include "params/HawkeyeRP.hh"
#include "sim/cur_tick.hh"

namespace gem5
{

namespace replacement_policy
{

Hawkeye::Hawkeye(const Params &p)
    : Base(p), trainingSize(1000) // Example size for training window
{
}

void
Hawkeye::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
{
    auto data = std::static_pointer_cast<HawkeyeReplData>(replacement_data);
    data->reusePrediction = false;
    data->pc = 0;
}

void
Hawkeye::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<HawkeyeReplData>(replacement_data);
    // Mark the block as reused if it was predicted reusable
    if (data->pc != 0) {
        predictionTable[data->pc] = true;
    }
}

void
Hawkeye::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    auto data = std::static_pointer_cast<HawkeyeReplData>(replacement_data);

    // Capture program counter (PC) from memory access trace
    data->pc = /* Insert logic to capture PC here */ 0;

    // Predict reuse based on historical data
    if (predictionTable.find(data->pc) != predictionTable.end()) {
        data->reusePrediction = predictionTable[data->pc];
    } else {
        data->reusePrediction = false; // Default prediction
    }
}

ReplaceableEntry*
Hawkeye::getVictim(const ReplacementCandidates& candidates) const
{
    // Search for the best victim (not predicted for reuse)
    ReplaceableEntry* victim = nullptr;
    for (const auto& candidate : candidates) {
        auto data = std::static_pointer_cast<HawkeyeReplData>(
            candidate->replacementData);
        if (!data->reusePrediction) {
            victim = candidate;
            break;
        }
    }

    // If no non-reuse candidate is found, fallback to the first candidate
    if (!victim) {
        victim = candidates[0];
    }

    return victim;
}

std::shared_ptr<ReplacementData>
Hawkeye::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new HawkeyeReplData());
}

} // namespace replacement_policy
} // namespace gem5
