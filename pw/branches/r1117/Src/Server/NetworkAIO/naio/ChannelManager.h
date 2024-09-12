#pragma once
#include <IOTerabit/ChannelManager.h>
#include "naio/Types.h"
#include <map>

namespace naio
{
  class ChannelManager : public Terabit::ChannelManager
  {
  public:
    ChannelManager(const ACE_TCHAR * name,
                   Terabit::IOThreadPool &    task,
                   Terabit::AsynchChannelFactory &  channelFactory);
    ~ChannelManager();

  public:
    ChannelContextStrongPtr RegisterChannel(Terabit::AsynchChannel* chnl, ConnectionContextStrongPtr const & spconn);
    void UnregisterChannel(int chnlid);

    void readBlockSize(unsigned int rbsz);
    unsigned int readBlockSize() const;

    void soRcvbuf(int rb);
    int soRcvbuf() const;

    void disableNagleAlgorithm(int flag);
    int disableNagleAlgorithm() const;

    void soSndbuf(int sb);
    int soSndbuf() const;

    void soKeepalive(int _keepalive);
    int soKeepalive() const;

    void logWrittenBytes(unsigned int wb);
    unsigned int logWrittenBytes();

    void connectionsActivityTimeout(unsigned int sec);

  private:
    typedef std::map<int, ChannelContextStrongPtr> ChannelsMapT;
    ACE_Thread_Mutex channelsMutex_;
    ChannelsMapT channels_;
    unsigned int read_block_size_;
    int so_rcvbuf_;  //  SO_RCVBUF
    int disableNagleAlgorithm_;
    int so_sndbuf_;  //  SO_SNDBUF
    int so_keepalive_;  //  SO_KEEPALIVE
    unsigned int logWrittenBytes_;
  };

  inline
  void ChannelManager::readBlockSize(unsigned int rbsz)
  {
    read_block_size_ = rbsz;
  }

  inline
  unsigned int ChannelManager::readBlockSize() const
  {
    return read_block_size_;
  }

  inline
  void ChannelManager::soRcvbuf(int rb)
  {
    so_rcvbuf_ = rb;
  }

  inline
  int ChannelManager::soRcvbuf() const
  {
    return so_rcvbuf_;
  }

  inline
  void ChannelManager::disableNagleAlgorithm(int flag)
  {
    disableNagleAlgorithm_ = flag;
  }

  inline
  int ChannelManager::disableNagleAlgorithm() const
  {
    return disableNagleAlgorithm_;
  }

  inline
  void ChannelManager::soSndbuf(int sb)
  {
    so_sndbuf_ = sb;
  }

  inline
  int ChannelManager::soSndbuf() const
  {
    return so_sndbuf_;
  }

  inline
  void ChannelManager::connectionsActivityTimeout(unsigned int sec)
  {
    this->set_timeout(ACE_Time_Value(sec, 0));
  }

  inline
  void ChannelManager::logWrittenBytes(unsigned int wb)
  {
    logWrittenBytes_ = wb;
  }

  inline
  unsigned int ChannelManager::logWrittenBytes()
  {
    return logWrittenBytes_;
  }

  inline
  void ChannelManager::soKeepalive(int _keepalive)
  {
    so_keepalive_ = _keepalive;
  }

  inline
  int ChannelManager::soKeepalive() const
  {
    return so_keepalive_;
  }
}
