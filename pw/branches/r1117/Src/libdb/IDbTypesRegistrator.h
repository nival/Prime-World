#ifndef IDBTYPESREGISTRATOR_H_6884EC73_7
#define IDBTYPESREGISTRATOR_H_6884EC73_7

namespace NDb
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class DbTypesRegistrator
  {
    typedef hash_map<string, DbResourceNewFunc> TNewFuncs;
    TNewFuncs newFuncs;
    bool isActive;


  public:

    DbTypesRegistrator()
    {
      isActive = true;
    }

    ~DbTypesRegistrator() 
    {
      isActive = false;
    };

    void RegisterResoruceType( const char *typeName, DbResourceNewFunc pDbResourceNewFunc )
    {
      if ( !isActive ) return;

      NI_VERIFY( newFuncs.find( typeName ) == newFuncs.end(), NI_STRFMT( "Resource type %s already registred", typeName ), return );

      newFuncs[typeName] = pDbResourceNewFunc;
    }

    DbResource *Create( const DBID &dbid, const char *typeName, const bool loaded )
    {
      if ( !isActive ) return 0;

      TNewFuncs::const_iterator pos = newFuncs.find( typeName );
#ifndef DB_TYPES_REGISTRATOR_SILENT
      NI_VERIFY( pos != newFuncs.end(), NI_STRFMT( "Resource type %s not registred", typeName ), return 0 );
#else
      if ( pos == newFuncs.end() )
        return 0;
#endif

      DbResourceNewFunc newFunc = pos->second;
      NI_VERIFY( pos != newFuncs.end(), NI_STRFMT( "Invalid new function for resource type %s", typeName ), return 0 );

      DbResource *pResult = newFunc( dbid );

      if ( pResult )
        pResult->loaded = loaded;

      return pResult;
    }
  };

	DbTypesRegistrator &GetDbTypesRegistrator();
}	// namespace NDb

#endif //#define IDBTYPESREGISTRATOR_H_6884EC73_7
