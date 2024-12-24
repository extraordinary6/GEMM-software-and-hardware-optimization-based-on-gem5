/**
 * @file
 * Declaration of a Dynamic Re-Reference Interval Prediction (DRRIP) replacement policy.
 * Combines SRRIP and BRRIP to adaptively handle access patterns.
 */

#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_DRRIP_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_DRRIP_RP_HH__

#include "mem/cache/replacement_policies/base.hh"

namespace gem5
{

struct DRRIPRPParams;

namespace replacement_policy
{

class DRRIP : public Base
{
  protected:
    /** DRRIP-specific implementation of replacement data. */
    struct DRRIPReplData : ReplacementData
    {
        /** Re-reference prediction value. */
        uint8_t rrpv;

        /**
         * Default constructor. Initialize RRPV to max value.
         */
        DRRIPReplData() : rrpv(3) {}
    };

    /** Current mode: 0 for SRRIP, 1 for BRRIP. */
    mutable bool mode;

    /** Threshold for mode switching. */
    const unsigned threshold;

    /** Counters for access pattern statistics. */
    mutable unsigned srrip_hits;
    mutable unsigned brrip_hits;

  public:
    typedef DRRIPRPParams Params;
    DRRIP(const Params &p);
    ~DRRIP() = default;

    /**
     * Invalidate replacement data to set it as the next probable victim.
     *
     * @param replacement_data Replacement data to be invalidated.
     */
    void invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
                                                                    override;

    /**
     * Touch an entry to update its replacement data.
     * Decreases its RRPV to indicate recent use.
     *
     * @param replacement_data Replacement data to be touched.
     */
    void touch(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    /**
     * Reset replacement data on insertion.
     * Chooses RRPV based on current mode (SRRIP or BRRIP).
     *
     * @param replacement_data Replacement data to be reset.
     */
    void reset(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    /**
     * Find replacement victim based on RRPV.
     *
     * @param candidates Replacement candidates, selected by indexing policy.
     * @return Replacement entry to be replaced.
     */
    ReplaceableEntry* getVictim(const ReplacementCandidates& candidates) const
                                                                     override;

    /**
     * Instantiate a replacement data entry.
     *
     * @return A shared pointer to the new replacement data.
     */
    std::shared_ptr<ReplacementData> instantiateEntry() override;

    /**
     * Adaptive mode switching logic.
     */
    void updateMode() const;
};

} // namespace replacement_policy
} // namespace gem5

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_DRRIP_RP_HH__
