#ifndef COINBILL_USER_BLOCK
#define COINBILL_USER_BLOCK

#include <Support/Types.h>

namespace CoinBill
{
    class BlockHeaderv1 final
    {
    
        SHA512_t    m_PrevHash;
        ACCOUNT     m_Auther;

        uint64_t    m_Version;
        uint64_t    m_TimeStamp;
        uint64_t    m_Difficulty;
        uint64_t    m_Number;
        
        uint64_t    m_CoinLimit;
        uint64_t    m_CoinUsed;
        
        uint64_t    m_Nonce;
    public:
        void incNonce();
        
        void setPrevHash(SHA512_t& hash);
        void setAuther(ACCOUNT& account);
        void setVersion(uint64_t version);
        void setDifficulty(uint64_t difficulty);
        void setNumber(uint64_t number);
        void setCoinLimit(uint64_t coin_limit);
        void setCoinUsed(uint64_t coin_used);
        void setNonce(uint64_t nonce);

        SHA512_t& getPrevHash();
        ACCOUNT& getAccount();
        uint64_t getVersion() const;
        uint64_t getDifficulty() const;
        uint64_t getNumber() const;
        uint64_t getCoinLimit() const;
        uint64_t getCoinUsed() const;
        uint64_t getNonce() const;
    };

    class Blockv1
    {
        BlockHeaderv1   m_Header;
        SHA512_t        m_HeaderHash;

    public:

    };
}

#endif