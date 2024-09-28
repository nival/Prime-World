#ifndef SOCIALLOBBYPINNEDLOCATIONS_H_INCLUDED
#define SOCIALLOBBYPINNEDLOCATIONS_H_INCLUDED

#include <map>
#include <string>
#include "SocialLobbyLog.h"
#include "System/SafeTextFormatStl.h"

namespace socialLobby
{


class PinnedLocations : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( PinnedLocations, BaseObjectMT );

public:
  typedef std::map<std::string, std::string> TMapping; //locations id -> cluster id
  typedef std::map<std::string, int> TPriorityData; //cluster id -> priority

  PinnedLocations( const string & _mapping, const string & _clustersPriority )
  {
    LoadMapping( _mapping );
    LoadPriority( _clustersPriority );
  }

  const TMapping & Mapping() const { return mapping; }
  const TPriorityData & Priority() const { return priority; }

private:
  TMapping mapping;
  TPriorityData priority;

  void LoadMapping( const string & _mapping )
  {
    vector<string> split;
    NStr::SplitString( _mapping, &split, ',' );

    for ( int i = 0; i < split.size(); ++i )
    {
      const string & splitted = split[i];
      char locId[16] = "", clusterId[16] = "";
      int len = 0;
      if ( sscanf( splitted.c_str(), "%15s %15s%n", locId, clusterId, &len ) == 2 )
        if ( len == (int)splitted.length() )
        {
          if ( strlen( locId ) && strlen( clusterId ) )
          {
            mapping[locId] = clusterId;
            continue;
          }
        }

      SOCLOBBY_LOG_WRN( "Wrong pinned location config. str=%s", splitted );
    }

    SOCLOBBY_LOG_MSG( "Pinned locations loaded. mapping=%d", mapping );
  }


  void LoadPriority( const string & _clustersPriority )
  {
    vector<string> split;
    NStr::SplitString( _clustersPriority, &split, ',' );

    for ( int i = 0; i < split.size(); ++i )
    {
      const string & splitted = split[i].c_str();
      char clusterId[16] = "";
      int prio = 0, len = 0;
      if ( sscanf( splitted.c_str(), "%15s %d%n", clusterId, &prio, &len ) == 2 )
        if ( len == (int)splitted.length() )
          if ( strlen( clusterId ) && ( prio >= 0 ) )
          {
            bool found = false;
            for ( TMapping::const_iterator it = mapping.begin(); !found && ( it != mapping.end() ); ++it )
              if ( it->second == clusterId )
                found = true;
            if ( found )
            {
              priority[clusterId] = prio;
              continue;
            }
          }

      SOCLOBBY_LOG_WRN( "Wrong pinned location priority config. str=%s", splitted );
    }

    SOCLOBBY_LOG_MSG( "Pinned locations loaded. priority=%d", priority );
  }
};

} //namespace socialLobby

#endif //SOCIALLOBBYPINNEDLOCATIONS_H_INCLUDED
