using System;
using System.Collections.Generic;
using System.Text;

namespace FixSln.SolutionStruct
{
	public sealed class UnknownProject : Project
	{
		private readonly Guid typeGuid = Guid.Empty;

		public UnknownProject( string name, Guid guid, string filePath, Guid typeGuid ) : base( name, guid, filePath ) { this.typeGuid = typeGuid; }

		public override void Load() { }

		public override Guid TypeGuid { get { return typeGuid; } }
	}
}
