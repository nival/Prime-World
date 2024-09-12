using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using DBTypes;
using System.ComponentModel;
using libdb.DB;

namespace EditorPlugins.LayoutEditor
{
  [IndexField( "PEName" )]
	internal class LayoutPropertiesEditorObject
	{
    private Rectangle parentPosition;
		private UILayout window;
    private UILayout parentWindow;
    private LayoutEditorControl control;
    private int globalWidth;
    private int globalHeight;

    internal LayoutPropertiesEditorObject( UILayout _window, LayoutEditorControl _control )
		{
      control = _control;
      window = _window;
      parentWindow = control.GetWindowParent( window );
      globalWidth = ( control.RootLayout != null ) ? control.RootLayout.size.x : 1280;
      globalHeight = ( control.RootLayout != null ) ? control.RootLayout.size.y : 1024;
      if ( null == parentWindow )
      {
        parentPosition.X = 0;
        parentPosition.Y = 0;
        parentPosition.Width = globalWidth;
        parentPosition.Height = globalHeight;
      }
      else
      {
        parentPosition = control.GetWindowRectangle( parentWindow );
        if ( parentWindow.size.x > 0 )
          parentPosition.Width = parentWindow.size.x;
        if ( parentWindow.size.y > 0 )
          parentPosition.Height = parentWindow.size.y;
      }
		}

    public string Type { get { return window.GetType().Name; } }

    [Browsable( false )]
    public string PEName
    {
      get { return window.DBId.ToString();  }
    }

    public string Name
    {
      get { return window.name; }
      set { window.name = value; }
    }

    [Category( "Size" )]
    public int Width
    {
      get { return window.size.x; }
      set
      {
        switch ( window.hAlign )
        {
          case EUIElementHAlign.Left:
          case EUIElementHAlign.Proportional:
          case EUIElementHAlign.FixedMargins:
            {
              window.size.x = value;
              break;
            }
          case EUIElementHAlign.Right:
            {
              int diff = window.size.x - value;
              window.size.x = value;
              window.location.x = window.location.x + diff;
              break;
            }
          case EUIElementHAlign.Center:
            {
              int diff = window.size.x - value;
              window.size.x = value;
              window.location.x = window.location.x + diff / 2;
              break;
            }
        }
      }
    }

    [Category( "Size" )]
    public int Height
    {
      get { return window.size.y; }
      set
      {
        switch ( window.vAlign )
        {
          case EUIElementVAlign.Top:
          case EUIElementVAlign.Proportional:
          case EUIElementVAlign.FixedMargins:
            {
              window.size.y = value;
              break;
            }
          case EUIElementVAlign.Bottom:
            {
              int diff = window.size.y - value;
              window.size.y = value;
              window.location.y = window.location.y + diff;
              break;
            }
          case EUIElementVAlign.Center:
            {
              int diff = window.size.y - value;
              window.size.y = value;
              window.location.y = window.location.y + diff / 2;
              break;
            }
        }
      }
    }

    [Category( "Position H" )]
    public int Left
    {
      get { return window.location.x; }
      set {
        switch ( window.hAlign )
        {
          case EUIElementHAlign.Left:
          case EUIElementHAlign.Proportional:
            {
              window.location.x = value;
              break;
            }
          case EUIElementHAlign.Right:
          case EUIElementHAlign.FixedMargins:
            {
              int diff = window.location.x - value;
              window.location.x = value;
              window.size.x = window.size.x + diff;
              break;
            }
          case EUIElementHAlign.Center:
            {
              int diff = window.location.x - value;
              window.location.x = value;
              window.size.x = window.size.x + diff + diff;
              break;
            }
        }
      }
    }

    [Category( "Position H" )]
    public int Right
    {
      get { return parentPosition.Width - Left - Width; }
      set
      {
        switch ( window.hAlign )
        {
          case EUIElementHAlign.Left:
          case EUIElementHAlign.FixedMargins:
            {
              window.size.x = parentWindow.size.x - window.location.x - value;
              break;
            }
          case EUIElementHAlign.Proportional:
          case EUIElementHAlign.Right:
            {
              int diff = ( parentWindow.size.x - window.location.x - window.size.x ) - value;
              window.location.x = window.location.x + diff;
              break;
            }
          case EUIElementHAlign.Center:
            {
              int diff = ( parentWindow.size.x - window.location.x - window.size.x ) - value;
              window.size.x = window.size.x + diff + diff;
              window.location.x = window.location.x - diff;
              break;
            }
        }
      }
    }

    [Category( "Position V" )]
    public int Top
		{
      get { return window.location.y; }
      set
      {
        switch ( window.vAlign )
        {
          case EUIElementVAlign.Top:
          case EUIElementVAlign.Proportional:
            {
              window.location.y = value;
              break;
            }
          case EUIElementVAlign.Bottom:
          case EUIElementVAlign.FixedMargins:
            {
              int diff = window.location.y - value;
              window.location.y = value;
              window.size.y = window.size.y + diff;
              break;
            }
          case EUIElementVAlign.Center:
            {
              int diff = window.location.y - value;
              window.location.y = value;
              window.size.y = window.size.y + diff + diff;
              break;
            }
        }
      }
    }

    [Category("Position V")]
    public int Bottom
		{
      get { return parentPosition.Height - Top - Height; }
      set
      {
        switch ( window.vAlign )
        {
          case EUIElementVAlign.Top:
          case EUIElementVAlign.FixedMargins:
            {
              window.size.y = parentWindow.size.y - window.location.y - value;
              break;
            }
          case EUIElementVAlign.Proportional:
          case EUIElementVAlign.Bottom:
            {
              int diff = ( parentWindow.size.y - window.location.y - window.size.y ) - value;
              window.location.y = window.location.y + diff;
              break;
            }
          case EUIElementVAlign.Center:
            {
              int diff = ( parentWindow.size.y - window.location.y - window.size.y ) - value;
              window.size.y = window.size.y + diff + diff;
              window.location.y = window.location.y - diff;
              break;
            }
        }
      }
    }

    [Category( "Position H" )]
    [DisplayName( "From Center H" )]
    public int CenterHoriz
    {
      get { return Left - ( parentPosition.Width - Width ) / 2; }
      set { window.location.x = ( parentPosition.Width - window.size.x ) / 2 + value; }
    }

    [Category( "Position V" )]
    [DisplayName("From Center V")]
    public int CenterVert
    {
      get { return Top - ( parentPosition.Height - Height ) / 2; }
      set { window.location.y = ( parentPosition.Height - window.size.y ) / 2 + value; }
    }

    [Category("Alignment")]
    [DisplayName("Horizontal Alignment")]
		public EUIElementHAlign HAlign
		{
      get { return window.hAlign; }
      set { window.hAlign = value; }
		}

    [Category("Alignment")]
    [DisplayName("Vertical Alignment")]
		public EUIElementVAlign VAlign
		{
      get { return window.vAlign; }
      set { window.vAlign = value; }
		}

    [Category("Alignment")]
    [DisplayName("Keep aspect ratio")]
    public EUIElementAspectRatio KeepAspectRatio
    {
      get { return window.keepAspectRatio; }
      set { window.keepAspectRatio = value; }
    }

    [Category("Position")]
    [DisplayName("Abs Left")]
		public int GlobalLeft
		{
      get { return control.GetWindowRectangle( window ).X; }
		}

    [Category("Position")]
    [DisplayName("Abs Top")]
		public int GlobalTop
		{
      get { return control.GetWindowRectangle( window ).Y; }
    }

    [Category("Position")]
    [DisplayName("Abs Right")]
		public int GlogalRight
		{
      get { return globalWidth - control.GetWindowRectangle( window ).X - Width; }
		}

    [Category("Position")]
    [DisplayName("Abs Bottom")]
		public int GlobalBottom
		{
      get { return globalHeight - control.GetWindowRectangle( window ).Y - Height; }
		}

    [DisplayName("Visible")]
    public bool Visible
    {
      get { return window.visible; }
      set { window.visible = value; }
    }

    [DisplayName("Enabled")]
    public bool Enabled
    {
      get { return window.enabled; }
      set { window.enabled = value; }
    }

    [Category("Element")]
    [DisplayName("Layout Properties")]
    public UILayout sharedObject { get { return window; } }
	}
}
