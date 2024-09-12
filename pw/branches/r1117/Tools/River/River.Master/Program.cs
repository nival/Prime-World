using System;
using System.IO;
using System.Reflection;
using System.Runtime.Remoting;
using System.Threading;
using log4net;
using log4net.Config;

namespace River.Master
{
	class Program
	{
		private static bool exit = false;
	  private static readonly ILog logger = LogManager.GetLogger(typeof (Program));

		private static void OnExit( object sender, ConsoleCancelEventArgs e )
		{
			exit = true;
			e.Cancel = true;
		}

		static void Main( string[] args )
		{
      XmlConfigurator.Configure();
			Console.CancelKeyPress += OnExit;
      try
      {
        RemotingConfiguration.Configure(Path.GetFileName(Assembly.GetEntryAssembly().Location) + ".config", false);
        Master.Create("master.rem");
        while (!exit)
          Thread.Sleep(100);
        logger.Info("Shutting down River.Master service...");
        Master.Terminate();
      }
      catch(Exception ex)
      {
        logger.Fatal("Unhandled exception.", ex);
      }
		}
	}
}
