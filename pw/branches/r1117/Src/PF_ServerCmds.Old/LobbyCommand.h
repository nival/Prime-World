/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef LOBBYCOMMAND_H_
#define LOBBYCOMMAND_H_

#include "../Server/src/TypeProxy.h"
#include "../Server/src/ServerThread.h"
#include "CommandFactory.h"
#include "../System/Stream.h"
#include "../System/MemoryStream.h"
#include "SQLStream.h"

class LobbyCommand: public CommandFactory
{
  OBJECT_BASIC_METHODS(LobbyCommand);
public:
  enum Status
  {
    CS_NA = -1,
    CS_SEND_WAIT = 0,
    CS_SENDING,
    CS_INPROGRESS,
    CS_RECEIVING,
    CS_RECEIVED,
    CS_LAST
  };

  enum Priority
  {
    CP_LOW,
    CP_MEDIUM,
    CP_HIGH,
    CP_LAST
  };

  //borrowed from SDK directly since it the only information we do need from SDK in our class
  static const int INVALID_ID_NUMBER      = 0;
  static const int INVALID_COMMAND_NUMBER = -1;

protected:

  MemoryStream m_requestCmd;
  MemoryStream m_replyCmd;
  SQLStream    m_SQLReply; // the one we get from SQL server

  int     m_nRequestSize; //used for priority queue
  int     m_nReplySize; //used for priority queue

  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
  //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
  virtual void serialize(void) {return;}
  //convert command from serialized form to normal one
  virtual void deserialize(class ClientThread const *) {return;}

  //pack reply data
  virtual void serializeReply(void);
  //convert reply currently arrived from field by field form to command structure
  virtual void deserializeReply(void);

  // convert from normal form to SQL command! Should be called on server environment only
  virtual nstl::wstring serializeSQL(void) {return nstl::wstring(L"SET NAMES 'UTF8';");}

  // build class from SQL server response: stored in replyCmd buffer
  virtual void     deserializeSQL(SQLStream &) {return;}

  // priority for current command: is it high or not
  virtual Priority getPriority(void) const {return CP_LOW;}

  virtual bool     isPartialDecodeSupported(void) {return false;}

  //services functions
  static nstl::wstring  Utf8ToUnc16(char const * cp);
  static nstl::string   Unc16ToUtf8(wchar_t const * cp);
  static void           WriteStringToStream (Stream &str, nstl::wstring const &s);
  static nstl::wstring  ReadStringFromStream(Stream &str);
  static void           ReadStringFromStream(Stream &str, nstl::wstring       &s) {s = ReadStringFromStream(str);}
  static wchar_t const* BoolToStr(bool b)   {return (b)?L"TRUE":L"FALSE";}

public:
   //is command result ready to be used
  bool isReady() {return m_bRecievedFromServer && m_replyCmd.GetSize() == getTotalReplySize();}

  //get size
  int replySize()           const {return m_replyCmd.GetSize();}
  int getTotalReplySize()   const {return m_nReplySize;}
  int getTotalRequestSize() const {return m_nRequestSize;}

  //obtain current status of the command
  Status getStatus()         {return m_nStatus;}

  //get command priority
  Priority GetPriority(void) const {return getPriority();}

  LobbyCommand();
  virtual ~LobbyCommand() {}

  //internal interfaces for LobbyCLient and server only: no i do not want specific ILobbyCommand class
  MemoryStream &GetRequestStream()  {return m_requestCmd;}
  MemoryStream &GetReplyStream()    {return m_replyCmd;}
  SQLStream    &GetSQLStream()      {return m_SQLReply;}
  void          DeserializeReply();
  bool          IsPartialDecodeSupported()  {return isPartialDecodeSupported();}
  int           GetCommandNumber() const {return m_nCommandNumber;}
  void          SetCommandNumber(int nNumber)
  {
    m_nCommandNumber = nNumber;
  }
  void          SetReplySize(int size)         {m_nReplySize = size;}
  void          SetRequestSize(int size)       {m_nRequestSize = size;}
  void          SetReceivedFromServer()        {m_bRecievedFromServer = true;}
  void          SetReceivedFromClient()        {m_bRecievedFromClient = true;}
  void          SetExecutionSuccess()          {m_bExecutionSuccess   = true;}
  void          SetReply()                     {m_bReply              = true;}
  void          SetStatus(Status s)            {m_nStatus = s;}
  void          PrepareForSending()            ;

protected:
  void          initCommonFields();
private:
  int           requestSize() { return m_requestCmd.GetSize();}

  bool    m_bRecievedFromClient;
  bool    m_bRecievedFromServer;
  bool    m_bReply;
  bool    m_bExecutionSuccess; // Error flag: 1 if command was executed successfully
  int     m_nCommandNumber;
  Status  m_nStatus;

  REG_COMMAND_H(LobbyCommand, CommandFactory);

  friend inline Stream& Stream::operator>><nstl::wstring> ( nstl::wstring &res );
  friend inline Stream& Stream::operator<<<nstl::wstring> ( const nstl::wstring &res );
  friend class SQLStream;
};

typedef CObj<LobbyCommand>           CommandHolder;

template<> inline Stream& Stream::operator>> <nstl::wstring>( nstl::wstring &res ) { res = LobbyCommand::ReadStringFromStream(*this); return *this; }
template<> inline Stream& Stream::operator<< <nstl::wstring>( const nstl::wstring &res ) { LobbyCommand::WriteStringToStream(*this, res); return *this; }


#endif /* LOBBYCOMMAND_H_ */
