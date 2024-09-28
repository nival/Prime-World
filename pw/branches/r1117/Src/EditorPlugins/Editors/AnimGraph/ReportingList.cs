using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace EditorPlugins.Editors.AnimGraph
{
  public class ReportingList<T> : Collection<T>
  {
    #region Enevts

    public delegate void ItemInserted(int _pos);
    public event ItemInserted OnItemInserted;

    public delegate void ItemDeleting(int _pos);
    public event ItemDeleting OnItemDeleting;

    public delegate void ListChanged();
    public event ListChanged OnListChanged;

    public delegate void ListCleared();
    public event ListCleared OnListCleared;

    private void RaiseOnItemInserted( int _index )
    {
      if( OnItemInserted != null )
        OnItemInserted( _index );
    }

    private void RaiseOnItemDeleting( int _index )
    {
      if( OnItemDeleting != null )
        OnItemDeleting( _index );
    }

    private void RaiseOnListChanged()
    {
      if( OnListChanged != null )
        OnListChanged();
    }

    private void RaiseOnListCleared()
    {
      if( OnListCleared != null )
        OnListCleared();
    }

    #endregion

    public ReportingList()
    {
    }

    public ReportingList(IList<T> _list)
      : base(_list)
    {
    }

    protected override void InsertItem( int _index, T _item )
    {
      base.InsertItem( _index, _item );

      RaiseOnItemInserted( _index );
      RaiseOnListChanged();
    }

    protected override void RemoveItem( int _index )
    {
      RaiseOnItemDeleting( _index );
      base.RemoveItem( _index );
      RaiseOnListChanged();
    }

    protected override void ClearItems()
    {
      base.ClearItems();
      RaiseOnListCleared();
      RaiseOnListChanged();
    }
  }
}
