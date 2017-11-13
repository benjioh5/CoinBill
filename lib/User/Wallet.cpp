#include <User/Wallet.h>
#include <User/Host.h>
#include <User/Blockv1.h>

#include <Support/Logger.h>

namespace CoinBill
{
    RSA4096_t& Wallet::getPubKey() {
        // returning a public key of wallet.
        return m_data.m_PubKey;
    }
    RSA4096_t& Wallet::getPrvKey() {
        // returning a private key of wallet.
        return m_data.m_PrvKey;
    }
    SHA512_t& Wallet::getWalletBlock() {
        // block that accout created.
        return m_data.m_Block;
    }
    uint64_t CoinBill::Wallet::getWalletCoin() {
        // get wallet coin left.
        // maybe we should refresh coin left before you reqesting how much coin left.
        return m_data.m_Money;
    }
    WalletData& Wallet::getWalletData() {
        return m_data;
    }
    bool Wallet::refreshAccount() {
        // Public key didn't refreshed.
        // Try extracting public key from private key.
        if (m_data.m_PrvKey == m_data.m_PubKey || m_data.m_PubKey.isEmpty())
            if (!refreshPublicKey())
                return false;

        // check is this still empty.
        if (m_data.m_PubKey.isEmpty())
            // Failed to refresh account.
            // we don't holding a public key.
            return false;

        // We created a hash for account.
        Cryption::getSHA256Hash(m_account, &m_data.m_PubKey);
        return true;
    }

    bool Wallet::refreshPublicKey() {
        // Public key didn't refreshed.
        // Try extracting public key from private key.
        if (!m_data.m_PrvKey.isEmpty()) {
            // The private key should not empty.
            RSA*  PubKey = RSA_new();
            void* PrvKeyBuf = m_data.m_PrvKey;
            void* PubKeyBuf = m_data.m_PubKey;

            // Extract key from data.
            d2i_RSAPrivateKey(&PubKey, (const unsigned char**)&PrvKeyBuf, sizeof(RSA4096_t) * 8);

            // Re Initialize key to data.
            i2d_RSAPublicKey(PubKey, (unsigned char**)&PubKeyBuf);
            RSA_free(PubKey);
            return true;
        }
        return false;
    }
    void Wallet::dump() {
        LogInf() << " Wallet Dump Report " << this << std::endl;
        LogInf() << "\t ==========================================="    << std::endl;
        LogInf() << "\t - Accoount   : 0x" << this->getAccount()        << std::endl;
        LogInf() << "\t - PubKey     : 0x" << this->getPubKey()         << std::endl;
        LogInf() << "\t - PrvKey     : 0x" << this->getPrvKey()         << std::endl;
        LogInf() << "\t - Block Hash : 0x" << this->getWalletBlock()    << std::endl;
        LogInf() << "\t - Coins      : 0x" << this->getWalletCoin()     << std::endl;
        LogInf() << "\t ==========================================="    << std::endl;
    }
    SHA256_t& Wallet::getAccount() {
        return m_account;
    }

    // TODO : Mananged allocation.
    Wallet* createManagedWallet() {
        return new Wallet;
    }
    void deleteManagedWallet(Wallet* wallet) {
        delete wallet;
    }
    
    Wallet* createAccount(BlockV1* block, RSA4096_t& PrvKey, RSA4096_t& PubKey) {
        Wallet*         wallet      = createManagedWallet();
        WalletData&     walletData  = wallet->getWalletData();

        walletData.m_PubKey        = PubKey;
        walletData.m_PrvKey        = PrvKey;
        walletData.m_Money         = 0;
        walletData.m_Block         = block != nullptr ? block->m_HeaderHash : 0;

        // Verify wallet.
        if (!wallet->refreshAccount()) {
            deleteManagedWallet(wallet);
            return nullptr;
        }

        return wallet;
    }
    Wallet* createAccount(BlockV1* block, RSA4096_t& PrvKey) {
        return createAccount(block, PrvKey, PrvKey);
    }
    Wallet* createAccount(RSA* Key) {
        RSA4096_t PrvKey = 0;
        RSA4096_t PubKey = 0;
        void* pPrvBuf = PrvKey;
        void* pPubBuf = PubKey;

        // Key should not nullptr, also valid.
        if (Key == nullptr || !RSA_check_key(Key))
            return nullptr;

        

        return createAccount(Host::getLastBlock(), PrvKey, PubKey);
    }
    Wallet* createAccountPrv(RSA4096_t& PrvKey) {
        return createAccount(Host::getLastBlock(), PrvKey);
    }
    Wallet* createAccountPub(RSA4096_t& PubKey) {
        return createAccount(Host::getLastBlock(), (RSA4096_t)0, PubKey);
    }
    Wallet* createAccount() {
        Wallet* wallet  = nullptr;

        RSA*    Key     = RSA_new();
        BIGNUM* Bne     = BN_new();

        IF_FAILED_GOTO(BN_set_word(Bne, RSA_F4)                 , END_POINT);
        IF_FAILED_GOTO(RSA_generate_key_ex(Key, 2048, Bne, 0)   , END_POINT);

        wallet = createAccount(Key);

    END_POINT:
        RSA_free(Key);
        BN_free(Bne);
        return wallet;
    }
}