/*
#about Скрипт ищет во всех измененных объектах ссылки на файлы исходников и проверяет файлы на наличие.
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
#ref sharpsvn.dll
*/

using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using DBTypes;
using EditorLib;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using SharpSvn;

namespace Scripts
{
	internal class ModifiedSourceFilesChecker
	{
		// здесь сложим все найденные ссылки
		private readonly List<KeyValuePair<SrcFile, SrcFileAttribute>> refsToFiles =
			new List<KeyValuePair<SrcFile, SrcFileAttribute>>();

		// функтор добавляет непустые ссылки в список
		private bool Functor(ref SrcFile value, SrcFileAttribute attr, string s)
		{
			if ( !string.IsNullOrEmpty( value.FileName ) ) 
				refsToFiles.Add( new KeyValuePair<SrcFile, SrcFileAttribute>( value, attr ) );

			return true;
		}

		public IEnumerable Main(IEditorCommonApplication app)
		{
			refsToFiles.Clear();
			List<DBID> types = new List<DBID>();
			SvnClient client = new SvnClient();

			// идем по всем xdb файлам в data
			foreach (string folder in GetAllFolders( app, "/" ))
				foreach ( string file in app.FileSystem.GetFiles( folder, "*.xdb" ) )
				{
					string afile = FileUtils.Combine( app.FileSystem.WriteFileSystem.RootPath, file );
					Collection<SvnStatusEventArgs> st = null;
					try
					{
						client.GetStatus( afile, out st );
					}
					catch (SvnWorkingCopyException ex)
					{
						Log.TraceWarning( "Something wrong with this file: {0}. But i'll check it. Details: {1}", afile, ex.ToString() );

						types.Add( DBID.FromFileName( afile, false ) );
						continue;
					}

					foreach (var s in st)
						if ( s.LocalContentStatus == SvnStatus.Added ||
						     s.LocalContentStatus == SvnStatus.Merged ||
						     s.LocalContentStatus == SvnStatus.Replaced ||
						     s.LocalContentStatus == SvnStatus.NotVersioned ||
						     s.LocalContentStatus == SvnStatus.Modified )
							types.Add( DBID.FromFileName( afile, false ) );
				}


			FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 0,
			                                                                       FieldsWalker.ObjectType.DBPtr,
			                                                                       FieldsWalker.ObjectType.All );
			foreach (var t in types)
			{
				DBResource res = DataBase.Get<DBResource>( t ).Get();
				if ( res is Texture && !string.IsNullOrEmpty( (res as Texture).generatedFileName ) ) continue;
				FieldsWalker.VisitFields<SrcFile, SrcFileAttribute>( res, Functor, depth.Functor );
			}

			Log.TraceMessage( "Searching for missing files" );
			int cnt = 0;
			foreach (var f in  refsToFiles)
				if ( !app.SourceFileSystem.IsFileExists( f.Key.FileName ) )
				{
					string suggestedName;
					if ( f.Value != null && string.IsNullOrEmpty( f.Value.SourceFolder ) )
						suggestedName = FileUtils.Combine( FileUtils.GetFolderName( f.Key.GetOwner().DBId.FileName ),
						                                   FileUtils.GetFileName( f.Key.FileName ) );
					else
						suggestedName = FileUtils.Combine( FileUtils.GetFolderName( f.Value.SourceFolder ),
						                                   FileUtils.GetFileName( f.Key.FileName ) );


					if ( suggestedName == f.Key.FileName || !app.SourceFileSystem.IsFileExists( suggestedName ) )
					{
						Log.TraceError( "File missing: {0} | refferer: {1} ", f.Key.FileName, f.Key.GetOwner().DBId.FileName );
						cnt++;
					}
					else
					{
						Log.TraceWarning( "Correcting {0} to {1} in {2}", f.Key.FileName, suggestedName, f.Key.GetOwner().DBId.FileName );
						f.Key.SetFileName( suggestedName );
					}
				}
			DataBase.Store();
			Log.TraceMessage( "TOTAL MISSING FILES COUNT: " + cnt );
			yield return true;
		}

		private static IEnumerable GetAllFolders(IEditorCommonApplication app, string root)
		{
			yield return root;
			foreach (string f in app.FileSystem.GetFolders( root, "*" )) foreach (string s in GetAllFolders( app, f )) yield return s;
		}
	}
}