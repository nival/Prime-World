using System;
using libdb;

namespace EditorPlugins.Editors.AnimGraph
{
  public class OutlinerReadOnlyList<T> : ReportingList<T>, IRichList
	{
    public bool CanAdd { get { return false; } }
    public bool CanInsert { get { return false; } }
		public bool CanDelete { get { return false; } }
    public bool CanMoveItems { get { return false; } }

    public Type EnumType { get { return null; } }
    public int MinCount { get { return 1; } }
    public int MaxCount { get { return 0; } }

    public void ResetElement( int _index ) { }
    public bool IsElementDerivedFromParent( int _index ) { return true; }
  }
}
