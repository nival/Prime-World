using System;
using System.Drawing;
using System.Windows.Forms;

namespace EditorLib.Wizards.TableDataEditing
{
  public partial class CheckedMenu : Form
  {
    private readonly Type[] types = new Type[0];
    private readonly Type[] selectedTypes = new Type[0];
    private bool supressEvents = false;

    public CheckedMenu()
    {
      InitializeComponent();
    }

    public CheckedMenu( Type[] _types, Type[] _selectedTypes )
      : this()
    {
      types = _types;
      selectedTypes = _selectedTypes;
    }

    public Type[] GetSelectedTypes()
    {
      Type[] result = new Type[lstArrayTypes.CheckedItems.Count];

      for( int i = 0; i < lstArrayTypes.CheckedItems.Count; i++ )
      {
        result[i] = (Type)lstArrayTypes.CheckedItems[i];
      }

      return result; 
    }

    private void CheckedMenu_Load( object sender, EventArgs e )
    {
      lstArrayTypes.DisplayMember = "Name";
      lstArrayTypes.Items.Clear();

      foreach( Type item in types )
      {
        int index = lstArrayTypes.Items.Add( item );

        if( Array.Exists( selectedTypes, x => x == item ) )
        {
          lstArrayTypes.SetItemChecked( index, true );
        }
      }

      RefreshSize();
      
      lstArrayTypes.Focus();
    }

    private void CheckedMenu_LocationChanged( object sender, EventArgs e )
    {
      if( supressEvents )
        return;

      RefreshSize();
    }

    private void RefreshSize()
    {
      supressEvents = true;

      int menuHeight = ( lstArrayTypes.Items.Count*( lstArrayTypes.ItemHeight + 2 ) ) + 20 +btnOk.Height + 2;
      Point menuLocation = Location;
      Rectangle screenArea = Screen.FromPoint( Location ).WorkingArea;

      if((screenArea.Height - menuLocation.Y < menuLocation.Y - screenArea.Top) && 
         (screenArea.Height - menuLocation.Y < menuHeight))
      {
        Location = new Point( menuLocation.X, menuLocation.Y > menuHeight ? menuLocation.Y - menuHeight : 0  );       
        menuHeight = menuLocation.Y - 10;
      }
      else if( menuLocation.Y + menuHeight > screenArea.Height )
      {
        menuHeight = screenArea.Height - menuLocation.Y - 10;
      }

      Height = menuHeight;
      Width = lstArrayTypes.PreferredSize.Width;

      supressEvents = false;
    }

		private void OnItemCheck( object sender, ItemCheckEventArgs e )
		{
			if(lstArrayTypes.Items.Count == 1 && e.Index == 0)
			{
				e.NewValue = CheckState.Checked;
			}
		}
  }
}
