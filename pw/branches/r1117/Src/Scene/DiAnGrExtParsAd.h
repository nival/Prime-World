#pragma once

#include "DiAnGrUtils.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
//class DiAnimGraph;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct EditorGraphParamAddress
{
  enum OwnerType
  {
    VT_NA = -1,
    VT_NODE,
    VT_ANIM_SEQUENCE,
    VT_TRANSACTION,
    _VT_COUNT,
  };

  OwnerType         type;
  int               nodeIdx;
  int               nextNodeIdx; // used for type VT_TRANSACTION only
  int               subTransIdx; // 0 by default, used for type VT_TRANSACTION only
  int               subNodeIdx;  // used for type VT_ANIM_SEQUENCE only
  string            paramName;

  EditorGraphParamAddress();
  void setNodeParamAddress(int nodeIdx, const string &paramName);
  void setAnimSeqParamAddress(int nodeIdx, const string &paramName, int subNodeIdx = 0);
  void setTransactionParamAddress(int nodeIdx, int nextNodeIdx, const string &paramName, int subTransIdx = 0);
  bool operator == ( const EditorGraphParamAddress& other ) const; 

private:
  void setParamsInternal( OwnerType _type, int _nodeIdx, int _nextNodeIdx, 
    int _subTransIdx, int _subNodeIdx, const string &_paramName);
};

///eugbelNSCENE///} // end of namespace NScene

