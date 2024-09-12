#include "transport/stdafx.h"
#include "transport/TLConnectionOutputOp.h"
#include "transport/TLConnection.h"
#include <naio/OpScope.h>
#include "transport/TLGlobalCfg.h"
#include "transport/TLInPlaceMessageBlockFactory.h"
#include "transport/TLChannel.h"

namespace TransportLayer
{
  namespace op
  {
    ////////////////////////////////////////////////////////////////////////////
    //  ConnectionOutput
    ConnectionOutput::ConnectionOutput(TL::ConnectionSP const & spconn, 
      TL::MessageBlockFactorySP const & mbf, ChannelOpPtr const & op)
      :naio::Operation(op::CONNECTION_OUTPUT, spconn->connectionContext()),
      spconn_(spconn),
      mbf_(mbf),
      op_(op)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
    }

    ConnectionOutput::~ConnectionOutput()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      CloseOps();
    }

    naio::StatusT 
    ConnectionOutput::execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      typedef naio::OpScope<ChannelOp> OpScopeT;

      const unsigned int block_limit = GlobalCfg::GetMaxWriteBlockSize();
      ChannelOpPtr gop = op_;
      ACE_Message_Block* pmb = 0;
      naio::StatusT st = naio::status::FAIL;
      unsigned int chunk_count = 0;

      while (gop)
      {
        NI_PROFILE_BLOCK("while");

        unsigned int chainsize = 0;
        OpScopeT currentChain;

        //  определяем операции(цепочку), которые исполним в текущем цикле
        {
          NI_PROFILE_BLOCK("select chain");

          ChannelOpPtr tmpop = gop;
          ChannelOpPtr prevtmpop = 0;
          while(tmpop)
          {
            NI_PROFILE_BLOCK("while(op)");
            unsigned int opsz = tmpop->getFinalOutputDataSize(dh);
            if (opsz > block_limit)
            {
              NI_ASSERT(opsz <= block_limit, "Operation size is greater than available block size!");
              st = naio::status::NO_MEMORY;
              return st;
            }

            if (chainsize + opsz <= block_limit)
            {
              chainsize += opsz;
              prevtmpop = tmpop;
              tmpop = tmpop->next();
            }
            else
            {
              break;
            }
          }

          currentChain.scope(gop, prevtmpop);
        }

        //  начало следующей цепочки операций
        gop = currentChain.last()->next();

        //  аллоцируем память под цепочку операций
        ACE_Message_Block* chunk = 0;
        {
          NI_PROFILE_BLOCK("outmbf.alloc_msg");
          chunk = outmbf.alloc_msg(chainsize);
        }
        if (!chunk)
          return naio::status::NO_MEMORY;

        //  используем in-place аллокатор для сериализации операций
        InPlaceMessageBlockFactory localmbf;
        localmbf.set_place(chunk->wr_ptr(), chunk->size());

        //  обходим и исполняем операции
        unsigned int op_count = 0;
        st = naio::status::FAIL;
        op::ChannelOpPtr tmpop = currentChain.first();
        do
        {
          NI_PROFILE_BLOCK("while op->execute()");

          ACE_Message_Block* loutmb = 0;
          st = tmpop->execute(dh, localmbf, loutmb);
          if (loutmb)
            localmbf.free_msg(loutmb);
          else
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. No output for op(op=%d seqnum=%d op_count=%d allocated=%d ch=%d)"), 
            __FUNCTION__, tmpop->type(), tmpop->seqNum(), op_count, localmbf.bytes_allocated(), spconn_->id()));

          if (naio::status::SUCCESS == st)
            ++op_count;
        }
        while (naio::status::SUCCESS == st && !(gop == (tmpop = tmpop->next())));

        if (naio::status::SUCCESS == st)
        {
          NI_ASSERT(chainsize == localmbf.bytes_allocated(), 
            NI_STRFMT("Calculated and allocated size must be equal(calc=%d alloc=%d)", chainsize, localmbf.bytes_allocated()));
        }
        //  выставляем смещение в используемом блоке памяти
        chunk->wr_ptr(localmbf.bytes_allocated());

        //  кладем результат в output цепочку message block'ов
        ++chunk_count;
        if (!pmb)
        {
          pmb = chunk;
          poutmb = pmb;
        }
        else
        {
          ACE_ERROR((LM_INFO, ACE_TEXT("%s. Use more than one block(chunk_count=%d op_count=%d allocated=%d ch=%d)"), 
            __FUNCTION__, chunk_count, op_count, localmbf.bytes_allocated(), spconn_->id()));
          pmb->cont(chunk);
          pmb = pmb->cont();
        }
      }

      return st;
    }

    naio::StatusT 
    ConnectionOutput::complete()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      spconn_->completeActiveOp(this);
      CloseOps();
      return naio::status::SUCCESS;
    }

    void ConnectionOutput::CloseOps()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      op_ = 0;
    }
  }
}
