#ifndef COINBILL_USER_TRANSACTION
#define COINBILL_USER_TRANSACTION

#include <Support/Types.h>

namespace CoinBill
{
    class Transaction
    {
        RSA256_t TransKey;
        SHA256_t TransHash;


    };
}

#endif