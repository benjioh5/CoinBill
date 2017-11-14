#include <User/Wallet.h>
#include <User/Host.h>
#include <User/Blockv1.h>

#include <Support/Logger.h>

namespace CoinBill
{
    RSA_t& Wallet::getPubKey() {
        // returning a public key of wallet.
        return m_data.m_PubKey;
    }
    RSA_t& Wallet::getPrvKey() {
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

        return true;
    }

    bool Wallet::refreshPublicKey() {
        // Public key didn't refreshed.
        // Try extracting public key from private key.
        if (!m_data.m_PrvKey.isEmpty()) {
            // The private key should not empty.
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
    
    Wallet* createAccount(BlockV1* block, RSA_t& PrvKey, RSA_t& PubKey) {
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
    Wallet* createAccount(BlockV1* block, RSA_t& PrvKey) {
        return createAccount(block, PrvKey, PrvKey);
    }
    Wallet* createAccountPrv(RSA_t& PrvKey) {
        return createAccount(Host::getLastBlock(), PrvKey);
    }
    Wallet* createAccountPub(RSA_t& PubKey) {
        return createAccount(Host::getLastBlock(), (RSA_t)0, PubKey);
    }
    Wallet* createAccount() {
    }
}