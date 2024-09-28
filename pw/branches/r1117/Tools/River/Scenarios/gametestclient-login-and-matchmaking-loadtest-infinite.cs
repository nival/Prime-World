using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using River.Core;

[DistributeAttribute( 1 )]
class CommonScenario : Scenario
{
  private const string src_image_folder = @"L:\QA\Load\testclient\bin";
  private const string common_logs_folder = @"L:\QA\Load\testclient\logs";
  private const string dst_root = @"C:\!GameTestClient1";
  private const string exename = "GameTestClientApp.exe";
  private const string args = "--login pws.zzima.com:35001 -s loadgamesrv3 --clients 300";
  
  private string dst_image_folder;
  private const int timeOut = 60 * 60 * 1000;

  static public void CopyFolder( string sourceFolder, string destFolder )
  {
    if ( !Directory.Exists( destFolder ) )
      Directory.CreateDirectory( destFolder );
    string[] files = Directory.GetFiles( sourceFolder );
    foreach ( string file in files )
    {
      string name = Path.GetFileName( file );
      string dest = Path.Combine( destFolder, name );
      File.Copy( file, dest );
    }
    string[] folders = Directory.GetDirectories( sourceFolder );
    foreach ( string folder in folders )
    {
      string name = Path.GetFileName( folder );
      string dest = Path.Combine( destFolder, name );
      CopyFolder( folder, dest );
    }
  }

  private static void DeleteWithAttributes(FileSystemInfo info)
  {  
    info.Attributes = FileAttributes.Normal;  
    if (info is DirectoryInfo)  
    {  
      foreach (FileSystemInfo i in (info as DirectoryInfo).GetFileSystemInfos())  
      {  
        DeleteWithAttributes(i);  
      }  
    }  
    info.Delete();  
  }  
  
  public override void Install( IContext context )
  {
    dst_image_folder = dst_root;
    dst_image_folder += @"\Bin" + context.MyBot.ID;

    if ( Directory.Exists( dst_image_folder ) )
      DeleteWithAttributes(new DirectoryInfo(dst_image_folder));

    CopyFolder( src_image_folder, dst_image_folder );
  }

  public override void Execute( IContext context )
  {
    Process p = new Process();
    p.StartInfo.FileName = Path.Combine( dst_image_folder, exename );
    p.StartInfo.Arguments = args;	  
    p.StartInfo.WorkingDirectory = Path.GetDirectoryName( p.StartInfo.FileName );
    try
    {
      while (true)
      {
        p.Start();
        if (!p.WaitForExit(timeOut))
          p.Kill();
      }
    }
    finally
    {
      p.Kill();
      
      // Copying log files in any case
      string source_folder = Path.Combine(p.StartInfo.WorkingDirectory, "log\\");
      if (!Directory.Exists(source_folder))
        throw new DirectoryNotFoundException("Not found path " + source_folder);

      string logs_folder = Path.Combine(common_logs_folder, context.MyBot.ToString());
      if (!Directory.Exists(logs_folder))
        Directory.CreateDirectory(logs_folder);

      foreach (string f in Directory.GetFiles(source_folder))
      {
        string f_dest = Path.Combine(logs_folder, Path.GetFileName(f));
        File.Copy(f, f_dest, true);
      }
    }
  }
}
