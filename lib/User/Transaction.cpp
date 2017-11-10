#include <User/Transaction.h>
#include <User/Host.h>
#include <User/Wallet.h>

#include <Support/Cryption.h>

namespace CoinBill {
    TransactionBase& TransactionNode::getTransaction() {
        return (*m_transaction);
    }
    TransactionNode& TransactionNode::getNextNode() {
        return (*m_nextNode);
    }
    TransactionNode& TransactionNode::getPrevNode() {
        return (*m_prevNode);
    }

    RSA2048_t& TransactionNode::getTransAuther() {
        return getTransaction().m_TransAuther;
    }
    RSA2048_t& TransactionNode::getTransAutherSign() {
        return getTransaction().m_TransAutherSign;
    }

    bool TransactionNode::isNodeHasSign() {
        // Empty sign mean that never initialized transaction sign.
        // we will return false if its empty. not signed.
        return !(getTransAutherSign().isEmpty());
    }
    bool TransactionNode::isNodeOwnerSame(Wallet* user) {
        // public key value of owner's account should same. 
        return user->getPubKey() == getTransAuther();
    }

    bool TransactionNode::isNodeCoinTransferType() {
        return getTransaction().m_TransType == TransactionType::COIN_TRANSFER;
    }

    bool TransactionNode::isNodeCoinReward() {
        return getTransaction().m_TransType == TransactionType::COIN_REWARD;
    }

    bool TransactionNode::isNodeSignatureValid() {
        // Sign doesn't exists.
        if (getTransAutherSign().isEmpty())
            return false;

        return (Cryption::proofSignature(
            getTransAutherSign()    ,   // Transaction Auther Signature.
            getTransaction()        ,   // Transaction.
            getTransAuther())           // Transaction Auther.
        != CRESULT::SUCCESSED);
    }

    bool TransactionNode::RefreshNodeData() {
        getTransaction().m_TransTime = Host::getHostTime();
    }

    bool TransactionNode::RefreshNodeSign(Wallet* user) {
        // Try signing it.
        RSA2048_t sign = encryptTransaction(getTransaction(), user);

        // Signing failed, returned empty sign, or signature isn't match with original.
        if (sign.isEmpty() || (Cryption::proofSignature(sign, getTransaction(), user->getPubKey()) != CRESULT::SUCCESSED))
            return false;

        // use this sign.
        getTransaction().m_TransAutherSign  = sign;
        getTransaction().m_TransAuther      = user->getPubKey();

        return true;
    }

    RSA2048_t encryptTransaction(TransactionBase& transaction, Wallet* user) {
        RSA2048_t sign = 0;

        // You cannot sign without your private key.
        // this wallet is currupted, returning a empty sign.
        if (user->getPrvKey().isEmpty())
            return sign;

        // Signing a transaction.
        Cryption::getSignature<TransactionBase>(sign, transaction, user->getPrvKey());

        return sign;
    }
}