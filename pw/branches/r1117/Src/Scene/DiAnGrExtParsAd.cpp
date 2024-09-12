#include "stdafx.h"

#include "DiAnGrExtPars.h"
//#include "DiAnGr.h"

namespace
{
  const int    s_err                = -1; // common invalid flag
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorGraphParamAddress::setParamsInternal(
                        OwnerType _type, int _nodeIdx, int _nextNodeIdx, 
                        int _subTransIdx, int _subNodeIdx, const string &_paramName)
{
  type        = _type;
  nodeIdx     = _nodeIdx;
  nextNodeIdx = _nextNodeIdx;
  subTransIdx = _subTransIdx;
  subNodeIdx  = _subNodeIdx;
  paramName   = _paramName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorGraphParamAddress::EditorGraphParamAddress()
: type(VT_NA)
, nodeIdx(s_err)
, nextNodeIdx(s_err)
, subTransIdx(s_err)
, paramName("")
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  nodeIdx    - index of node
  paramName  - name of the dependent parameter ("speed", "startPar" or "stopPar")
*/
void EditorGraphParamAddress::setNodeParamAddress(int nodeIdx, const string &paramName)
{
  setParamsInternal(EditorGraphParamAddress::VT_NODE, nodeIdx, s_err, s_err, s_err, paramName);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  nodeIdx    - index of node
  paramName  - name of the dependent parameter ("startPar", "stopPar", "speed" or "weight")
  subNodeIdx - index of sub-node (if node is a macronode). By default 0.
*/
void EditorGraphParamAddress::setAnimSeqParamAddress(int nodeIdx, const string &paramName, int subNodeIdx)
{
  setParamsInternal(EditorGraphParamAddress::VT_ANIM_SEQUENCE, nodeIdx, s_err, s_err, subNodeIdx, paramName);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  nodeIdx      - nodeFrom index
  nextNodeIdx  - nodeTo   index
  paramName    - name of the dependent parameter ("speed", "parA", "parB", "fromMin", "fromMax" or "toParam")
  subTransIdx  - index of sub-transaction (if there are several intervals, i.e. several transactions, from
                                           nodeFrom to nodeTo). Equal to 0 by default.
*/
void EditorGraphParamAddress::setTransactionParamAddress(int nodeIdx, int nextNodeIdx, const string &paramName, int subTransIdx)
{
  setParamsInternal(EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeIdx, subTransIdx, s_err, paramName);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditorGraphParamAddress::operator == ( const EditorGraphParamAddress& other ) const 
{
  bool same(true);
  if (type != other.type)
    same = false;
  else
  {
    switch(type)
    {
    case VT_NODE:
      same = (nodeIdx == other.nodeIdx);
      break;
    case VT_ANIM_SEQUENCE:
      same = (nodeIdx == other.nodeIdx && subNodeIdx == other.subNodeIdx);
      break;
    case VT_TRANSACTION:
      same = (nodeIdx == other.nodeIdx && nextNodeIdx == other.nextNodeIdx && subTransIdx == other.subTransIdx);
      break;
    }
    same = same && (paramName == other.paramName);
  }

  return same;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///} // end of namespace NScene