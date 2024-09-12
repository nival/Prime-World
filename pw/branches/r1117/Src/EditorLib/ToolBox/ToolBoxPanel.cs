using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.Panels;

namespace EditorLib.ToolBox
{
	public sealed class ToolBoxPanel : EditorPanel
	{
		private readonly ToolBox toolBox = new ToolBox() { Dock = DockStyle.Fill };
    private EditorLib.Extensions.AbstractEditor activeEditor = null;
	
		public ToolBoxPanel()
		{
			TabText = "Tool Box";

			toolBox.ItemSelected += tag =>
			{
				if ( activeEditor != null )
				{
          activeEditor.OnSelectToolBoxItem( tag );
				}
			};

			toolBox.ItemAddClicked += tag =>
			{
				if ( activeEditor != null )
				{
          ToolBoxItem item = activeEditor.GetActiveItem();
          if ( item != null )
          {
            if ( item.category == string.Empty )
              item.category = (string)tag;

            AddItem( item, true );
          }
				}
			};

			Controls.Add( toolBox );

		}

		protected override bool Initialize( IEditorWinApplication application )
		{
			return true;
		}

		public void AddItem( ToolBoxItem item, bool userItem )
		{
      toolBox.AddItem( item, userItem );
		}

		public void Clear()
		{
			toolBox.Clear();
		}

    //public void SelectNull()
    //{
    //  toolBox.SelectNull();
    //}

		internal List<ToolBoxItem> UserToolBoxItems
		{
			get { return toolBox.UserItems; }
		}

    internal void InitRecentlyUsedToolBoxItems(List<string> items)
    {
      toolBox.InitRecentlyUsed(items);
    }

    internal List<string> RecentlyUsedToolBoxItems
    {
      get { return toolBox.RecentlyUsed; }
    }

    public void UpdateRecentlyUsed()
    {
      toolBox.UpdateRecentlyUsed();
    }

    public EditorLib.Extensions.AbstractEditor ActiveEditor
    {
      get { return activeEditor; }
      set
      {
        if ( activeEditor != value )
        {         
          Clear();
          activeEditor = value;
          toolBox.activeEditor = value;
        }
      }
    }
	}
}
