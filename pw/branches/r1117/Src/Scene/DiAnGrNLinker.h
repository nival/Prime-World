#pragma once

#include "DiAnGrUtils.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {


// Forward declaration
class DiAnimGraph;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class is used t link nodes' names in user's AnimGraph with IDs of these names in the graph.
// Main functionality: function GetID(enum ID)
template <class T> // T - is user's enum
class DiAnGrNamesIDLinker
{
public:
  // structure to link nodes' names of AnimGraph with their IDs
  template <class T>
  struct ID2NameLink
  {
    T      enumID;
    string name;
  };

  DiAnGrNamesIDLinker(DiAnimGraph const* animGraph, const ID2NameLink<T> *links, int count, int max);
  DiAnGrNamesIDLinker(DiAnimGraph const* animGraph, int max);

  ~DiAnGrNamesIDLinker();
  DiUInt32 GetID(T enumID) const;
  void     CreateLink(T id, string const& name);

private:
  DiUInt32*          graphIDs;
  DiAnimGraph const* animGraph;
};


template <class T>
DiAnGrNamesIDLinker<T>::DiAnGrNamesIDLinker(DiAnimGraph const* animGraph, const ID2NameLink<T> *links, int count, int max)
  : graphIDs(NULL)
  , animGraph(animGraph)
{
  DIASSERT(links != NULL);
  DIASSERT(max > 0);
  DIASSERT(count > 0);
  DIASSERT(animGraph != NULL);

  graphIDs = new DiUInt32[max];
  for( int i = 0 ; i < max; ++i)
    graphIDs[i] = DIANGR_NO_SUCH_ELEMENT;
  
  for (int i = 0; i < count; i++)
  {
    if( links[i].name.empty() )
      continue;

    DIASSERT( 0 <= links[i].enumID );
    DIASSERT(DIANGR_NO_SUCH_ELEMENT == graphIDs[ links[i].enumID ]);
    graphIDs[ links[i].enumID ] = animGraph->GetNodeIDByNameSlowQuite(links[i].name.begin());  
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
DiAnGrNamesIDLinker<T>::DiAnGrNamesIDLinker(DiAnimGraph const* animGraph, int max)
  : graphIDs(NULL)
  , animGraph(animGraph)
{
  DIASSERT(max > 0);
  DIASSERT(animGraph != NULL);

  graphIDs = new DiUInt32[max];
  for( int i = 0 ; i < max; ++i)
    graphIDs[i] = DIANGR_NO_SUCH_ELEMENT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void   DiAnGrNamesIDLinker<T>::CreateLink(T id, string const& name)
{
  if( !name.empty() )
  {
    DIASSERT( 0 <= id );
    DIASSERT(DIANGR_NO_SUCH_ELEMENT == graphIDs[ id ]);
    graphIDs[ id ] = animGraph->GetNodeIDByNameSlowQuite( name.begin() );  
  } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
DiAnGrNamesIDLinker<T>::~DiAnGrNamesIDLinker()
{
  delete [] graphIDs;
  graphIDs = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
DiUInt32 DiAnGrNamesIDLinker<T>::GetID(T enumID) const
{
  return graphIDs[enumID];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///eugbelNSCENE///} // end of namespace NScene

