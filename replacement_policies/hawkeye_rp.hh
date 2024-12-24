#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_HAWKEYE_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_HAWKEYE_RP_HH__

#include "mem/cache/replacement_policies/base.hh"
#include <unordered_map>

namespace gem5
{

namespace replacement_policy
{

class Hawkeye : public Base
{
  protected:
    /** Hawkeye-specific implementation of replacement data. */
    struct HawkeyeReplData : ReplacementData
    {
        /** Prediction value for reuse (0: not reused, 1: reused). */
        bool reusePrediction;

        /** Program counter (used for training prediction). */
        uint64_t pc;

        /** Default constructor. */
        HawkeyeReplData() : reusePrediction(false), pc(0) {}
    };

    /** Table for training reuse predictions based on PC. */
    mutable std::unordered_map<uint64_t, bool> predictionTable;

    /** Number of training accesses to maintain history. */
    const size_t trainingSize;

  public:
    typedef Params Params;
    Hawkeye(const Params &p);
    ~Hawkeye() = default;

    void invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
                                                                    override;

    void touch(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    void reset(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    ReplaceableEntry* getVictim(const ReplacementCandidates& candidates) const
                                                                     override;

    std::shared_ptr<ReplacementData> instantiateEntry() override;
};

} // namespace replacement_policy
} // namespace gem5

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_HAWKEYE_RP_HH__
