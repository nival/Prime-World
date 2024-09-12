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
using DBTypes;
using EditorNative;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Importer.Mesh
{
  [ApplicableForDeriver]
	public sealed class AnimationImporter : StructImporter<DBTypes.Skeleton, DBTypes.Animation>
	{
		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertSkeletalAnimationSafe( string intermediateFileName, string gameFileName );

		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skeleton Animation"; }

		protected override bool Process( Animation importStruct, DBPtr<Skeleton> resource, IEditorCommonApplication application, bool fast )
		{
			if ( !fast )
			{
				if ( !ImportFromMaya( resource, importStruct, application ) )
					return false;
			}

			return ImportFromIntermediate( resource, importStruct, application );
		}

		private static bool ImportFromMaya( DBPtr<DBTypes.Skeleton> resource, DBTypes.Animation animation, IEditorCommonApplication application )
		{
			DBTypes.Skeleton skeleton = resource.Get();

			string SkelSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if ( !File.Exists( SkelSrcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", SkelSrcFileName );
				return false;
			}

			string AnimSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( animation.srcFileName.FileName ) );
			if ( !File.Exists( AnimSrcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", AnimSrcFileName );
				return false;
			}

			string tempFileName = FileUtils.FixFileName( Path.GetTempFileName() );

			if ( !MayaOperationsUtility.LaunchAnimationImportScript(
				SkelSrcFileName,
				skeleton.selection,
				AnimSrcFileName,
				tempFileName,
				animation.compression
				) )
			{
				Log.TraceError( "Maya exporter returned error." );
			}

			string mayaFileName = FileUtils.FixFileName( animation.mayaFileName );
			application.FileSystem.AddFile( tempFileName, mayaFileName );

			return true;
		}

		private static bool ImportFromIntermediate( DBPtr<DBTypes.Skeleton> resource, DBTypes.Animation animation, IEditorCommonApplication application )
		{
			string mayaFileName = application.FileSystem.GetRealFileName( animation.mayaFileName );
			if ( !File.Exists( mayaFileName ) )
			{
				Log.TraceError( "Intermediate file (\"{0}\") not found for resource \"{1}\"", animation.mayaFileName, resource.DBId.Name );
				return false;
			}

			if ( application.FileSystem.GetFileInfo( animation.animationFileName ).IsFileExists )
				application.FileSystem.DeleteFile( animation.animationFileName );

			application.FileSystem.CreateFile( animation.animationFileName ).Close();
			string animationFileName = application.FileSystem.GetRealFileName( animation.animationFileName );

            EditorRender.MarkAsDirtySkeletonAnim(animation.animationFileName);
			int result = ConvertSkeletalAnimationSafe( mayaFileName, animationFileName );
			if ( result < 0 )
			{
				Log.TraceError( "Import animation from \"{0}\" failed with code {1}", resource.DBId.Name, result );
				return false;
			}

			return true;
		}
	}

  [ApplicableForDeriver]
  public sealed class AnimationDBAnimatedSceneComponentImporter : StructImporter<DBTypes.DBAnimatedSceneComponent, DBTypes.Animation>
	{
		[DllImport("MeshConverter", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 ConvertSkeletalAnimationSafe(string intermediateFileName, string gameFileName);

		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skeleton Animation"; }

		protected override bool Process(Animation importStruct, DBPtr<DBAnimatedSceneComponent> resource, IEditorCommonApplication application, bool fast)
		{
			if (!fast)
			{
				if (!ImportFromMaya(resource, importStruct, application))
					return false;
			}

			return ImportFromIntermediate(resource, importStruct, application);
		}

		private static bool ImportFromMaya(DBPtr<DBTypes.DBAnimatedSceneComponent> resource, DBTypes.Animation animation, IEditorCommonApplication application)
		{
			DBTypes.DBAnimatedSceneComponent skeleton = resource.Get();

			string SkelSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if (!File.Exists(SkelSrcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", SkelSrcFileName);
				return false;
			}

			string AnimSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( animation.srcFileName.FileName ) );
			if (!File.Exists(AnimSrcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", AnimSrcFileName);
				return false;
			}

			string tempFileName = FileUtils.FixFileName(Path.GetTempFileName());

			if (!MayaOperationsUtility.LaunchAnimationImportScript(
				SkelSrcFileName,
				skeleton.selection,
				AnimSrcFileName,
				tempFileName,
				animation.compression
				))
			{
				Log.TraceError("Maya exporter returned error.");
			}

			string mayaFileName = FileUtils.FixFileName(animation.mayaFileName);
			application.FileSystem.AddFile(tempFileName, mayaFileName);

			return true;
		}

		private static bool ImportFromIntermediate(DBPtr<DBTypes.DBAnimatedSceneComponent> resource, DBTypes.Animation animation, IEditorCommonApplication application)
		{
			string mayaFileName = application.FileSystem.GetRealFileName(animation.mayaFileName);
			if (!File.Exists(mayaFileName))
			{
				Log.TraceError("Intermediate file (\"{0}\") not found for resource \"{1}\"", animation.mayaFileName, resource.DBId.Name);
				return false;
			}

			if ( application.FileSystem.GetFileInfo( animation.animationFileName ).IsFileExists )
				application.FileSystem.DeleteFile(animation.animationFileName);

			application.FileSystem.CreateFile(animation.animationFileName).Close();
			string animationFileName = application.FileSystem.GetRealFileName(animation.animationFileName);

            EditorRender.MarkAsDirtySkeletonAnim(animation.animationFileName);
            int result = ConvertSkeletalAnimationSafe(mayaFileName, animationFileName);
			if (result < 0)
			{
				Log.TraceError("Import animation from \"{0}\" failed with code {1}", resource.DBId.Name, result);
				return false;
			}

			return true;
		}
	}
}
