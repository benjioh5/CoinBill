#ifndef COINBILL_USER_BLOCK
#define COINBILL_USER_BLOCK

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;
    struct BlockHeaderV1
    {
        SHA512_t    m_PrevHash;
        RSA2048_t   m_Auther;

        uint64_t    m_Version;
        uint64_t    m_TimeStamp;
        uint512_t   m_Difficulty;
        uint256_t   m_Number;
        
        uint128_t   m_CoinLimit;
        uint128_t   m_CoinUsed;
        
        uint256_t   m_Nonce;

        void dump();
    };

    struct BlockV1
    {
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

#endif