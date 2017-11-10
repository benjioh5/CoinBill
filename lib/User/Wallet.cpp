#include <User/Wallet.h>

namespace CoinBill
{
    RSA2048_t& Wallet::getPubKey() const {
        // returning a public key of wallet.
        return m_data->m_PubKey;
    }
    RSA2048_t& Wallet::getPrvKey() const {
        // returning a private key of wallet.
        return m_data->m_PrvKey;
    }
    RSA2048_t& Wallet::getOwner() const {
        // the identifier of user is public key.
        // so we returning a public key when owner requested.
        return getPubKey();
    }
    SHA512_t& Wallet::getWalletBlock() const {
        // block that accout created.
        return m_data->m_Block;
    }
    uint64_t CoinBill::Wallet::getWalletCoin() const {
        // get wallet coin left.
        // maybe we should refresh coin left before you reqesting how much coin left.
        return m_data->m_Money;
    }
}