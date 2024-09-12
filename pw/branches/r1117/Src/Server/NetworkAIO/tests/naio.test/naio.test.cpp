#pragma warning(push)
#pragma warning(disable:4996)
#include "stdafx.h"
#include "naio/Driver.h"
#include "naio/Cfg.h"
#include "naio/ConnectionContext.h"
#include "NLProtocolHandlerFactory.h"
#include <string>
#include <conio.h>
#pragma warning(pop)


//////////////////////////////////////////////////////////////////////////
//
//  main
//
int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  argc;
  argv;

  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "NLServer", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerTextFileDumper> textLogDumper;
  Reset( textLogDumper, new NLogg::CServerTextFileDumper( &GetSystemLog() ) );
  NBSU::InitUnhandledExceptionHandler();
  textLogDumper->SetFileName("output");

  GetSystemLog().AddChannel("naoi.test");

  naio::DriverSP spdrv(new naio::Driver);
  NetworkLayer::ProtocolHandlerFactory phf;
  naio::Cfg naiocfg;
  //naiocfg.loglvl_ = 1;
  naiocfg.phf_ = &phf;

  if (!spdrv->Init(naiocfg))
    return 1;

  int i = 1;
  while (i--)
  {
    naio::ConnectionContextStrongPtr spcc = spdrv->OpenConnection(ACE_INET_Addr("localhost:35001"), 0);
    if (!spcc.null())
      ::Sleep(10);
  }

  printf("Press 'Q' to quit\n");
  int ch = 0;
  while ((ch = _getch()) != 'Q');

  spdrv->Fini();

  return 0;
}

////////////////////////////////////////////////////////////////////////////
////  Connection
////
//class NetConnection
//{
//  friend class NetDriver;
//  friend class ProtocolHandler;
//
//public:
//  enum StatusT
//  {
//    INVALID = -2,
//    CLOSED = -1,
//    CONNECTED = 0,
//    CONNECTING = 1,
//  };
//
//public:
//  NetConnection()
//    :sts_(INVALID)
//  {}
//  NetConnection(naio::ConnectionContextStrongPtr const & spctx)
//    :spconn_(spctx),
//    sts_(INVALID)
//  {}
//  ~NetConnection()
//  {}
//
//public:
//  virtual int send(char const * data, unsigned int size);
//  virtual int recv(char*& data, unsigned int& size);
//  virtual void close();
//
//  StatusT status() const
//  {
//    return sts_;
//  }
//
//private:
//  void status(StatusT sts)
//  {
//    sts_ = sts;
//  }
//
//private:
//  naio::ConnectionContextStrongPtr spconn_;
//  StatusT sts_;
//};
//
//int NetConnection::send(char const * data, unsigned int size)
//{
//  std::auto_ptr<naio::SendData> sdop(new naio::SendData(size, data, false, spconn_));
//  int rc = sdop->Post();
//  if (0 == rc)
//    sdop.release();
//  else
//    printf("sdop->Post() failed");
//
//  return rc;
//}
//
//int NetConnection::recv(char*& /*data*/, unsigned int& /*size*/)
//{
//
//  return 0;
//}
//
//void NetConnection::close()
//{
//
//}
//
////////////////////////////////////////////////////////////////////////////
////
////  ProtocolHandler
////
//class ProtocolHandler : public naio::IProtocolHandler
//{
//  static const unsigned short  HEADER_SIZE = sizeof(unsigned short);
//  static const unsigned short  MAX_PACKET_SIZE = 0xFFFF;
//  static const unsigned short  MAX_DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;
//
//  NetConnection* connection(naio::ConnectionContextStrongPtr const & spconn) const
//  {
//    return reinterpret_cast<NetConnection*>(spconn->userContext());
//  }
//
//public:
//  virtual naio::StatusT OnOpenConnection(bool success, bool isactive, naio::ConnectionContextStrongPtr const & spconn)
//  {
//    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T %s(l=%d)\n"), __FUNCTION__));
//
//    NetConnection* pconn = connection(spconn);
//    if (success)
//      pconn->status(NetConnection::CONNECTED);
//    else
//      pconn->status(NetConnection::CLOSED);
//
//    return naio::status::SUCCESS;
//  }
//
//  naio::StatusT HandleInput(size_t length, const char *data, size_t& readBytes, naio::ConnectionContextStrongPtr const & /*spconn*/, 
//    Terabit::MessageBlockFactory& /*outmbf*/, ACE_Message_Block*& /*poutmb*/)
//  {
//    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T %s(l=%d)\n"), __FUNCTION__, length));
//
//    if (length < HEADER_SIZE)
//      return naio::status::SUCCESS;
//
//    unsigned short packet_size = *((unsigned short*)data);
//    if (length - HEADER_SIZE < packet_size)
//      return naio::status::SUCCESS;
//
//    size_t consumed_bytes = 0;
//    size_t remain_bytes = length - HEADER_SIZE;
//    char const * pdata = data + HEADER_SIZE;
//
//    do
//    {
//      consumed_bytes += HEADER_SIZE;
//
//      //////////////////////////////////////////////////////////////////////////
//      //  TODO: add real handling here
//      //////////////////////////////////////////////////////////////////////////
//      ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t)%T %s Handling (packet size=%d)\n"), 
//        __FUNCTION__, packet_size));
//
//      int rc = packet_size;
//
//      consumed_bytes += rc;
//      remain_bytes -= rc;
//      pdata += rc;
//
//      if (remain_bytes >= HEADER_SIZE)
//      {
//        packet_size = *((unsigned short*)pdata);
//        pdata += HEADER_SIZE;
//        remain_bytes -= HEADER_SIZE;
//      }
//      else
//        packet_size = MAX_PACKET_SIZE;
//    }
//    while(packet_size <= remain_bytes);
//
//    readBytes = consumed_bytes;
//    return naio::status::SUCCESS;
//  }
//
//  virtual naio::StatusT HandleOutput(ACE_Message_Block* pmb, naio::ConnectionContextStrongPtr const & spconn, 
//    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
//  {
//    return naio::status::INVALID;
//  }
//
//  virtual naio::StatusT HandleOutput(size_t length, const char *data, bool /*preallocated*/, naio::ConnectionContextStrongPtr const & /*spconn*/, 
//    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
//  {
//    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T %s(l=%d)\n"), __FUNCTION__, length));
//
//    if (length > MAX_DATA_SIZE)
//      return naio::status::FAIL;
//
//    ACE_Message_Block* pout = outmbf.alloc_msg(HEADER_SIZE + length);
//    if (!pout)
//      return naio::status::FAIL;
//
//    //unsigned short bodylen = unsigned short(length);
//    pout->copy((char*)&length, sizeof(HEADER_SIZE));
//    pout->copy(data, length);
//    poutmb = pout;
//
//    return naio::status::SUCCESS;
//  }
//
//  virtual naio::StatusT OnUserOperation(naio::Operation* /*op*/, naio::ConnectionContextStrongPtr const & /*spconn*/,
//    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
//  {
//    return naio::status::SUCCESS;
//  }
//
//  virtual void UserOperationPostHandler(naio::StatusT const & sts, naio::Operation* op, 
//    naio::ConnectionContextStrongPtr const & spconn)
//  {
//  }
//
//  virtual void OnCloseConnection(naio::ConnectionContextStrongPtr const & spconn)
//  {
//    NetConnection* pconn = connection(spconn);
//    pconn->status(NetConnection::CLOSED);
//  }
//};
//
//class HandlerFactory : public naio::IProtocolHandlerFactory
//{
//public:
//  virtual naio::IProtocolHandler* CreateProtocolHandler(void const * /*userdata*/)
//  {
//    return new ProtocolHandler;
//  }
//
//  virtual void DestroyProtocolHandler(naio::IProtocolHandler* ph)
//  {
//    delete ph;
//  }
//};
//
//
////////////////////////////////////////////////////////////////////////////
////
////  driver
////
//class NetDriver : public naio::Driver
//{
//public:
//  NetDriver()
//  {
//  }
//
//public:
//  NetConnection* Connect(std::string const & addr);
//
//private:
//  HandlerFactory handlerFactory_;
//
//};
//
//NetConnection* NetDriver::Connect(std::string const & addr)
//{
//  NetConnection* nc(new NetConnection);
//  naio::ConnectionContextStrongPtr spconn = this->OpenConnection(ACE_INET_Addr(addr.c_str()), (void*)nc);
//  if (spconn.null())
//  {
//    delete nc;
//    return 0;
//  }
//
//  nc->spconn_ = spconn;
//  nc->status(NetConnection::CONNECTING);
//  return nc;
//}
//
////////////////////////////////////////////////////////////////////////////
////
////  main
////
//int
//ACE_TMAIN (int argc, ACE_TCHAR *argv[])
//{
//  argc;
//  argv;
//
//  NetDriver drv;
//  HandlerFactory phf;
//  naio::Cfg naiocfg;
//  //naiocfg.loglvl_ = 1;
//  naiocfg.phf_ = &phf;
//
//  if (!drv.Init(naiocfg))
//    return 1;
//
//  NetConnection* conn = drv.Connect("localhost:35001");
//  while (NetConnection::CONNECTING == conn->status())
//    ::Sleep(10);
//
//  if (NetConnection::CONNECTED != conn->status())
//    return 1;
//
//  int i = 5000;
//  char data[16] = "DATA";
//  while(i!=0 && conn->send(&data[0], strlen(data)) == 0)
//  {
//    ::Sleep(10);
//    //--i;
//  }
//
//  ::Sleep(1000);
//
//  printf("Press 'Q' to quit\n");
//  int ch = 0;
//  while ((ch = _getch()) != 'Q');
//
//  strcpy_s(&data[0], sizeof(data)-1, "CLOSE");
//  if (conn->send(&data[0], strlen(data)) < 0)
//    return 1;
//
//  while (NetConnection::CLOSED != conn->status())
//    ::Sleep(10);
//
//  drv.Fini();
//
//  return 0;
//}
