#ifndef SYSTEM_REGISTRYSTORAGE_H_INCLUDED
#define SYSTEM_REGISTRYSTORAGE_H_INCLUDED

namespace registry {

class Storage : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Storage, BaseObjectST );

public:
  Storage();
  Storage( const char * productName, bool currentUser = true, const char * companyName = 0 );
  ~Storage();

  bool StoreDword( const char * valueName, DWORD value );
  bool ReadDwordEx( const char * valueName, DWORD & value, bool doAsserts );

  DWORD ReadDword( const char * valueName, DWORD defaultValue )
  {
    DWORD value = 0;
    if ( !ReadDwordEx( valueName, value, false ) )
      return defaultValue;
    return value;
  }

  bool StoreString( const char * valueName, const char * value );
  bool ReadStringEx( const char * valueName, string & value, bool doAsserts );

  void ReadString( const char * valueName, string & value, const char * defaultValue )
  {
    if ( !ReadStringEx( valueName, value, false ) )
      value = defaultValue;
  }

  bool StoreBinary( const char * valueName, const vector<ni_detail::Byte> & data );
  bool ReadBinaryEx( const char * valueName, vector<ni_detail::Byte> & buffer, bool doAsserts );

  bool OpenSubKey( const char*, PHKEY, bool, bool );
  void CloseKey( PHKEY );

  //FIXME: Enums <-> string search service, move to separate class/file
  template<typename T>
  static void RegisterEnumValue( T value, const char * name )
  {
    AccessEnumMaps<T>().enum2Name[(int)value] = name;
    AccessEnumMaps<T>().name2Enum[name] = (int)value;
  }

  template<typename T>
  static const char * FindEnumName( T value, const char * defaultName = 0 )
  {
    TEnum2Name::iterator it = AccessEnumMaps<T>().enum2Name.find( value );
    if ( it == AccessEnumMaps<T>().enum2Name.end() )
      return defaultName;
    return it->second.c_str();
  }

  template<typename T>
  static T FindEnumValue( const char * name, T defaultValue = (T)0 )
  {
    TName2Enum::iterator it = AccessEnumMaps<T>().name2Enum.find( name );
    if ( it == AccessEnumMaps<T>().name2Enum.end() )
      return defaultValue;
    return (T)it->second;
  }

  template<typename T>
  bool StoreEnum( const char * valueName, T value )
  {
    const char * name = FindEnumName<T>( value, "<unknown>" );
    return StoreString( valueName, name );
  }

  template<typename T>
  T ReadEnum( const char * valueName, T defaultValue )
  {
    string value;
    if ( !ReadStringEx( valueName, value, false ) )
      return defaultValue;
    if ( value == "<unknown>" )
      return defaultValue;
    return FindEnumValue<T>( value.c_str(), defaultValue );
  }

private:
  HKEY  hMain;

  typedef map<int, string> TEnum2Name;
  typedef map<string, int> TName2Enum;
  struct SEnumMaps
  {
    TEnum2Name  enum2Name;
    TName2Enum  name2Enum;
  };

  template<typename T>
  static SEnumMaps & AccessEnumMaps()
  {
    static SEnumMaps maps;
    return maps;
  }
};

} //namespace registry

#define NI_REGISTER_ENUM_VALUE( value )  RegisterEnumValue( value, #value );

#endif //SYSTEM_REGISTRYSTORAGE_H_INCLUDED
