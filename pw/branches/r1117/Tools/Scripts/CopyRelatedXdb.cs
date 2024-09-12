/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
	public class CopyRelatedXdb
	{
		private const string DESTINATION_FOLDER = @"C:\publish-pbt-shipping\Data";
		private List<DBID> roots = new List<DBID>();

		private IEditorCommonApplication application = null;
		private List<DBID> resources = new List<DBID>();	

		public IEnumerable Main( IEditorCommonApplication app )
		{
			application = app;
			
			List<DBID> types;

			//тут надо добавить рутовые XDB
			roots.Add( DBID.FromFileName( "Session.ROOT", false ) );
			roots.Add( DBID.FromFileName( "/MiniGames/MinigameCommon.xdb", false ) );

			ObjectsSelector.CollectObjects( application, "/UI/", typeof( DBResource ), true, true, out types );
			roots.AddRange(types);
			types.Clear();

			ObjectsSelector.CollectObjects( application, "/Maps/Multiplayer/PFmap/", typeof( DBResource ), true, true, out types );
			roots.AddRange( types );
			types.Clear();

			ObjectsSelector.CollectObjects( application, "/MiniGames/Minigame02/", typeof( DBResource ), true, true, out types );
			roots.AddRange( types );
			types.Clear();

			Directory.CreateDirectory( DESTINATION_FOLDER );
			Log.TraceMessage( "Destination folder: '{0}'", DESTINATION_FOLDER );
			
			foreach ( DBID dbid in roots )
			{
				AddResources( dbid );
			}

			int cnt = CopyDBResources();
			Log.TraceMessage( "{0} resources copied", cnt );

			cnt += CopyDstFiles();
			Log.TraceMessage( "{0} fiels copied", cnt );

			yield break;
		}

		private void AddResources( DBID _dbid )
		{
			if ( resources.Contains( _dbid ) )
				return;

			resources.Add( _dbid );

			DBPtr<DBResource> resource = DataBase.Get<DBResource>( _dbid );
			resource.ForAllStates(res =>
			                      {
															List<DBID> list = FieldsWalker.CollectRelatedObjects( _dbid, 0, false );

															foreach ( var item in list )
															{
																AddResources( item );
															}
			                      });		
		}

		private int CopyDBResources()
		{
			var winFileSystem = new WinFileSystem( DESTINATION_FOLDER, true );
			application.FileSystem.RegisterFileSystem( winFileSystem );
			var oldWriteFileSystem = application.FileSystem.WriteFileSystem;
			application.FileSystem.WriteFileSystem = winFileSystem;

			int cnt = 0;

			foreach ( DBID id in resources )
			{
				DataBase.ChangeCallback( id );
				cnt++;
			}

			DataBase.Store( true );

			application.FileSystem.UnregisterFileSystem( winFileSystem );
			application.FileSystem.WriteFileSystem = oldWriteFileSystem;
			return cnt;
		}

		private int CopyDstFiles( )
		{
			int cnt = 0;

			foreach ( DBID id in resources )
			{
				CopyDst(id);
				cnt++;
			}

			return cnt;
		}

		private void CopyDst( DBID _dbid )
		{
			DBResource resource = DataBase.Get<DBResource>(_dbid).Get();

			DBFieldInfo[] fields = TypeUtils.GetFields(resource.GetType(), false);

			foreach (DBFieldInfo field in fields)
			{		
				if ( TypeUtils.HasAttribute<DstFileAttribute>( field, true ) && !TypeUtils.HasAttribute<NoCodeAttribute>(field, true) )
				{
					string fileName = (string)field.GetValue(resource);

					DirectoryInfo dirInfo = Directory.CreateDirectory(
						FileUtils.Combine( DESTINATION_FOLDER, FileUtils.GetFolderName( fileName ) ) );

					string srcFile = FileUtils.Combine( application.FileSystem.RootPath, fileName );
					string dstFile = FileUtils.Combine( dirInfo.FullName, FileUtils.GetFileName( fileName ) );

					//if(!File.Exists(srcFile))
					//{
					//  Log.TraceWarning("File \"{0}\" not found", srcFile);
					//  continue;
					//}

					try
					{
						File.Copy( srcFile, dstFile, true );
					}
					catch (Exception err)
					{
						continue;
					}
								
				}
			}
		}

	}
}