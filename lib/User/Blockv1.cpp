#include <User/Blockv1.h>
#include <User/Wallet.h>

#include <Support/Cryption.h>



namespace CoinBill
{
    BlockV1* CreateNewBlock(Wallet* user, BlockV1* prev) {
        bool            newDifficultyTriggered  = false;

        BlockV1*        block                   = new BlockV1();
        BlockHeaderV1&  blockHeader             = block->m_Header;
        
        // create blocks every 30 seconds, this mean we are going make diffcult harder every 2 month.
        if (prev->m_Header.m_Number % 2 * 60 * 30 * 2)
            newDifficultyTriggered = true;

        // Hash value of previus block.
        blockHeader.m_PrevHash      = prev->m_HeaderHash;

        // Difficulty will changed every 2 month.
        // lower value of difficulty is harder. 
        // we are going to make it lower when its triggered.
        blockHeader.m_Difficulty    = prev->m_Header.m_Difficulty - newDifficultyTriggered;
        blockHeader.m_Number        = prev->m_Header.m_Number + 1;

        // Auther of new block. it is Wallet that we are trying to make this block.
        blockHeader.m_Auther        = user->m_Owner;
        blockHeader.m_Version       = 0; // TODO : get current version.
        blockHeader.m_TimeStamp     = 0; // TODO : get current posix time.
        blockHeader.m_CoinLimit     = 0; // TODO : determine coin limit.
        blockHeader.m_CoinUsed      = 0;
        blockHeader.m_Nonce         = 0;

        if( !Cryption::hashBlockHeaderSHA512(
            block->m_HeaderHash,    // Hash value.
            block->m_Header         // Header to hash.
        )) return nullptr;

        return block;
    }
}