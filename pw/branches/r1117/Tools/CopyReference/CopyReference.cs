using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace CopyReference
{
	class CopyReference
	{
		static void Main( string[] args )
		{
			if ( args.Length != 2 && args.Length != 3 )
				return;

			string projName = args[0];
			string configName = args[1].ToLower().Trim();
			string outputDir = "";
			if ( args.Length == 3 )
				outputDir = args[2];

			Project project;

			if ( projName.IndexOf(".csproj") != -1 )
			{
				project = new VCSProject( projName );
			}
			else
			{
				project = new VCProject( projName );
			}

			foreach ( string file in project.Files )
			{
				if ( file.IndexOf( ".refs" ) != -1 )
				{
					RefFile reffile = new RefFile( Path.Combine( Path.GetDirectoryName( projName ), file ), Path.GetDirectoryName( projName ), configName, outputDir );
					reffile.Do();
				}
			}
		}
	}
}
