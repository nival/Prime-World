using System;
using System.Collections.Generic;
using System.Text;

namespace FixSln.SolutionStruct
{
	public sealed class SolutionFolder : Project
	{
		public static Guid SolutionFolderTypeGuid = new Guid( "2150E333-8FDC-42A3-9474-1A3956D46DE8" );

		public SolutionFolder( string name, Guid guid ) : base( name, guid, string.Empty ) { }

		public override void Load() { }

		public override Guid TypeGuid { get { return SolutionFolderTypeGuid; } }
	}
}
