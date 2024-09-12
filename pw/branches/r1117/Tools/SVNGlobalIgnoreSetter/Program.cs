using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SVNGlobalIgnoreSetter
{
	class Program
	{
		static void Main( string[] args )
		{

			try
			{
				string cfg = Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData ), "Subversion\\config" );
				string cfgvalue = "global-ignores = " + System.Configuration.ConfigurationManager.AppSettings["Ignore"];
				Console.ForegroundColor = ConsoleColor.White;
				Console.WriteLine( "Привет. Сейчас я изменю настройки твоего SVN.\n\r" );
				Console.WriteLine( "В файле \n\r{0}\n\rбудет прописана строчка \n\r{1}", cfg, cfgvalue );
				//-------------------------
				List<string> cfgContent = new List<string>();
				cfgContent.AddRange( File.ReadAllLines( cfg ) );

				int targetIdx =
					cfgContent.FindIndex( a => a.Trim().StartsWith( "global-ignores", StringComparison.InvariantCultureIgnoreCase ) );

				if(targetIdx>-1)
					cfgContent[targetIdx] = "#" + cfgContent[targetIdx];
				else
					targetIdx = cfgContent.FindIndex( a => a.Trim().StartsWith( "[miscellany]", StringComparison.InvariantCultureIgnoreCase ) );

				targetIdx++;

				cfgContent.Insert( targetIdx, cfgvalue );

				File.WriteAllLines( cfg, cfgContent.ToArray() );
				//-------------------------
				Console.ForegroundColor = ConsoleColor.Green;
				Console.WriteLine( "\n\r\n\rСделано. Press Any Key." );
			}
			catch ( Exception ex )
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine( "Что-то пошло не так, сообщите об этом доктору\n\r\n\r{0}", ex );
			}

			Console.ReadKey();
		}
	}
}
