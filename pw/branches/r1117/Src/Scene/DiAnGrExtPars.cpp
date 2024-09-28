#include "stdafx.h"

#include "DiAnGrExtPars.h"
#include "DiAnGr.h"


namespace
{
  const int    s_err                = -1; // common invalid flag
  const string s_constant           = "CONSTANT";
  const float  s_errorValue         = MAX_FLOAT;
  const float  s_extParDefaultValue = s_errorValue; // default value of each external parameter until set directly by SetExtParValue()
  
  /*
  void _convertData(const DiAnimGraph *graph, const NDb::AnGrExternalDependency &srcDep, EditorGraphParamAddress &paramAddr)
  {
    vector<nstl::string> params;

    NI_ASSERT(srcDep.depOwner.length() > 0, "Empty formula!");
    NStr::SplitString(srcDep.depOwner, &params, ".");

    if (params[0] == string("N"))
    {
      // "N.<nodename>.<paramname>"
      NI_ASSERT(params.size() == 3, "Wrong number of parameters: should be 'N.<nodename>.<paramname>'");
      paramAddr.type          = EditorGraphParamAddress::VT_NODE;
      paramAddr.nodeIdx       = graph->GetNodeIDByNameSlow(params[1].c_str());
      paramAddr.nextNodeIdx   = -1;
      paramAddr.subNodeIdx    = -1;
      paramAddr.subTransIdx   = -1;
      paramAddr.paramName     = params[2];
      
    }
    else if (params[0] == string("T"))
    {
      // "T.<nodenameFrom>.<nodenameTo>.<transSubIndex>.<paramname>"
      NI_ASSERT(params.size() == 5, "Wrong number of parameters: should be 'T.<nodenameFrom>.<nodenameTo>.<transSubIndex>.<paramname>'");
      paramAddr.type          = EditorGraphParamAddress::VT_TRANSACTION;
      paramAddr.nodeIdx       = graph->GetNodeIDByNameSlow(params[1].c_str());
      paramAddr.nextNodeIdx   = graph->GetNodeIDByNameSlow(params[2].c_str());
      paramAddr.subNodeIdx    = -1;
      paramAddr.subTransIdx   = NStr::ToInt(params[3]);
      paramAddr.paramName     = params[4];

    }
    else if (params[0] == string("S"))
    {
      // "S.<nodename>.<subNodeIndexOrZero>.<paramname>"
      NI_ASSERT(params.size() == 4, "Wrong number of parameters: should be 'S.<nodename>.<subNodeIndexOrZero>.<paramname>'");
      paramAddr.type          = EditorGraphParamAddress::VT_ANIM_SEQUENCE;
      paramAddr.nodeIdx       = graph->GetNodeIDByNameSlow(params[1].c_str());
      paramAddr.nextNodeIdx   = -1;
      paramAddr.subNodeIdx    = NStr::ToInt(params[2]);
      paramAddr.subTransIdx   = -1;
      paramAddr.paramName     = params[4];
    }
    else
    {
      NI_ALWAYS_ASSERT(("Wrong format of the formula! (formula: %s)", srcDep.depOwner.c_str()));
      return;
    }
    
  } */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::EditorExternalParam::EditorExternalParam(const string &_name, float _initialValue)
{
  DIASSERT(_name.length() > 0);
    name         = _name;
  initialValue = _initialValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::EditorExternalParamLink::EditorExternalParamLink(const string &_name, float _coeff)
{
  name  = _name;
  coeff = _coeff;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::EditorExternalParamLink::EditorExternalParamLink(float _constantValue)
{
  name   = s_constant;
  coeff = _constantValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::RuntimeExternalParamLink::RuntimeExternalParamLink()
: coeff(MAX_FLOAT)
, extParID(s_err) 
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::RuntimeExternalParamLink::RuntimeExternalParamLink(float _coeff, int _extParID)
{
  coeff    = _coeff;
  extParID = _extParID;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiAnGrExtPars::RuntimeExternalParam::RuntimeExternalParam(const string &_name, float _initialValue)
: name(_name)
, value(_initialValue)
, defaultValue(_initialValue)
{
}
/*DiAnGrExtPars::RuntimeExternalParam::RuntimeExternalParam(const EditorExternalParam &_extPar)
{
  name = _extPar.name;
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *DiAnGrExtPars::getFieldAddress(const EditorDependency &_dependency, DiAnimGraph &animGraph)
{
  if (EditorGraphParamAddress::VT_NODE == _dependency.internalParam.type)
    return getNodeFieldAddress(_dependency, animGraph);
  
  if (EditorGraphParamAddress::VT_ANIM_SEQUENCE == _dependency.internalParam.type)
    return getAnimSequenceFieldAddress(_dependency, animGraph);

  if (EditorGraphParamAddress::VT_TRANSACTION == _dependency.internalParam.type)
    return getTransactionFieldAddress(_dependency, animGraph);

  DIASSERT(3 == EditorGraphParamAddress::_VT_COUNT);
  NI_ALWAYS_ASSERT("Unsupported type of element!");

  return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *DiAnGrExtPars::getAnimSequenceFieldAddress(const EditorDependency &dep, DiAnimGraph &animGraph)
{
  DIASSERT(EditorGraphParamAddress::VT_ANIM_SEQUENCE == dep.internalParam.type);

  DiAnimNode  *node = animGraph.GetNodeData(dep.internalParam.nodeIdx);
  DiAnGrSequence *seq = NULL;
  DIASSERT(animGraph.GetNumParts() == 1); // change working with DiAnGrSequence if numParts > 1!

  if (node->bIsThisMacronode)
  {
    DiAnimMacronode *macronode = (DiAnimMacronode *)node;
    DIASSERT(0 <= dep.internalParam.subNodeIdx && 
                   dep.internalParam.subNodeIdx <= macronode->GetNumIntNodes());
    seq = &macronode->spSequences[dep.internalParam.subNodeIdx];
  }
  else
  {
    DIASSERT(0 == dep.internalParam.subNodeIdx);
    seq = &node->spSequences[0];
  }

  const string &name = dep.internalParam.paramName;
  if (strcmp(name.begin(), "startPar") == 0) 
    return &seq->rStartPar;
  if (strcmp(name.begin(), "stopPar")  == 0) 
    return &seq->rStopPar;
  if (strcmp(name.begin(), "speed")    == 0) 
    return &seq->rSpeed;
  if (strcmp(name.begin(), "weight")   == 0) 
    return &seq->rSpeed;

  NI_ALWAYS_ASSERT("Unknown field in AnimGraph sequence!");
  return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *DiAnGrExtPars::getNodeFieldAddress(const EditorDependency &dep, DiAnimGraph &animGraph)
{
  DIASSERT(EditorGraphParamAddress::VT_NODE == dep.internalParam.type);

  DiAnimNode   *node = animGraph.GetNodeData(dep.internalParam.nodeIdx);
  const string &name = dep.internalParam.paramName;
  return node->GetNodeFieldAddress( name );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *DiAnGrExtPars::getTransactionFieldAddress(const EditorDependency &dep, DiAnimGraph &animGraph)
{
  DIASSERT(EditorGraphParamAddress::VT_TRANSACTION == dep.internalParam.type);

  DiUInt32          edgeID = animGraph.GetMTransactionID(dep.internalParam.nodeIdx, dep.internalParam.nextNodeIdx);
  DiAnimFlTransaction *trans = animGraph.GetTransactionData(edgeID, dep.internalParam.subTransIdx);

  const string &name = dep.internalParam.paramName;
  if (strcmp(name.begin(), "speed")   == 0) return &trans->rSpeed;
  if (strcmp(name.begin(), "parA")    == 0) return &trans->rParA;
  if (strcmp(name.begin(), "parB")    == 0) return &trans->rParB;
  if (strcmp(name.begin(), "fromMin") == 0) return &trans->rFromParamMin;
  if (strcmp(name.begin(), "fromMax") == 0) return &trans->rFromParamMax;
  if (strcmp(name.begin(), "toParam") == 0) return &trans->rToParam;

  NI_ALWAYS_ASSERT("Unknown field in AnimGraph transaction!");
  return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// constructor
DiAnGrExtPars::DiAnGrExtPars(const vector<EditorDependency> &_dependencies, 
                             const vector<EditorExternalParam> &_extParsInitialValues,
                             DiAnimGraph &_animGraph, bool saveDataForEditor) : animGraph(&_animGraph), editorOnlyDependencies(NULL), editorOnlyParameters(NULL)
{
  InternalConstructor(_dependencies, _extParsInitialValues, _animGraph);
  if (saveDataForEditor)
  {
    editorOnlyDependencies = new vector<EditorDependency>(_dependencies);
    editorOnlyParameters   = new vector<EditorExternalParam>(_extParsInitialValues);
  }
}
void DiAnGrExtPars::InternalConstructor(const vector<EditorDependency> &_dependencies, 
                             const vector<EditorExternalParam> &_extParsInitialValues,
                             DiAnimGraph &_animGraph)
{
  dependencies.reserve(_dependencies.size());
  for (int i = 0; i < _dependencies.size(); i++)
  {
    RuntimeDependency newDep;

    newDep.fieldToFill = getFieldAddress(_dependencies[i], _animGraph);
    newDep.multipler = 1.0f;
    newDep.multipler = GetNodeMultipler( _dependencies[i], _animGraph );

    DIASSERT(newDep.fieldToFill != NULL);
    
    for (int j = 0; j < _dependencies[i].externalParams.size(); j++)
    {
      int extParID = s_err;
      if (_dependencies[i].externalParams[j].name == s_constant)
      {
        // constant's coefficient = 1.0f!
        extParams.push_back(RuntimeExternalParam(_dependencies[i].externalParams[j].name, 1.0f));
        extParID = extParams.size() - 1;
      }
      else
      {
        extParID = getExtParID(_dependencies[i].externalParams[j].name);
        if (s_err == extParID)
        {
          extParams.push_back(RuntimeExternalParam(_dependencies[i].externalParams[j].name, s_extParDefaultValue));
          extParID = extParams.size() - 1;
          DIASSERT(extParams.size() - 1 == getExtParID(_dependencies[i].externalParams[j].name));
        }
      }

      RuntimeExternalParamLink newExtParLink(_dependencies[i].externalParams[j].coeff, extParID);
      newDep.externalParams.push_back(newExtParLink);
    }
    dependencies.push_back(newDep);
  }

  // process all given external params
  for (int i = 0; i < _extParsInitialValues.size(); i++)
  {
    int extParID = getExtParID(_extParsInitialValues[i].name);
    //DIASSERT(extParID != s_err); // found unused external parameter Commented by EugBel - this assert annoys very much!
    if (s_err != extParID)
    {
      setExtParValue(extParID,        _extParsInitialValues[i].initialValue);
      setExtParDefaultValue(extParID, _extParsInitialValues[i].initialValue);
    } 
  }
}

void DiAnGrExtPars::AddFormulaIfExists(const NDb::AnGrFormula &formula, string paramName, EditorGraphParamAddress::OwnerType type, int nodeIdx, int nextNodeIdx, 
                                       int subTransIdx, int subNodeIdx, nstl::vector<EditorDependency> &editorOnlyDependencies)
{
  if (formula.coeffs.empty())
    return;

  DiAnGrExtPars::EditorDependency newDep;
  
  newDep.internalParam.type         = type;
  newDep.internalParam.nodeIdx      = nodeIdx;
  newDep.internalParam.nextNodeIdx  = nextNodeIdx;
  newDep.internalParam.subTransIdx  = subTransIdx;
  newDep.internalParam.subNodeIdx   = subNodeIdx;
  newDep.internalParam.paramName    = paramName;

  newDep.externalParams.reserve(formula.coeffs.size() + 1);

  for (int j = 0; j < formula.coeffs.size(); j++)
  {
    const NDb::AnGrExternalParameterCoeff &srcCoeff = formula.coeffs[j];

    DiAnGrExtPars::EditorExternalParamLink newLink(srcCoeff.name, srcCoeff.value);
    newDep.externalParams.push_back(newLink);
  }
  DiAnGrExtPars::EditorExternalParamLink newLink("CONSTANT", formula.value);
  newDep.externalParams.push_back(newLink);


  editorOnlyDependencies.push_back(newDep);
}

void DiAnGrExtPars::ExtractFormulasFromNode(int nodeIdx, const NDb::AnGrMacronode &node, nstl::vector<EditorDependency> &editorOnlyDependencies)
{
  //   * FOR NODES:'speed','startPar','stopPar'. 
  //AddFormulaIfExists(node.speed,    "speed",    EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, -1, editorOnlyDependencies);
  //AddFormulaIfExists(node.startPar, "startPar", EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, -1, editorOnlyDependencies);
  //AddFormulaIfExists(node.stopPar,  "stopPar",  EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, -1, editorOnlyDependencies);


  //   * FOR SEQUENCES:'startPar','stopPar','speed','weight'.")]
  {
    AddFormulaIfExists(node.startPar,  "startPar", EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, 0, editorOnlyDependencies);
    AddFormulaIfExists(node.stopPar,   "stopPar",  EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, 0, editorOnlyDependencies);
    AddFormulaIfExists(node.speed,     "speed",    EditorGraphParamAddress::VT_NODE, nodeIdx, -1, -1, 0, editorOnlyDependencies);
  }

  for (int i = 0; i < node.simpleTransactions.size(); i++)
  {
    const NDb::AnGrFlMultiTransaction &multiTrans = node.simpleTransactions[i];
    int nextNodeId = animGraph->GetNodeIDByNameSlow(multiTrans.targetNode.c_str());
    //   * FOR TRANSACTIONS:'speed','parA,'parB','fromMin','fromMax','toParam'. 
    const NDb::AnGrFlTransaction &trans = node.simpleTransactions[i].parameters;
    //AddFormulaIfExists(trans.speed,     "speed",   EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  j, -1, editorOnlyDependencies);    
    AddFormulaIfExists(trans.parA,      "parA",    EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  0, -1, editorOnlyDependencies);    
    AddFormulaIfExists(trans.parB,      "parB",    EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  0, -1, editorOnlyDependencies);    
    AddFormulaIfExists(trans.fromMin,   "fromMin", EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  0, -1, editorOnlyDependencies);    
    AddFormulaIfExists(trans.fromMax,   "fromMax", EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  0, -1, editorOnlyDependencies);    
    AddFormulaIfExists(trans.toParam,   "toParam", EditorGraphParamAddress::VT_TRANSACTION, nodeIdx, nextNodeId,  0, -1, editorOnlyDependencies);    
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// constructor (to fill by XDB data)
DiAnGrExtPars::DiAnGrExtPars(const NDb::AnimGraphCreator *_agCreator, DiAnimGraph *_animGraph)
{
  if (NULL == _animGraph)
  {
    DIASSERT_ALOOF_CODE(_animGraph->GetDBFileName());
    return;
  }
  animGraph = _animGraph;

  // Plan: convert data from Creator into DiAnGrExtPars::EditorXXX structures
  // 1. external parameters
  editorOnlyParameters = new nstl::vector<EditorExternalParam>;
  // 2. external dependencies
  editorOnlyDependencies = new nstl::vector<EditorDependency>;

  //if (NULL != _agCreator)
  //{
  //  // 1. save array of external parameters
  //  int extParamSize = 0;
  //  if ( _agCreator->extParameters )
  //    extParamSize = _agCreator->extParameters->parameters.size();

  //  editorOnlyParameters->reserve( extParamSize );
  //  for (int i = 0; i < extParamSize; i++)
  //  {
  //    const NDb::AnGrExternalParameter &srcPar = _agCreator->extParameters->parameters[i];
  //    DiAnGrExtPars::EditorExternalParam newPar(srcPar.paramName, srcPar.defaultValue);

  //    editorOnlyParameters->push_back(newPar);
  //  }

  //  // 2. save array of external editorOnlyDependencies

  //  // parse all nodes and search for formulas
  //  for (int nodeIdx = 0; nodeIdx < _agCreator->macroNodes.size(); nodeIdx++)
  //  {
  //    ExtractFormulasFromNode(nodeIdx, _agCreator->macroNodes[nodeIdx], *editorOnlyDependencies);
  //  }

  //} // end of if (NULL != _agCreator)

  // call native constructor
  InternalConstructor(*editorOnlyDependencies, *editorOnlyParameters, *_animGraph);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DiAnGrExtPars::getExtParID(const string &name)
{
  if (name == s_constant)
    return s_err; // each constant should be different parameter, can't use the system name (s_constant) to detect parameter

  for (int i = 0; i < extParams.size(); i++)
  {
    if (strcmp(extParams[i].name.begin(), name.begin()) == 0)
      return i;
  }

  return s_err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// destructor
DiAnGrExtPars::~DiAnGrExtPars()
{
  // Clear common data
  for (int i = 0; i < dependencies.size(); i++)
  {
    dependencies[i].externalParams.clear();    
  }
  dependencies.clear();
  extParams.clear();

  // Clear editor only data
  if (editorOnlyDependencies != NULL)
  {
    for (int i = 0; i < editorOnlyDependencies->size(); i++)
    {
      (*editorOnlyDependencies)[i].externalParams.clear();    
    }
    editorOnlyDependencies->clear();
    delete editorOnlyDependencies;
    editorOnlyDependencies = NULL;
  }
  if (editorOnlyParameters != NULL)
  {
    editorOnlyParameters->clear();
    delete editorOnlyParameters;
    editorOnlyParameters = NULL;
  }

  animGraph = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnGrExtPars::restart()
{
  // 1. set external parameters to their default values
  for (int i = 0; i < extParams.size(); ++i)
    extParams[i].value = extParams[i].defaultValue;

  // 2. apply dependencies to graph
  if (hasGraph())
    applyParamsToGraph();
}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnGrExtPars::applyParamsToGraph()
{
  ///eugbel/// @todo: Do not process params if external params don't change!!!
  for (int i = 0; i < dependencies.size(); i++)
  {
    DIASSERT(dependencies[i].fieldToFill != NULL);
    *(dependencies[i].fieldToFill) = dependencies[i].calcValue(extParams)*dependencies[i].multipler;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float DiAnGrExtPars::RuntimeDependency::calcValue(const vector<RuntimeExternalParam> &extParams)
{
  float res = 0.0f;
  for (int i = 0; i < externalParams.size(); i++)
  {
    res += externalParams[i].coeff * extParams[externalParams[i].extParID].value;
  }

  return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  DiAnGrExtPars::getExtParIDByName(const char *extParName)
{
  for (int i = 0; i < extParams.size(); i++)
    if (strcmp(extParName, extParams[i].name.begin()) == 0)
      return i;

  return s_err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return true on success, false otherwise
bool  DiAnGrExtPars::setExtParValue(const char *extParName, float _value)
{
  for (int i = 0; i < extParams.size(); i++)
    if (strcmp(extParName, extParams[i].name.begin()) == 0)
    {
      extParams[i].value = _value;
      return true;
    }

  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float DiAnGrExtPars::getExtParValue(const char *extParName)
{
  for (int i = 0; i < extParams.size(); i++)
    if (strcmp(extParName, extParams[i].name.begin()) == 0)
      return extParams[i].value;

  DIASSERT_ALOOF_CODE("-");
  return s_errorValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  DiAnGrExtPars::setExtParValue(int extParID, float _value)
{
  DIASSERT(0 <= extParID && extParID < extParams.size());

  extParams[extParID].value = _value;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float DiAnGrExtPars::getExtParValue(int extParID)
{
  DIASSERT(0 <= extParID && extParID < extParams.size());

  return extParams[extParID].value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool   DiAnGrExtPars::setExtParDefaultValue(int extParID, float _value)
{
  if(0 <= extParID && extParID < extParams.size())
  {
    extParams[extParID].defaultValue = _value;
    return true;
  }

  DIASSERT(!"Invalid external parameter index!")
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alexander Tveretinov////////////FUNCTIONS FOR DependenciesStorage CLASS ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void DiAnGrExtPars::DependenciesStorage::ClearStorage()
{
  m_dependencies.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Reserves a minimum length of storage for a vector object, allocating space if necessary.
void DiAnGrExtPars::DependenciesStorage::ReserveMemoryForStorage(int size)
{
  if ( size < 0 )
    return;
  
  m_dependencies.reserve( size );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this function adds a new dependency to the all dependencies.
void DiAnGrExtPars::DependenciesStorage::AddDependency(const EditorDependency& dependency)
{
  // check that new dependency doesn't duplicate existent dependency

  // find similar dependency
  EditorDependency *existentDep(NULL);
  for (int i = 0; i < m_dependencies.size(); i++)
  {
    if (m_dependencies[i].internalParam == dependency.internalParam)
    {
      existentDep = &m_dependencies[i];
      break;
    }
  }
  if (existentDep != NULL)
  {
    if (existentDep->externalParams.size() > 0)
    {
      DIASSERTMSG(false, "Filling same dependency second time! Fix this mistake in logic!");
      return;
    }

    existentDep->externalParams = dependency.externalParams;
  }
  else
  {
    m_dependencies.push_back( dependency );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this function returns the subsequence of dependencies from all Editor Dependencies by node ID and ownerType
vector<DiAnGrExtPars::EditorDependency*> DiAnGrExtPars::DependenciesStorage::GetDependencies(EditorGraphParamAddress::OwnerType ownerType, INT nodeIdx, INT nextNodeIdx /*= -1*/)
{
  vector<DiAnGrExtPars::EditorDependency*> result;

  vector<EditorDependency>::iterator it;
  for( it = m_dependencies.begin(); it != m_dependencies.end(); ++it)
  {
    //if it's a transaction
    if ( ((*it).internalParam.type == ownerType) && ((*it).internalParam.nodeIdx == nodeIdx) && ((*it).internalParam.nextNodeIdx == nextNodeIdx) )
    {      
      result.push_back( &(*it) );
    }    
    else //if it's a node
      if ( (*it).internalParam.type == ownerType && (*it).internalParam.nodeIdx == nodeIdx )
    {
      result.push_back( &(*it) );
    }    
  }//end of for

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this function returns all external parameters (vector externalParams) for specified node (transaction...) and specified name of field   of dependencies from all Editor Dependencies by node ID, ownerType and field name
vector<DiAnGrExtPars::EditorExternalParamLink>* DiAnGrExtPars::DependenciesStorage::GetExternalParams(EditorGraphParamAddress::OwnerType ownerType, string paramName, INT nodeIdx, INT nextNodeIdx/* = -1*/)
{
  vector<DiAnGrExtPars::EditorExternalParamLink>* result(NULL);

  vector<EditorDependency>::iterator it;
  for( it = m_dependencies.begin(); it != m_dependencies.end(); ++it)
  {
    //if it's a transaction
    if ( ((*it).internalParam.type == ownerType) && 
         (ownerType == EditorGraphParamAddress::VT_TRANSACTION) && 
         ((*it).internalParam.nodeIdx == nodeIdx) && ((*it).internalParam.nextNodeIdx == nextNodeIdx) )
    {      
      //now we should check the parameter name
      if ( (*it).internalParam.paramName.compare(paramName) == 0 )//if equal
      {      
        result = &(*it).externalParams;
        break;
      }
    }    
    else if ( ((*it).internalParam.type == ownerType) && 
              (ownerType == EditorGraphParamAddress::VT_NODE) &&
              (*it).internalParam.nodeIdx == nodeIdx )
    {
      //now we should check the parameter name
      if ( (*it).internalParam.paramName.compare(paramName) == 0 )//if equal
      {
        result = &(*it).externalParams;
        break;
      }        
    }
    else if ( ((*it).internalParam.type == ownerType) && 
      (ownerType == EditorGraphParamAddress::VT_ANIM_SEQUENCE) &&
      (*it).internalParam.nodeIdx == nodeIdx )
    {
      //now we should check the parameter name
      if ( (*it).internalParam.paramName.compare(paramName) == 0 )//if equal
      {
        result = &(*it).externalParams;
        break;
      }        
    }
  }//end of for

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nstl::vector<DiAnGrExtPars::EditorDependency> *DiAnGrExtPars::getEditorDependencies()
{
  return editorOnlyDependencies;
}
nstl::vector<DiAnGrExtPars::EditorExternalParam> *DiAnGrExtPars::getEditorExternalParams()
{
  return editorOnlyParameters;
}

//this function removes all linked with node(by nodeId) dependencies and all linked to this node edges
bool DiAnGrExtPars::DependenciesStorage::RemoveAllLinkedWithNodeDependencies(INT nodeId)
{
  //remove all edges (transactions) which are linked to this node with nodeId
  m_dependencies.erase( nstl::remove_if(m_dependencies.begin(), m_dependencies.end(), CCheckFunctor(nodeId, false)), m_dependencies.end());
  
  //remove node with nodeId
  m_dependencies.erase( nstl::remove_if(m_dependencies.begin(), m_dependencies.end(), CCheckFunctor(nodeId)), m_dependencies.end()); 
  
  return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//this function removes all edge dependencies
bool DiAnGrExtPars::DependenciesStorage::RemoveEdgeDependencies(INT nodeId, INT nextNodeId)
{
  //we are removing all dependencies for edge (nodeId, nextNodeId)
  m_dependencies.erase( nstl::remove_if(m_dependencies.begin(), m_dependencies.end(), CCheckFunctor(nodeId, false, nextNodeId)), m_dependencies.end());
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this function fills given vector with non-empty dependencies
void DiAnGrExtPars::DependenciesStorage::ExportNonEmptyDependencies(nstl::vector<DiAnGrExtPars::EditorDependency> &deps) const
{
  // Export non-empty dependencies and add constant to every dependency
  deps.clear();

  deps.reserve(m_dependencies.size());
  for (int i = 0; i < m_dependencies.size(); i++)
  {
    if (!m_dependencies[i].isEmpty())
      deps.push_back(m_dependencies[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *DiAnGrExtPars::getConstantString()
{
  return s_constant.c_str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DiAnGrExtPars::hasGraph() const
{
  return (animGraph != NULL);
}

float DiAnGrExtPars::GetNodeMultipler( const EditorDependency &dep, DiAnimGraph &animGraph )
{
  if (EditorGraphParamAddress::VT_NODE == dep.internalParam.type)
  {
    DiAnimNode   *node = animGraph.GetNodeData(dep.internalParam.nodeIdx);
    return 1.0f/node->GetMultiplier();
  }
  return 1.0f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///eugbelNSCENE///} // end of namespace NScene
