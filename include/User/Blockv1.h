#ifndef COINBILL_USER_BLOCKV1
#define COINBILL_USER_BLOCKV1

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;
    class BlockHeaderV1
    {
    public:
        SHA512_t    m_PrevHash;
        RSA_t       m_Auther;

        uint64_t    m_Version;
        uint64_t    m_TimeStamp;
        uint512_t   m_Difficulty;
        uint256_t   m_Number;
        
        uint128_t   m_CoinLimit;
        uint128_t   m_CoinUsed;
        
        uint256_t   m_Nonce;

        void dump();
    };

    class BlockV1
    {
    public:
        BlockHeaderV1   m_Header;
        SHA512_t        m_HeaderHash;

        void dump();
    };

    // arounding block in the program is all managed block object.
    // because use a custom allocator for creating new block.
    // so do not delete block manually. use disposeBlock function instead.
    // TODO : implement block allocator, distructor.

    BlockV1* createNewBlock(Wallet* user, BlockV1* prev);
    BlockV1* refreshBlockNonce(BlockV1* block, bool rehash = true);
    BlockV1* refreshBlockInfo(BlockV1* block, bool rehash = true);
    BlockV1* refreshBlockHash(BlockV1* block, uint32_t cycle);
}

#endif // COINBILL_USER_BLOCKV1