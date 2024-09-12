using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Settings
{
	[AttributeUsage( AttributeTargets.Class )]
	public sealed class ConfigObjectAttribute : Attribute
	{
		private readonly int version = 0;
		private readonly string fileName = string.Empty;
		private readonly bool userObject = false;

    public ConfigObjectAttribute( bool userObject ) : this( userObject, 0, string.Empty ) { }
    public ConfigObjectAttribute( bool userObject, int version ) : this( userObject, version, string.Empty ) { }
    public ConfigObjectAttribute( bool userObject, string fileName ) : this( userObject, 0, fileName ) { }
    public ConfigObjectAttribute( bool userObject, int version, string fileName ) { this.userObject = userObject; this.version = version; this.fileName = fileName; }

		public int Version { get { return version; } }
		public string FileName { get { return fileName; } }
    public bool UserObject { get { return userObject; } }

	}
}
