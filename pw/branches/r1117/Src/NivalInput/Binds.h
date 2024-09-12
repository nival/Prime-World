#ifndef BINDS_H_INCLUDED
#define BINDS_H_INCLUDED

#include "HwInputInterface.h"
#include "InputEvent.h"


namespace Input
{

_interface ICommandInstance;
_interface ICommandInstanceImplementation;

class Section;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef nstl::vector<nstl::string> TBindStrings;
typedef nstl::map<nstl::wstring, TBindStrings> TBinds;
typedef nstl::pair<nstl::wstring, TBindStrings> TBindsEntry;


class Binds : public CObjectBase
{
  OBJECT_BASIC_METHODS( Binds );

public:
  Binds();
  Binds( IHwInput * _hwInput );
  
  ~Binds();

  IHwInput * HwInput() const { return hwInput; }

  ICommandInstance * DefineCommand( const char * name, bool inverted, const vector<string> & controlNames, float factor = 0, bool factorIsUndefined = true, bool isRebind = false);
  void DeleteCommand( const char * name );
  void DeleteAllCommands();
  ICommandInstance * FindCommand( const char * name );

  void DefineCustomCommand( const char * name, ICommandInstanceImplementation * cmd );

  void Update( float deltaTime, bool appFocus );

  void ParseDefineCommand( const string & command, const vector<string> & keys, float factor = 0, bool factorIsUndefined = true, bool isRebind = false );

  void SetCurrentConfigSection( const char * name );
  void ActivateSection( const char * name );
  void DeactivateSection( const char * name );
  void DeactivateAllSections();

  void MuteNonDefaultSections( IBaseInterfaceST * owner );
  void UnmuteNonDefaultSections( IBaseInterfaceST * owner );

  nstl::vector<Event>& GetEvents();
  void ClearEvents();

  void RegisterBindString( const char * name, const vector<wstring> & _paramsSet );
  void ClearBindStrings();
  const TBinds& GetBindStrings();
  void ReplaceString(const wstring& context, const char * name, const vector<wstring> & _paramsSet, int index);

  void SetBindStringContext(const wstring& context);
  void RegisterBindString( const wstring& context, const char * name, const vector<wstring> & _paramsSet );

  bool IsBindStringAlreadyRegistered(const nstl::string& bndStr, const wstring& ctx);

private:
  typedef list<CObj<ICommandInstanceImplementation>>  TCommands;
  typedef map<string, CObj<Section>>  TSections;
  typedef set<Weak<IBaseInterfaceST>>  TMuteOwners;

  CObj<IHwInput>          hwInput;

  TCommands               commands;

  vector<Input::HwEvent>  hwEventsBuffer;

  TSections               sections;
  CObj<Section>           currentConfigSection;
  TMuteOwners             muteOwners;
  bool                    isNonDefaultSectionsMuted;
  vector<Event> eventz;

  TBinds                  bindStrings;

  TCommands::iterator FindCommandImpl( const char * name );
  TCommands::const_iterator FindCommandImpl( const char * name ) const;
  
  void AddSingleCommandSupersets( ICommandInstanceImplementation * cmd );
  void UpdateAllCommandsSupersets();

  void UpdateMutiness();

  wstring currentBindContext;
};

///////////////////////////////////////////////////////////////////////////////

class BindsManager
{
public:
  ~BindsManager() {};

  static BindsManager *Instance();

  void SetBinds(Binds * binds);
  const TBinds& GetBindStrings();
  Binds * GetBinds(void);

private:
  CPtr<Binds> s_binds;

};

///////////////////////////////////////////////////////////////////////////////

void SaveInputConfig( const string &szFileName, const Input::TBinds& bindStrings, const wstring& configContext );
void SaveInputConfig(const string &filePath, const wstring &ctx);

} //namespace Input

#endif //BINDS_H_INCLUDED
