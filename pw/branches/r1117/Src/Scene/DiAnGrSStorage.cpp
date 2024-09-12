#include "stdafx.h"

#include "DiAnGrSStorage.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///eugbelNSCENE///namespace NScene {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DiAnGrSimpleStorage::DeleteMe()
{
  // Delete nodes
  for (int i = 0; i < numMacronodes; i++)
    macronodes[i].DeleteMe();

  delete [] macronodes;
  macronodes = NULL;

  // Delete markers
  for (int i = 0; i < numMarkers; i++)
    markers[i].DeleteMe();

  delete [] markers;
  markers = NULL;

  // Delete external parameters
  for (int i = 0; i < numExtParams; i++)
    extParams[i].DeleteMe();

  delete [] extParams;
  extParams = NULL;

  // Delete external dependencies
  for (int i = 0; i < numExtDeps; i++)
    extDeps[i].DeleteMe();

  delete [] extDeps;
  extDeps = NULL;
}

void DiAnGrSimpleStorage::Marker::DeleteMe()
{
  delete [] name;
  name = NULL;
}

void DiAnGrSimpleStorage::ExternalParameter::DeleteMe()
{
  delete [] paramName;
  paramName = NULL;
}

void DiAnGrSimpleStorage::ExternalParameterCoeff::DeleteMe()
{
  delete [] paramName;
  paramName = NULL;
}

void DiAnGrSimpleStorage::ExternalDependency::DeleteMe()
{
  delete [] paramName;
  paramName = NULL;

  for (int i = 0; i < numElemsInFormula; i++)
    formula[i].DeleteMe();

  delete [] formula;
  formula = NULL;
}

void DiAnGrSimpleStorage::Macronode::DeleteMe()
{
  delete [] nodeName;
  nodeName = NULL;
  delete [] nextNodeName;
  nextNodeName = NULL;

  for (int i = 0; i < numSeqs; i++)
  {
    sequences[i].DeleteMe();
  }
  delete [] sequences;
  sequences = NULL;

  for (int i = 0; i < numTransactions; i++)
  {
    multiTransactions[i].DeleteMe();
  }
  delete [] multiTransactions;
  multiTransactions = NULL;
}

void DiAnGrSimpleStorage::Sequence::DeleteMe()
{
  delete [] sequenceName;
  sequenceName = NULL;
};

void DiAnGrSimpleStorage::MultiTransaction::DeleteMe()
{
  delete [] targetNodeName;
  targetNodeName = NULL;

  for (int i = 0; i < numTimes; i++)
  {
    timesAndParams[i].DeleteMe();
  }
  delete [] timesAndParams;
  timesAndParams = NULL;
};

void DiAnGrSimpleStorage::Transaction::DeleteMe()
{
  return;
}

///eugbelNSCENE///} // end of namespace NScene