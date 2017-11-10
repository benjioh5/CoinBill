#include <User/Host.h>
#include <User/Blockv1.h>
#include <User/Wallet.h>

#include <Support/Cryption.h>


namespace CoinBill
{
    // We use SHA-512 to hash block.
    BlockV1* refreshBlockHash(BlockV1* block, uint32_t cycle) {
        // Nothing to hash...
        if (cycle == 0) return nullptr;

        // Reset hash.
        SHA512_t &curHash = block->m_HeaderHash; 
        curHash = 0;

        // Prehash header.
        Cryption::getSHA512Hash(curHash, &block->m_Header);

        // Starting i with 1, because we prehashed it.
        // if it has 1 cycle will pass this job.
        for (unsigned int i = 1; i < cycle; ++i) {
            Cryption::getSHA512Hash(curHash, &curHash);
        }
        return block;
    }

    BlockV1* createNewBlock(Wallet* user, BlockV1* prev) {
        bool            newDifficultyTriggered  = false;

        BlockV1*        block                   = new BlockV1();
        BlockHeaderV1&  blockHeader             = block->m_Header;
        
        // We are going to make it more difficult when number is multiple of Host::getNumNewDiff()
        if (prev->m_Header.m_Number % Host::getNumNewDiff())
            newDifficultyTriggered = true;

        // Hash value of previus block.
        blockHeader.m_PrevHash      = prev->m_HeaderHash;

        // Difficulty will changed every 2 month. (just for now)
        // lower value of difficulty is harder. 
        // we are going to make it lower when its triggered.
        blockHeader.m_Difficulty    = prev->m_Header.m_Difficulty - newDifficultyTriggered;
        blockHeader.m_Number        = prev->m_Header.m_Number + 1;

        // Auther of new block. it is Wallet that we are trying to make this block.
        blockHeader.m_Auther        = user->getOwner();
        blockHeader.m_Version       = Host::getHostVersion();
        blockHeader.m_TimeStamp     = Host::getHostTime();
        blockHeader.m_CoinLimit     = 0; // TODO : determine coin limit.
        blockHeader.m_CoinUsed      = 0;
        blockHeader.m_Nonce         = 0;

        return refreshBlockHash(block, Host::getHashCycle());
    }

    BlockV1* refreshBlockNonce(BlockV1* block, bool rehash) {
        block->m_Header.m_Nonce++;

        return rehash ? refreshBlockHash(block, Host::getHashCycle()) : block;
    }

    BlockV1* refreshBlockInfo(BlockV1* block, bool rehash) {
        BlockHeaderV1&  blockHeader = block->m_Header;

        // Just refreshing time and versions.
        blockHeader.m_Version       = Host::getHostVersion();
        blockHeader.m_TimeStamp     = Host::getHostTime();

        return rehash ? refreshBlockHash(block, Host::getHashCycle()) : block;
    }
}