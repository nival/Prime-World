#include "StdAfx.h"
#include "IgnoreListStorage.h"
#include "../System/ChunklessSaver.h"
#include "../System/Crc32Checksum.h"
#include "../System/FileSystem/FileStream.h"
#include "../System/FileSystem/FileUtils.h"

#include "System/InlineProfiler.h"

#define _ULL(x) static_cast<unsigned long long>((x))

namespace
{
  const unsigned long long _IgnoreListMagic =
    (_ULL(0xFF) << 56) |
    (_ULL(0xFF) << 48) |
    (_ULL('E')  << 40) |
    (_ULL('R')  << 32) |
    (_ULL('O')  << 24) |
    (_ULL('N')  << 16) |
    (_ULL('G')  <<  8) |
    (_ULL('I')  <<  0);
}

#define _IGNORE_LIST_VERSIONLESS (0ULL)
#define _IGNORE_LIST_V1 (1ULL)
#define _IGNORE_LIST_V2 (2ULL)

#define IGNORE_LIST_MAGIC _IgnoreListMagic
#define IGNORE_LIST_VERSION _IGNORE_LIST_V2

namespace
{
  using namespace NGameX::IgnoreList;

  namespace EIgnoreListStorageFormat
  {
    enum Enum
    {
      Legacy,
      Regular,
    };
  }

  struct IgnoreListHeader
  {
    unsigned long long magic;
    unsigned long long version;
  };

  static nstl::string MakeIgnoreListFileName(const TUserId& _auid, const EIgnoreListStorageFormat::Enum format)
  {
    switch (format)
    {
    case EIgnoreListStorageFormat::Legacy:
      return NStr::StrFmt("ignorelist%llu.dat", _auid);
    case EIgnoreListStorageFormat::Regular:
      return NStr::StrFmt("%016llX.ignore", _auid);
    default:
      return NStr::StrFmt("~.ignore");
    }
  }

  static nstl::string MakeIgnoreListFilePath(const TUserId& _auid, const EIgnoreListStorageFormat::Enum format)
  {
    const nstl::string filename(MakeIgnoreListFileName(_auid, format));

    return NProfile::GetFullFilePath(filename, NProfile::FOLDER_USER);
  }

  class LegacyIgnoreListReaderImpl : public NonCopyable
  {
  public:
    explicit LegacyIgnoreListReaderImpl(const nstl::string& _path)
      : path(_path)
    {

    }

    bool operator()(TUserSet& users, TUserNicknameMap& nicknames) const
    {
      const CObj<FileStream> pStream(new FileStream(path, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING));

      if (!IsValid(pStream) || !pStream->IsOk() || !pStream->CanRead() || pStream->GetSize() <= 2)
      {
        MessageTrace("Cannot read ignore list file \"%s\"", path);
        return false;
      }

      wstring szBuffer;

      szBuffer.resize(pStream->GetSize());

      pStream->Read(&(szBuffer[0]), pStream->GetSize());
      pStream->Close();

      MessageTrace("Reading \"%s\"", path);

      typedef vector<wstring> TLines;

      TLines lines;

      NStr::SplitString(szBuffer.c_str() + 1, &lines, L"\r\n"); // пропускаем один wchar_t с BOM

      TLines::const_iterator it = lines.begin();
      TLines::const_iterator it_end = lines.end();
      for (; nstl::distance(it, it_end) > 1; nstl::advance(it, 2))
      {
        wstring line1(*(it + 0));
        wstring line2(*(it + 1));

        NStr::TrimBoth(line1, L"\n\r");
        NStr::TrimBoth(line2, L"\n\r");

        if (line1.empty() || line2.empty())
          continue;

        const TUserId auid = _wtoi64(line1.c_str());

        if (!auid)
          continue;

        users.insert(auid);
        nicknames.insert(nstl::make_pair(auid, line2));
      }

      return true;
    }
  private:
    LegacyIgnoreListReaderImpl();

    const nstl::string path;
  };

  class IgnoreListReaderImpl : public NonCopyable
  {
  public:
    explicit IgnoreListReaderImpl(const nstl::string& _path)
      : path(_path)
    {

    }

    bool operator()(TUserSet& users, TUserNicknameMap& nicknames)
    {
      const CObj<FileStream> pStream(new FileStream(path, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING));

      if (!IsValid(pStream) || !pStream->IsOk() || !pStream->CanRead())
      {
        MessageTrace("Cannot read ignore list file \"%s\"", path);
        return false;
      }

      MessageTrace("Reading \"%s\"", path);

      if (!TryReadHeader(pStream))
      {
        pStream->Seek(0, SEEKORIGIN_BEGIN);
      }

      TUserId userId;
      TUserNickname userNickname;

      while (pStream->GetPosition() < pStream->GetSize())
      {
        (*pStream) >> userId;

        if (!pStream->IsOk())
        {
          ErrorTrace("Read from \"%s\" failed!", path);
          break;
        }

        users.insert(userId);

        if (TryReadNickname(pStream, userNickname))
        {
          if (!userNickname.empty())
            nicknames[userId] = userNickname;
        }
      }

      pStream->Close();

      return true;
    }

    bool HasHeader() const
    {
      return
        (header.magic == IGNORE_LIST_MAGIC) &&
        (header.version != _IGNORE_LIST_VERSIONLESS);
    }
  private:
    IgnoreListReaderImpl();

    bool TryReadHeader(const CObj<FileStream>& stream)
    {
      const int bytesAvailable = (stream->GetSize() - stream->GetPosition());

      if (bytesAvailable < sizeof(IgnoreListHeader))
      {
        return false;
      }

      int bytesRead = 0;

      bytesRead += stream->Read(&header.magic, sizeof(header.magic));
      bytesRead += stream->Read(&header.version, sizeof(header.version));

      if (!stream->IsOk())
      {
        ErrorTrace("Read from \"%s\" failed! [header]", path);

        header.version = _IGNORE_LIST_VERSIONLESS;
        return false;
      }

      if (bytesRead != sizeof(IgnoreListHeader))
      {
        header.version = _IGNORE_LIST_VERSIONLESS;
        return false;
      }

      if (header.magic != IGNORE_LIST_MAGIC)
      {
        header.version = _IGNORE_LIST_VERSIONLESS;
        return false;
      }

      return true;
    }

    bool TryReadNickname(const CObj<FileStream>& stream, TUserNickname& nickname)
    {
      if (!ShouldReadNicknames())
        return true;

      unsigned short length;

      (*stream) >> length;

      if (!stream->IsOk())
      {
        ErrorTrace("Read from \"%s\" failed! [nickname:length]", path);
        return false;
      }

      nickname.resize(length);

      void* const _memory = &(nickname[0]);
      int const _capacity = nickname.length() * sizeof(TUserNickname::value_type);

      int const size = stream->Read(_memory, _capacity);

      if (!stream->IsOk() || (size != _capacity))
      {
        ErrorTrace("Read from \"%s\" failed! [nickname:data]", path);
        return false;
      }

      return true;
    }

    bool ShouldReadNicknames() const
    {
      return (header.version == _IGNORE_LIST_V2);
    }

    const nstl::string path;

    IgnoreListHeader header;
  };

  class IgnoreListWriterImpl : public NonCopyable
  {
  public:
    explicit IgnoreListWriterImpl(const nstl::string& _path)
      : path(_path)
      , header()
    {
      header.magic = IGNORE_LIST_MAGIC;
      header.version = IGNORE_LIST_VERSION;
    }

    bool operator()(const TUserSet& users, const TUserNicknameMap& nicknames) const
    {
      const CObj<FileStream> pStream(new FileStream(path, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW));

      if (!IsValid(pStream) || !pStream->IsOk() || !pStream->CanWrite())
      {
        MessageTrace("Cannot write ignore list file \"%s\"", path);
        return false;
      }

      MessageTrace("Writing \"%s\"", path);

      if (ShouldWriteHeader())
      {
        (*pStream) << header.magic;
        (*pStream) << header.version;
      }

      TUserSet::const_iterator it = users.begin();
      TUserSet::const_iterator it_end = users.end();
      for (; it != it_end; ++it)
      {
        (*pStream) << (*it);

        if (!pStream->IsOk())
        {
          ErrorTrace("Write to \"%s\" failed!", path);
          break;
        }

        if (TryWriteNickname(pStream, *it, nicknames))
        {
          // placeholder
        }
      }

      pStream->Close();

      return true;
    }
  private:
    IgnoreListWriterImpl();

    bool ShouldWriteHeader() const
    {
      return true;
    }

    bool ShouldWriteNicknames() const
    {
      return (header.version == _IGNORE_LIST_V2);
    }

    bool TryWriteNickname(const CObj<FileStream>& stream, const TUserId& userId, const TUserNicknameMap& nicknames) const
    {
      if (!ShouldWriteNicknames())
        return true;

      TUserNicknameMap::const_iterator it = nicknames.find(userId);

      if (it == nicknames.end())
        return WriteNicknameImpl(stream, TUserNickname());
      else
        return WriteNicknameImpl(stream, it->second);
    }

    bool WriteNicknameImpl(const CObj<FileStream>& stream, const TUserNickname& nickname) const
    {
      unsigned short length = nickname.length();

      // terminating zero
      if (length > 0)
        ++length;

      (*stream) << length;

      if (!stream->IsOk())
      {
        ErrorTrace("Write to \"%s\" failed! [nickname:length]", path);
        return false;
      }

      if (length > 0)
      {
        const void* const _memory = &(nickname[0]);
        int const _capacity = (nickname.length() + 1) * sizeof(TUserNickname::value_type);

        int const size = stream->Write(_memory, _capacity);

        if (!stream->IsOk() || (size != _capacity))
        {
          ErrorTrace("Write to \"%s\" failed! [nickname:data]", path);
          return false;
        }
      }

      return true;
    }

    const nstl::string path;

    IgnoreListHeader header;
  };

  class IgnoreListWriter : public NonCopyable
  {
  public:
    explicit IgnoreListWriter(const TUserId& _auid)
      : auid(_auid)
    {

    }

    bool operator()(const TUserSet& users, const TUserNicknameMap& nicknames) const
    {
      const nstl::string path(MakeIgnoreListFilePath(auid, EIgnoreListStorageFormat::Regular));

      return IgnoreListWriterImpl(path)(users, nicknames);
    }
  private:
    IgnoreListWriter();

    const TUserId auid;
  };

  class IgnoreListReader : public NonCopyable
  {
  public:
    explicit IgnoreListReader(const TUserId& _auid)
      : auid(_auid)
    {

    }

    bool operator()(TUserSet& users, TUserNicknameMap& nicknames) const
    {
      users.clear();
      nicknames.clear();

      {
        const nstl::string path(MakeIgnoreListFilePath(auid, EIgnoreListStorageFormat::Regular));

        if (NFile::DoesFileExist(path))
        {
          IgnoreListReaderImpl impl(path);

          const bool read = impl(users, nicknames);

          if (read && !impl.HasHeader())
          {
            const IgnoreListWriter writer(auid);
            writer(users, nicknames);
          }

          return read;
        }
      }

      {
        const nstl::string path(MakeIgnoreListFilePath(auid, EIgnoreListStorageFormat::Legacy));

        if (NFile::DoesFileExist(path))
        {
          const bool read = LegacyIgnoreListReaderImpl(path)(users, nicknames);

          if (read)
          {
            const IgnoreListWriter writer(auid);
            writer(users, nicknames);
          }

          return read;
        }
      }

      return true;
    }
  private:
    IgnoreListReader();

    const TUserId auid;
  };
}

namespace NGameX
{

  IgnoreListStorage::IgnoreListStorage(const TUserId _auid)
    : ownerUserId(_auid)
    , users()
  {
    LoadFromFile();
  }

  void IgnoreListStorage::AddListener(IIgnoreListListener* const listener)
  {
    if (!listener)
      return;

    // TODO: не добавлять listener'а, если он уже зарегистрирован

    listeners.push_back(listener);
  }

  void IgnoreListStorage::AddUser(const TUserId auid)
  {
    if (!auid)
      return;

    TUserSet::const_iterator it = users.find(auid);

    if (it != users.end())
      return;

    users.insert(auid);

    SaveToFile();

    for (TListeners::iterator it_listener = listeners.begin(); it_listener != listeners.end(); ++it_listener)
    {
      if (const TListenerPtr listener = (*it_listener))
      {
        listener->OnUserAddedToIgnoreList(auid);
      }
    }
  }

  void IgnoreListStorage::RemoveUser(const TUserId auid)
  {
    if (!auid)
      return;

    TUserSet::iterator it = users.find(auid);

    if (it == users.end())
      return;

    users.erase(it);

    SaveToFile();

    for (TListeners::iterator it_listener = listeners.begin(); it_listener != listeners.end(); ++it_listener)
    {
      if (const TListenerPtr listener = (*it_listener))
      {
        listener->OnUserRemovedFromIgnoreList(auid);
      }
    }
  }

  void IgnoreListStorage::AddUserNickname(const TUserId auid, const TUserNickname& nickname)
  {
    if (!auid)
      return;

    if (nickname.empty())
      nicknames.erase(auid);
    else
      nicknames[auid] = nickname;
  }

  void IgnoreListStorage::LoadFromFile()
  {
    const IgnoreListReader reader(ownerUserId);
    reader(users, nicknames);
  }

  void IgnoreListStorage::SaveToFile() const
  {
    const IgnoreListWriter writer(ownerUserId);
    writer(users, nicknames);
  }

}

NI_DEFINE_REFCOUNT(NGameX::IgnoreListStorage);
NI_DEFINE_REFCOUNT(NGameX::IIgnoreListListener);