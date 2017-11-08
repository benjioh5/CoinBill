#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    enum TransactionType {
        MINED,
        TRANSFER,
    };

    struct TransactionBase
    {
        TransactionType m_TransType;

        SHA256_t        m_TransHash;
        SHA256_t        m_TransAuther;
        RSA2048_t       m_TransKey;
    };

    class TransactionNode 
    {
        TransactionBase* currNode;
        TransactionBase* prevNode;
    };
}

#endif