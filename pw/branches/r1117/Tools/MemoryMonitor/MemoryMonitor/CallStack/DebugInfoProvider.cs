using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace MemoryMonitor.CallStack
{
  public class DebugInfoProvider
  {
    private ModuleLayout moduleLayout = null;
    private Dictionary<string, ModuleLineInfo> lineInfos = new Dictionary<string, ModuleLineInfo>();
    private string lastPDBPath = string.Empty;

    public string GetInfo( uint address )
    {
      if ( null == moduleLayout )
        return "No module info loaded";
      string moduleName = moduleLayout.GetModuleName( address );

      if ( string.IsNullOrEmpty( moduleName ) )
        return "Unknown module";

      if ( !lineInfos.ContainsKey( moduleName ) )
        TryLoadPDB( moduleName );

      ModuleLineInfo lineInfo = lineInfos[moduleName];
      if ( null == lineInfo )
        return moduleName + ", no debug info";
      else
        return lineInfo.GetLineInfo( address - moduleLayout.GetModuleBase( moduleName ) );
    }

    public void LoadModuleLayout( string fileName )
    {
      ModuleLayout oldLayout = moduleLayout;
      moduleLayout = new ModuleLayout();

      try
      {
        StreamReader sr = new StreamReader( fileName, System.Text.Encoding.Default );
        string line;

        while ( ( line = sr.ReadLine() ) != null )
        {
          if ( line.Length == 0 )
            continue;

          string[] parts = line.Split( ',' );
          if ( parts.Length != 3 )
            throw new Exception( "Wrong format" );

          UInt32 moduleStart = UInt32.Parse( parts[0].Trim(), System.Globalization.NumberStyles.HexNumber );
          UInt32 moduleLength = UInt32.Parse( parts[1].Trim(), System.Globalization.NumberStyles.HexNumber );

          moduleLayout.RegisterModule( parts[2].Trim(), moduleStart, moduleLength );
        }
      }
      catch
      {
        MessageBox.Show( "Module Layout Info loading failed" );
        moduleLayout = oldLayout;
      }
    }

    private void TryLoadPDB( string moduleName )
    {
      lineInfos[moduleName] = null;
      ModuleLineInfo moduleInfo = TryFindPDB( moduleName );

      if ( null == moduleInfo )
        return;

      moduleInfo.LoadLines();

      lineInfos[moduleName] = moduleInfo;
    }

    private ModuleLineInfo TryFindPDB( string moduleName )
    {
      ModuleLineInfo moduleInfo = null;

      string moduleFileName = moduleLayout.GetModulePath( moduleName );
      string modulePath = Path.GetDirectoryName( moduleFileName );
      string moduleShortName = Path.GetFileNameWithoutExtension( moduleFileName );

      string pdbName = modulePath + "\\" + moduleShortName + ".pdb";
      if ( File.Exists( pdbName ) )
        moduleInfo = new ModuleLineInfo( pdbName );
      else if ( !string.IsNullOrEmpty( lastPDBPath ) )
      {
        pdbName = lastPDBPath + "\\" + moduleShortName + ".pdb";
        if ( File.Exists( pdbName ) )
          moduleInfo = new ModuleLineInfo( pdbName );
      }

      if ( null == moduleInfo && modulePath.ToUpper().Contains( "WINDOWS" ) )
        return null;

      if ( null == moduleInfo )
      {
        OpenFileDialog dialog = new OpenFileDialog();
        dialog.CheckFileExists = true;
        dialog.CheckPathExists = true;
        dialog.InitialDirectory = lastPDBPath;
        dialog.Filter = "Debug Info (" + moduleShortName + ".pdb" + ")|" + moduleShortName + ".pdb";
        if ( DialogResult.OK == dialog.ShowDialog() && File.Exists( dialog.FileName ) )
        {
          moduleInfo = new ModuleLineInfo( dialog.FileName );
          lastPDBPath = Path.GetDirectoryName( dialog.FileName );
        }
      }



      return moduleInfo;
    }
  }
}
