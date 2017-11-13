#include <User/Transaction.h>
#include <User/Host.h>
#include <User/Wallet.h>

#include <Support/Cryption.h>

namespace CoinBill {
    TransactionHead& TransactionNode::getHead() {
        // returning the transaction now holding.
        return (*m_TransHead);
    }
    TransactionBody& TransactionNode::getBody() {
        return (*m_TransBody);
    }
    TransactionNode& TransactionNode::getNextNode() {
        // returning next trasaction node.
        return (*m_nextNode);
    }
    TransactionNode& TransactionNode::getPrevNode() {
        // returning prev transaction node.
        return (*m_prevNode);
    }
    RSA4096_t& TransactionNode::getTransSignature() {
        // returning auther signature of transaction.
        return m_TransSign;
    }

    bool TransactionNode::isNodeHasSign() {
        // Empty sign mean that never initialized transaction sign.
        // we will return false if its empty. not signed.
        return !(getTransSignature().isEmpty());
    }
    bool TransactionNode::isNodeOwnerSame(Wallet* user) {
        // public key value of owner's account should same. 
        // we cannot proof the signature if owner isn't same.
        return (user == m_creator) || (user->getAccount() == m_creator->getAccount());
    }

    bool TransactionNode::isNodeCoinTransferType() {
        return getHead().m_Type == TransactionType::COIN_SEND;
    }

    bool TransactionNode::isNodeCoinReward() {
        return getHead().m_Type == TransactionType::COIN_REWARD;
    }

    bool TransactionNode::isNodeSignatureValid() {
        // Sign doesn't exists.
        if (getTransSignature().isEmpty())
            return false;

        return (Cryption::verifySignature(
            getTransSignature()     ,   // Transaction Auther Signature.
            getHead()               ,   // Transaction.
            m_creator->getPubKey())     // Transaction Auther.
        != CRESULT::SUCCESSED);
    }

    bool TransactionNode::RefreshNodeData() {
        getHead().m_Version  = Host::getHostVersion();
        getHead().m_Time     = Host::getHostTime();

        return true;
    }

    bool TransactionNode::RefreshNodeSign() {
        return RefreshNodeSign(m_creator);
    }

    bool TransactionNode::RefreshNodeSign(Wallet* user) {
        // Try signing it.
        RSA4096_t sign = encryptTransaction(getHead(), user);

        // Signing failed, returned empty sign, or signature isn't match with original.
        if (sign.isEmpty() || (Cryption::verifySignature(sign, getHead(), user->getPubKey()) != CRESULT::SUCCESSED))
            return false;

        // use this sign.
        m_creator           = user;
        m_TransSign         = sign;
        
        return true;
    }

    RSA4096_t encryptTransaction(TransactionHead& transaction, Wallet* user) {
        RSA4096_t sign = 0;

        // You cannot sign without your private key.
        // this wallet is currupted, returning a empty sign.
        if (user->getPrvKey().isEmpty())
            return sign;

        // Signing a transaction.
        Cryption::getSignature<TransactionHead>(sign, transaction, user->getPrvKey());

        // return signed signature.
        return sign;
    }
}