#include <User/Transaction.h>
#include <User/Host.h>

namespace CoinBill {
    TransactionBase* TransactionNode::getTransaction() {
        return m_transaction;
    }
    TransactionNode* TransactionNode::getNextNode() {
        return m_nextNode;
    }
    TransactionNode* TransactionNode::getPrevNode() {
        return m_prevNode;
    }

    bool TransactionNode::isNodeHasSign() {
        return !(getTransaction()->m_TransSign).isEmpty();
    }
    bool TransactionNode::isNodeOwnerSame(Wallet* user) {
        // TODO : implement wallet first.
        return true;
    }

    bool TransactionNode::isNodeCoinTransferType() {
        return getTransaction()->m_TransType == TransactionType::COIN_TRANSFER;
    }

    bool TransactionNode::isNodeCoinReward() {
        return getTransaction()->m_TransType == TransactionType::COIN_REWARD;
    }

    bool TransactionNode::isNodeSignatureValid() {
        // TODO : signature check.
        return true;
    }

    void TransactionNode::RefreshNodeData() {
        TransactionBase* transaction = getTransaction();

        transaction->m_TransTime = Host::getHostTime();
    }

    void TransactionNode::RefreshNodeSign(Wallet* user) {
        // TODO : implement wallet first.
    }
}