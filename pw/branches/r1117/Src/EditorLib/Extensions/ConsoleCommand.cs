using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Plugin
{
	public interface IConsoleCommand
	{
    int Execute( IEditorCommonApplication application, string[] parameters );
	}
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public sealed class CommandNameAttribute : Attribute
	{
		public readonly string fullName = string.Empty;
		public readonly string shortName = string.Empty;
		public readonly string description = string.Empty;
		public CommandNameAttribute( string _fullName, string _shortName, string _description )
		{ fullName = _fullName; shortName = _shortName; description = _description; }
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public sealed class CommandArgumentAttribute : Attribute
	{
		public readonly string fullName = string.Empty;
		public readonly string shortName = string.Empty;
		public readonly string description = string.Empty;
		public CommandArgumentAttribute( string _fullName, string _shortName, string _description )
		{ fullName = _fullName; shortName = _shortName; description = _description; }
	}
}
