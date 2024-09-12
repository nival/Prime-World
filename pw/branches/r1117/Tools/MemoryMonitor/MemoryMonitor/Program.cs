using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace MemoryMonitor
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
      Application.SetCompatibleTextRenderingDefault( false );
      Application.Run( new Forms.MainForm( null != args && args.Length > 0 ? args[0] : null ) );
    }
  }
}
