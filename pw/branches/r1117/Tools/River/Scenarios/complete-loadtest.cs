//---------------------------------------------------------------------------
// complete-loadtest
// 
// Данный сценарий запускает два тестовых клиента: игровой и социальный.
//---------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.IO;
using River.Core;

[DistributeAttribute(1)]
class CommonScenario : Scenario
{
  private const string main_dir = @"C:\!Test";

  //-----------------------------------------------------------------------------------------------
  // gtc = Game Test Client
  private bool gtc_update = true; // Нужно ли взять новый GameTestClient, или использовать имеющийся
  private string gtc_source = @"L:\QA\Load\testclient\bin";

  // Директория GameTestClient. Если указано gtc_update=true, то текущее значение игнорируется
  // а сценарий сам положит свежую версию тестового клиента в main_dir.
  private string gtc_dir = @"c:\GameTestClient";
  private string gtc_exefile = "GameTestClientApp.exe";
  string gtc_args = "--login pw.SITE:35001 -s loadsocial --socpickupdir ";

  //-----------------------------------------------------------------------------------------------
  // mainpy = Social Test Client
  private bool mainpy_update = true; // Нужно ли брать из svn новый SocialTestClient, или использовать имеющийся
  private string mainpy_source_url = "https://svn.SITE/pw_publish/trunk/Server/Social";
  private string mainpy_source_rev = "HEAD";

  // Директория SocialTestClient. Если указано gtc_update=true, то текущее значение игнорируется
  // а сценарий сам положит свежую версию тестового клиента в main_dir.
  private string mainpy_dir = @"c:\Sources\pw\SocialServer\tests\SocialTestClient";
  private string mainpy_exefile = "main.py";
  private string mainpy_args =
    @"--scenario=load_login --threads=2 --verbose=2 --login=http://localhost:8801 --ping_wait=5.0 --period=0.3" +
    " --logfile=" + mainpy_logfile + " --session_key_dir=" + mainpy_keysdir;

  static string mainpy_logfile = "main.py." + DateTime.Now.ToString("yyMMdd-HHmm") + ".log";
  static string mainpy_keysdir = "keysdir";

  //-----------------------------------------------------------------------------------------------
  // Общие настройки
  private string logs_upload_folder = @"L:\QA\Load\Logs"; // куда складывать логи после выполнения
  private int timeOut = 30 * 60 * 1000; // максимальное время выполнения сценария


  private static void CopyFolder(string sourceFolder, string destFolder)
  {
    if (!Directory.Exists(destFolder))
      Directory.CreateDirectory(destFolder);
    string[] files = Directory.GetFiles(sourceFolder);
    foreach (string file in files)
    {
      string name = Path.GetFileName(file);
      string dest = Path.Combine(destFolder, name);
      File.Copy(file, dest);
    }
    string[] folders = Directory.GetDirectories(sourceFolder);
    foreach (string folder in folders)
    {
      string name = Path.GetFileName(folder);
      string dest = Path.Combine(destFolder, name);
      CopyFolder(folder, dest);
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

  /// <summary>
  /// Инсталляция тестовых клиентов
  /// </summary>
  public override void Install(IContext context)
  {
    if (gtc_update)
    {
      gtc_dir = main_dir + context.MyBot.ID + @"\GameTestClient";
      if (Directory.Exists(gtc_dir))
        DeleteWithAttributes(new DirectoryInfo(gtc_dir));

      CopyFolder(gtc_source, gtc_dir);
    }
    if (!File.Exists(Path.Combine(gtc_dir, gtc_exefile)))
    {
      throw new InvalidOperationException("GameTestClient was not found!");
    }

    if (mainpy_update)
    {
      string socialserver_dir = main_dir + context.MyBot.ID + @"\SocialServer";
      if (Directory.Exists(socialserver_dir))
        DeleteWithAttributes(new DirectoryInfo(socialserver_dir));

      Process svn = new Process();
      svn.StartInfo.FileName = "svn";
      svn.StartInfo.Arguments = String.Format("export -r {0} {1} {2}", mainpy_source_rev, mainpy_source_url, socialserver_dir);
      svn.Start();
      svn.WaitForExit();

      mainpy_dir = Path.Combine(socialserver_dir, @"tests\SocialTestClient");
    }

    if (!File.Exists(Path.Combine(mainpy_dir, mainpy_exefile)))
    {
      throw new InvalidOperationException("SocialTestClient was not found!");
    }

    gtc_args += Path.Combine(mainpy_dir, mainpy_keysdir);
  }

  /// <summary>
  /// Запуск тестовых клиентов
  /// </summary>
  public override void Execute(IContext context)
  {
    Process gtc_process = new Process();
    gtc_process.StartInfo.FileName = Path.Combine(gtc_dir, gtc_exefile);
    gtc_process.StartInfo.Arguments = gtc_args;
    gtc_process.StartInfo.WorkingDirectory = Path.GetDirectoryName(gtc_process.StartInfo.FileName);

    Process mainpy_process = new Process();
    mainpy_process.StartInfo.FileName = "python";
    mainpy_process.StartInfo.Arguments = mainpy_exefile + " " + mainpy_args;
    mainpy_process.StartInfo.WorkingDirectory = Path.GetDirectoryName(mainpy_dir);

    try
    {
      mainpy_process.Start();
      gtc_process.Start();
      if (!gtc_process.WaitForExit(timeOut))
      {
        if (!mainpy_process.HasExited)
          mainpy_process.Kill();

        if (!gtc_process.HasExited)
          gtc_process.Kill();
      }
    }
    finally
    {
      if (!mainpy_process.HasExited)
        mainpy_process.Kill();

      if (!gtc_process.HasExited)
        gtc_process.Kill();

      // Copying GameTestClient log files
      string gtc_logs_folder = Path.Combine(gtc_process.StartInfo.WorkingDirectory, "log\\");
      if (!Directory.Exists(gtc_logs_folder))
        throw new DirectoryNotFoundException("Not found path " + gtc_logs_folder);

      string logs_folder = Path.Combine(logs_upload_folder, context.MyBot.ToString());
      if (!Directory.Exists(logs_folder))
        Directory.CreateDirectory(logs_folder);

      foreach (string f in Directory.GetFiles(gtc_logs_folder))
      {
        string f_dest = Path.Combine(logs_folder, Path.GetFileName(f));
        File.Copy(f, f_dest, true);
      }

      // Copying SocialTestClient log files
      string mainpy_logfile_path = Path.Combine(mainpy_dir, mainpy_logfile);
      if (!File.Exists(mainpy_logfile_path))
        throw new DirectoryNotFoundException("Not found Social test client log " + mainpy_logfile_path);

      File.Copy(mainpy_logfile_path, Path.Combine(logs_folder, mainpy_logfile), true);
    }
  }
}