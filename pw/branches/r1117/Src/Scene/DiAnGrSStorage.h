#pragma once

#include "DiAnGrUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {

// Forward declaration
//struct DiAnGrNodesMap;

#define NODE_NAME_SIZE 50

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This structure is a C-style copy of class AnimGraphCreator which is used to work with XDB data.
// This structure is to pass data from C++ panel to C# Editor using marshalling mechanism.
struct DiAnGrSimpleStorage
{
  struct Sequence
  {
    char  *sequenceName;
    float startPar;
    float stopPar;
    float speed;
    float weight;

    Sequence() : sequenceName(NULL), startPar(MAX_FLOAT), stopPar(MAX_FLOAT), speed(MAX_FLOAT), weight(MAX_FLOAT)
    { }
    void DeleteMe();
  };

  struct Transaction // simple transaction
  {
    int   updateType; // for float transaction only
    int   kind;
    float parA;
    float parB;
    float fromMin;
    float fromMax;
    float toParam;
    float speed;

    Transaction() : updateType(-1), kind(-1), parA(MAX_FLOAT), parB(MAX_FLOAT),
                    fromMin(MAX_FLOAT), fromMax(MAX_FLOAT), toParam(MAX_FLOAT), speed(MAX_FLOAT)
    { }
    void DeleteMe();
  };

  struct MultiTransaction
  {
    char *targetNodeName;
    float priority;
    int   probability;

    Transaction *timesAndParams;
    int         numTimes;

    MultiTransaction() : targetNodeName(NULL), priority(MAX_FLOAT), probability(-1), timesAndParams(NULL), numTimes(-1)
    { }
    void DeleteMe();
  };

  struct Macronode
  {
    char              *nodeName;	 
    char              *nextNodeName;	 
    float             speed;
    float             surfSpeedX;
    float             surfSpeedY;
    float             startPar;
    float             stopPar;
    
    Sequence          *sequences;
    int               numSeqs;

    MultiTransaction  *multiTransactions;
    int               numTransactions;

    int               posX;
    int               posY;
    
    Macronode() : nodeName(NULL), nextNodeName(NULL), speed(MAX_FLOAT), 
                  surfSpeedX(MAX_FLOAT), surfSpeedY(MAX_FLOAT),
						      startPar(MAX_FLOAT), stopPar(MAX_FLOAT), sequences(NULL), 
                  numSeqs(-1), multiTransactions(NULL), numTransactions(-1),
                  posX(-1111), posY(-1111)
    { }
    void DeleteMe();
  };

  struct Marker
  {
    char  *name;
    int   markerOwner; // 0 - node, 1 - transaction
    int   nodeIdx;
    int   transIdx;
    int   subTransIdx;
    float virtPar;

    Marker() : name(NULL), markerOwner(-1), nodeIdx(-1), transIdx(-1), subTransIdx(-1), virtPar(MAX_FLOAT)
    { }
    void DeleteMe();
  };

  struct ExternalParameter
  {
    char    *paramName;
    float   defaultValue;

    ExternalParameter() : paramName(NULL), defaultValue(MAX_FLOAT)
    { }
    void DeleteMe();
  };

  struct ExternalParameterCoeff
  {
    char    *paramName;
    float   coeff;

    ExternalParameterCoeff() : paramName(NULL), coeff(MAX_FLOAT)
    { }
    void DeleteMe();
  };

  struct ExternalDependency
  {
    int     dependencyOwner; // 0 - node, 1 - transaction
    int     nodeIdx;
    int     nextNode;
    int     subTransIdx;
    int     subNodeIdx;
    char    *paramName; // "Name of the parameter. FOR NODES:'speed','startPar','stopPar'. FOR TRANSACTIONS:'speed','parA,'parB','fromMin','fromMax','toParam'. FOR SEQUENCES:'startPar','stopPar','speed','weight'."

    ExternalParameterCoeff *formula;
    int                    numElemsInFormula;

    ExternalDependency() : dependencyOwner(-1), nodeIdx(-1), nextNode(-1), subTransIdx(-1), subNodeIdx(-1), paramName(NULL),
                           formula(NULL), numElemsInFormula(-1)
    { }
    void DeleteMe();
  };

  //////////////////////////////////////////////////////////////////////////

  int                 numParts; // now always equal to 1
  
  // Nodes' and transactions' data
  Macronode           *macronodes;
  int                 numMacronodes;
  
  // Markers' data
  Marker              *markers;
  int                 numMarkers;

  // External parameters' data
  ExternalParameter   *extParams;
  int                 numExtParams;

  // External dependencies' data
  ExternalDependency  *extDeps;
  int                 numExtDeps;

  DiAnGrSimpleStorage() : numParts(-1), macronodes(NULL), numMacronodes(-1), 
                          markers(NULL), numMarkers(-1),
                          extParams(NULL), numExtParams(-1),
                          extDeps(NULL), numExtDeps(-1)
  { }
  void DeleteMe();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///eugbelNSCENE///} // end of namespace NScene

