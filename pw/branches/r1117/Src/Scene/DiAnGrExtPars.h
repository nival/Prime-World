#pragma once
//#include "DiAnGr.h"
#include "DiAnGrUtils.h"
#include "DiAnGrExtParsAd.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
class DiAnimGraph;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DiAnGrExtPars
{
public:

  struct EditorExternalParamLink
  {
    string    name;  // name of the external parameter
    float     coeff; // it's influence in the concrete dependency

    EditorExternalParamLink(): name(""), coeff(0.0){}
    EditorExternalParamLink(const string &_name, float _coeff);
    EditorExternalParamLink(float _constantValue); // This is the way to define a constant
  };

  struct EditorExternalParam
  {
    string    name;  // name of the external parameter
    float     initialValue; // external parameter value

    EditorExternalParam() : name(""), initialValue(MAX_FLOAT) {}
    EditorExternalParam(const string &_name, float _initialValue);
  };

  struct EditorDependency
  {    
    EditorGraphParamAddress          internalParam;
    vector<EditorExternalParamLink> externalParams;

    bool isEmpty() const
    {
      return (externalParams.size() == 0);
    }
  };

  //=========================================================================================
  // Alexander Tveretinov:
  // this structure is functionality interface 
  struct IDependenciesManager
  {
    virtual void ClearStorage() = 0;

    //Reserves a minimum length of storage for a vector object, allocating space if necessary.
    virtual void ReserveMemoryForStorage(int size) = 0;

    //this function adds a new dependency to the all dependencies.
    virtual void AddDependency(const EditorDependency& dependency) = 0;    

    //this function returns the subsequence of dependencies from all Editor Dependencies by node ID and ownerType
    virtual vector<EditorDependency*> GetDependencies(EditorGraphParamAddress::OwnerType ownerType, INT nodeIdx, INT nextNodeIdx = -1) = 0;

    //this function returns all external parameters (vector externalParams) for specified node (transaction...) and specified name of field   of dependencies from all Editor Dependencies by node ID, ownerType and field name
    virtual vector<EditorExternalParamLink>* GetExternalParams(EditorGraphParamAddress::OwnerType ownerType, string paramName, INT nodeIdx, INT nextNodeIdx = -1) = 0;

    //this function removes all linked with node(by nodeId) dependencies and all linked to this node edges
    virtual bool RemoveAllLinkedWithNodeDependencies(INT nodeId) = 0;

    //this function removes all edge dependencies
    virtual bool RemoveEdgeDependencies(INT nodeId, INT nextNodeId) = 0;
  };

  //=========================================================================================
  // Alexander Tveretinov:
  // This class will contain all dependencies and functionality 
  class DependenciesStorage : public IDependenciesManager
  {  
    vector<EditorDependency> m_dependencies;

    public:
      
      void ClearStorage();

      //Reserves a minimum length of storage for a vector object, allocating space if necessary.
      void ReserveMemoryForStorage(int size);

      //this function adds a new dependency to the all dependencies.
      void AddDependency(const EditorDependency& dependency);

      //this function returns the subsequence of dependencies from all Editor Dependencies by node ID and ownerType
      vector<EditorDependency*> GetDependencies(EditorGraphParamAddress::OwnerType ownerType, INT nodeIdx, INT nextNodeIdx = -1);
      
      //this function returns all external parameters (vector externalParams) for specified node (transaction...) and specified name of field   of dependencies from all Editor Dependencies by node ID, ownerType and field name
      vector<EditorExternalParamLink>* GetExternalParams(EditorGraphParamAddress::OwnerType ownerType, string paramName, INT nodeIdx, INT nextNodeIdx = -1);

      //this function removes all linked with node(by nodeId) dependencies and all linked to this node edges
      bool RemoveAllLinkedWithNodeDependencies(INT nodeId);

      //this function removes all edge dependencies
      bool RemoveEdgeDependencies(INT nodeId, INT nextNodeId);

      // this function fills given vector with non-empty dependencies
      void ExportNonEmptyDependencies(vector<EditorDependency> &deps) const;

    private:      
      class CCheckFunctor
      {
        private:
          INT m_nodeId;
          INT m_nextNodeId;
          bool m_checkNode; 
        public:
          explicit CCheckFunctor( INT nodeId, bool checkNode = true, INT nextNodeId = -1 ) 
            : m_nodeId(nodeId)
            , m_checkNode(checkNode)
            , m_nextNodeId(nextNodeId) {}

          bool operator() (const EditorDependency& dep) const
          {
            //we will check the edge with 2 parameters: from node m_nodeId, to node m_nextNodeId
            if ( m_nextNodeId >= 0 )
            {
              return (dep.internalParam.nodeIdx == m_nodeId) && (dep.internalParam.nextNodeIdx == m_nextNodeId);
            }
            
            //if we will check only node
            if ( m_checkNode )
            {               
                return dep.internalParam.nodeIdx == m_nodeId;
            }
            else //look for the in/out edge to/from node with n_nodeId. Example: m_nodeId = 0, we look for all edges with one point == 0 => (0, 1), (2,0), (4, 0)...
              return (dep.internalParam.nodeIdx == m_nodeId) || (dep.internalParam.nextNodeIdx == m_nodeId);
          }
      }; 
  };

  //=========================================================================================
  struct RuntimeExternalParamLink
  {
    float     coeff; // coefficient of this external parameter (if 0.0f then this parameter affects nothing)
    int       extParID; // external parameter index

    RuntimeExternalParamLink();
    RuntimeExternalParamLink(float coeff, int extParID);
  };

  struct RuntimeExternalParam
  {
    string    name;  // 
    float     value; // external parameter value
    float     defaultValue;

    RuntimeExternalParam(const string &_name, float _initialValue);

    RuntimeExternalParam() : name(""), value(MAX_FLOAT), defaultValue(MAX_FLOAT) {}
  };

  struct RuntimeDependency
  {
    float                            *fieldToFill;
    //TODO
    float multipler;
    nstl::vector<RuntimeExternalParamLink> externalParams;

    float calcValue(const nstl::vector<RuntimeExternalParam> &extParams);
  };


private:
  /// Data
  nstl::vector<RuntimeDependency>    dependencies;
  nstl::vector<RuntimeExternalParam> extParams;
  DiAnimGraph                  *animGraph;

  // Next two pointers are valid ONLY in Editor
  nstl::vector<EditorDependency>     *editorOnlyDependencies;
  nstl::vector<EditorExternalParam>  *editorOnlyParameters;

public:
  // constructor (for "manual" filling)
  DiAnGrExtPars(const nstl::vector<EditorDependency> &_dependencies, 
                const nstl::vector<EditorExternalParam> &_extParsInitialValues,
                DiAnimGraph &_animGraph, bool saveDataForEditor = false);
  void InternalConstructor(const nstl::vector<EditorDependency> &_dependencies, 
                const nstl::vector<EditorExternalParam> &_extParsInitialValues,
                DiAnimGraph &_animGraph);

  // constructor (to fill by XDB data)
  DiAnGrExtPars(const NDb::AnimGraphCreator *agCreator, DiAnimGraph *_animGraph);

  // destructor
  ~DiAnGrExtPars();
  float *getFieldAddress(const EditorDependency &_dependency, DiAnimGraph &animGraph);
  float *getNodeFieldAddress(const EditorDependency &dep, DiAnimGraph &animGraph);
  float *getTransactionFieldAddress(const EditorDependency &_dependency, DiAnimGraph &animGraph);
  float *getAnimSequenceFieldAddress(const EditorDependency &dep, DiAnimGraph &animGraph);
  
  bool  hasGraph() const;
  void  applyParamsToGraph();
  void  restart();

  static const char *getConstantString();

  // Working with external parameters
  int  getExtParIDByName(const char *extParName);

  float GetNodeMultipler(const EditorDependency &dep, DiAnimGraph &animGraph);

  bool  setExtParValue(const char *extParName, float value);
  float getExtParValue(const char *extParName);
  
  bool  setExtParValue(int extParID, float value);
  float getExtParValue(int extParID);

  bool  setExtParDefaultValue(int extParID, float value);

  nstl::vector<EditorDependency>     *getEditorDependencies();
  nstl::vector<EditorExternalParam>  *getEditorExternalParams();

  // Reading methods
  void AddFormulaIfExists(const NDb::AnGrFormula &formula, string paramName, EditorGraphParamAddress::OwnerType type, int nodeIdx, int nextNodeIdx, int subTransIdx, int subNodeIdx, 
                          nstl::vector<EditorDependency> &editorOnlyDependencies);
  void ExtractFormulasFromNode(int nodeIdx, const NDb::AnGrMacronode &node, nstl::vector<EditorDependency> &editorOnlyDependencies);

  
private:
  int getExtParID(const string &name);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///eugbelNSCENE///} // end of namespace NScene

