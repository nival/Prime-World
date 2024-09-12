#ifndef SOCIALLOBBYCLIENTREVISIONS_H_INCLUDED
#define SOCIALLOBBYCLIENTREVISIONS_H_INCLUDED

#include <map>
#include "SocialLobbyLog.h"

namespace socialLobby
{

class ClientRevisions : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClientRevisions, BaseObjectMT );

public:
  ClientRevisions( const string & configData )
  {
    vector<string> split;
    NStr::SplitString( configData, &split, ' ');

    set<int> rev;
    for ( int i = 0; i < split.size(); ++i )
    {
      int r = NStr::ToInt( split[i] );
      if ( r > 0 )
        rev.insert( r );
    }

    revisions.clear();

    int replacement = 0;
    if ( !rev.empty() )
    {
      set<int>::iterator it = rev.begin();
      replacement = *it;
      for( ++it; it != rev.end(); ++it ) {
        int r = *it;
        revisions[r] = replacement;
      }
    }

    string dbgStr;
    if ( revisions.empty() )
      dbgStr = "empty";
    else
    {
      dbgStr = "( ";
      for ( TRevisionsMap::iterator it = revisions.begin(); it != revisions.end(); ++it )
        dbgStr += NI_STRFMT( "%d ", it->first );
      dbgStr += NI_STRFMT( ") -> %d", replacement );
    }

    SOCLOBBY_LOG_MSG( "Loaded client revisions map: %s", dbgStr );
  }


  int Map( int srcRev )
  {
    TRevisionsMap::iterator it = revisions.find( srcRev );
    if ( it == revisions.end() )
      return srcRev;
    return it->second;
  }


private:
  typedef std::map<int, int> TRevisionsMap;

  TRevisionsMap revisions;
};

} //namespace socialLobby

#endif //SOCIALLOBBYCLIENTREVISIONS_H_INCLUDED
