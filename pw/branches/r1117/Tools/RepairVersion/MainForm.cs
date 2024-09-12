using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Net;
using System.Threading;
using System.Windows.Forms;
using System.Xml;
using Microsoft.Win32;
using System.Reflection;

namespace fixcontent
{
  public partial class MainForm: Form
  {
    private const string updatesUrl = "pw-updates.SITE";

    private bool forceSelect = false;
    private bool halting = false;
    private bool canExit = false;

    public MainForm ( )
    {
      InitializeComponent();
    }

    private string SearchAppInRegistry ( RegistryKey root, string searchDispalyName )
    {
      using(RegistryKey reg = Registry.CurrentUser.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"))
      {
        foreach(string app in reg.GetSubKeyNames())
        {
          try
          {
            using(RegistryKey appReg = reg.OpenSubKey(app))
            {
              string displayName = appReg.GetValue("DisplayName") as string;
              string installLocation = appReg.GetValue("InstallLocation") as string;
              if(displayName != null && installLocation != null && displayName.StartsWith(searchDispalyName))
                return installLocation;
            }
          }
          catch(Exception e)
          {
            WriteLn("Ошибка при чтении реестра. {0}", e.Message);
          }
        }
      }

      return string.Empty;
    }

    private string FindInstalledApp ( bool force )
    {
      string path = string.Empty;

      if(!force)
      {
        path = Environment.CurrentDirectory;
        if(File.Exists(Path.Combine(path, "launcher.ui.exe")))
          return path;

        path = SearchAppInRegistry(Registry.CurrentUser, "Prime World Launcher");
        if(string.IsNullOrEmpty(path))
          path = SearchAppInRegistry(Registry.LocalMachine, "Prime World Launcher");

        if(!string.IsNullOrEmpty(path) && File.Exists(Path.Combine(path, "launcher.ui.exe")))
          return path;
      }

      OpenFileDialog dialog = new OpenFileDialog() { CheckFileExists = true, CheckPathExists = true, Filter = "Prime World Launcher|launcher.ui.exe", Multiselect = false, RestoreDirectory = true, ShowReadOnly = true, Title = "Выберите каталог с установленным Prime World" };
      if(dialog.ShowDialog(this) == DialogResult.Cancel)
        return string.Empty;
      path = Path.GetDirectoryName(dialog.FileName);
      if(string.IsNullOrEmpty(path) || !File.Exists(Path.Combine(path, "launcher.ui.exe")))
        return string.Empty;
      return path;
    }

    private int FindTargetVersion ( string path, string currModule )
    {
      try
      {
        XmlDocument xml = new XmlDocument();
        xml.Load(Path.Combine(path, String.Format("{0}\\{0}.version", currModule)));
        XmlNode nameNode = xml.DocumentElement.SelectSingleNode("/PackageVersion/PatcherTaskStatus/TargetName/text()");
        if(nameNode == null)
        {
          return -1;
        }

        XmlNode versionNode = xml.DocumentElement.SelectSingleNode("/PackageVersion/PatcherTaskStatus/TargetVersion/text()");
        if(versionNode == null)
        {
          return -1;
        }

        int version = 0;
        if(!int.TryParse(versionNode.Value, out version))
        {
          WriteLn("Prime World установленн некорректно: \"{0}\" недопустимый номер требуемой версии", versionNode.Value);
          return -1;
        }

        WriteLn("Требуемая версия Prime World: {0} ({1})", nameNode.Value, version);
        return version;
      }
      catch(Exception e)
      {
        WriteLn("Ошибка при чтении описателя версии \"{0}\". {1}", Path.Combine(path, String.Format("{0}\\{0}.version", currModule)), e.Message);
        return -1;
      }
    }

    private int FindInstalledVersion ( string path, string currModule )
    {
      try
      {
        XmlDocument xml = new XmlDocument();
        xml.Load(Path.Combine(path, String.Format("{0}\\{0}.version", currModule)));
        XmlNode nameNode = xml.DocumentElement.SelectSingleNode("/PackageVersion/Name/text()");
        if(nameNode == null)
        {
          WriteLn("Prime World установленн некорректно: Ошибка чтения имени версии");
          return -1;
        }

        XmlNode versionNode = xml.DocumentElement.SelectSingleNode("/PackageVersion/Version/text()");
        if(versionNode == null)
        {
          WriteLn("Prime World установленн некорректно: Ошибка чтения номера версии");
          return -1;
        }

        int version = 0;
        if(!int.TryParse(versionNode.Value, out version))
        {
          WriteLn("Prime World установленн некорректно: \"{0}\" недопустимый номер версии", versionNode.Value);
          return -1;
        }

        WriteLn("Установленная версия Prime World: {0} ({1})", nameNode.Value, version);
        return version;
      }
      catch(Exception e)
      {
        WriteLn("Ошибка при чтении описателя версии \"{0}\". {1}", Path.Combine(path, String.Format("{0}\\{0}.version", currModule)), e.Message);
        return -1;
      }
    }

    private XmlDocument GetFilesList ( int version, string currModule )
    {
      //string url = string.Format("http://" + updatesUrl + "/PvP.Source/{0}", version);
      string url = String.Format("http://{0}/{1}.Source/{2}", updatesUrl, currModule, version);
      try
      {
        WebRequest request = WebRequest.Create(url + "/files");
        System.Net.WebProxy proxy = new System.Net.WebProxy(updatesUrl, 80);
        proxy.Credentials = CredentialCache.DefaultCredentials;
        request.Credentials = CredentialCache.DefaultCredentials;
        request.Proxy = proxy;
        request.Credentials = CredentialCache.DefaultCredentials;
        WebResponse response = request.GetResponse() as WebResponse;
        Stream stream = response.GetResponseStream();
        XmlDocument result = new XmlDocument();
        result.Load(stream);
        stream.Close();

        WriteLn("Список файлов загружен с \"{0}\"", url);
        return result;
      }
      catch(Exception e)
      {
        WriteLn("Ошибка при загрузке списка файлов \"{0}\". {1}", url, e.Message);
        return null;
      }
    }

    private List<string> VerifyFiles ( string root, XmlDocument list, out List<string> obsoleteFiles )
    {
      obsoleteFiles = null;
      try
      {
        WriteLn("Проверка файлов в каталоге \"{0}\"", root);
        List<string> result = new List<string>();
        Dictionary<string, object> neededFiles = new Dictionary<string, object>();
        DateTime logTime = DateTime.Now;
        for(int i = 0;i < list.DocumentElement.ChildNodes.Count;++i)
        {
          XmlElement fileDesc = list.DocumentElement.ChildNodes[i] as XmlElement;
          if(fileDesc == null)
            continue;
          string fileName = fileDesc.InnerText;

          if(!fileDesc.HasAttribute("Size"))
            continue;
          XmlAttribute sizeAttribute = fileDesc.Attributes["Size"];
          if(sizeAttribute == null)
            continue;

          long size = 0;
          if(!long.TryParse(sizeAttribute.Value, out size))
            continue;

          neededFiles.Add(fileName.ToLower(), null);
          string fullFilePath = Path.Combine(root, fileName);
          FileInfo file = new FileInfo(fullFilePath);
          if(!file.Exists || file.Length != size)
            result.Add(fileName);

          if(DateTime.Now > logTime)
          {
            WriteLn("{0}% проверено, поврежденных файлов: {1}", i * 100 / list.DocumentElement.ChildNodes.Count, result.Count);
            logTime = DateTime.Now + TimeSpan.FromSeconds(5.0);
          }

          if(halting)
            return null;
        }

        obsoleteFiles = new List<string>();
        List<string> checkDirs = new List<string>(Directory.GetDirectories(root));
        while(checkDirs.Count > 0)
        {
          checkDirs.AddRange(Directory.GetDirectories(checkDirs[0]));
          foreach(var filePath in Directory.GetFiles(checkDirs[0]))
          {
            string fileName = filePath.Substring(root.Length).TrimStart('\\', '/');
            if(!neededFiles.ContainsKey(fileName.ToLower()))
              obsoleteFiles.Add(fileName);

            if(halting)
            {
              obsoleteFiles = null;
              return null;
            }
          }

          if(DateTime.Now > logTime)
          {
            WriteLn("Поиск устаревших файлов ({0}), найдено файлов: {1}", checkDirs[0], obsoleteFiles.Count);
            logTime = DateTime.Now + TimeSpan.FromSeconds(5.0);
          }
          checkDirs.RemoveAt(0);
        }

        WriteLn("100% проверено, поврежденных файлов: {0}", result.Count + obsoleteFiles.Count);
        return result;
      }
      catch(Exception e)
      {
        WriteLn("Ошибка при проверке файлов. {0}", e.Message);
        obsoleteFiles = null;
        return null;
      }
    }

    private void CopyFiles ( int version, string root, List<string> files, string currModule )
    {
      //string url = string.Format("http://" + updatesUrl + "/PvP.Source/{0}", version);
      string url = string.Format("http://{0}/{1}.Source/{2}", updatesUrl, currModule, version);
      for(int i = 0;i < files.Count;++i)
      {
        string file = files[i];
        try
        {
          WriteLn("{0} ({1}/{2})", file, i + 1, files.Count);
          string webFileName = "/" + file.Replace('\\', '/');


          WebRequest request = WebRequest.Create(url + webFileName);
          System.Net.WebProxy proxy = new System.Net.WebProxy(updatesUrl, 80);
          proxy.Credentials = CredentialCache.DefaultCredentials;
          request.Credentials = CredentialCache.DefaultCredentials;
          request.Proxy = proxy;
          WebResponse response = request.GetResponse() as WebResponse;
          Stream stream = response.GetResponseStream();

          string resultFileName = Path.Combine(root, file);
          if(!Directory.Exists(Path.GetDirectoryName(resultFileName)))
            Directory.CreateDirectory(Path.GetDirectoryName(resultFileName));

          using(Stream result = new FileStream(resultFileName, FileMode.Create, FileAccess.Write))
          {
            byte[] buffer = new byte[32768];
            int readen = stream.Read(buffer, 0, buffer.Length);
            long copied = 0;
            DateTime logTime = DateTime.Now;
            while(readen > 0)
            {
              result.Write(buffer, 0, readen);
              copied += readen;
              readen = stream.Read(buffer, 0, buffer.Length);
              if(DateTime.Now > logTime)
              {
                WriteLn("  {0} байт скопировано", copied);
                logTime = DateTime.Now + TimeSpan.FromSeconds(5.0);
              }
              if(halting)
                return;
            }
          }

          stream.Close();
        }
        catch(Exception e)
        {
          WriteLn("Ошибка при исправлении \"{0}\". {1}", file, e.Message);
        }
      }
    }

    private void DeleteFiles ( string root, List<string> files )
    {
      for(int i = 0;i < files.Count;++i)
      {
        string file = files[i];
        try
        {
          WriteLn("Удаление {0} ({1}/{2})", file, i + 1, files.Count);
          string resultFileName = Path.Combine(root, file);
          if(File.Exists(resultFileName))
          {
            File.SetAttributes(resultFileName, FileAttributes.Normal);
            File.Delete(resultFileName);
          }

          if(halting)
            return;
        }
        catch(Exception e)
        {
          WriteLn("Ошибка при удалении \"{0}\". {1}", file, e.Message);
        }
      }
    }

    private void FixContent ( string path )
    {
      List<string> modules = new List<string>() { "PvP", "Castle" };
      foreach(string currModule in modules)
      {
        int version = FindTargetVersion(path, currModule);
        if(version < 0)
          version = FindInstalledVersion(path, currModule);
        if(version >= 0)
        {
          XmlDocument filesXml = GetFilesList(version, currModule);
          if(filesXml != null)
          {
            List<string> obsoleteFiles;
            List<string> files = VerifyFiles(Path.Combine(path, currModule), filesXml, out obsoleteFiles);
            if(files != null && files.Count > 0)
              CopyFiles(version, Path.Combine(path, currModule), files, currModule);
            if(obsoleteFiles != null && obsoleteFiles.Count > 0)
              DeleteFiles(Path.Combine(path, currModule), obsoleteFiles);
          }
        }
      }

      WriteLn(string.Empty);
      canExit = true;
      if(!halting)
        WriteLn("Приложение завершило работу. Если вы хотите скопировать отчет, нажмите Ctrl+C и отчет будет скопирован в буфер обмена");
      else
        Invoke((MethodInvoker)delegate { Close(); });
    }

    private void FixContentThread ( object obj )
    {
      FixContent(obj as string);
    }

    private delegate void WriteSafeHandle ( string message );

    private WriteSafeHandle writeSafe;

    private void WriteSafe ( string message )
    {
      logTextBox.Text += message;
      logTextBox.Text += Environment.NewLine;
      logTextBox.SelectionStart = logTextBox.Text.Length;
      logTextBox.ScrollToCaret();
    }

    private void WriteLn ( string format, params object[] args )
    {
      logTextBox.Invoke(writeSafe, string.Format(format, args));
    }

    protected override void OnLoad ( EventArgs e )
    {
      base.OnLoad(e);
      logTextBox.Font = new Font(FontFamily.GenericMonospace, Font.Size);
      writeSafe = new WriteSafeHandle(WriteSafe);

      WriteLn(Assembly.GetExecutingAssembly().GetName().Version.ToString());

      string path = FindInstalledApp(forceSelect);

      if(string.IsNullOrEmpty(path))
      {
        WriteLn("Prime World не найден на этом компьютере");
        canExit = true;
      }
      else
      {
        WriteLn("Prime World установлен в каталог \"{0}\"", path);
        Thread thread = new Thread(FixContentThread);
        thread.Start(path);
      }
    }

    protected override void OnClosing ( CancelEventArgs e )
    {
      base.OnClosing(e);
      if(!canExit)
      {
        WriteLn("Прервано пользователем");
        halting = true;
        e.Cancel = true;
      }
    }

    private void OnCopyButtonClick ( object sender, EventArgs e )
    {
      Clipboard.SetText(logTextBox.Text);
    }

    [STAThread]
    static void Main ( params string[] args )
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);

      MainForm form = new MainForm();
      form.forceSelect = args.Length == 1 && args[0] == "force";

      Application.Run(form);
    }
  }
}
