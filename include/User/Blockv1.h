#ifndef COINBILL_USER_BLOCK
#define COINBILL_USER_BLOCK

#include <Support/Types.h>

namespace CoinBill
{
    class BlockHeaderv1
    {
    public:
        SHA512_t        m_PrevHash;
        AUTHER_t        m_AutherPub;

        uint64_t        m_Version;
        uint64_t        m_TimeStamp;
        uint64_t        m_Difficulty;
        uint64_t        m_Number;
        
        uint64_t        m_CoinLimit;
        uint64_t        m_CoinUsed;
        
        uint64_t        m_Nonce;
    };
}

#endif