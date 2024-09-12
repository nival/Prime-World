using System;
using System.Collections.Generic;
using System.Windows.Forms;
using libdb.Diagnostics;

namespace EditorLib.ObjectsBrowser
{
	public partial class ItemSelectorForm<T> : Form
    where T : class
	{
		private readonly List<T> types;
    private readonly List<T> checkedItems;

		public ItemSelectorForm(IEnumerable<T> _items, IEnumerable<T> _checkedItems)
		{
			InitializeComponent();

			Log.Assert( _items != null, "_items can't be null" );

			types = new List<T>();
      if ( _items != null )
        types.AddRange(_items);

      checkedItems = new List<T>();
      if ( _checkedItems != null )
        checkedItems.AddRange(_checkedItems);

      AddItems( types );
		}

    protected override void OnLoad( EventArgs e )
    {
      base.OnLoad( e );
      UpdateItemsCheck();
      UpdateCheckedLabel();
    }

    #region Properties

    public List<T> SelectedItems
		{
			get
			{
				List<T> result = new List<T>();

        foreach ( T item in checkedItems )
				{
					result.Add( item );
				}
				
				return result;
			}
		}

		public bool IsAllSelected
		{
			get { return lstTypes.CheckedItems.Count == types.Count; }
		}

	  public string DisplayMember
	  {
      get { return lstTypes.DisplayMember; }
      set { lstTypes.DisplayMember = value; }
	  }

	  #endregion

    private void AddItems( List<T> _types )
		{
			lstTypes.Items.Clear();
			lstTypes.Items.AddRange( _types.ToArray() );
		}

		private void UpdateItemsCheck()
		{
      if ( checkedItems == null )
				return;

			for ( int index = 0; index < lstTypes.Items.Count; index++ )
			{
				T item = lstTypes.Items[index] as T;
			  lstTypes.SetItemChecked( index, checkedItems.Contains( item ) );
			}
		}

    private void UpdateCheckedLabel()
    {
      lblSelectedItems.Text = string.Join(", ", checkedItems.ConvertAll(x => lstTypes.GetItemText(x)).ToArray());
    }

		private void Filter(string _filter)
		{               
			if(string.IsNullOrEmpty(_filter))
			{
				AddItems( types );
			}
			else
			{
				List<T> filtered = types.FindAll(item => lstTypes.GetItemText( item ).ToLower().Contains( _filter.ToLower() ));
				AddItems( filtered );				
			}

      UpdateItemsCheck();
		  UpdateCheckedLabel();
		}

		#region Event Handlers

		private void OnCheckAllCheckedChanged(object sender, EventArgs e)
		{
			lstTypes.ItemCheck -= OnItemCheck;

		  checkedItems.Clear();
      
      if( chkCheckAll.Checked )
		    checkedItems.AddRange( types );

		  UpdateItemsCheck();
      UpdateCheckedLabel();
			lstTypes.ItemCheck += OnItemCheck;
		}

		private void OnItemCheck(object sender, ItemCheckEventArgs e)
		{
			chkCheckAll.CheckedChanged -= OnCheckAllCheckedChanged;

		  T item = lstTypes.Items[e.Index] as T;

			if(e.CurrentValue != CheckState.Checked && e.NewValue == CheckState.Checked)
			{ 
        //поставили галочку напротив элемента
        if(!checkedItems.Contains(item))
          checkedItems.Add( item );

        chkCheckAll.Checked = checkedItems.Count == types.Count;// будут установлены все галочки	      
			}
			else
			{
				//убрали галочку с элемента
				chkCheckAll.Checked = false;
			  checkedItems.Remove(item);
			}

		  UpdateCheckedLabel();
			chkCheckAll.CheckedChanged += OnCheckAllCheckedChanged;
		}

		private void OnFilterChanged( object sender, EventArgs e )
		{
			Filter(txtFilter.Text);
		}

		#endregion
	}
}
