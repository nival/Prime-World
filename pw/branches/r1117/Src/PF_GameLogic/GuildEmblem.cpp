#include "stdafx.h"
#include "GuildEmblem.h"
#include "curl/curl.h"
#include <string>
#include <sstream>

namespace NGameX
{

class GetGuildEmblemJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GetGuildEmblemJob, threading::IThreadJob, BaseObjectMT )
  CURL *curl;
  nstl::vector<byte> data;
  GuildEmblem* guildEmblem;
  nstl::string logoUrl;
  unsigned __int64 guildAuid;

public:
  GetGuildEmblemJob( GuildEmblem* guildEmblem, const nstl::string& logoUrl, unsigned __int64 guildAuid ) 
  : guildEmblem(guildEmblem), logoUrl(logoUrl), guildAuid(guildAuid) {}

  virtual void Work( volatile bool& isRunning )
  {
    curl = curl_easy_init();
    if ( curl )
    {
      curl_easy_setopt( curl, CURLOPT_URL, logoUrl.c_str() );
      curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteData );
      curl_easy_setopt( curl, CURLOPT_WRITEDATA, this );
      CURLcode res = curl_easy_perform( curl );
      NI_ASSERT( res == CURLE_OK, "Error download guild emblem" );
      curl_easy_cleanup( curl );
      guildEmblem->SetData( guildAuid, data );
    }
  }

  void AddData( void *ptr, size_t size, size_t nmemb )
  {
    data.reserve( data.size()+size*nmemb );
    for ( size_t i = 0; i != size*nmemb; i++ )
    {
      data.push_back( ((byte*)ptr)[i] );
    }
  }

  static size_t WriteData( void *ptr, size_t size, size_t nmemb, void *data )
  {
    GetGuildEmblemJob* emblem = (GetGuildEmblemJob*)data;
    emblem->AddData( ptr, size, nmemb );
    return size*nmemb;
  }
};

GuildEmblem::GuildEmblem()
{
  curl_global_init(CURL_GLOBAL_ALL);
}

void GuildEmblem::StartDownload( unsigned __int64 guildAuid, uint id, const nstl::string& url )
{
  if ( guildAuid > 0 && !url.empty() )
    downloadJobs.push_back( new threading::JobThread( new GetGuildEmblemJob( this, url, guildAuid ), "GetGuildEmblemJob", 10000 ) );
}

bool GuildEmblem::IsDownloaded()
{
  for ( int i = 0; i < downloadJobs.size(); i++ )
  {
    if ( downloadJobs[i] )
      if ( !downloadJobs[i]->Wait( 0 ) )
        continue;
    downloadJobs[i] = 0;
    downloadJobs.erase( downloadJobs.begin() + i );
    i--;
  }

  return downloadJobs.empty();
}

void GuildEmblem::SetData( unsigned __int64 guildAuid, const nstl::vector<byte>& _data )
{
  threading::MutexLock lock( mutex );
  data[guildAuid] = _data;
}

bool GuildEmblem::GetData( unsigned __int64 guildAuid, nstl::vector<byte>& _data )
{
  if ( data.find( guildAuid ) != data.end() )
  {
    _data = data[guildAuid];
    return true;
  }
  return false;
}

}

NI_DEFINE_REFCOUNT( NGameX::GuildEmblem );
