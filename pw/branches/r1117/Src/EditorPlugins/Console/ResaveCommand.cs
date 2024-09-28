using System;
using System.Collections.Generic;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Console
{
	[CommandName( "resave", "S", "resave specified resource(s)" )]
	public sealed class ResaveCommand : IConsoleCommand
	{
		#region Command's arguments

    [CommandArgument( "types", "t", "treat arguments as types names" )]
    public bool importTypes = false;

    [CommandArgument( "inherit", "i", "resave resources with inherited tyeps too" )]
    public bool inheritTypes = false;

		#endregion

		#region IConsoleCommand Members

    public int Execute( IEditorCommonApplication application, string[] parameters )
		{
			List<DBID> objectsToImport = new List<DBID>();
			if ( !importTypes )
			{
				foreach( string param in parameters )
					objectsToImport.Add( DBID.FromString( param ) );
			}
			else
			{
				Dictionary<Type, bool> types = new Dictionary<Type, bool>();
				foreach( string param in parameters )
				{
					Type type = null;
          if ( param == "DBResource" )
            types.Add( typeof( DBResource ), true );
					else if ( !DataBase.TryGetType( param, out type ) )
						Log.TraceWarning( "Type \"{0}\" not found in database", param );
					else if ( !types.ContainsKey( type ) )
						types.Add( type, true );
				}

				List<Type> _types = new List<Type>();
				foreach( Type type in types.Keys )
					_types.Add( type );

				Dictionary<Type, List<DBID>> typedObjects = new Dictionary<Type,List<DBID>>();
        ObjectsSelector.CollectObjects( application, string.Empty, _types.ToArray(), true, inheritTypes, out typedObjects );
				foreach( KeyValuePair<Type, List<DBID>> objects in typedObjects )
					objectsToImport.AddRange( objects.Value );
			}

			foreach( DBID dbid in objectsToImport )
				DataBase.ChangeCallback( dbid );

			DataBase.Store();
      return 0;
		}

		#endregion
	}
}
