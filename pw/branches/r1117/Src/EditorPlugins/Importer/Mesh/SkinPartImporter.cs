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
  public sealed class SkinPartImporter : StructImporter<DBTypes.Skeleton, DBTypes.SkinPart>
	{
		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skin Part"; }

		protected override bool Process( SkinPart importStruct, DBPtr<Skeleton> resource, IEditorCommonApplication application, bool fast )
		{
			if ( !fast )
			{
				if ( !ImportFromMaya( importStruct, resource, application ) )
					return false;
			}

			return ImportFromIntermediate( importStruct, resource, application );
		}

		private static bool ImportFromMaya( DBTypes.SkinPart skin, DBPtr<DBTypes.Skeleton> resource, IEditorCommonApplication application )
		{
			DBTypes.Skeleton skeleton = resource.Get();

			string SkelSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if ( !File.Exists( SkelSrcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", SkelSrcFileName );
				return false;
			}

      if (string.IsNullOrEmpty(skin.srcFileName.FileName))
      {
        skin.srcFileName = skeleton.srcFileName;
      }
      string SkinSrcFileName = FileUtils.FixFileName(application.SourceFileSystem.GetFullFileName(skin.srcFileName.FileName));
			if ( !File.Exists( SkinSrcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", SkinSrcFileName );
				return false;
			}

			string tempFileName = FileUtils.FixFileName( Path.GetTempFileName() );

			if ( !MayaOperationsUtility.LaunchSkinPartImportScript( SkelSrcFileName, SkinSrcFileName, skin.selection, tempFileName, skeleton.selection ) )
			{
				Log.TraceError( "Maya exporter returned error." );
			}

			Log.TraceMessage( "Export from Maya completed" );

			string mayaFileName = FileUtils.FixFileName( skin.mayaFileName );
			application.FileSystem.AddFile( tempFileName, mayaFileName );

			return true;
		}

		private static bool ImportFromIntermediate( DBTypes.SkinPart skin, DBPtr<DBTypes.Skeleton> resource, IEditorCommonApplication application )
		{
			string mayaFileName = application.FileSystem.GetRealFileName( skin.mayaFileName );
			if ( !File.Exists( mayaFileName ) )
			{
				Log.TraceError( "Intermediate file (\"{0}\") not found for resource \"{1}\"", skin.mayaFileName, resource.DBId.Name );
				return false;
			}

			if ( application.FileSystem.GetFileInfo( skin.geometryFileName ).IsFileExists )
				application.FileSystem.DeleteFile( skin.geometryFileName );

			application.FileSystem.CreateFile( skin.geometryFileName ).Close();
			string geometryFileName = application.FileSystem.GetRealFileName( skin.geometryFileName );
			string skeletonFileName = application.FileSystem.GetRealFileName( resource.Get().skeletonFileName );

      // Collect material requirements
      uint convertTBN = 0;
      int convertColors = 0;
      foreach (DBPtr<Material> materialReference in skin.materialsReferences)
      {
        Material material = materialReference.Get();
        if (material != null)
        {
          MeshUtils.AnalizeMaterialRequirementsOR(material, ref convertTBN, ref convertColors);
        }
      }

      EditorRender.MarkAsDirtyGeometry( skin.geometryFileName );
      EditorRender.MarkAsDirtySkeletonData( resource.Get().skeletonFileName );
      float[] aabb = new float[6];

      int subMeshCount = MeshUtils.ConvertSkeletalMeshGeometrySafe(mayaFileName, geometryFileName, skeletonFileName, convertTBN, convertColors, 
                                                                   (byte)skin.uvSetCount, (uint)skin.jointsCountPerVertex, aabb);
			if ( subMeshCount < 0 )
			{
				Log.TraceError( "Import mesh from \"{0}\" failed with code {1}", resource.DBId.Name, subMeshCount );
				return false;
			}

			MeshUtils.FixMaterialReference( skin.materialsReferences, subMeshCount );

      if (string.IsNullOrEmpty(skin.skinPartName))
      {
        skin.skinPartName = skin.selection;
      }

			return true;
		}
	}

  [ApplicableForDeriver]
  public sealed class SkinPartDBAnimatedSceneComponentImporter : StructImporter<DBTypes.DBAnimatedSceneComponent, DBTypes.SkinPart>
	{
		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Skin Part"; }

		protected override bool Process(SkinPart importStruct, DBPtr<DBAnimatedSceneComponent> resource, IEditorCommonApplication application, bool fast)
		{
			if (!fast)
			{
				if (!ImportFromMaya(importStruct, resource, application))
					return false;
			}

			return ImportFromIntermediate(importStruct, resource, application);
		}

		private static bool ImportFromMaya(DBTypes.SkinPart skin, DBPtr<DBTypes.DBAnimatedSceneComponent> resource, IEditorCommonApplication application)
		{
			DBTypes.DBAnimatedSceneComponent skeleton = resource.Get();

			string SkelSrcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( skeleton.srcFileName.FileName ) );
			if (!File.Exists(SkelSrcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", SkelSrcFileName);
				return false;
			}

      if (string.IsNullOrEmpty(skin.srcFileName.FileName))
      {
        skin.srcFileName = skeleton.srcFileName;
      }
      string SkinSrcFileName = FileUtils.FixFileName(application.SourceFileSystem.GetFullFileName(skin.srcFileName.FileName));
      if (!File.Exists(SkinSrcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", SkinSrcFileName);
				return false;
			}

			string tempFileName = FileUtils.FixFileName(Path.GetTempFileName());

      if ( !MayaOperationsUtility.LaunchSkinPartImportScript( SkelSrcFileName, SkinSrcFileName, skin.selection, tempFileName, skeleton.selection ) )
			{
				Log.TraceError( "Maya exporter returned error." );
			}

      Log.TraceMessage( "Export from Maya completed" );

			string mayaFileName = FileUtils.FixFileName(skin.mayaFileName);
			application.FileSystem.AddFile(tempFileName, mayaFileName);

			return true;
		}

		private static bool ImportFromIntermediate(DBTypes.SkinPart skin, DBPtr<DBTypes.DBAnimatedSceneComponent> resource, IEditorCommonApplication application)
		{
			string mayaFileName = application.FileSystem.GetRealFileName(skin.mayaFileName);
			if (!File.Exists(mayaFileName))
			{
				Log.TraceError("Intermediate file (\"{0}\") not found for resource \"{1}\"", skin.mayaFileName, resource.DBId.Name);
				return false;
			}

			if ( application.FileSystem.GetFileInfo( skin.geometryFileName ).IsFileExists )
				application.FileSystem.DeleteFile(skin.geometryFileName);

			application.FileSystem.CreateFile(skin.geometryFileName).Close();
			string geometryFileName = application.FileSystem.GetRealFileName(skin.geometryFileName);
			string skeletonFileName = application.FileSystem.GetRealFileName(resource.Get().skeletonFileName);

      // Collect material requirements
      uint convertTBN = 0;
      int convertColors = 0;
      foreach (DBPtr<Material> materialReference in skin.materialsReferences)
      {
        Material material = materialReference.Get();
        if (material != null)
        {
          MeshUtils.AnalizeMaterialRequirementsOR(material, ref convertTBN, ref convertColors);
        }
      }

      EditorRender.MarkAsDirtyGeometry( skin.geometryFileName );
      EditorRender.MarkAsDirtySkeletonData( resource.Get().skeletonFileName );
			float[] aabb = new float[6];
      int subMeshCount = MeshUtils.ConvertSkeletalMeshGeometrySafe(mayaFileName, geometryFileName, skeletonFileName, convertTBN, convertColors, 
                                                                  (byte)skin.uvSetCount, (uint)skin.jointsCountPerVertex, aabb);
			if (subMeshCount < 0)
			{
				Log.TraceError("Import mesh from \"{0}\" failed with code {1}", resource.DBId.Name, subMeshCount);
				return false;
			}

			MeshUtils.FixMaterialReference(skin.materialsReferences, subMeshCount);

      if (string.IsNullOrEmpty(skin.skinPartName))
      {
        skin.skinPartName = skin.selection;
      }

			return true;
		}
	}
}
