#pragma once

#include "DiAnGrExtPars.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
class DiAnimGraph;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DiAnGrEditorMarker
{
public:
  friend class DiAnGrMarker;

  string                  name;
  EditorGraphParamAddress  address;
  float                   virtPar;

  void setMarkerOnNode(const string &_markerName, int _nodeIdx, float _virtPar);
  void setMarkerOnTransaction(const string &_markerName, int _nodeIdx, int _nextNodeIdx, float _virtPar, int _subTransIdx = 0);

  DiAnGrEditorMarker() : name(""), virtPar(MAX_FLOAT) {}
};

// class for runtime (on contrast to DiAnGrEditorMarker which is used in Editor)
// This class is separated from DiAnGrEditorMarker to have ability to change 
// members/functionality of these classes independently.
class DiAnGrMarker
{
private:
  // common
  string                              markerName;
  // marker's place
  EditorGraphParamAddress::OwnerType  owner;   // node/transaction
  int                                 nodeIdx; // node ID (for VT_NODE) or nodeFrom (for VT_TRANSACTION)
  //int                                 nodeToIdx; // for VT_TRANSACTION
  int                                 transIdx; // for VT_TRANSACTION
  int                                 subTransIdx; // for VT_TRANSACTION, default 0
  // marker's time
  float                               virtPar; // virtual parameter (in [0..1] )

public:
  DiAnGrMarker();
  DiAnGrMarker(const DiAnGrEditorMarker &editorMarker, const DiAnimGraph &animGraph);

  static void FillMarkers(const vector<DiAnGrEditorMarker> &editorMarkers, const DiAnimGraph &animGraph,
                          vector<DiAnGrMarker> &graphMarkers);

	float GetVirtPar() const
	{
		return virtPar;
	}

  friend class DiAnimGraph;
  friend class CAnimGraphDoc;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///eugbelNSCENE///} // end of namespace NScene

