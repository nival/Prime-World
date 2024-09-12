using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using libdb.Diagnostics;
using System.Threading;
using System.Diagnostics;

namespace PF_Editor
{
	internal static class Program
	{
		#region External Functions

		[DllImport( "PW_GameLogic.dll" )]
		private static extern void TooSmartCompiler();
    
    [DllImport("User32.dll")]
    private static extern Int32 SetForegroundWindow(IntPtr hWnd);

    const int SW_SHOW = 5;
    const int SW_NORMAL = 1;
    const int SW_RESTORE = 9;

    [DllImport("User32.dll")]
    private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
    
		#endregion


		[STAThread]
		private static int Main( string[] args )
		{
      using (Mutex mutex = new Mutex(false, "PFEditorInstanceMutex"))
      {
        bool isUpdate = false;

        foreach (var arg in args)
        {
          isUpdate = arg.ToLower().Contains("update");
          break;
        }
        
        if(isUpdate)
        {
          return StartUpdate() ? 0 : 1; //errorCode
        }

        bool isFirstInstance = mutex.WaitOne(0, false);

        if (isFirstInstance)
        {
          Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo( "en-US" );

          Log.AttachDumper(new DebuggerDumper(false));
          Application.EnableVisualStyles();
          Application.SetCompatibleTextRenderingDefault(false);
          TooSmartCompiler(); // COMMON REASON OF CRASH HERE: you forgot to set working directory to <project>\Bin! Do this for projects PF_Game, PF_Editor for both Debug and Release configurations!
          var editorApplication = new EditorApplication();

          editorApplication.Initialize(null);
          if (!editorApplication.SourceFileSystem.IsRootPathSet)
            Log.TraceWarning("Source Folder not set. 'My Documents' directory will be used instead. Please set Source Folder from the main menu (TOOLS->SELECT SOURCE FOLDER)");

          PF_Editor.TypesHash.Check();
          PF_Editor.PF_TypesHash.Check();
          //Application.Run( new SplashScreen( editorApplication ) );
          Application.Run(new MainForm(editorApplication, args));
        }
        else
        {            
          using (Process proc = GetEditorProcess())
          {
            if (proc != null)
            {
              ShowWindow(proc.MainWindowHandle, SW_RESTORE);
              SetForegroundWindow(proc.MainWindowHandle);
            }
          }
        }
      }

      return 0;
		}

    private static bool StartUpdate()
    {
      using (Process proc = GetEditorProcess())
      {
        if (proc == null || proc.HasExited || proc.CloseMainWindow())
        {
          if (IsUserWantsUpdate(proc))
          {
            return true;
          }
        }
        else
        {
          MessageBox.Show("Unable to update. Please close all modal dialogs and try again.",
                          Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }
        return false;
      }
    }

    /// <summary>
    /// Возвращает процесс редактора, в котором работает дизайнер.
    /// </summary>
    /// <returns>Process</returns>
    private static Process GetEditorProcess()
    {
      Process current = Process.GetCurrentProcess();
      Process[] processes = Process.GetProcessesByName(current.ProcessName);

      foreach (Process p in processes)
      {
        if (p.Id != current.Id)
        {
          return p;
        }
      }

      return null;
    }

    /// <summary>
    /// Ждет завершения процесса или события отмены обновления.
    /// </summary>
    /// <param name="process"></param>
    /// <returns>True - пользователь согласился обновится. False - пользователь отменил обновление. </returns>
    private static bool IsUserWantsUpdate(Process process)
    {
      try
      {
        //второй процесс не запущен, можно обновлять
        if ((process == null) || (process.HasExited))
          return true;

        EventWaitHandle cancelEvent = EventWaitHandle.OpenExisting("PFEditorCancelCloseEvent");

        /* Если пользователь с момента старта приложения хоть раз делал отмену закртытия главного окна,
         * то при запуске updater сразу решит, что обновление отменяется, 
         * т.к. _cancelEvent будет взведен до завершения основного приложения.
         * Из-за этого надо ресетить эвент, до того как мы отправим запрос на закрытие редактора.
         */
        cancelEvent.Reset();


        //ждем закрытия редактора или отмены обновления
        while (true)
        {
          if (process.WaitForExit(0))
            return true;

          if (cancelEvent.WaitOne())
            return false;

          Thread.Sleep(40);
        }
      }
      catch (WaitHandleCannotBeOpenedException)
      {
        //The named system event does not exist. Therefore we can updatin.g
        return true;
      }
      catch
      {
      }

      return false;
    }
	}
}
