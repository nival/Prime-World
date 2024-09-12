#ifndef GUILDEMBLEM_H_5D67B548_52C0_4AEA
#define GUILDEMBLEM_H_5D67B548_52C0_4AEA

#pragma warning( disable: 4530 )
#include "System/JobThread.h"
#include <sstream>

namespace NGameX
{

class GuildEmblem : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( GuildEmblem, BaseObjectST );

  nstl::vector<StrongMT<threading::JobThread>> downloadJobs;
  nstl::map<unsigned __int64, nstl::vector<byte>> data;
  threading::Mutex mutex;

public:
  GuildEmblem();

  void StartDownload( unsigned __int64 guildAuid, uint id, const nstl::string& url );
  bool IsDownloaded();
  void SetData( unsigned __int64 guildAuid, const nstl::vector<byte>& _data );
  bool GetData( unsigned __int64 guildAuid, nstl::vector<byte>& _data );
};

}

#endif //#define GUILDEMBLEM_H_5D67B548_52C0_4AEA