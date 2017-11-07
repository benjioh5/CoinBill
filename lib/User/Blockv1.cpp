#include <User/Blockv1.h>

namespace CoinBill
{
    void BlockHeaderv1::incNonce() {
        m_Nonce++;
    }
    
    void BlockHeaderv1::setPrevHash(SHA512_t& hash) {
        m_PrevHash = hash;
    }
    void BlockHeaderv1::setAuther(ACCOUNT& account) {
        m_Auther = account;
    }
    void BlockHeaderv1::setVersion(uint64_t version) {
        m_Version = version;
    }
    void BlockHeaderv1::setDifficulty(uint64_t difficulty) {
        m_Difficulty = difficulty;
    }
    void BlockHeaderv1::setNumber(uint64_t number) {
         m_Number = number;
    }
    void BlockHeaderv1::setCoinLimit(uint64_t coin_limit) {
        m_CoinLimit = coin_limit;
    }
    void BlockHeaderv1::setCoinUsed(uint64_t coin_used) {
        m_CoinUsed = coin_used;
    }
    void BlockHeaderv1::setNonce(uint64_t nonce) {
        m_Nonce = nonce;
    }

    SHA512_t& BlockHeaderv1::getPrevHash() {
        return m_PrevHash;
    }
    ACCOUNT& BlockHeaderv1::getAccount() {
        return m_Auther;
    }
    uint64_t BlockHeaderv1::getVersion() const {
        return m_Version;
    }
    uint64_t BlockHeaderv1::getDifficulty() const {
        return m_Difficulty;
    }
    uint64_t BlockHeaderv1::getNumber() const {
        return m_Number;
    }
    uint64_t BlockHeaderv1::getCoinLimit() const {
        return m_CoinLimit;
    }
    uint64_t BlockHeaderv1::getCoinUsed() const {
        return m_CoinUsed;
    }
    uint64_t BlockHeaderv1::getNonce() const {
        return m_Nonce;
    }
}