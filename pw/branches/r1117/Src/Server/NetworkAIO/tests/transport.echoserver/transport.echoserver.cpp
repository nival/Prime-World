#include "stdafx.h"
#include "transport.echoserver.h"

int g_tes_loglevel = 1;

REGISTER_VAR("tes_loglevel", g_tes_loglevel, STORAGE_GLOBAL);

namespace Transport
{
  struct ChannelContext
  {
    ChannelContext(StrongMT<Transport::IChannel> chnl)
      :lastRecvSeqNum_(0),
      chnl_(chnl)
    {
    }

    unsigned long lastRecvSeqNum_;
    StrongMT<Transport::IChannel> chnl_;
  };

  EchoServer::EchoServer()
  {
    GetSystemLog().AddChannel("echo");
  }

  int EchoServer::Process(volatile bool& isRunning)
  {
    typedef vector<ChannelContext> ChannelsT;
    ChannelsT channels;
    channels.reserve( 1000 );
    messagesSent = 0;

    StrongMT<Transport::IChannelListener> chlistener = ts->CreateChannelListenerDirect( "", listenAddr );
    LOG_D(0) << "created EchoServer listener=" << chlistener.Get() << ", ip=" << listenAddr;

    while( isRunning )
    {
      messagesReceived = 0;

      vector<StrongMT<Transport::IChannel>> newChannels;
      chlistener->GetNewConnections( &newChannels );

      for ( Transport::TChannels::iterator it = newChannels.begin(); it != newChannels.end(); ++it )
      {
        StrongMT<Transport::IChannel> chnl = *it;
        channels.push_back( ChannelContext(chnl) );
        chnl->GetAddress();
        LOG_M("echo").Trace("New channel(t=%s s=%s c=%d) ",
          chnl->GetAddress().target.c_str(), 
          chnl->GetAddress().source.c_str(), 
          chnl->GetAddress().client);
      }

      ChannelsT::iterator it = channels.begin();
      while(it != channels.end())
      {
        ChannelContext* cc = it;
        StrongMT<Transport::IChannel> chnl(it->chnl_);

        vector<byte> data;
        while(chnl->ReceiveRaw(&data))
        {
          unsigned long seqnum = *((unsigned long*)(&data[0]));

          NI_ASSERT(seqnum > cc->lastRecvSeqNum_, NI_STRFMT("WRONG RECV SEQUENCE(c=%d seqnum=%d lastseqnum=%d)", 
            chnl->GetAddress().client, seqnum, cc->lastRecvSeqNum_));
          if (seqnum > cc->lastRecvSeqNum_)
          {
            //if (g_tes_loglevel <= NLogg::LEVEL_MESSAGE)
            //  LOG_M("echo").Trace("recv(time=%f c=%d rseq=%d lastrseq=%d)",
            //    NHPTimer::GetScalarTime(), chnl->GetAddress().client, seqnum, cc->lastRecvSeqNum_);

            chnl->SendRaw(data.begin(), data.size());
          }
          //else
          //{
          //  systemLog(NLogg::LEVEL_WARNING) << 
          //    "transport: WRONG SEQUENCE (time = "<< NHPTimer::GetScalarTime() << 
          //    " chnl: t=" << chnl->GetAddress().target <<
          //    " s=" << chnl->GetAddress().source << 
          //    " c=" << chnl->GetAddress().client << 
          //    " seq " << seqnum << 
          //    ")" << endl;
          //}

          messagesReceived++;

          cc->lastRecvSeqNum_ = seqnum;
        }

        if (chnl->GetStatus() != Network::ConnectionState::Connected)
          it = channels.erase(it);
        else
          ++it;
      }

      if ( messagesReceived )
        LOG_M("echo").Trace("recv(time=%.3f chans=%d msg_recvd=%d)", NHPTimer::GetScalarTime(), channels.size(), messagesReceived);

      Sleep( delay );
    }

    return 0;
  }
}
