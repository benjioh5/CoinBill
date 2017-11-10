#include <User/Transaction.h>
#include <User/Host.h>
#include <User/Wallet.h>

#include <Support/Cryption.h>

namespace CoinBill {
    TransactionBase& TransactionNode::getTransaction() {
        // returning the transaction now holding.
        return (*m_transaction);
    }
    TransactionNode& TransactionNode::getNextNode() {
        // returning next trasaction node.
        return (*m_nextNode);
    }
    TransactionNode& TransactionNode::getPrevNode() {
        // returning prev transaction node.
        return (*m_prevNode);
    }

    RSA2048_t& TransactionNode::getTransAuther() {
        // returning auther of transaction.
        return m_TransAuther;
    }
    RSA2048_t& TransactionNode::getTransAutherSign() {
        // returning auther signature of transaction.
        return m_TransAutherSign;
    }

    bool TransactionNode::isNodeHasSign() {
        // Empty sign mean that never initialized transaction sign.
        // we will return false if its empty. not signed.
        return !(getTransAutherSign().isEmpty());
    }
    bool TransactionNode::isNodeOwnerSame(Wallet* user) {
        // public key value of owner's account should same. 
        // we cannot proof the signature if owner isn't same.
        return (user == m_creator) || (user->getPubKey() == getTransAuther());
    }

    bool TransactionNode::isNodeCoinTransferType() {
        return getTransaction().m_Type == TransactionType::COIN_SEND;
    }

    bool TransactionNode::isNodeCoinReward() {
        return getTransaction().m_Type == TransactionType::COIN_REWARD;
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
        getTransaction().m_Version  = Host::getHostVersion();
        getTransaction().m_Time     = Host::getHostTime();

        return true;
    }

    bool TransactionNode::RefreshNodeSign() {
        return RefreshNodeSign(m_creator);
    }

    bool TransactionNode::RefreshNodeSign(Wallet* user) {
        // Try signing it.
        RSA2048_t sign = encryptTransaction(getTransaction(), user);

        // Signing failed, returned empty sign, or signature isn't match with original.
        if (sign.isEmpty() || (Cryption::proofSignature(sign, getTransaction(), user->getPubKey()) != CRESULT::SUCCESSED))
            return false;

        // use this sign.
        m_creator           = user;
        m_TransAutherSign   = sign;
        m_TransAuther       = user->getPubKey();
        
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

        // return signed signature.
        return sign;
    }
}