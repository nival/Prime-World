using System.Collections.Generic;
using DBTypes;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;

namespace EditorPlugins.Editors.AnimGraph
{
  public interface IAgController
  {
    void SetInvalid();
    bool IsValid();
    void PlayNodes(IList<int> _nodeIndices, float loopTime);
    void SetGlobalSpeed(float _speed);
    int GetCurTargetNode();
    void SetFlTransactionsInfo(int _indexFrom, int _indexTo, int _partIndex, AnGrFlTransaction _partInfo);
    void SetNodeInfo(int _nodeIndex, AnGrMacronode _nodeInfo);
    void SetSequenceInfo(int _nodeIndex, int _seqIndex, AnGrFormula _startPar, AnGrFormula _stopPar, AnGrFormula _speed, string _sequenceName);
    void SetFlMultiTransactionsInfo(int _indexFrom, int _indexTo, AnGrFlMultiTransaction _transInfo);
    DBID DbId { get; }
    IList<AnimInfo> GetAnimInfos();
    void SwitchToAnims();
    void SwitchToAg();
  }
}
