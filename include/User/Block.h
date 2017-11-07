#ifndef COINBILL_USER_BLOCK
#define COINBILL_USER_BLOCK

#include <Support/Types.h>

namespace CoinBill
{
    struct BlockHeader
    {
        // The hash of previus block.
        // This isn't a header of block hash. this includes full hash of full block object.
        SHA512_t        m_PrevHash;

        // Version of CoinBill client that created this block.
        uint64_t        m_Version;

        // Timestamp that this block created.
        // stamp will be recorded when the block creating.
        // this is posix based time stamp.
        uint64_t        m_TimeStamp;

        // The offset to make a PoW(proof of works) block.
        uint64_t        m_Nonce;

        // Difficult of mining.
        // This will increased every 500 blocks.
        uint64_t        m_DifficultBits;
    };
}

#endif