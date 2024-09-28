using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using DBTypes;
using EditorLib.Extensions;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using EditorLib.Wizards;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;

namespace EditorPlugins.Wizards
{
  [ImportWizard( ".png" )]
  class TextureImportWizard : IImportWizard
  {
    private DBTypes.UIBaseMaterial targetResource = null;
    private string resourceFolder = string.Empty;

    public string FileExtension { get { return "*.png"; } }
    public string FileDescription { get { return "UI Textures"; } }

    public bool Run( EditorLib.IEditorWinApplication application, string fileName )
    {
      if ( !ValidateTarget( application, fileName ) )
        return false;

      DBID dbid = null;
      string shortFileName = Path.GetFileNameWithoutExtension( fileName );

      if ( !DBID.TryCreateDBID( resourceFolder, shortFileName, typeof( DBTypes.UIBaseMaterial ), out dbid ) )
      {
        MessageBox.Show( "Target resource already exists. Import failed.", "Unable To Import", MessageBoxButtons.OK, MessageBoxIcon.Warning );
        return false;
      }

      Texture tex;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Texture Import Wizard Activities" ) )
      {
        targetResource = new UIBaseMaterial();
        DataBase.Create<DBResource>( dbid, targetResource );

        tex = new Texture();

        tex.srcFileName = new SrcFile( resourceFolder + "/" + Path.GetFileName( fileName ) );
        tex.pixelFormat = EPixelFormat.RGBA;
        DataBase.Create( DBID.FromDBID( dbid, true ), tex );
        targetResource.DiffuseMap.texture = DataBase.Get<TextureBase>( tex.DBId );
        targetResource.UseDiffuse = BooleanPin.Present;

        trans.Commit();
      }
 
      if ( application.Application.Extensions.HasImporter( tex.GetType() ) )
      {
        List<Executor.OperationHandler> ops = new List<Executor.OperationHandler>();
        IImporter importer = application.Application.Extensions.CreateImporter( tex.DBId, application.Application, false );
        ops.Add( importer.Import );
        application.Application.OperationExecutor.Start( ops.ToArray() );
      }

      application.Panels.GetSingletonPanel<ObjectsBrowserPanel>().CurrentFolder = resourceFolder;

      return false;
    }

    private bool ValidateTarget( EditorLib.IEditorWinApplication application, string fileName )
    {
      string srcRoot = FileUtils.FixFolderName( application.Application.SourceFileSystem.RootPath ).ToLower();
      string fileFixed = FileUtils.FixFileName( fileName ).ToLower();
      if ( !fileFixed.Contains( srcRoot ) )
      {
        MessageBox.Show( "Source file must be selected from source tree \n(" + srcRoot + ")", "Unable To Import", MessageBoxButtons.OK, MessageBoxIcon.Warning );
        return false;
      }
      fileFixed = FileUtils.GetFolderName( FileUtils.FixFileName( fileName ) );

      resourceFolder = fileFixed.Substring( srcRoot.Length - 1 );

      return true;
    }
  }
}
