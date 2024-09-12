using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Settings
{
	[AttributeUsage( AttributeTargets.Field | AttributeTargets.Property )]
	public class ConfigObjectFieldAttribute : Attribute
	{
		private readonly string fileName = string.Empty;
		private readonly bool userObject = false;

    public ConfigObjectFieldAttribute( bool userObject ) : this( userObject, string.Empty ) { }
    public ConfigObjectFieldAttribute( bool userObject, string fileName ) { this.userObject = userObject; this.fileName = fileName; }

		public string FileName { get { return fileName; } }
		public bool UserObject { get { return userObject; } }
	}
}
