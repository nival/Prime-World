using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using libdb.DB;
using EditorLib;
using libdb.Diagnostics;
using libdb.IO;
using System.Runtime.InteropServices;
using System.IO;
using EditorNative;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Importer.Mesh
{
  [ApplicableForDeriver]
  public sealed class SkeletonImporter : Importer<DBTypes.Skeleton>
	{
		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertSkeletonSafe( string intermediateFileName, string gameFileName );

		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skeleton"; }

		protected override bool Process( libdb.DB.DBPtr<DBTypes.Skeleton> resource, EditorLib.IEditorCommonApplication application, bool fast )
		{
			if ( !fast )
			{
				if ( !ImportMayaToIntermediate( resource, application ) )
					return false;
			}

			if ( !ImportIntermediateToBin( resource, application ) )
				return false;

			return true;
		}

		private static bool ImportMayaToIntermediate( DBPtr<DBTypes.Skeleton> resource, IEditorCommonApplication application )
		{
			DBTypes.Skeleton skeleton = resource.Get();

			if ( string.IsNullOrEmpty( skeleton.srcFileName.FileName ) )
			{
				Log.TraceError( "srcFileName not specified in resource \"{0}\"", resource.DBId.Name );
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if ( !File.Exists( srcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", srcFileName );
				return false;
			}

			string tempFileName = FileUtils.FixFileName( Path.GetTempFileName() );

			if ( !MayaOperationsUtility.LaunchSkeletonImportScript( srcFileName, skeleton.selection, tempFileName	) )
			{
				Log.TraceError( "Maya exporter returned error." );
			}

			string mayaFileName = FileUtils.FixFileName( skeleton.mayaFileName );
			application.FileSystem.AddFile( tempFileName, mayaFileName );

			return true;
		}

		private static bool ImportIntermediateToBin( DBPtr<DBTypes.Skeleton> resource, IEditorCommonApplication application )
		{
			var skeleton = resource.Get();

			string mayaFileName = application.FileSystem.GetRealFileName( skeleton.mayaFileName );
			if ( !File.Exists( mayaFileName ) )
			{
				Log.TraceError( "Intermediate file (\"{0}\") not found for resource \"{1}\"", skeleton.mayaFileName, resource.DBId.Name );
				return false;
			}

			if ( application.FileSystem.GetFileInfo( skeleton.skeletonFileName ).IsFileExists )
				application.FileSystem.DeleteFile( skeleton.skeletonFileName );

			application.FileSystem.CreateFile( skeleton.skeletonFileName ).Close();
			string skeletonFileName = application.FileSystem.GetRealFileName( skeleton.skeletonFileName );

      EditorRender.MarkAsDirtySkeletonData( skeleton.skeletonFileName );
      int result = ConvertSkeletonSafe(mayaFileName, skeletonFileName);
			if ( result < 0 )
			{
				Log.TraceError( "Import skeleton from \"{0}\" failed with code {1}", resource.DBId.Name, result );
				return false;
			}

			return true;
		}
	}

  [ApplicableForDeriver]
  public sealed class DBAnimatedSceneComponentImporter : Importer<DBTypes.DBAnimatedSceneComponent>
	{
		[DllImport("MeshConverter", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 ConvertSkeletonSafe(string intermediateFileName, string gameFileName);

		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skeleton"; }

		protected override bool Process(libdb.DB.DBPtr<DBTypes.DBAnimatedSceneComponent> resource, EditorLib.IEditorCommonApplication application, bool fast)
		{
			if (!fast)
			{
				if (!ImportMayaToIntermediate(resource, application))
					return false;
			}

			if (!ImportIntermediateToBin(resource, application))
				return false;

			return true;
		}

		private static bool ImportMayaToIntermediate(DBPtr<DBTypes.DBAnimatedSceneComponent> resource, IEditorCommonApplication application)
		{
			DBTypes.DBAnimatedSceneComponent skeleton = resource.Get();

			if ( string.IsNullOrEmpty( skeleton.srcFileName.FileName ) )
			{
				Log.TraceError("srcFileName not specified in resource \"{0}\"", resource.DBId.Name);
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if (!File.Exists(srcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", srcFileName);
				return false;
			}

			string tempFileName = FileUtils.FixFileName(Path.GetTempFileName());

			if (!MayaOperationsUtility.LaunchSkeletonImportScript(srcFileName, skeleton.selection, tempFileName))
			{
				Log.TraceError("Maya exporter returned error.");
			}

			string mayaFileName = FileUtils.FixFileName(skeleton.mayaFileName);
			application.FileSystem.AddFile(tempFileName, mayaFileName);

			return true;
		}

		private static bool ImportIntermediateToBin(DBPtr<DBTypes.DBAnimatedSceneComponent> resource, IEditorCommonApplication application)
		{
			DBTypes.DBAnimatedSceneComponent skeleton = resource.Get();

			string mayaFileName = application.FileSystem.GetRealFileName(skeleton.mayaFileName);
			if (!File.Exists(mayaFileName))
			{
				Log.TraceError("Intermediate file (\"{0}\") not found for resource \"{1}\"", skeleton.mayaFileName, resource.DBId.Name);
				return false;
			}

			if ( application.FileSystem.GetFileInfo( skeleton.skeletonFileName ).IsFileExists )
				application.FileSystem.DeleteFile(skeleton.skeletonFileName);

			application.FileSystem.CreateFile(skeleton.skeletonFileName).Close();
			string skeletonFileName = application.FileSystem.GetRealFileName(skeleton.skeletonFileName);

      EditorRender.MarkAsDirtySkeletonData( skeleton.skeletonFileName );
      int result = ConvertSkeletonSafe(mayaFileName, skeletonFileName);
			if (result < 0)
			{
				Log.TraceError("Import skeleton from \"{0}\" failed with code {1}", resource.DBId.Name, result);
				return false;
			}

			return true;
		}
	}
}
