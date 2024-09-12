/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "../Server/src/TypeProxy.h"

#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LoggerStream.h"
#include "../System/SystemLog.h"
#include "../System/Basic.h"

#include "LobbyCommand.h"
#include "LobbyPacket.h"

LobbyPacket::LobbyPacket(int nBufferSize):
m_nBufferSize(nBufferSize)
, m_pBuffer(NULL)
, m_pWritePointer(NULL)
, m_pReadPointer(NULL)
, m_state(CS_NEED_HEADER)
, m_pCurCmdStart(NULL)
, m_nCurCmdSize(-1)
{
  m_pBuffer        = new char[m_nBufferSize * 2];
  m_pWritePointer  = m_pBuffer;
  m_pReadPointer   = m_pBuffer;
  m_pReceiveBuffer = new char[m_nResBufferSize];
}

int LobbyPacket::performRecieve(NiSocket &nSocket)
{
  int nDataRecieved;
  nDataRecieved = recv(nSocket, (char *)m_pReceiveBuffer, m_nResBufferSize, 0);
  if(nDataRecieved == SOCKET_ERROR)
  {
    return -1;
  }
  //simply disconnected
#ifdef NI_PLATF_WIN
  if(nDataRecieved == 0 || WSAGetLastError() == WSAECONNRESET)
#else
  if(nDataRecieved == 0 || ENOTCONN == errno)
#endif
  {
    return -1;
  }
  NI_VERIFY((m_pWritePointer + nDataRecieved) < (m_pBuffer + m_nBufferSize * 2), "Not enough buffer space.", return -1;)
  memcpy(m_pWritePointer, m_pReceiveBuffer, nDataRecieved);
  m_pWritePointer += nDataRecieved;
  return 0;
}

int LobbyPacket::getHeaderSize(bool bLongCommand, bool bFirstPacket)
{
  int nHeaderSize  = 8;
  if(bFirstPacket && bLongCommand)
    nHeaderSize += 4;
  if(bFirstPacket && !bLongCommand)
    nHeaderSize += 2;
  return nHeaderSize;
}
bool LobbyPacket::SendLobbyCommandPacket(NiSocket &nSocket, LobbyCommand const *pCmd, MemoryStream &sendStr, void *pVoidBuff, int nBuffSize)
{
  int nDataToSend;
  int nHeaderSize = 0;
  unsigned char *pBuff = (unsigned char *)pVoidBuff;

  bool bFirstPacket = sendStr.GetPosition() == 0;
  bool bLongComamnd = sendStr.GetSize() > 0xFFFF;
  unsigned int nCmdType = pCmd->getCommandID();
  nHeaderSize = getHeaderSize(bLongComamnd, bFirstPacket);

  //write to buffer: data
  nDataToSend = sendStr.Read(pBuff + nHeaderSize, nBuffSize - nHeaderSize);
  NI_ASSERT(nDataToSend > 0, "Attempt to send zero length command. Are you sure?");
  //form first byte
  NI_ASSERT(nCmdType < 0x2FFF, "Too many commands declared");
  unsigned char nFirstByte = (unsigned char)((nCmdType & 0xFF00) >> 8);
  if(bLongComamnd)
  {
    nFirstByte |= LONG_MASK;
  }
  if(bFirstPacket)
  {
    nFirstByte |= FIRST_MASK;
  }
  *pBuff = nFirstByte;
  pBuff++;
  *pBuff = (unsigned char)(nCmdType & 0xFF);
  pBuff++;
  if(bFirstPacket)
  {
    if(bLongComamnd)
    {
      *(unsigned int * )pBuff = sendStr.GetSize();
      pBuff += 4;
    }
    else
    {
      *(UINT16 * )pBuff       = sendStr.GetSize() & 0xFFFF;
      pBuff += 2;
    }
  }

  *(UINT16 * )pBuff = nDataToSend;
  pBuff += 2;

  *(unsigned int * )pBuff = pCmd->GetCommandNumber();
  pBuff += 4;

  int nDataActuallySend = 0;
  while(nDataActuallySend < (nDataToSend + nHeaderSize))
  {
    int nError = send(nSocket, (char *)pVoidBuff + nDataActuallySend, nDataToSend + nHeaderSize - nDataActuallySend, 0);
    if(SOCKET_ERROR == nError)
#ifndef NI_PLATF_LINUX
      if(WSAGetLastError() != WSAEINPROGRESS)
#endif
    {
      //we have problems: goto disconnect
      return false;
    }
    nDataActuallySend += nError;
  }
  return true;
}

bool LobbyPacket::ReceiveLobbyCommandPacket(NiSocket &nSocket, PacketInfo &pi)
{
  int nError;
  //wait for packet to arrive
  while(m_state != CS_PACKET_READY)
  {
    if(m_state == CS_NEED_HEADER)
    {
      nError = receiveStart(nSocket);
      if(nError == -1)
      {
        return false;
      }
    }
    if(m_state == CS_NEED_DATA)
    {
      nError = receiveCont(nSocket, pi);
      if(nError == -1)
      {
        return false;
      }
    }
  }
  if(m_state == CS_PACKET_READY)
  {
    receiveCleanup();
  }
  return true;
}

//we are clear and expect new packet
int LobbyPacket::receiveStart(NiSocket &nSocket)
{
  NI_ASSERT(m_state == CS_NEED_HEADER, "Invalid state to call this function.");

  int nDataSize = (m_pWritePointer - m_pReadPointer);
  //guard
  if(nDataSize <= 0)
  {
    return performRecieve(nSocket);
  }
  //
  UINT8  *pByte  = (UINT8 *)m_pReadPointer;

  //check high byte
  bool bLongCommand  = ((*pByte) & LONG_MASK ) != 0;
  bool bFirstPacket  = ((*pByte) & FIRST_MASK) != 0;

  int nExtectedSize  = getHeaderSize(bLongCommand, bFirstPacket);
  if(nDataSize < nExtectedSize)
  {
    return performRecieve(nSocket);
  }
  m_info.m_bFirstPacket = bFirstPacket;
  m_info.m_bLongCommand = bLongCommand;
  m_info.m_nCommandSize = -1;
  m_info.m_nCommandType = 0;
  m_info.m_nCommandType |= ((*(pByte + 0)) & 0x2F) << 8;
  m_info.m_nCommandType |=   *(pByte + 1);
  m_pReadPointer += 2;
  if(bFirstPacket)
  {
    if(bLongCommand)
    {
      m_info.m_nCommandSize = *(int *)m_pReadPointer;
      m_pReadPointer += 4;
    }
    else
    {
      m_info.m_nCommandSize = *(UINT16 *)m_pReadPointer;
      m_pReadPointer += 2;
    }
  }
  m_info.m_nPacketSize = *(UINT16 *)m_pReadPointer;
  m_pReadPointer += 2;

  m_info.m_nCommandNumber = *(int *)m_pReadPointer;
  m_pReadPointer += 4;

  m_state = CS_NEED_DATA;

  return 0;
}

int LobbyPacket::receiveCont(NiSocket &nSocket, PacketInfo &pi)
{
  int nRet = 0;
  NI_ASSERT(m_state == CS_NEED_DATA, "Invalid state to call this function.");
  int nDataSize = (m_pWritePointer - m_pReadPointer);

  if(m_info.m_nPacketSize <= nDataSize)
  {
    if(m_info.m_pDataStream == NULL)
    {
      m_info.m_pDataStream = new MemoryStream(m_info.m_nPacketSize);
    }
    else
    {
      m_info.m_pDataStream->Seek(0, SEEKORIGIN_BEGIN);
    }
    //we have this packet fully
    m_info.m_pDataStream->Write(m_pReadPointer, m_info.m_nPacketSize);
    m_pReadPointer += m_info.m_nPacketSize;
    m_state = CS_PACKET_READY;
    m_info.m_pDataStream->Seek(0, SEEKORIGIN_BEGIN);
    //give ownership to caller
    NI_ASSERT(pi.m_pDataStream == NULL, "Memory leak will appear otherwise.");
    pi = m_info;
    m_info.Reset();
  }
  else
  {
    nRet = performRecieve(nSocket);
  }
  //we do not have any packet ready yet.
  return nRet;
}

void LobbyPacket::receiveCleanup()
{
  NI_ASSERT(m_state == CS_PACKET_READY, "Invalid state to call this function.");
  int nShift = m_pReadPointer - m_pBuffer;
  //shift read and write pointers back
  NI_ASSERT(m_pWritePointer - m_pReadPointer >= 0, "Well this could not happen, but writeover is immanent.");
  memmove(m_pBuffer, m_pReadPointer, m_pWritePointer - m_pReadPointer);
  //shift pointers
  m_pReadPointer   -= nShift;
  m_pWritePointer  -= nShift;

  m_state = CS_NEED_HEADER;
}

LobbyPacket::~LobbyPacket()
{
  if(m_pBuffer)
    delete [] m_pBuffer;
  if(m_pReceiveBuffer)
    delete [] m_pReceiveBuffer;
}

