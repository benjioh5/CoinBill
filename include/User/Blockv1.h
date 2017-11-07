#ifndef COINBILL_USER_BLOCK
#define COINBILL_USER_BLOCK

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;
    struct BlockHeaderV1
    {
    
        SHA512_t    m_PrevHash;
        SHA256_t    m_Auther;

        uint64_t    m_Version;
        uint64_t    m_TimeStamp;
        uint64_t    m_Difficulty;
        uint64_t    m_Number;
        
        uint64_t    m_CoinLimit;
        uint64_t    m_CoinUsed;
        
        uint64_t    m_Nonce;
    };

    struct BlockV1
    {
        BlockHeaderV1   m_Header;
        SHA512_t        m_HeaderHash;
    };


    BlockV1* CreateNewBlock(Wallet* user, BlockV1* prev);
}

#endif