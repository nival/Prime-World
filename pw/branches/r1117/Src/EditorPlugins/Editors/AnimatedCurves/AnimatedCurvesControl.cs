using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using EditorLib;
using EditorPlugins.Editors.Animated;
using libdb.Animated;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.AnimatedCurves
{
	public partial class AnimatedCurvesControl : UserControl
	{
		public AnimatedCurvesControl()
		{
			InitializeComponent();
		}   

    public bool Initialize( IEditorWinApplication _application )
    {
      animEditor.Initialize( _application );

      listBoxTracks.DrawMode = DrawMode.OwnerDrawFixed;
      listBoxTracks.ItemHeight = 16;

      return true;
    }

    public void Deinitialize()
    {
      animEditor.Deinitialize();
    }

		#region Items

		public void SetRoot(AnimatedCurvesItem _root)
		{
			Clear();

			if(_root == null)
				return;

			FillListBox( _root );
			SetTrackSet( _root );
			listBoxTracks.SetSelected( 0, true );
		}

		private void Clear()
		{
			listBoxTracks.Items.Clear();
			animEditor.ClearSelection();
		}

		private void SetTrackSet( AnimatedCurvesItem root )
		{
			List<IAnimated> animObjs = new List<IAnimated>();
			List<Color> animColors = new List<Color>();

			Action<AnimatedCurvesItem> action = _item =>
			{
				if ( !animObjs.Contains( _item.Animated ) )
				{
					animObjs.Add( _item.Animated );
				}

				animColors.Add( _item.Color );
			};

			root.ForEachAnimated( action );

			CombinedAnimated animated = new CombinedAnimated( animObjs.ToArray() );
			animEditor.SetTrackSet( animated, animColors.ToArray() );
		}

		private void FillListBox( AnimatedCurvesItem root )
		{
			listBoxTracks.SuspendLayout();
			root.ForEach( x => listBoxTracks.Items.Add( x ) );
			listBoxTracks.ResumeLayout();
		}

		#endregion

    #region Event Handlers

		private void OnSelectItem( object _sender, EventArgs _args )
		{
			animEditor.ClearSelection();

			List<int> selectedTracks = new List<int>();

			foreach ( object obj in listBoxTracks.SelectedItems )
			{
				AnimatedCurvesItem item = obj as AnimatedCurvesItem;

				if ( item != null )
				{
					item.Selected = true;

					Action<AnimatedCurvesItem> action = x =>
					{
						if ( x.Selected && x.Animated != null )
							selectedTracks.Add( x.TrackAbsNo );
					};

					item.ForEachAnimated( action );
				}
			}

			animEditor.SelectTracks( selectedTracks );
		}

		private void OnDrawItem( object sender, DrawItemEventArgs e )
    {
      if( e.Index < 0 )
        return;

      const int INDENT_SIZE = 16;//px

      e.DrawBackground();

      AnimatedCurvesItem item = listBoxTracks.Items[e.Index] as AnimatedCurvesItem;

      if( item == null )
        return;

      Rectangle rect = e.Bounds;

      rect.X += item.Indent * INDENT_SIZE;

      if(item.Animated != null)
      {
        using( Brush colorBrush = new SolidBrush( item.Color ) )
        {
          e.Graphics.FillRectangle( colorBrush, rect.X + 2, rect.Y + 2, 8, 8 );
          e.Graphics.DrawRectangle( Pens.Black, rect.X + 2, rect.Y + 2, 8, 8 );
          rect.X += 8 + 4;
        } 
      }

      bool selected = ( e.State & DrawItemState.Selected ) == DrawItemState.Selected;
      Brush myBrush =  selected ? SystemBrushes.HighlightText : SystemBrushes.ControlText;

      Font font = e.Font;

      if(item.Animated == null)
      {
        font = new Font( e.Font, FontStyle.Underline); 
      }

      e.Graphics.DrawString( item.Text, font, myBrush, rect.Location );
      
      e.DrawFocusRectangle();
    }

		private void OnTimeValidating( object sender, System.ComponentModel.CancelEventArgs e )
		{
			float value;

			if ( !float.TryParse( txtTime.Text, out value ) &&
					!float.TryParse( txtTime.Text, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out value ) )
			{
				e.Cancel = true;
			}
			else
			{
				e.Cancel = value < 0;
			}
		}

		private void OnTimeValidated( object sender, EventArgs e )
		{
			float value;
			if ( !float.TryParse( txtTime.Text, out value ) &&
					!float.TryParse( txtTime.Text, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out value ) )
				return;

			if ( value < 0 )
				return;

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Change Tracks Times" ) )
			{
				foreach ( AnimatedEditor.KeyInfo key in animEditor.SelectedItems )
				{
					animEditor.Animated.GetObjectTrack( key.trackIndex ).SetKey( key.keyIndex, value );
				}
				trans.Commit();
			}

			UpdateAnimatedTime();
			animEditor.Invalidate();
		}

		private void OnValueValidating( object sender, System.ComponentModel.CancelEventArgs e )
		{
			object value = 0;
			if ( !TryParse( txtValue.Text, out value ) )
				e.Cancel = true;
		}

		private void OnValueValidated( object sender, EventArgs e )
		{
			object value;
			if ( !TryParse( txtValue.Text, out value ) )
				return;

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Change Tracks Values" ) )
			{
				foreach ( AnimatedEditor.KeyInfo key in animEditor.SelectedItems )
				{
					animEditor.Animated.GetObjectTrack( key.trackIndex ).SetObjectValue( key.keyIndex, value );
				}
				trans.Commit();
			}

			UpdateAnimatedValue();
			animEditor.Invalidate();
		}

		private void OnEditBoxKeyPress( object sender, KeyPressEventArgs e )
		{
			if ( e.KeyChar == '\r' )
			{
				animEditor.Focus();
				e.Handled = true;
			}
		}

		private void OnSelectedItemsChanged( object sender, EventArgs e )
		{
			List<int> tracks = new List<int>();
			bool hasUnmovableKey = false;
			foreach ( AnimatedEditor.KeyInfo key in animEditor.SelectedItems )
			{
				if ( tracks.Contains( key.trackIndex ) || key.keyIndex == 0 )
				{
					hasUnmovableKey = true;
					break;
				}

				tracks.Add( key.trackIndex );
			}

			txtTime.Enabled = animEditor.HasSelectedItems && !hasUnmovableKey;
			txtValue.Enabled = animEditor.HasSelectedItems;

			UpdateAnimatedTime();
			UpdateAnimatedValue();
		}

		private void OnSelectedItemsMoved( object sender, EventArgs e )
		{
			UpdateAnimatedTime();
			UpdateAnimatedValue();
		}

    #endregion

		#region Helpers

		private void UpdateAnimatedTime()
		{
			if ( !animEditor.HasSelectedItems )
			{
				txtTime.Text = string.Empty;
				return;
			}

			float time = 0;
			bool firstKey = true;
			bool allTimeSame = true;
			foreach ( AnimatedEditor.KeyInfo key in animEditor.SelectedItems )
			{
				float currentTime = animEditor.Animated.GetObjectTrack( key.trackIndex ).GetKey( key.keyIndex );

				if ( firstKey )
				{
					time = currentTime;
					firstKey = false;
				}
				else if ( time != currentTime )
					allTimeSame = false;
			}

			if ( allTimeSame )
				txtTime.Text = time.ToString();
			else
				txtTime.Text = string.Empty;
		}

		private void UpdateAnimatedValue()
		{
			if ( !animEditor.HasSelectedItems )
			{
				txtValue.Text = string.Empty;
				return;
			}

			object value = 0;
			bool firstKey = true;
			bool allValueSame = true;
			foreach ( AnimatedEditor.KeyInfo key in animEditor.SelectedItems )
			{
				object currentValue = animEditor.Animated.GetObjectTrack( key.trackIndex ).GetObjectValue( key.keyIndex );

				if ( firstKey )
				{
					value = currentValue;
					firstKey = false;
				}
				else if ( !value.Equals( currentValue ) )
					allValueSame = false;
			}

			if ( allValueSame )
				txtValue.Text = value.ToString();
			else
				txtValue.Text = string.Empty;
		}

		private bool TryParse( string value, out object result )
		{
			result = null;

			CombinedAnimated animated = animEditor.Animated;

			if ( animated.TrackValueType == typeof( float ) )
			{
				float temp = 0.0f;
				if ( !float.TryParse( value, out temp ) &&
						!float.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out temp ) )
					return false;

				if ( temp > 10000f )
					temp = 10000f;

				if ( temp < -10000f )
					temp = -10000f;


				result = temp;
			}
			else if ( animated.TrackValueType == typeof( int ) )
			{
				int temp = 0;
				if ( !int.TryParse( value, out temp ) )
					return false;

				if ( temp > 10000 )
					temp = 10000;

				if ( temp < -10000 )
					temp = -10000;

				result = temp;
			}
			else if ( animated.TrackValueType == typeof( string ) )
			{
				result = value;
			}
			else
				return false;

			return true;
		}

		#endregion
	}
}
