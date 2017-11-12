#include <User/Wallet.h>

CoinBill::Wallet* createManagedWallet()
{
    new CoinBill::Wallet();
}

void deleteManagedWallet(CoinBill::Wallet* wallet)
{
    delete wallet;
}

namespace CoinBill
{
    RSA4096_t& Wallet::getPubKey() const {
        // returning a public key of wallet.
        return m_data->m_PubKey;
    }
    RSA4096_t& Wallet::getPrvKey() const {
        // returning a private key of wallet.
        return m_data->m_PrvKey;
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
    WalletData* Wallet::getWalletData() const {
        return m_data;
    }
    bool Wallet::refreshAccount() {
        // Public key didn't refreshed.
        // Try extracting public key from private key.
        if (m_data->m_PrvKey == m_data->m_PubKey || m_data->m_PubKey.isEmpty())
            if (!refreshPublicKey())
                return false;

        // check is this still empty.
        if (m_data->m_PubKey.isEmpty())
            // Failed to refresh account.
            // we don't holding a public key.
            return false;

        // We created a hash for account.
        Cryption::getSHA256Hash(m_account, &m_data->m_PubKey);
        return true;
    }

    bool Wallet::refreshPublicKey() {
        // Public key didn't refreshed.
        // Try extracting public key from private key.
        if (!m_data->m_PrvKey.isEmpty()) {
            // The private key should not empty.
            RSA*  PubKey = RSA_new();
            void* PrvKeyBuf = m_data->m_PrvKey;
            void* PubKeyBuf = m_data->m_PubKey;

            // Extract key from data.
            d2i_RSAPrivateKey(&PubKey, (const unsigned char**)&PrvKeyBuf, sizeof(RSA4096_t) * 8);

            // Re Initialize key to data.
            i2d_RSAPublicKey(PubKey, (unsigned char**)&PubKeyBuf);
            RSA_free(PubKey);
            return true;
        }
        return false;
    }
    SHA256_t& Wallet::getAccount() {
        return m_account;
    }

    Wallet* createAccount() {
        return nullptr;
    }
    Wallet* createAccount(BlockV1* block, SHA256_t& hash) {
        return nullptr;
    }
    Wallet* createAccount(RSA* Key) {
        return nullptr;
    }
    Wallet* createAccountPrv(RSA4096_t& PrvKey) {
        Wallet*     wallet      = createManagedWallet();
        WalletData* walletData  = wallet->getWalletData();

        walletData->m_Money             = 0;
        walletData->m_PrvKey            = PrvKey;
        // TODO : implement get last block.
        walletData->m_Block             = 0;

        wallet->refreshPublicKey();
        wallet->refreshAccount();

        return wallet;
    }
    Wallet* createAccountPub(RSA4096_t& PubKey) {
        Wallet*     wallet      = createManagedWallet();
        WalletData* walletData  = wallet->getWalletData();

        walletData->m_Money     = 0;
        walletData->m_PubKey    = PubKey;
        // TODO : implement get last block.
        walletData->m_Block     = 0;

        wallet->refreshAccount();
        return wallet;
    }
}