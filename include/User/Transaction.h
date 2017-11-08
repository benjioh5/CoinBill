#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    enum TransactionType {
        MINE,
        TRANSFER,
    };

    class TransactionBase
    {
        TransactionType m_TransType;
        SHA256_t        m_TransHash;
        SHA256_t        m_TransAuther;
    };
}

#endif