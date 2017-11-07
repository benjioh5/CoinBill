#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    class TransactionBase
    {
        SHA256_t    m_TransHash;
        ACCOUNT     m_TransAuther;
    };
}

#endif