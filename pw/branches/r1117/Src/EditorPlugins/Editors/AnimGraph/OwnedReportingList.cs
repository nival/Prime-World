using System;
using System.Collections.Generic;
using libdb;

namespace EditorPlugins.Editors.AnimGraph
{
  public interface IOwnedListElement<T>
  {
    T Owner { get; set; }
  }

  public class OwnedReportingList<T, TOwner> : ReportingList<T>, IRichList, IList<T>
    where T : IOwnedListElement<TOwner>
  {
    private readonly TOwner owner;
    private readonly int minCount = 0;
    private readonly int maxCount = 0;

    public OwnedReportingList(TOwner _owner)
      : this(_owner, 0, 0) { }

    public OwnedReportingList(TOwner _owner, int _minCount)
      : this(_owner, _minCount, 0) { }

    public OwnedReportingList(TOwner _owner, int _minCount, int _maxCount)
    {
      owner = _owner;
      minCount = _minCount;
      maxCount = _maxCount;
    }

    protected override void SetItem(int _index, T _item)
    {
      _item.Owner = owner;
      base.SetItem(_index, _item);
    }

    protected override void InsertItem( int _index, T _item )
    {
      //тут не возникает события вставки в лист и изменения листа, т.к. это изменение ЭЛЕМЕНТА листа
      _item.Owner = owner;
      base.InsertItem( _index, _item );
    }

    public Type EnumType { get { return null; } }

    public int MinCount { get { return minCount; } }
    public int MaxCount { get { return maxCount; } }

    public void ResetElement(int _index) { }
    public bool IsElementDerivedFromParent(int _index) { return true; }

    public bool CanAdd { get { return (maxCount == 0 || Count < maxCount); } }
    public bool CanInsert { get { return (maxCount == 0 || Count < maxCount); } }
    public bool CanDelete { get { return (Count > minCount); } }
    public bool CanMoveItems { get { return false; } }
  }
}
