using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using libdb.DB;
using System.IO;
using System.Runtime.InteropServices;
using libdb.Diagnostics;
using DBTypes;
using EditorLib;
using libdb.IO;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Importer.Mesh
{
	public sealed class CollisionGeometryImporter : Importer<CollisionGeometry>
	{
		protected override bool KnownDuration { get { return false; } }

		protected override bool Process( DBPtr<CollisionGeometry> resource, IEditorCommonApplication application, bool fast )
		{
			Progress( string.Format( "Import collision geometry from \"{0}\"", resource.DBId.Name ) );

			if ( ReferenceEquals( resource.Get(), null ) )
			{
				Log.TraceError( "Cannot load resource \"{0}\"", resource.DBId.Name );
				return false;
			}

			if ( !fast )
			{
				if ( !ImportMayaToIntermediate( resource, application ) )
				{
					return false;
				}
			}

			Progress( string.Format( "Import binary collision geometry from \"{0}\"", resource.DBId.Name ) );
      bool res = ImportIntermediateToBin( resource, application );
      DataBase.ChangeResource( resource.DBId, resource );
			return res;
		}

		private bool ImportMayaToIntermediate( DBTypes.CollisionGeometry geometry, IEditorCommonApplication application )
		{
			if ( string.IsNullOrEmpty( geometry.srcFileName.FileName ) )
			{
				Log.TraceError( "srcFileName not specified in resource \"{0}\"", geometry.DBId.Name );
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( geometry.srcFileName.FileName ) );
			if ( !File.Exists( srcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", srcFileName );
				return false;
			}

			string selection = geometry.selection;
			if ( selection.Length == 0 )
			{
				selection = "AI";
			}

			string tempFileName = FileUtils.FixFileName( Path.GetTempFileName() );
			
			if ( !MayaOperationsUtility.LaunchCollisionGeometryImportScript( srcFileName, selection, tempFileName ) )
			{
				Log.TraceError( "Maya exporter failed." );
				return false;
			}

			string mayaFileName = FileUtils.FixFileName( geometry.mayaFileName );
			application.FileSystem.AddFile( tempFileName, mayaFileName );

			return true;
		}

		private static bool ImportIntermediateToBin( DBTypes.CollisionGeometry geometry, IEditorCommonApplication application )
		{
			if ( application.FileSystem.GetFileInfo( geometry.fileName ).IsFileExists )
				application.FileSystem.DeleteFile( geometry.fileName );

			if ( !application.FileSystem.FileExists( geometry.mayaFileName ) )
			{
				Log.TraceError( "Import collision geometry for \"{0}\" failed. Intermediate file \"{1}\" not found", geometry.DBId.Name, geometry.mayaFileName );
				return false;
			}

			byte[] mayaFileData = FileUtils.ReadFile( application.FileSystem, geometry.mayaFileName );
			GCHandle mayaFileDataHandle = GCHandle.Alloc( mayaFileData, GCHandleType.Pinned );

			byte[] geometryFileBuffer = new byte[10 * 1024 * 1024];
			GCHandle geometryFileBufferHandle = GCHandle.Alloc( geometryFileBuffer, GCHandleType.Pinned );

			int geometryFileBufferActualLenth = 0;
			int result = MeshUtils.ConvertCollisionGeometry( mayaFileDataHandle.AddrOfPinnedObject(), mayaFileData.Length,
				geometryFileBufferHandle.AddrOfPinnedObject(), geometryFileBuffer.Length, out geometryFileBufferActualLenth );

			if ( result != 0 )
			{
				Log.TraceError( "Import collision geometry for \"{0}\" failed", geometry.DBId.Name );
				return false;
			}

			if ( geometryFileBufferActualLenth > geometryFileBuffer.Length )
			{
				Log.TraceError( "Import collision geometry for \"{0}\" failed. Buffer overflow error", geometry.DBId.Name );
				return false;
			}

			BinaryWriter writer = new BinaryWriter( application.FileSystem.CreateFile( geometry.fileName ) );
			writer.Write( geometryFileBuffer, 0, geometryFileBufferActualLenth );
			writer.Close();

			return true;
		}
	}
}
