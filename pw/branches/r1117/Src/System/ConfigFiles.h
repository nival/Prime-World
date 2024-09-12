#ifndef CONFIGFILES_H_C778C002_9F81_4EBF
#define CONFIGFILES_H_C778C002_9F81_4EBF

namespace NGlobal
{

///////////////////////////////////////////////////////////////////////////////

  //const wstring DEFAULT_COMMAND_CONTEXT = L"global";
  class CmdListManager;

///////////////////////////////////////////////////////////////////////////////

  //storage defined from profile
  vector<wstring> LoadConfig( const string &szFileName, const NProfile::EProfileFolder folder );

  // folder defined from storage
  void SaveConfig( const string &szFileName, const EStorageClass storage , const wstring& configContext = DEFAULT_COMMAND_CONTEXT);

  //storage defined from profile
  bool ExecuteConfig( const string &szFileName, const NProfile::EProfileFolder folder, const wstring& configContext = DEFAULT_COMMAND_CONTEXT );

  wstring ContextNameFromFileName( const string &szFileName );

///////////////////////////////////////////////////////////////////////////////

  template <typename TCmdContextDataType = nstl::string>
  class CmdContext
  {
  public:
    CmdContext(const TCmdContextDataType& ctxName) : contextName(ctxName) {}

    const TCmdContextDataType& GetName(){ return contextName; }
  protected:
    TCmdContextDataType contextName;
  };

///////////////////////////////////////////////////////////////////////////////

  class CmdList
  {
    friend class CmdListManager;

    // made private so that command lists are created only via CmdListManager
    CmdList( const string &configFileName, const NProfile::EProfileFolder folder, const wstring &ctx = DEFAULT_COMMAND_CONTEXT )
      : curCommand(0), context(ctx)
    {
      commands = LoadConfig( configFileName, folder );
    }

  public:

    int  GetNumCommands() const { return commands.size(); }
    bool Finished() const { return (curCommand == commands.size()); }
    void Execute();

  protected:
    vector<wstring>     commands;
    int                  curCommand;
    CmdContext<wstring> context;
  };

///////////////////////////////////////////////////////////////////////////////

  class CmdListManager
  {
  public:
    ~CmdListManager();

    static CmdListManager *Instance();

    bool CreateAndExecute( const string &configFileName, const NProfile::EProfileFolder folder, const wstring& ctx );
    void Step();

  protected:
    void ExecuteList(list<CmdList*>::iterator &it);

    list<CmdList*>  cmdLists;
  };

}
#endif //#define CONFIGFILES_H_C778C002_9F81_4EBF
