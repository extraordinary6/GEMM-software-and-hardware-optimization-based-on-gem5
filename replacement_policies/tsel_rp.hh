/**
 * @file
 * Declaration of a Time-Selector (TSel) replacement policy.
 * The victim is chosen based on custom timestamp logic.
 */

#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_TSEL_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_TSEL_RP_HH__

#include "mem/cache/replacement_policies/base.hh"

namespace gem5
{

struct TSelRPParams;

namespace replacement_policy
{

class TSel : public Base
{
  protected:
    /** TSel-specific implementation of replacement data. */
    struct TSelReplData : ReplacementData
    {
        /** Tick on which the entry was last touched. */
        Tick lastTouchTick;

        /**
         * Default constructor. Invalidate data.
         */
        TSelReplData() : lastTouchTick(0) {}
    };

  public:
    typedef TSelRPParams Params;
    TSel(const Params &p);
    ~TSel() = default;

    /**
     * Invalidate replacement data to set it as the next probable victim.
     * Resets its last touch tick.
     *
     * @param replacement_data Replacement data to be invalidated.
     */
    void invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
                                                                    override;

    /**
     * Touch an entry to update its replacement data.
     * Sets its last touch tick as the current tick.
     *
     * @param replacement_data Replacement data to be touched.
     */
    void touch(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    /**
     * Reset replacement data. Used when an entry is inserted.
     * Sets its last touch tick as the current tick.
     *
     * @param replacement_data Replacement data to be reset.
     */
    void reset(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;

    /**
     * Find replacement victim using TSel timestamps.
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
};

} // namespace replacement_policy
} // namespace gem5

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_TSEL_RP_HH__
