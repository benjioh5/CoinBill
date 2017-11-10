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
        // TODO : signature check.
        return true;
    }

    void TransactionNode::RefreshNodeData() {
        getTransaction().m_TransTime = Host::getHostTime();
    }

    void TransactionNode::RefreshNodeSign(Wallet* user) {
        getTransaction().m_TransAutherSign = signTransaction(getTransaction(), user);
    }

    SHA256_t signTransaction(TransactionBase& transaction, Wallet* user) {
        SHA256_t sign = 0;

        // You cannot sign without your private key.
        // this wallet is currupted, returning a empty sign.
        if (user->getPrvKey().isEmpty())
            return sign;

        // Signing a transaction.
        Cryption::getSignature256<TransactionBase>(sign, transaction, user->getPrvKey());
        return sign;
    }
}