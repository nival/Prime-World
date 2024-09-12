using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Menu
{
	public class CommandGroups
	{
		public static Guid FileMenuGroupGuid { get { return fileMenuGroupGuid; } }
		private static Guid fileMenuGroupGuid = new Guid( "2a983d89-542d-4492-8985-5a6c9f6b2eb4" );

		public static Guid EditMenuGroupGuid { get { return editMenuGroupGuid; } }
		private static Guid editMenuGroupGuid = new Guid( "7ca028b1-623b-4fda-92b1-b56934cddbf8" );

		public static Guid ViewMenuGroupGuid { get { return viewMenuGroupGuid; } }
		private static Guid viewMenuGroupGuid = new Guid( "ba82d488-a5f8-4004-be6c-d4fd09f7abe1" );

		public static Guid ToolsMenuGroupGuid { get { return toolsMenuGroupGuid; } }
		public static Guid toolsMenuGroupGuid = new Guid( "343c79f4-5072-4785-abd5-5419731e932e" );

		public static Guid HelpMenuGroupGuid { get { return helpMenuGroupGuid; } }
		public static Guid helpMenuGroupGuid = new Guid( "93d0ec50-cfbb-4dac-8987-347a6646e13f" );
	}
}
