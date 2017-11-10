#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;

    enum TransactionType {
        COIN_REWARD,
        COIN_SEND,
    };

    struct TransactionBase {
        TransactionType     m_Type;
        uint64_t            m_Version;
        // Time that created transaction.
        // This will be a posix time.
        uint64_t            m_Time;
        // block that this transaction created.
        SHA512_t            m_Block;
    };

    struct TransactionReward : public TransactionBase {
        SHA512_t            m_BlockMined;
        uint64_t            m_CoinReward;
    };
    struct TransactionSend : public TransactionBase {
        RSA2048_t           m_TransferTo;
        uint64_t            m_CoinSent;
    };

    class TransactionNode final
    {
        Wallet*          m_creator;

    protected:
        TransactionBase* m_transaction;
        RSA2048_t        m_TransAuther;
        RSA2048_t        m_TransAutherSign;

        TransactionNode* m_prevNode;
        TransactionNode* m_nextNode;

    public:
        TransactionBase& getTransaction();
        TransactionNode& getPrevNode();
        TransactionNode& getNextNode();

        RSA2048_t& getTransAuther();
        RSA2048_t& getTransAutherSign();

        bool isNodeHasSign();
        bool isNodeOwnerSame(Wallet* user);
        bool isNodeCoinTransferType();
        bool isNodeCoinReward();
        bool isNodeSignatureValid();

        bool RefreshNodeData();
        bool RefreshNodeSign();
        bool RefreshNodeSign(Wallet* user);
    };

    RSA2048_t encryptTransaction(TransactionBase& transaction, Wallet* user);
}

#endif
