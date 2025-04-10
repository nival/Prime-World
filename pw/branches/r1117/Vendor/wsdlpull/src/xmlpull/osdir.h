#ifndef OSLINK_OSDIR_HEADER_H_
#define OSLINK_OSDIR_HEADER_H_

#if defined(unix) || defined(__unix) || defined(__unix__)
#define OSLINK_OSDIR_POSIX
#elif defined(_WIN32)
#define OSLINK_OSDIR_WINDOWS
#else
#define OSLINK_OSDIR_NOTSUPPORTED
#endif

#include <string>

#if defined(OSLINK_OSDIR_NOTSUPPORTED)

namespace oslink
{
  class directory
  {
  public:
    directory(const std::string&)		{ }
    operator void*() const				{ return (void*)0; }
    std::string next()					{ return ""; }
  };
}

#elif defined(OSLINK_OSDIR_POSIX)

#include <sys/types.h>
#include <dirent.h>

namespace oslink
{
  class directory
  {
  public:
    directory(const std::string& aName)
      : handle(opendir(aName.c_str())), willfail(false)
    {
      if (!handle)
        willfail = true;
      else
      {
        dirent* entry = readdir(handle);
        if (entry)
          current = entry->d_name;
        else
          willfail = true;
      }
    }
    ~directory()
    {
      if (handle)
        closedir(handle);
    }
    operator void*() const
    {
      return willfail ? (void*)0:(void*)(-1);
    }
    std::string next()
    {
      std::string prev(current);
      dirent* entry = readdir(handle);
      if (entry)
        current = entry->d_name;
      else
        willfail = true;
      return prev;
    }
  private:
    DIR* handle;
    bool willfail;
    std::string current;
  };
}

#elif defined(OSLINK_OSDIR_WINDOWS)

#include <windows.h>
#include <winbase.h>

namespace oslink
{
  class directory
  {
  public:
    directory(const std::string& aName)
      : handle(INVALID_HANDLE_VALUE), willfail(false)
    {
      // First check the attributes trying to access a non-directory with 
      // FindFirstFile takes ages
      DWORD attrs = GetFileAttributes(aName.c_str());
      if ( (attrs == 0xFFFFFFFF) || ((attrs && FILE_ATTRIBUTE_DIRECTORY) == 0) )
      {
        willfail = true;
        return;
      }
      std::string Full(aName);
      // Circumvent a problem in FindFirstFile with c:\\* as parameter 
      if ( (Full.length() > 0) && (Full[Full.length()-1] != '\\') )
        Full += "\\";
      WIN32_FIND_DATA entry;
      handle = FindFirstFile( (Full+"*").c_str(), &entry);
      if (handle == INVALID_HANDLE_VALUE)
        willfail = true;
      else
        current = entry.cFileName;
    }
    ~directory()
    {
      if (handle != INVALID_HANDLE_VALUE)
        FindClose(handle);
    }

    operator void*() const				
    {
      return willfail ? (void*)0:(void*)(-1);
    }
    std::string next()
    {
      std::string prev = current;
      WIN32_FIND_DATA entry;
      int ok = FindNextFile(handle, &entry);
      if (!ok)
        willfail = true;
      else
        current = entry.cFileName;
      return current; 
    }
  private:
    HANDLE	handle;
    bool	willfail;
    std::string current;
  };
}


#endif

#endif
