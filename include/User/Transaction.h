#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;

    enum TransactionType {
        COIN_REWARD,
        COIN_TRANSFER,
    };

    struct TransactionBase
    {
        TransactionType     m_TransType;
        SHA256_t            m_TransSign;
        SHA256_t            m_TransOwner;
        
        // Time that created transaction.
        // This will be a posix time.
        uint64_t            m_TransTime;
    };

    class TransactionNode 
    {
    protected:
        bool m_isNodeHasSign;

        TransactionBase* m_transaction;
        TransactionNode* m_prevNode;
        TransactionNode* m_nextNode;

    public:
        TransactionBase* getTransaction();
        TransactionNode* getPrevNode();
        TransactionNode* getNextNode();

        bool isNodeHasSign();
        bool isNodeOwnerSame(Wallet* user);
        bool isNodeCoinTransferType();
        bool isNodeCoinReward();
        bool isNodeSignatureValid();

        void RefreshNodeData();
        void RefreshNodeSign(Wallet* user);
    };
}

#endif