using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using System.IO;
using EditorPlugins.Importer.Texture;
using libdb.Diagnostics;
using libdb.DB;
using EditorLib.ObjectSelector;
using libdb.UndoRedo;
using EditorPlugins.Scene;
using EditorPlugins.LayoutEditor;
using libdb.IO;
using EditorLib.ObjectsBrowser;
using System.Text.RegularExpressions;

namespace EditorPlugins.ImageStylesEditor
{

	public partial class ImageStylesEditorControl : UserControl
	{
		private DBPtr<BaseUIMaterial> selectedStyle;
		private IEditorWinApplication editorApplication;
    internal IEditorWinApplication Application { get { return editorApplication; } }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Cursor zoomIco;
		Cursor dragIco;
		private int Zoom
		{
			set
			{
				imageStyleView.Zoom = value;
        SetDataToUI();
			}
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		public ImageStylesEditorControl()
		{
			InitializeComponent();
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		private void SubscribeToEvent()
		{
			splitContainer1.Panel1.Resize += new EventHandler(Panel1_Resize);
			DataBase.ChangeDBResourceEvent += new DataBase.ChangeDBResourceEventHandler( DataBase_ChangeDBResourceEvent );
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    internal void UnsubscribeFromEvent()
		{
			splitContainer1.Panel1.Resize -= new EventHandler(Panel1_Resize);
			DataBase.ChangeDBResourceEvent -= new DataBase.ChangeDBResourceEventHandler(DataBase_ChangeDBResourceEvent);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public void Initialize(DBPtr<BaseUIMaterial> style, IEditorWinApplication _application)
		{
			editorApplication = _application;

      SelectedStylePtr = style;

			SubscribeToEvent();

			Graphics g = Graphics.FromImage( LayoutEditor.Resource.zoom );
			g.DrawString( "arya", this.Font, Brushes.Blue, 0, 0 );
			IntPtr ptr = LayoutEditor.Resource.zoom.GetHicon();
			zoomIco = new Cursor( ptr );
			
			g = Graphics.FromImage( LayoutEditor.Resource.drag );
			g.DrawString( "arya", this.Font, Brushes.Blue, 0, 0 );
			ptr = LayoutEditor.Resource.drag.GetHicon();
			dragIco = new Cursor( ptr );
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Panel1_Resize( object sender, EventArgs e )
		{
			int newHValue = splitContainer1.Panel1.HorizontalScroll.Value;
			int newVValue = splitContainer1.Panel1.VerticalScroll.Value;
			
			if ( newHValue > splitContainer1.Panel1.HorizontalScroll.Maximum ) 
        newHValue = splitContainer1.Panel1.HorizontalScroll.Maximum;

			if ( newVValue > splitContainer1.Panel1.VerticalScroll.Maximum ) 
        newVValue = splitContainer1.Panel1.VerticalScroll.Maximum;
			
      if ( splitContainer1.Panel1.HorizontalScroll.Visible )
				splitContainer1.Panel1.HorizontalScroll.Value = (newHValue < 0) ? 0 : newHValue;

      if ( splitContainer1.Panel1.VerticalScroll.Visible )
				splitContainer1.Panel1.VerticalScroll.Value = (newVValue < 0) ? 0 : newVValue;
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void DataBase_ChangeDBResourceEvent( DBID dbid )
		{
      if ( ( selectedStyle.DBId == dbid ) || libdb.DB.DataBase.HasDependency(selectedStyle.DBId, dbid))
        SetDataToUI();
		}

		private DBPtr<BaseUIMaterial> SelectedStylePtr
		{
			get
			{
				return selectedStyle;
			}
			set
			{
				if (selectedStyle == value)
					return;

				selectedStyle = value;
				imageStyleView.Style = value != null ? value.Get() : null;
				splitContainer1.Panel1.AutoScrollMinSize = new Size( 0, 0 );
				if (selectedStyle == null || selectedStyle.Get() == null)
					return;

        SetDataToUI();
			}
		}

		internal BaseUIMaterial SelectedStyle
		{
			get
			{
				if ( selectedStyle != null )
					return selectedStyle.Get();

				return null;
			}
		}

    private bool insideSetData = false;

		private void SetDataToUI()
		{
      insideSetData = true;
			if ( SelectedStyle != null )
			{
				TextureX.Text = SelectedStyle.textureShift.x.ToString();
				TextureY.Text = SelectedStyle.textureShift.y.ToString();
				TextureWidth.Text = SelectedStyle.imageSize.x.ToString();
				TextureHeight.Text = SelectedStyle.imageSize.y.ToString();

        TileLeftMargin.Text = SelectedStyle.imageTileShift.x.ToString();
        TileRightMargin.Text = (SelectedStyle.imageSize.x - SelectedStyle.imageTileShift.x - SelectedStyle.imageTileSize.x).ToString();
        TileTopMargin.Text = SelectedStyle.imageTileShift.y.ToString();
        TileBottomMargin.Text = (SelectedStyle.imageSize.y - SelectedStyle.imageTileShift.y - SelectedStyle.imageTileSize.y).ToString();
      
        AutosizeCheck.Checked = (SelectedStyle.UseAutosize == DBTypes.BooleanPin.Present);
      }

      SampleHeight.Text = imageStyleView.SamplerHeight.ToString();
      SampleWidth.Text = imageStyleView.SamplerWidth.ToString();

      UpdateCheckedButtons();
      UpdateHStretchButtons();
      UpdateVStretchButtons();

      Invalidate();
      insideSetData = false;
    }

		private void UpdateCheckedButtons()
		{
			if ( SelectedStyle == null )
				return;

// 			UITexture uiTexture = SelectedStyle.texture.Get();
// 			if(uiTexture != null)
// 			{
// 				toolShapeAlphaThreshold.Text = ((int)Math.Round( ((float)(uiTexture.shapeAlphaThreshold) * (float)100 / (float)255) )).ToString() + "%";
// 			}
// 			else
// 			{
// 				toolShapeAlphaThreshold.Text = "0%";
// 			}
//      imageStyleView.SetShapeVisible(toolShowShape.Checked);

			ToolZoomCombo.Text = imageStyleView.Zoom.ToString() + "%";
			ToolShowShape.Enabled = true;
			imageStyleView.Invalidate();

      if ( SelectedStyle.UseAutosize == DBTypes.BooleanPin.Present )
      {
        TextureX.Enabled = false;
        TextureWidth.Enabled = false;
        TextureY.Enabled = false;
        TextureHeight.Enabled = false;

        TileTopMargin.Enabled = false;
        TileLeftMargin.Enabled = false;
        TileBottomMargin.Enabled = false;
        TileRightMargin.Enabled = false;
      }
      else
      {
        TextureX.Enabled = true;
        TextureWidth.Enabled = true;
        TextureY.Enabled = true;
        TextureHeight.Enabled = true;

        TileTopMargin.Enabled = (SelectedStyle.verticalDrawMode == EUIImageDrawMode.Tile || SelectedStyle.verticalDrawMode == EUIImageDrawMode.StretchedTile);
        TileBottomMargin.Enabled = (SelectedStyle.verticalDrawMode == EUIImageDrawMode.Tile || SelectedStyle.verticalDrawMode == EUIImageDrawMode.StretchedTile);
        TileLeftMargin.Enabled = (SelectedStyle.horizontalDrawMode == EUIImageDrawMode.Tile || SelectedStyle.horizontalDrawMode == EUIImageDrawMode.StretchedTile);
        TileRightMargin.Enabled = (SelectedStyle.horizontalDrawMode == EUIImageDrawMode.Tile || SelectedStyle.horizontalDrawMode == EUIImageDrawMode.StretchedTile);
      }
		}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private void UpdateHStretchButtons()
    {
      ToolHLeft.Checked = false;
      ToolHStretch.Checked = false;
      ToolHCenter.Checked = false;
      ToolHTile.Checked = false;
      ToolHStretchedTile.Checked = false;

      if (SelectedStyle != null)
      {
        switch (SelectedStyle.horizontalDrawMode)
        {
          case EUIImageDrawMode.Normal:
            ToolHLeft.Checked = true;
            break;
          case EUIImageDrawMode.Stretch:
            ToolHStretch.Checked = true;
            break;
          case EUIImageDrawMode.Center:
            ToolHCenter.Checked = true;
            break;
          case EUIImageDrawMode.Tile:
            ToolHTile.Checked = true;
            break;
          case EUIImageDrawMode.StretchedTile:
            ToolHStretchedTile.Checked = true;
            break;
        }
      }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private void UpdateVStretchButtons()
    {
      ToolVTop.Checked = false;
      ToolVStretch.Checked = false;
      ToolVCenter.Checked = false;
      ToolVTile.Checked = false;
      ToolVStretchedTile.Checked = false;

      if (SelectedStyle != null)
      {
        switch (SelectedStyle.verticalDrawMode)
        {
          case EUIImageDrawMode.Normal:
            ToolVTop.Checked = true;
            break;
          case EUIImageDrawMode.Stretch:
            ToolVStretch.Checked = true;
            break;
          case EUIImageDrawMode.Center:
            ToolVCenter.Checked = true;
            break;
          case EUIImageDrawMode.Tile:
            ToolVTile.Checked = true;
            break;
          case EUIImageDrawMode.StretchedTile:
            ToolVStretchedTile.Checked = true;
            break;
        }
      }
    }

		private void toolShowShape_Click( object sender, EventArgs e )
		{
			ToolShowShape.Checked = !ToolShowShape.Checked;
			UpdateCheckedButtons();
		}

		private void toolShapeAlphaThreshold_SelectedIndexChanged( object sender, EventArgs e )
		{
			if ( sender is ToolStripComboBox )
			{
				string str = (sender as ToolStripItem).Text;
				SetShapeAlphaThreshold( ConvertToInt( str ) );
			}
		}

		private int ConvertToInt(string str)
		{
			string shab = "-1234567890";
			string strT = new string( str.ToCharArray() );
			for ( int i = 0; i < strT.Length; i++ )
			{
				if ( !shab.Contains( strT[i].ToString() ) )
				{
					strT = strT.Remove( i--, 1 );
				}
			}
			if ( strT.Length > 0 )
			{
				if(!strT.Contains("-")|| !strT.Substring(1).Contains("-"))
				return System.Convert.ToInt32( strT );
			}
			return 0;
		}

		private void toolShapeAlphaThreshold_KeyUp( object sender, KeyEventArgs e )
		{
			if(e.KeyCode == Keys.Enter && sender is ToolStripItem)
			{
				string str = (sender as ToolStripItem).Text;

				SetShapeAlphaThreshold( ConvertToInt( str ) );
			}
		}

		private void SetShapeAlphaThreshold( int _value )
		{
			if ( SelectedStyle == null)
				return;

      SetDataToUI();

// 			UITexture uiTexture = SelectedStyle.texture.Get();
// 			if(uiTexture != null)
// 			{
// 				imageStyleView.IsAlphaChanged = true;
// 				uiTexture.shapeAlphaThreshold = (int)Math.Round((float)(Math.Min( 100, Math.Max( 0, _value ) )) * (float)255 / (float)100);
// 				imageStyleView.IsAlphaChanged = false;
// 				UpdateCheckedButtons();
// 			}
		}

		private void toolZoomCombo_KeyUp( object sender, KeyEventArgs e )
		{
			if ( e.KeyCode == Keys.Enter && sender is ToolStripItem )
			{
				string str = (sender as ToolStripItem).Text;
				Zoom = ConvertToInt( str ) ;
			}
		}

		private void toolZoomCombo_SelectedIndexChanged( object sender, EventArgs e )
		{
			if ( sender is ToolStripItem )
			{
				if ( ToolZoomCombo.SelectedIndex == 0 )
					Zoom = 100;
				else
				{
					string str = (sender as ToolStripItem).Text;
					Zoom = ConvertToInt( str );
				}
			}
		}

		private int UVsSave( object sender )
		{
			if ( sender is TextBox )
			{
				string str = (sender as TextBox).Text;
				return ConvertToInt( str );
			}
			return 0;
		}

    private void GetDataFromUI( object sender )
    {
      if ( insideSetData )
        return;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Update properties" ) )
      {
        imageStyleView.SamplerWidth = UVsSave( SampleWidth );
        imageStyleView.SamplerHeight = UVsSave( SampleHeight );

        imageStyleView.TextureX = UVsSave( TextureX );
        imageStyleView.TextureY = UVsSave( TextureY );
        imageStyleView.TextureSizeX = UVsSave( TextureWidth );
        imageStyleView.TextureSizeY = UVsSave( TextureHeight );

        imageStyleView.TileLeftMargin = UVsSave( TileLeftMargin );
        imageStyleView.TileRightMargin = UVsSave( TileRightMargin );
        imageStyleView.TileTopMargin = UVsSave( TileTopMargin );
        imageStyleView.TileBottomMargin = UVsSave( TileBottomMargin );

        if( sender == ToolHLeft )
          SelectedStyle.horizontalDrawMode = EUIImageDrawMode.Normal;
        if( sender == ToolHStretch )
          SelectedStyle.horizontalDrawMode = EUIImageDrawMode.Stretch;
        if( sender == ToolHCenter )
          SelectedStyle.horizontalDrawMode = EUIImageDrawMode.Center;
        if( sender == ToolHTile )
          SelectedStyle.horizontalDrawMode = EUIImageDrawMode.Tile;
        if( sender == ToolHStretchedTile )
          SelectedStyle.horizontalDrawMode = EUIImageDrawMode.StretchedTile;

        if( sender == ToolVTop )
          SelectedStyle.verticalDrawMode = EUIImageDrawMode.Normal;
        if( sender == ToolVStretch )
          SelectedStyle.verticalDrawMode = EUIImageDrawMode.Stretch;
        if( sender == ToolVCenter )
          SelectedStyle.verticalDrawMode = EUIImageDrawMode.Center;
        if( sender == ToolVTile )
          SelectedStyle.verticalDrawMode = EUIImageDrawMode.Tile;
        if( sender == ToolVStretchedTile )
          SelectedStyle.verticalDrawMode = EUIImageDrawMode.StretchedTile;

        SelectedStyle.UseAutosize = AutosizeCheck.Checked ? DBTypes.BooleanPin.Present : DBTypes.BooleanPin.None;

        SetDataToUI();

        imageStyleView.Invalidate();

        trans.Commit();
      }
    }

    private void UpdateDataOnLeave(object sender, EventArgs e)
    {
      GetDataFromUI(sender);
    }

    private void UpdateDataOnKeyUp(object sender, KeyEventArgs e)
    {
      if ( e.KeyCode == Keys.Enter )
        GetDataFromUI(sender);
    }

    private void SizeFromTexture_Click(object sender, EventArgs e)
    {
      imageStyleView.TextureX = 0;
      imageStyleView.TextureY = 0;
      imageStyleView.TextureSizeX = imageStyleView.TextureWidth;
      imageStyleView.TextureSizeY = imageStyleView.TextureHeight;

      imageStyleView.TileLeftMargin = 0;
      imageStyleView.TileTopMargin = 0;
      imageStyleView.TileRightMargin = 0;
      imageStyleView.TileBottomMargin = 0;

      SetDataToUI();
    }
	}
}
