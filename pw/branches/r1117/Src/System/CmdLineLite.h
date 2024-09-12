#ifndef SYSTEM_CMDLINELITE_H_INCLUDED
#define SYSTEM_CMDLINELITE_H_INCLUDED

#include "systemStdAfx.h"

class CmdLineLite
{
public:
  typedef list<string> TStringList;
  typedef list<TStringList> TMultiStringArgs;

  typedef list<int> TIntList;
  typedef list<TIntList> TMultiIntArgs;

  static CmdLineLite & Instance();

  CmdLineLite()    {}
  ~CmdLineLite()   {}

  void          Init( int nArgsCount, const char * const ppszArgs[] ); //console mode: just stores pointers inside
  void          Init( const char * pszCmdLn ); //Win32 mode, copies data
  void          InitFromWin32();

  int           ArgsCount() const { return m_arArgs.size(); }
  const char *  Argument( int uIndex );
  bool          IsKeyDefined( const char * pszKey ) const;
  const char *  GetStringKey( const char * pszKey, const char * pszDefault = NULL ) const;
  int           GetIntKey( const char * pszKey, int nDefault = 0 ) const;
  float         GetFloatKey( const char * pszKey, float fDefault = 0.0f ) const;
  int           GetStringKeys( vector<string> & result, const char * pszKey, const char * pszDefault = NULL ) const;
  int           GetIntKeys( vector<int> & result, const char * pszKey, int nDefault = 0 ) const;
  //Extended version, can pass multiple instances of same command with multiple arguments of varying number
  int           GetMultipleStringKeys( const char * key, TMultiStringArgs & result ) const;
  int           GetMultipleIntKeys( const char * key, TMultiIntArgs & result ) const;

private:
  vector<string> m_arArgs;

  bool          ItIsArg( int index ) const;
};

#endif // SYSTEM_CMDLINELITE_H_INCLUDED
