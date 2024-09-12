/*
#about Ищет ссылки на файлы и сверяет их Case c Case реального файла
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
	class FixFileREfCases
	{
		public IEnumerable Main( EditorLib.IEditorWinApplication app )
		{
			Log.TraceMessage( "Wrongcased references fixer started." );

			List<DBID> types;
			int tcount = ObjectsSelector.CollectObjects( app.Application, "/", typeof( DBResource ), true, true, out types );
			Log.TraceMessage( tcount + " types found" );

			foreach ( DBID t in types )
			{
				DBResource res = DataBase.Get<DBResource>( t ).Get();

				foreach ( PropertyInfo memb in res.GetType().GetProperties() )
				{
					if ( TypeUtils.GetAttribute<DstFileAttribute>( memb, false ) == null || (!(memb.GetValue( res, null ) is string)) )
						continue;

					string refName = memb.GetValue( res, null ).ToString();
					foreach(string f in app.Application.FileSystem.GetFiles(Path.GetDirectoryName(refName),"*"))
					{
						if ( string.Compare( FileUtils.FixFileName( f ).Trim( FileUtils.PathSeparatorChar ), 
																 FileUtils.FixFileName( refName ).Trim( FileUtils.PathSeparatorChar ), 
																 StringComparison.CurrentCultureIgnoreCase ) !=
								 string.Compare( FileUtils.FixFileName( f ).Trim( FileUtils.PathSeparatorChar ),
																 FileUtils.FixFileName( refName ).Trim( FileUtils.PathSeparatorChar ),
																 StringComparison.CurrentCulture ))
						{
							Log.TraceMessage("Wrong casing found: ref='{0}' in '{2}.{3}'. real file name is '{1}'", refName, f, memb.Name, memb.DeclaringType.Name );
						//	memb.SetValue( res, FileUtils.FixFileName( f ), null );
							break;
						}
					}
				}
			}
			Log.TraceMessage( " Wrongcased references fixer finished." );
			yield return true;
		}

	}
}
