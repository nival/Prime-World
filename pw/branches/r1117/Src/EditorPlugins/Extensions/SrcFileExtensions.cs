using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorPlugins.Importer.Texture;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorPlugins.Extensions
{
  public sealed class SrcFileEditor : TwoTypedValueEditor<SrcFile, SrcFileAttribute>
  {
    public SrcFileEditor( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) { }

    public override bool IsDropDownResizable { get { return true; } }
    public override System.Drawing.Design.UITypeEditorEditStyle EditorEditStyle 
    { 
      get { return System.Drawing.Design.UITypeEditorEditStyle.DropDown; } 
    }

    private bool IsImageExtension( string extension )
    {
      return string.Compare( extension, ".tga", StringComparison.InvariantCultureIgnoreCase ) == 0 ||
         string.Compare( extension, ".png", StringComparison.InvariantCultureIgnoreCase ) == 0 ||
         string.Compare( extension, ".bmp", StringComparison.InvariantCultureIgnoreCase ) == 0 ||
         string.Compare( extension, ".gif", StringComparison.InvariantCultureIgnoreCase ) == 0;
    }

    private Image LoadImage( string fileName )
    {
      string ext = Path.GetExtension( fileName );
      if ( !IsImageExtension( ext ) )
        return null;

      using ( Stream s = Application.Application.SourceFileSystem.OpenFile( fileName ) )
      {
        if ( s == null )
          return null;

        try
        {
          return ( string.Compare( ext, ".tga", StringComparison.InvariantCultureIgnoreCase ) == 0 ) ? TgaReader.LoadImage( s ) : Bitmap.FromStream( s );
        }
        catch ( Exception )
        {
          Log.TraceWarning( "Cannot load image from file \"{0}\"", fileName );
          return null;
        }
      }
    }

    private bool HasImageExtensions( string extensions )
    {
      foreach ( string extension in extensions.Split( ';' ) )
      {
        if ( IsImageExtension( Path.GetExtension( extension ) ) )
          return true;
      }
      return false;
    }

    protected override SrcFile EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, SrcFile value )
    {
      SrcFile srcFile = context.PropertyDescriptor.GetValue( instance ) as SrcFile;
      DBID ownerDbid = DBID.Empty;
      if ( instance is IOwnerable )
      {
        IOwnerable ownerable = instance as IOwnerable;
        if ( ownerable != null && ownerable.GetOwner() != null )
          ownerDbid = ownerable.GetOwner().DBId;
      }
      else if ( instance is DBResource )
      {
        DBResource resource = instance as DBResource;
        ownerDbid = resource.DBId;
      }
      else if ( instance is DBPtrBase )
      {
        DBPtrBase ptr = instance as DBPtrBase;
        ownerDbid = ptr.DBId;
      }

      string srcFolder = string.IsNullOrEmpty( Attribute.SourceFolder ) ? Path.GetDirectoryName( ownerDbid.FileName ) : Attribute.SourceFolder;

      List<SrcFile> values = new List<SrcFile>();
      if ( !DBID.IsNullOrEmpty( ownerDbid ) )
      {
        string[] files = Application.Application.SourceFileSystem.GetFileNames( FileUtils.FixFolderName( srcFolder ), Attribute.Extensions, SearchOption.TopDirectoryOnly );
        foreach ( string file in files )
          values.Add( new SrcFile( file ) );
      }

      IWindowsFormsEditorService formEditor = provider.GetService( typeof( IWindowsFormsEditorService ) ) as IWindowsFormsEditorService;
      SrcFileListControl srcFileListControl = null;

      if ( HasImageExtensions( Attribute.Extensions ) )
        srcFileListControl = new SrcFileListControl( formEditor, values, value, LoadImage);
      else
        srcFileListControl = new SrcFileListControl( formEditor, values, value, null );

      formEditor.DropDownControl( srcFileListControl );

      if ( srcFileListControl.NeedBrowse )
      {
        string rootFolder = FileUtils.FixFolderName( Path.GetFullPath( Application.Application.SourceFileSystem.GetFullDirectory( FileUtils.PathSeparatorString ) ) );
        string wantedFolder = FileUtils.FixFolderName( Path.GetFullPath( Application.Application.SourceFileSystem.GetFullDirectory( srcFolder ) ) );

				OpenFileDialog dialog = new OpenFileDialog()
        {
					RestoreDirectory = true,
					Filter = string.Format( "{0} ({1})|{1}", Attribute.Description, Attribute.Extensions ),
					Title = Attribute.Description,
					CheckFileExists = true,
					CheckPathExists = true
        };

        if ( dialog.ShowDialog() == DialogResult.Cancel )
          return value;

        string fullFileName = FileUtils.FixFileName( Path.GetFullPath( dialog.FileName ) );
        string wantedFileName = FileUtils.Combine( srcFolder, FileUtils.GetFileName( fullFileName ) );
        if ( fullFileName.StartsWith( wantedFolder, StringComparison.InvariantCultureIgnoreCase ) )
        {
					return new SrcFile(wantedFileName);
        }
        else if ( fullFileName.StartsWith( rootFolder, StringComparison.InvariantCultureIgnoreCase ) )
        {
          if ( MessageBox.Show( string.Format( "You've select file (\"{0}\") from source folder (\"{1}\") but not from appropriate sub folder (\"{2}\"). Do you want to copy file to appropriate sub folder?", fullFileName, rootFolder, wantedFolder ),
            "Copy Source File", MessageBoxButtons.YesNo, MessageBoxIcon.Question ) == DialogResult.Yes )
          {
            Application.Application.SourceFileSystem.AddFile( wantedFileName, fullFileName, true );
            return new SrcFile( wantedFileName );
          }
          else
            return value;
        }
        else
        {
          if ( MessageBox.Show( string.Format( "You've select file (\"{0}\") not from source folder (\"{1}\"). Do you want to copy file to appropriate sub folder?", fullFileName, rootFolder ),
            "Copy Source File", MessageBoxButtons.YesNo, MessageBoxIcon.Question ) == DialogResult.Yes )
          {
            Application.Application.SourceFileSystem.AddFile( wantedFileName, fullFileName, true );
            return new SrcFile( wantedFileName );
          }
          else
            return value;
        }
      }
      else
        return srcFileListControl.Value;
    }
  }

  public sealed class SrcFileStringConverter : TypedStringConvertor<SrcFile>
  {
    public override bool SuppressProperties { get { return true; } }

    public SrcFileStringConverter( IEditorWinApplication application ) : base( application ) { }

    protected override SrcFile ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      DBResource owner = instance as DBResource;
      if ( owner == null )
      {
        IOwnerable ownerable = instance as IOwnerable;
        if ( ownerable != null )
          owner = ownerable.GetOwner();
      }

      string parentFolder = string.Empty + FileUtils.PathSeparatorChar;

      if ( owner == null )
        Log.TraceMessage( "Cannot resolve owner in SrcFileStringConverter" );
      else
      {
        parentFolder = FileUtils.FixFolderName( FileUtils.PathSeparatorChar + FileUtils.GetParentFolderPath( owner.DBId.FileName ) );
        foreach ( Attribute attr in context.PropertyDescriptor.Attributes )
        {
          SrcFileAttribute srcFileAttr = attr as SrcFileAttribute;
          if ( srcFileAttr != null && !string.IsNullOrEmpty( srcFileAttr.SourceFolder ) )
          {
            parentFolder = FileUtils.FixFolderName( FileUtils.PathSeparatorChar + srcFileAttr.SourceFolder );
            break;
          }
        }
      }

      if ( value == "<None>" )
        return null;

      return new SrcFile( FileUtils.Combine( parentFolder, value ) );
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, SrcFile value )
    {
      if ( value == null )
        return "<None>";
      return FileUtils.GetFileName( value.FileName );
    }
  }
}