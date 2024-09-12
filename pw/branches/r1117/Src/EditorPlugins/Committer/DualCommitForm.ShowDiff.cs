using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using Microsoft.Win32;
using SharpSvn;

namespace EditorPlugins.Committer
{

  public partial class DualCommitForm : Form
  {

    private bool TryFindTortoiseMerge( out string diffExecFullPath, out string diffCommandLine )
    {
      diffExecFullPath = string.Empty;
      diffCommandLine = string.Empty;

      try
      {
        RegistryKey tsvnKey = Registry.ClassesRoot.OpenSubKey( "tsvn\\shell\\open\\command" );
        if ( tsvnKey == null )
          return false;

        string tortoiseProcPath = tsvnKey.GetValue( string.Empty ) as string;
        if ( string.IsNullOrEmpty( tortoiseProcPath ) )
          return false;

        int fileNameIndex = tortoiseProcPath.IndexOf( "TortoiseProc.exe", StringComparison.InvariantCultureIgnoreCase );
        if ( fileNameIndex < 0 )
          return false;

        string tortoisePath = tortoiseProcPath.Substring( 0, fileNameIndex ).TrimStart( '\"' );
        string tortoiseMergePath = Path.Combine( tortoisePath, "TortoiseMerge.exe" );
        if ( File.Exists( tortoiseMergePath ) )
        {
          diffExecFullPath = tortoiseMergePath;
          diffCommandLine = "/base:\"${PrevPath}\" /mine:\"${CurrentPath}\" /basename:\"${FileName}  (rev: ${Revision})\" /minename:\"${FileName}\"";
          return true;
        }
      }
      catch
      {
        return false;
      }

      return true;
    }

    private void ShowDiff( ChangeItemInfo status )
    {
      string diffExecFullPath = null;
      string commandLine = null;

      if ( !TryFindTortoiseMerge( out diffExecFullPath, out commandLine ) )
      {
        return;
      }

      long revision = status.LastChangeRevision;
      string prevFile = Path.GetTempFileName();
      SvnUriTarget baseTarget = new SvnUriTarget( status.Uri, revision );

      SvnClient client = new SvnClient();
      var args = new SvnExportArgs {Overwrite = true};
      if ( !client.Export( baseTarget, prevFile, args) )
      {
        return;
      }

      if ( commandLine.IndexOf( "${PrevPath}" ) >= 0 )
        commandLine = commandLine.Replace( "${PrevPath}", prevFile );
      if ( commandLine.IndexOf( "${CurrentPath}" ) >= 0 )
        commandLine = commandLine.Replace( "${CurrentPath}", status.Path );
      if ( commandLine.IndexOf( "${FilePath}" ) >= 0 )
        commandLine = commandLine.Replace( "${FilePath}", status.Path );
      if ( commandLine.IndexOf( "${FileName}" ) >= 0 )
        commandLine = commandLine.Replace( "${FileName}", Path.GetFileName( status.Path ) );
      if ( commandLine.IndexOf( "${Revision}" ) >= 0 )
        commandLine = commandLine.Replace( "${Revision}", revision.ToString() );

      ProcessStartInfo diffStartupInfo = new ProcessStartInfo( diffExecFullPath );
      diffStartupInfo.Arguments = commandLine;

      diffStartupInfo.CreateNoWindow = true;
      diffStartupInfo.UseShellExecute = false;
      diffStartupInfo.RedirectStandardOutput = true;
      diffStartupInfo.RedirectStandardError = true;

      Process diffProcess = Process.Start( diffStartupInfo );
      diffProcess.WaitForExit();
      File.Delete( prevFile );
    }

  }
}
