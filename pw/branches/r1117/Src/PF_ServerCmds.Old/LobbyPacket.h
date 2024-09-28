/*
 * LobbyPacket.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef LOBBYPACKET_H_
#define LOBBYPACKET_H_

#include "../Server/src/TypeProxy.h"
#include "../System/Stream.h"
#include "../System/MemoryStream.h"
#include "LobbyCommand.h"

//this class serves as TCP stream defragmenter
class LobbyPacket
{
public:
  LobbyPacket(int nBufferSize = 10 * 1024);
  ~LobbyPacket();

  enum State
  {
    CS_NEED_HEADER,
    CS_NEED_DATA,
    CS_PACKET_READY
  };
  struct PacketInfo
  {
    int    m_nCommandType;
    int    m_nCommandSize;
    int    m_nPacketSize;
    int    m_nCommandNumber;
    bool   m_bLongCommand;
    bool   m_bFirstPacket;
    MemoryStream *m_pDataStream;
    PacketInfo()
    {Reset();}
    ~PacketInfo()
    {
      if(m_pDataStream) delete m_pDataStream;
    }
    void Reset()
    {
      m_nCommandType   = -1;
      m_nCommandSize   = -1;
      m_nPacketSize    = -1;
      m_nCommandNumber = -1;
      m_bLongCommand   = false;
      m_bFirstPacket   = false ;
      m_pDataStream    = NULL;
    }
  };

  bool ReceiveLobbyCommandPacket(NiSocket &nSocket, PacketInfo &pi);
  static bool SendLobbyCommandPacket(NiSocket &nSocket, LobbyCommand const *pCmd, MemoryStream &sendStr, void *pBuff, int nBuffSize);

protected:
private:
  static const unsigned char LONG_MASK     = 0x80;
  static const unsigned char FIRST_MASK    = 0x40;

  static int getHeaderSize(bool bLongCommand, bool bFirstPacket);
  int  receiveStart(NiSocket &nSocket);
  int  receiveCont(NiSocket &nSocket, PacketInfo &pi);
  void receiveCleanup();
  int  performRecieve(NiSocket &nSocket);

  int    m_nBufferSize;
  char * m_pBuffer;
  char * m_pWritePointer;
  char * m_pReadPointer;
  static const int    m_nResBufferSize = 1000;
  char * m_pReceiveBuffer;
  
  State  m_state;
  bool   m_bHeaderReady;

  char * m_pCurCmdStart;
  int    m_nCurCmdSize;
  
  //command stats
  PacketInfo m_info;
};


#endif /* LOBBYPACKET_H_ */
