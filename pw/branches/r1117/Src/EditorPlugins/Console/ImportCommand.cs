using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.Text.RegularExpressions;
using System.Threading;
using EditorLib.IO;
using EditorLib.Operations;
using EditorLib.Plugin;
using libdb.DB;
using libdb.UndoRedo;
using EditorLib;
using System.Reflection;
using libdb;

namespace EditorPlugins.Console
{
	[CommandName( "import", "I", "import specified resource(s)" )]
	public sealed class ImportCommand : IConsoleCommand
	{
		#region Command's arguments

		[CommandArgument( "fields", "f", "import subfields of specified objects (use field{.field}{;field{.field}})" )]
		public string importFields = string.Empty;

		[CommandArgument( "types", "t", "treat arguments as types names (use type{.field} to import subfields)" )]
		public bool importTypes = false;

		[CommandArgument( "fast", "", "perform only fast import" )]
		public bool fastImport = false;

		#endregion

		private static object[] CollectObjectsToImport( DBResource rootObject, string _fieldNames )
		{
			List<object> objects = new List<object>();
			objects.Add( rootObject );
			string[] fieldNames = _fieldNames.Split( '.' );
			for ( int i = 0; i < fieldNames.Length; ++i )
			{
				string fieldName = fieldNames[i];

				DBFieldInfo field = null;
				DBFieldInfo[] fields = TypeUtils.GetFields( rootObject.GetType(), true );
				foreach ( DBFieldInfo _field in fields )
				{
					if ( _field.Name == fieldName )
					{
						field = _field;
						break;
					}
				}

				if ( field == null )
				{
					Log.TraceError( "Field \"{0}\" (\"{1}\") not found in resource \"{2}\"", fieldName, _fieldNames, rootObject.DBId.ToString() );
					return new object[0];
				}

				if ( TypeUtils.GetTypeFromPtr( field.FieldType ) != null )
				{
					Log.TraceError( "Field \"{0}\" (\"{1}\") is DBPtr in resource \"{2}\". Specify type instead", fieldName, _fieldNames, rootObject.DBId.ToString() );
					return new object[0];
				}

				if ( !TypeUtils.IsList( field.FieldType ) )
				{
					for ( int n = 0; n < objects.Count; ++n )
						objects[n] = field.GetValue( objects[n] );
				}
				else
				{
					// actually count property is from ICollection<> interface so we have do some work extract it
					PropertyInfo countProperty = TypeUtils.GetProperty( field.FieldType, "Count" );
					PropertyInfo indexProperty = TypeUtils.GetProperty( field.FieldType, "Item" );
					if ( countProperty == null || indexProperty == null )
					{
						Log.TraceError( "Cannot extract list from field \"{0}\" (\"{1}\") in resource \"{2}\"", fieldName, _fieldNames, rootObject.DBId.ToString() );
						return new object[0];
					}

					List<object> _objects = new List<object>();
					foreach ( object obj in objects )
					{
						object fieldValue = field.GetValue( obj );
						int count = (int)countProperty.GetValue( fieldValue, new object[0] { } );
						for ( int n = 0; n < count; ++n )
						{
							object[] index = new object[1] { n };
							_objects.Add( indexProperty.GetValue( fieldValue, index ) );
						}
					}

					objects = _objects;
				}
			}

			return objects.ToArray();
		}

		private static void ImportObjects( IEditorCommonApplication application, List<DBID> dbids, string fieldNames, bool fast )
		{
			foreach ( DBID dbid in dbids )
			{
				DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
				
				if ( ptr.Get() == null )
					Log.TraceError( "Cannot find resource \"{0}\"", dbid.ToString() );
				else
				{
					if ( string.IsNullOrEmpty( fieldNames ) )
						application.Extensions.Import( dbid, application, fast );
					else
					{
						object[] objects = CollectObjectsToImport( ptr.Get(), fieldNames );
						foreach( object obj in objects )
						{
							IOwnerable ownerableObj = obj as IOwnerable;
							if ( ownerableObj != null )
								application.Extensions.Import( ownerableObj, application, fast );
						}
					}
				}
			}
		}

		private class ObjectsToImportColletor
		{
			private static Dictionary<Type, ObjectsToImportColletor> collectedObjects = new Dictionary<Type, ObjectsToImportColletor>();

			public static bool RegisterFields( string _fieldNames )
			{
				string typeName = _fieldNames;
				string fieldNames = string.Empty;
				int dotPos = _fieldNames.IndexOf( '.' );
				if ( dotPos > 0 && dotPos < _fieldNames.Length - 1 )
				{
					typeName = _fieldNames.Substring( 0, dotPos );
					fieldNames = _fieldNames.Substring( dotPos + 1 );
				}

				Type type = null;
				if ( !DataBase.TryGetType( typeName, out type ) )
				{
					Log.TraceError( "Type \"{0}\" (\"{1}\") is not registred", typeName, _fieldNames );
					return false;
				}

				ObjectsToImportColletor collector = null;
				if ( !collectedObjects.TryGetValue( type, out collector ) )
				{
					collector = new ObjectsToImportColletor( type );
					collectedObjects.Add( type, collector );
				}

				if ( collector.fields.ContainsKey( fieldNames ) )
				{
					Log.TraceError( "Field \"{0}\" (\"{1}\") registred twice", fieldNames, _fieldNames );
					return false;
				}

				collector.fields.Add( fieldNames, true );
				return true;
			}

			public static void CollectObjects( IEditorCommonApplication application )
			{
				List<Type> typesToFind = new List<Type>();
				foreach ( Type type in collectedObjects.Keys )
					typesToFind.Add( type );

				Dictionary<Type, List<DBID>> lists = new Dictionary<Type, List<DBID>>();
				ObjectsSelector.CollectObjects( application, string.Empty, typesToFind.ToArray(), true, false, out lists );
				foreach ( KeyValuePair<Type, List<DBID>> list in lists )
				{
					ObjectsToImportColletor collector = null;
					if ( collectedObjects.TryGetValue( list.Key, out collector ) && collector != null )
						collector.dbids = list.Value;
				}
			}

			public static void PerformImport( IEditorCommonApplication application, bool fast )
			{
				foreach ( ObjectsToImportColletor collector in collectedObjects.Values )
				{
					foreach ( string fieldNames in collector.fields.Keys )
					{
						ImportObjects( application, collector.dbids, fieldNames, fast );
					}
				}
			}

			private readonly Type objectsType = null;
			private List<DBID> dbids = null;
			private Dictionary<string, bool> fields = new Dictionary<string, bool>();

			private ObjectsToImportColletor( Type _objectsType ) { objectsType = _objectsType; }
		}

		#region IConsoleCommand Members

		public int Execute( IEditorCommonApplication application, string[] parameters )
		{
			if ( !importTypes )
			{
				List<DBID> dbids = new List<DBID>();
				foreach ( string param in parameters )
					dbids.Add( DBID.FromString( param ) );

				ImportObjects( application, dbids, importFields, fastImport );
			}
			else
			{
				foreach( string param in parameters )
					ObjectsToImportColletor.RegisterFields( param );

				ObjectsToImportColletor.CollectObjects( application );
				ObjectsToImportColletor.PerformImport( application, fastImport );
			}

			DataBase.Store();
      return 0;
		}

		#endregion
	}
}
