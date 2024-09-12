using System.Collections.Generic;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Editors.AnimGraph
{
  public class AgControllerWrapper : IAgController
  {
    private readonly AGController controller = null;

    public AgControllerWrapper(AGController _controller)
    {
      controller = _controller;
    }

    public void SetInvalid()
    {
      controller.SetInvalid();
    }

    public bool IsValid()
    {
      return controller.IsValid();
    }

    public void PlayNodes(IList<int> _nodeIndices, float loopTime)
    {
      controller.PlayNodes( _nodeIndices, loopTime );
    }

    public void SetGlobalSpeed(float _speed)
    {
      controller.SetGlobalSpeed(_speed);
    }

    public int GetCurTargetNode()
    {
      return controller.GetCurTargetNode();
    }

    public void SetFlTransactionsInfo(int _indexFrom, int _indexTo, int _partIndex, DBTypes.AnGrFlTransaction _partInfo)
    {
      controller.SetFlTransactionsInfo(_indexFrom, _indexTo, _partIndex, _partInfo);
    }

    public void SetNodeInfo(int _nodeIndex, DBTypes.AnGrMacronode _nodeInfo)
    {
      controller.SetNodeInfo(_nodeIndex, _nodeInfo);
    }

    public void SetSequenceInfo(int _nodeIndex, int _seqIndex, DBTypes.AnGrFormula _startPar, DBTypes.AnGrFormula _stopPar, DBTypes.AnGrFormula _speed, string _sequenceName)
    {
      controller.SetSequenceInfo(_nodeIndex, _seqIndex, _startPar, _stopPar, _speed, _sequenceName);
    }

    public void SetFlMultiTransactionsInfo(int _indexFrom, int _indexTo, DBTypes.AnGrFlMultiTransaction _transInfo)
    {
      controller.SetFlMultiTransactionsInfo(_indexFrom, _indexTo, _transInfo);
    }

    public libdb.DB.DBID DbId
    {
      get { return controller.DBID; }
    }

    public IList<AnimInfo> GetAnimInfos()
    {
      return controller.GetAnimInfos();
    }

    public void SwitchToAnims()
    {
      controller.SwitchToAnims();
    }

    public void SwitchToAg()
    {
      controller.SwitchToAG();
    }
  }
}
