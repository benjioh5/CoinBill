#include <User/Wallet.h>

namespace CoinBill
{
    RSA2048_t& Wallet::getPubKey() const {
        return m_data->m_PubKey;
    }
    RSA2048_t& Wallet::getPrvKey() const {
        return m_data->m_PrvKey;
    }
    RSA2048_t& Wallet::getOwner() const {
        return getPubKey();
    }
    SHA512_t& Wallet::getWalletBlock() const {
        return m_data->m_Block;
    }
    uint64_t CoinBill::Wallet::getWalletCoin() const {
        return m_data->m_Money;
    }
}