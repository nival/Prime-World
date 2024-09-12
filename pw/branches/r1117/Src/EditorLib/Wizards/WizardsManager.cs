using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using EditorLib.Settings;
using libdb.DB;
using libdb.Diagnostics;
using System.Windows.Forms;
using System.IO;
using EditorLib.Menu;
using libdb.IO;
using System.Text.RegularExpressions;

namespace EditorLib.Wizards
{
  [ConfigObject( true )]
  public class RecentImportedConfig : SimpleConfigObject
  {
    public const int MaxRecent = 5;
    public List<string> RecentFiles = new List<string>();

    public void Remember( string file )
    {
      if ( RecentFiles.Contains( file ) )
        RecentFiles.Remove( file );

      if ( RecentFiles.Count >= MaxRecent )
        RecentFiles.RemoveRange( MaxRecent - 1, RecentFiles.Count - MaxRecent + 1 );

      RecentFiles.Insert( 0, file );
    }
  }

  public class WizardsManager
  {
    public readonly static Guid ImportRecentMenuGroupGuid = new Guid( "83137BDC-5CE0-4923-A75A-D18D7157B080" );

    private TypedExtensionContainer<IResourceCreationWizard> creationWizards = new TypedExtensionContainer<IResourceCreationWizard>( true );
    private Dictionary<string, IImportWizard> importWizards = new Dictionary<string, IImportWizard>();

    #region Initialization.

    internal void TryRegisterType( Type type )
    {
      ImportWizardAttribute iWizAttr = TypeUtils.GetAttribute<ImportWizardAttribute>( type, true );
      if ( iWizAttr != null )
      {
        IImportWizard newWizard = TypeUtils.CreateObject( type ) as IImportWizard;
        if ( newWizard != null )
          importWizards[iWizAttr.extension] = newWizard;
      }

      creationWizards.TryRegisterExtensionType( type );
    }

    #endregion

    public ResourceCreationResult CreateResource( DBID dbId, Type type, IEditorWinApplication application, DBResource defaultResource )
    {
      var wizardInstances = creationWizards.GetExtensions( type );
      if ( wizardInstances.Count > 0 )
      {
        if ( wizardInstances.Count != 1 )
        {
          Log.TraceWarning( "There are {0} wizards for type \"{1}\" (selected first).", wizardInstances.Count, type );
        }
        return wizardInstances[0].CreateResource( application, dbId );
      }
      else
      {
        DataBase.Create<DBResource>( dbId, defaultResource );
        return ResourceCreationResult.Succeeded;
      }
    }

    private static Regex validFileNameRegex = new Regex( @"^[_A-Za-z][-_A-Za-z0-9]*\.?[-_A-Za-z0-9]+$", RegexOptions.Compiled );

    private string savedDir;

    public bool RunImportWizard( IEditorWinApplication application )
    {
      if ( importWizards.Count == 0 )
        return false;

      string fileFilter = "All files (*.*)|*.*";

			foreach ( IImportWizard item in importWizards.Values )
			{
				fileFilter += "|" + item.FileDescription + " (" + item.FileExtension + ")|" + item.FileExtension;
			}

      OpenFileDialog dialog = new OpenFileDialog();

      if( !string.IsNullOrEmpty( savedDir ) )
      {
        dialog.InitialDirectory = savedDir;
      }
      else
      {
        dialog.InitialDirectory = application.Application.SourceFileSystem.RootPath.Replace( '/', '\\' );
      }
      
      dialog.Filter = fileFilter;

      dialog.RestoreDirectory = true;//это необходимо, иначе слетит импорт и все что работает по относительным путям
      if ( dialog.ShowDialog() != DialogResult.OK )
        return false;

      Log.TraceMessage( Environment.CurrentDirectory );

      savedDir = Path.GetDirectoryName( dialog.FileName );

      return RunImportWizardExplicit( application, dialog.FileName );
    }

    public bool RunImportWizardExplicit( IEditorWinApplication application, string fileNameExplicit )
    {
      if ( importWizards.Count == 0 || string.IsNullOrEmpty( fileNameExplicit ) )
        return false;

      string fileName = Path.GetFileName( fileNameExplicit );
      if ( !validFileNameRegex.IsMatch( fileName ) )
      {
        MessageBox.Show( "The specified resource (" + fileName + ") has invalid characters in its filename.", "Invalid Resource", MessageBoxButtons.OK, MessageBoxIcon.Warning );
        return false;
      }

      string fileExt = Path.GetExtension( fileNameExplicit );
      IImportWizard wizard;
      if ( importWizards.TryGetValue( fileExt, out wizard ) )
      {
        bool result = wizard.Run( application, fileNameExplicit );
        if ( result )
        {
          var recentConfig = application.Application.Settings.Get<RecentImportedConfig>();
          recentConfig.Remember( fileNameExplicit );
          UpdateImportRecentMenu( application.MainMenu, application.Application.Settings );
        }
        return result;
      }

      MessageBox.Show( "There are no Import Wizards associated with this file type.", "Nothing To Import", MessageBoxButtons.OK, MessageBoxIcon.Information );

      return false;
    }

    public static void UpdateImportRecentMenu( EditorMenu menu, SettingsManager settings )
    {
      menu.ClearMenuGroup( ImportRecentMenuGroupGuid );

      bool hotkeyAdded = false;
      var recentConfig = settings.Get<RecentImportedConfig>();
      foreach ( string item in recentConfig.RecentFiles )
      {
        menu.RegisterMenuCommand( ImportRecentMenuGroupGuid, 0, new ImportRecentMenuItem( item ), hotkeyAdded ? Keys.None : ( Keys.Alt | Keys.R ) );
        hotkeyAdded = true;
      }
    }
  }

  public class ImportWizardMenuItem : IEditorCommand
  {
    public override void Execute( IEditorWinApplication application )
    {
      application.Application.Extensions.Wizards.RunImportWizard( application );
    }

    public override string Name { get { return "Import..."; } }

    public override string TooltipText
    {
      get { return "Run Import Wizard for an Art-Source file"; }
    }

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return EditorLibResources.BigRedButton;
      }
    }
  }

  public class ImportRecentMenuItem : IEditorCommand
  {
    private string fullFileName = string.Empty;

    public ImportRecentMenuItem( string _file )
    {
      fullFileName = _file;
    }

    public override void Execute( IEditorWinApplication application )
    {
      application.Application.Extensions.Wizards.RunImportWizardExplicit( application, fullFileName );
    }

    public override string Name { get { return fullFileName; } }
  }

}
