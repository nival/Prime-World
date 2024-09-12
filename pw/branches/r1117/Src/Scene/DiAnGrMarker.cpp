#include "stdafx.h"

#include "DiAnGrMarker.h"
#include "DiAnGr.h"


namespace
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DiAnGrEditorMarker::setMarkerOnNode(const string &_markerName, int _nodeIdx, float _virtPar)
{
  name    = _markerName;
  virtPar = _virtPar;

  address.setNodeParamAddress(_nodeIdx, "");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnGrEditorMarker::setMarkerOnTransaction(const string &_markerName, int _nodeIdx, 
                                                int _nextNodeIdx, float _virtPar, int _subTransIdx)
{
  name    = _markerName;
  virtPar = _virtPar;

  address.setTransactionParamAddress(_nodeIdx, _nextNodeIdx, "", _subTransIdx);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
DiAnGrMarker::DiAnGrMarker()
: markerName("")
, owner(EditorGraphParamAddress::VT_NA)
, nodeIdx(-1)
, transIdx(-1)
, subTransIdx(-1)
, virtPar(-1.0f)
{

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrMarker::DiAnGrMarker(const DiAnGrEditorMarker &editorMarker, const DiAnimGraph &animGraph)
{
  markerName = editorMarker.name;
  owner      = editorMarker.address.type;
  nodeIdx    = editorMarker.address.nodeIdx;
  if (owner == EditorGraphParamAddress::VT_TRANSACTION)
  {
    transIdx   = animGraph.GetEdgeID(editorMarker.address.nodeIdx, editorMarker.address.nextNodeIdx);
    subTransIdx= editorMarker.address.subTransIdx;
  }
  virtPar    = editorMarker.virtPar;

  DIASSERT(markerName.length() > 0);
  DIASSERT(EditorGraphParamAddress::VT_NODE == owner 
           || EditorGraphParamAddress::VT_TRANSACTION == owner); // can't set marker on VT_ANIM_SEQUENCE!
  if (EditorGraphParamAddress::VT_NODE == owner)
  {
    DIASSERT(0 <= nodeIdx && nodeIdx < int(animGraph.GetNumNodes()));
  }
  else
  {
    DIASSERT(EditorGraphParamAddress::VT_TRANSACTION == owner);
    DIASSERT(0 <= editorMarker.address.nextNodeIdx && editorMarker.address.nextNodeIdx < int(animGraph.GetNumNodes()));
    DIASSERT(0 <= transIdx && transIdx < int(animGraph.GetNumEdges()));
    DIASSERT(0 <= subTransIdx &&
             subTransIdx < int(animGraph.GetTransactionNumIntervals(transIdx)));
  }
  DIASSERT(0.0f <= virtPar && virtPar <= 1.0f);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnGrMarker::FillMarkers( const vector<DiAnGrEditorMarker> &editorMarkers,
                                const DiAnimGraph &animGraph,
                                vector<DiAnGrMarker> &graphMarkers)
{
  // convert editor markers into graph markers
  DIASSERT(graphMarkers.size() == 0); // should be empty

  graphMarkers.reserve(editorMarkers.size());
  for (int i = 0; i < editorMarkers.size(); i++)
  {
    graphMarkers.push_back(DiAnGrMarker(editorMarkers[i], animGraph));
  }
}

///eugbelNSCENE///} // end of namespace NScene