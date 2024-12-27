#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_GEN_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_GEN_RP_HH__

#include "mem/cache/replacement_policies/base.hh"
#include <unordered_map>

namespace gem5
{

namespace replacement_policy
{

class GenRP : public Base
{
  protected:
    /** GenRP-specific implementation of replacement data. */
    struct GenReplData : ReplacementData
    {
        /** Generation number, indicating the "age" of the entry. */
        uint8_t generation;

        /** Access counter, to track the frequency of access. */
        uint32_t accessCount;

        /** Default constructor, initialize generation and access counter. */
        GenReplData() : generation(0), accessCount(0) {}
    };

  public:
    typedef Params Params;
    GenRP(const Params &p);
    ~GenRP() = default;

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

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_GEN_RP_HH__
