#ifndef RESOURCESCOLLECTION_H_400363F7_5
#define RESOURCESCOLLECTION_H_400363F7_5

namespace NDb
{
  struct AdvMap;
  struct AdvMapDescription;
  struct AdvMapSettings;
}

namespace NWorld
{
template <typename T>
class ResourcesCollection
{
public:
  int size() const { return resources.size(); }
  int GetSize() const { return size(); }
  NDb::Ptr<T>& operator[] (int index) { return resources[index]; }
  const NDb::Ptr<T>& operator[] (int index) const { return resources[index]; }
  int Scan(const char* folder, const char* mask, bool recursive=true)
  {
    vector<string> buf;
#ifdef _SHIPPING
    // Palliative for  http://SITE
    RootFileSystem::GetFilesFromPileOnly( &buf, folder, mask, recursive );
#else
    RootFileSystem::GetFiles( &buf, folder, mask, recursive );
#endif //_SHIPPING
    int result = 0;
    for ( int i = 0; i < buf.size(); ++i )
    {
      string name = folder;
      AppendSlash( name );
      name += buf[i];
      if (Add(name))
      {
        result++;
      }
    }
    return result;
  }
private:
  void AppendSlash( string & result )
  {
    if ( !result.empty() )
      if ( result[result.size() - 1] != '\\' && result[result.size() - 1] != '/' )
        result += '\\';
  }

  bool Add(const string& name)
  {
    NDb::Ptr<T> ptr = NDb::Get<T>( NDb::DBID( name ) );
    if (ptr)
    {
      resources.push_back( ptr );
      return true;
    }
    return false;
  }
  vector<NDb::Ptr<T>> resources;
};

} // NWorld
#endif //#define RESOURCESCOLLECTION_H_400363F7_5