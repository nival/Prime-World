using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
using EditorLib.Settings;

namespace EditorLib.ObjectsBrowser
{
  [ConfigObject( true )]
  public sealed class NewItemTypesConfig : SimpleConfigObject
	{
		public List<string> allTypes = new List<string>();
		public List<string> recentTypes = new List<string>();

		public void UpdateKnownTypes( IEnumerable<Type> knownResources )
		{
			// load existing valid types
			allTypes.Clear();
			foreach ( Type type in knownResources )
				if ( TypeUtils.CanCreate( type ) )
					allTypes.Add( type.Name );

			allTypes.Sort();

			// remove invalid recent entries
			List<string> toRemove = new List<string>();
			
			foreach ( var item in recentTypes)
				if ( !allTypes.Contains( item ) )
					toRemove.Add( item );

			foreach (var item in toRemove)
				recentTypes.Remove( item );
		}

		public void AddRecentItem(string item)
		{
			recentTypes.Remove( item );
			recentTypes.Insert( 0, item );
			if ( recentTypes.Count > 10 )
				recentTypes.RemoveRange( 10, recentTypes.Count - 10 );
		}

	}
}
