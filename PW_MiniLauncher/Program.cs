using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace PW_MiniLauncher
{
  static class Program
  {
    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main( string[] args )
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      string defaultName = "";
      if ( args.Length > 0 )
        defaultName = args[0];

      if ( args.Contains("force_play") )
        LoginForm.LaunchGame(defaultName, false);
            else
                Application.Run(new LoginForm(defaultName));
    }
  }
}
