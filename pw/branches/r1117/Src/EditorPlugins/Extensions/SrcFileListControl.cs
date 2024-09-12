using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using EditorPlugins.Forms;
using libdb.IO;

namespace EditorPlugins.Extensions
{
  public class SrcFileListControl : ListBox
  {
    private class SrcFileWrapper
    {
      private readonly SrcFile file;
      public SrcFileWrapper( SrcFile file ) { this.file = file; }

      public SrcFile File { get { return file; } }
      public override string ToString()
      {
        if ( file == null )
          return "<Browse...>";
        else
          return FileUtils.GetFileName( file.ToString() );
      }
    }

    private const int IMAGE_SIZE = 48;

    private readonly IWindowsFormsEditorService service;
    private int fontHeight = 0;

    private readonly Image lightChecker = null;
    private readonly Image darkChecker = null;
    private readonly LoadImageFunctor loadImageFunctor = null;
    private readonly Image[] images = null;
    private readonly BackgroundWorker worker = null;

    private SrcFile result = null;
    private bool needBrowse = false;

    private static Image CreateChecker( Brush brush1, Brush brush2, int width, int height, int cellSize )
    {
      Image image = new Bitmap( width, height );
      using ( Graphics g = Graphics.FromImage( image ) )
      {
        for ( int y = 0; y < IMAGE_SIZE; y += cellSize )
        {
          bool black = ( y % ( 2 * cellSize ) ) == 0;
          for ( int x = 0; x < IMAGE_SIZE; x += cellSize )
          {
            if ( black )
              g.FillRectangle( brush1, x, y, cellSize, cellSize );
            else
              g.FillRectangle( brush2, x, y, cellSize, cellSize );
            black = !black;
          }
        }
      }
      return image;
    }

    private static bool IsDarkImage( Image image )
    {
      Bitmap b = image as Bitmap;
      if ( b == null )
        return false;

      BitmapData data = b.LockBits( new Rectangle( 0, 0, b.Width, b.Height ), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
      int bytes = data.Stride * b.Height;
      byte[] rgba = new byte[bytes];
      System.Runtime.InteropServices.Marshal.Copy( data.Scan0, rgba, 0, bytes );
      b.UnlockBits( data );

      int light = 0;
      int dark = 0;
      for ( int i = 0; i < rgba.Length; i += 4 )
      {
        if ( rgba[i + 3] < 64 || rgba[i + 3] > 192 )
          continue;
        int intensity = rgba[i] * rgba[i] + rgba[i + 1] * rgba[i + 1] + rgba[i + 2] * rgba[i + 2];
        if ( intensity > 3 * 128 * 128 )
          ++light;
        else
          ++dark;
      }

      return dark > light;
    }

    public delegate Image LoadImageFunctor( string fileName );

    private int itemHeight = 0;
    
    public override int ItemHeight
    {
      get { return itemHeight; }
      set { itemHeight = value; }
    }

    public SrcFileListControl( IWindowsFormsEditorService service, IList<SrcFile> files, SrcFile selected, LoadImageFunctor loadImageFunctor )
    {
      this.service = service;
      this.loadImageFunctor = loadImageFunctor;

      result = selected;
      fontHeight = TextRenderer.MeasureText( "Ig", Font ).Height;

      BorderStyle = BorderStyle.None;
      IntegralHeight = true;

      int height = 0;

      if( loadImageFunctor != null )
      {
        itemHeight = IMAGE_SIZE + 2;
        DrawMode = DrawMode.OwnerDrawFixed;
        height = files.Count * itemHeight;
      }
      else
      {
        DrawMode = DrawMode.Normal;
        itemHeight = fontHeight + 2;
        height = ( files.Count + 1 ) * itemHeight;
      }

      Height = Math.Min( height, GetHeight( Cursor.Position.Y, this ) );
      
      foreach ( SrcFile file in files )
      {
        int index = Items.Add( new SrcFileWrapper( file ) );
        if ( selected.FileName == file.FileName )
          SelectedIndex = index;
      }
      Items.Add( new SrcFileWrapper( null ) );
      
      if ( loadImageFunctor != null )
      {
        lightChecker = CreateChecker( Brushes.Gainsboro, Brushes.White, IMAGE_SIZE, IMAGE_SIZE, 8 );
        darkChecker = CreateChecker( Brushes.Black, Brushes.DimGray, IMAGE_SIZE, IMAGE_SIZE, 8 );

        images = new Image[Items.Count];
        for ( int i = 0; i < images.Length - 1; ++i )
          images[i] = EditorPluginResources.SrcFileLoading;
        images[images.Length - 1] = EditorPluginResources.SrcFileBrowse;

        worker = new BackgroundWorker();
        worker.DoWork += LoadImages;
        worker.RunWorkerAsync();
      }
    }

    private void LoadImages( object sender, DoWorkEventArgs e )
    {
      for ( int i = 0; i < Items.Count; ++i )
      {
        SrcFileWrapper file = Items[i] as SrcFileWrapper;
        if ( file == null || file.File == null )
          continue;

        Image image = loadImageFunctor( file.File.FileName );
        if ( image == null )
          continue;

        Image scaledImage = new Bitmap( IMAGE_SIZE, IMAGE_SIZE );
        using ( Graphics g = Graphics.FromImage( scaledImage ) )
        {
          float scale = Math.Max( (float)scaledImage.Width / (float)image.Width, (float)scaledImage.Height / (float)image.Height );
          int scaledWidth = (int)Math.Round( image.Width * scale );
          int scaledHeight = (int)Math.Round( image.Height * scale );
          g.DrawImage( image, new Rectangle( ( scaledImage.Width - scaledWidth ) / 2, ( scaledImage.Height - scaledHeight ) / 2, scaledWidth, scaledHeight ), new Rectangle( 0, 0, image.Width, image.Height ), GraphicsUnit.Pixel );
        }

        bool darkImage = IsDarkImage( scaledImage );

        Bitmap result = new Bitmap( IMAGE_SIZE, IMAGE_SIZE );
        using ( Graphics g = Graphics.FromImage( result ) )
        {
          g.DrawImage( darkImage ? lightChecker : darkChecker, new Point( 0, 0 ) );
          g.DrawImage( scaledImage, new Point( 0, 0 ) );
        }
        lock ( images )
        {
          images[i] = result;
        }
      }

      FormUtils.Invoke( this, () => Invalidate() );
    }

    protected override void OnClick( EventArgs e )
    {
      base.OnClick( e );
      result = ( SelectedItem as SrcFileWrapper ).File;
      needBrowse = result == null;
      service.CloseDropDown();
    }

    protected override void OnFontChanged( EventArgs e )
    {
      base.OnFontChanged( e );
      fontHeight = TextRenderer.MeasureText( "Ig", Font ).Height;
      ItemHeight = images != null ? IMAGE_SIZE + 2 : fontHeight + 2;
      Invalidate();
    }

    protected override void OnDrawItem( DrawItemEventArgs e )
    {
      base.OnDrawItem( e );
      e.DrawBackground();
      e.DrawFocusRectangle();
      if( images == null )
      {
        TextRenderer.DrawText( e.Graphics, Items[e.Index].ToString(), Font, new Point( e.Bounds.Left + 1, e.Bounds.Top + ( e.Bounds.Height - fontHeight ) / 2 ), e.ForeColor );
      }
      else
      {
        TextRenderer.DrawText( e.Graphics, Items[e.Index].ToString(), Font, new Point( e.Bounds.Left + IMAGE_SIZE + 2, e.Bounds.Top + ( e.Bounds.Height - fontHeight ) / 2 ), e.ForeColor );
        lock( images )
        {
          if( images[e.Index] != null )
            e.Graphics.DrawImage( images[e.Index], new Point( e.Bounds.X + 1, e.Bounds.Y + 1 ) );
        }
      }
    }
    
    public SrcFile Value { get { return result; } }
    public bool NeedBrowse { get { return needBrowse; } }

    private int GetHeight( int y, Control control )
    {
      Rectangle screen = Screen.GetBounds( control );
      Rectangle workingArea = Screen.GetWorkingArea( control );

      int taskBar = screen.Height - workingArea.Height;

      if( y < ( screen.Height / 2 ) )
      {
        return screen.Height - taskBar - y - 40;
      }

      return y - taskBar - 40;
    }
  }
}
