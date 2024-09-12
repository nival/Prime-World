using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorLib.Utils;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Editors.AnimGraph;
using libdb.Diagnostics;

namespace EditorPlugins.Scene.Viewers
{
	public partial class AnimationsSelectionPanel : UserControl
  {
		#region class AnimationInfo

		private sealed class AnimationInfo
		{
      public int Index { get; private set; }
      public string FileName { get; private set; }
      public string Name { get; private set; }
      public int Frames { get; private set; }
      public float Seconds { get; private set; }
      

  		public AnimationInfo( Animation animation, int index, int frames, float sec)
			{
        Name = animation.name;
        FileName = animation.srcFileName.FileName;
  		  Index = index;
  		  Frames = frames;
        Seconds = sec;
			}

			public override string ToString()
			{
				if ( !IsValid )
					return "WARNING: Invalid animation";

				return FileName;
			}

			public bool IsValid { get { return !string.IsNullOrEmpty(FileName); } }
		}

		#endregion

		#region Private members.

		private IAnimationSelectionPanelExtension controller;
    private readonly ListViewColumnSorter lvwColumnSorter;

		#endregion

		#region Initialization.

		public AnimationsSelectionPanel() : base()
		{
			InitializeComponent();
      lvwColumnSorter = new ListViewColumnSorter();
      animationsListView.ListViewItemSorter = lvwColumnSorter;
		}

		#endregion

		#region Event handlers.

		private void OnPlayClick( object sender, EventArgs e )
		{
      if(animationsListView.SelectedItems.Count > 0)
      {
        AnimationInfo animation = animationsListView.SelectedItems[0].Tag as AnimationInfo;
			  if ( animation != null && IsValid )
			  {
				  controller.StartAnimation( animation.Index );
				  controller.PauseAnimation( false );
			  } 
      }
		}

    private void OnHeaderClick(object sender, ColumnClickEventArgs e)
    {
      // Determine if clicked column is already the column that is being sorted.
      if (e.Column == lvwColumnSorter.SortColumn)
      {
        // Reverse the current sort direction for this column.
        if (lvwColumnSorter.Order == SortOrder.Ascending)
        {
          lvwColumnSorter.Order = SortOrder.Descending;
        }
        else
        {
          lvwColumnSorter.Order = SortOrder.Ascending;
        }
      }
      else
      {
        // Set the column number that is to be sorted; default to ascending.
        lvwColumnSorter.SortColumn = e.Column;
        lvwColumnSorter.Order = SortOrder.Ascending;
      }

			ListViewSortIconExtension.SetSortIcon( animationsListView, e.Column, lvwColumnSorter.Order );

      // Perform the sort with these new sort options.
      animationsListView.Sort();
    }

		#endregion

		#region Public & Internal properties

		internal IAnimationSelectionPanelExtension Controller
		{
			set
			{
				controller = value;
				RebuildAnimationsList();
			}
		}

		public bool MeasureInFrames { get; set; }

		#endregion

		#region Private helper methods and properties.

    private static AnimInfo FindAnimInfo(IEnumerable<AnimInfo> _animations, string _name)
    {
      foreach( var info in _animations )
      {
        if(info.animName == _name)
          return info;
      }
      return null;
    }

		public void RebuildAnimationsList()
		{
			if ( IsValid )
			{
        IList<AnimInfo> animInfos = controller.GetAnimInfos();

				controller.PauseAnimation( true );

				noResourceLabel.Visible = false;
				animationsListView.Visible = true;

        animationsListView.Items.Clear();

  			IList<Animation> animations = controller.Items;

				for ( int i = 0; i < animations.Count; ++i )
				{
				  AnimInfo inf = FindAnimInfo( animInfos, animations[i].name );

          if(inf == null) continue;

					AnimationInfo animation = new AnimationInfo( animations[i], i, inf.animFrames, inf.animLength);

					if ( animation.IsValid )
					{
            //если имя анимации по какимто причинам отсутствует пишем имя файла
					  string itemText = string.IsNullOrEmpty(animation.Name) ? animation.FileName : animation.Name;

					  var item = new ListViewItem(itemText);
					  item.Tag = animation;

						if ( MeasureInFrames )
              item.SubItems.Add(animation.Frames.ToString());
            else
              item.SubItems.Add(animation.Seconds.ToString("##0.##"));

					  animationsListView.Items.Add(item);
					}
					else
						Log.TraceWarning( "There is invalid animation entry in resource \"{0}\" at index {1}", controller.ResourceId.Name, i );
				}

        if (animationsListView.Items.Count > 0)
				{
				  animationsListView.Items[0].Selected = true;
				}

        animationsListView.Columns[0].Width = -1;//Fit column header to item text

				animationsListView.Columns[1].Text = MeasureInFrames ? "Frames" : "Sec";
        animationsListView.Columns[1].Width = -2;//Fit column header to column text

				controller.PauseAnimation( false );
			}
			else
			{
				noResourceLabel.Visible = true;
        animationsListView.Visible = false;
			}
		}

		private bool IsValid
		{
			get { return !ReferenceEquals( controller, null ) && !ReferenceEquals( controller.Items, null ); }
		}

		#endregion
	}
}
