using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.IO;
using System.Reflection;

namespace libdb.DB
{
	internal sealed class DBTypesCache
	{
		private readonly Dictionary<string, Type> typeCache = new Dictionary<string, Type>();

		public void LoadTypesFromAssembly( string fileName )
		{
			try
			{
				string activeAssemblyLocation = Path.GetDirectoryName( Assembly.GetExecutingAssembly().Location );
				string fullFileName = Path.Combine( activeAssemblyLocation, fileName );
				if ( !File.Exists( fullFileName ) )
					fullFileName = Path.GetFullPath( fileName );

				Assembly assembly = Assembly.LoadFile( fullFileName );
				foreach ( Type type in assembly.GetTypes() )
				{
					if ( !type.FullName.Contains( "DBTypes" ) )
						continue;
					if ( type.DeclaringType != null )
						continue;
					if ( typeCache.ContainsKey( type.Name ) )
						Log.TraceWarning( "Cannot register type \"{0}\" from assembly \"{1}\". Type already registred", type.Name, fileName );
					else
						typeCache.Add( type.Name, type );
				}
			}
			catch ( Exception e )
			{
				Log.TraceError( "Cannot load types from assembly \"{0}\". Exception {1}: {2}", fileName, e.ToString(), e.Message );
			}
		}

		public bool TryGetType( string typeName, out Type result )
		{
			return typeCache.TryGetValue( typeName, out result );
		}

		public IEnumerable<Type> KnownTypes { get { return typeCache.Values; } }
	}
}
