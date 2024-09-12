using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Settings
{
	public sealed class ConfigVersionAttribute : Attribute
	{
		private readonly int version = 0;
		public ConfigVersionAttribute( int version ) { this.version = version; }

		public int Version { get { return version; } }
	}
}
