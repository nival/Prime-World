using System;
using libdb.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.IO;
using EditorNative;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Importer.Mesh
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public sealed class ImporterCommon
{
  static public bool ImportMayaToIntermediate(IEditorCommonApplication application, string srcFileName, string mayaFileName, 
                                              string resourceId, string selection)
  {
    if (string.IsNullOrEmpty(srcFileName))
    {
      Log.TraceError("srcFileName not specified in resource \"{0}\"", resourceId);
      return false;
    }

    string srcFileNameFixed = FileUtils.FixFileName(application.SourceFileSystem.GetFullFileName(srcFileName));
    if (!File.Exists(srcFileNameFixed))
    {
      Log.TraceError("Source file \"{0}\" is not exist.", srcFileNameFixed);
      return false;
    }

    string tempFileName = FileUtils.FixFileName(Path.GetTempFileName());
    if (!MayaOperationsUtility.LaunchStaticMeshImportScript(srcFileNameFixed, selection, tempFileName))
    {
      Log.TraceError("Maya exporter returned error.");
    }

    string mayaFileNameFixed = FileUtils.FixFileName(mayaFileName);
    application.FileSystem.AddFile(tempFileName, mayaFileNameFixed);

    return true;
  }

  static public int ImportIntermediateToBin(IEditorCommonApplication application, string mayaFileName, string geoFileName, 
                                            string resourceName, uint convertTBN, int numColorChannels, out float[] aabbs)
  {
    aabbs = null;

    string geometryFileName = FileUtils.FixFileName(geoFileName);
    EditorRender.MarkAsDirtyGeometry(geometryFileName);
    if (application.FileSystem.GetFileInfo(geometryFileName).IsFileExists)
    {
      application.FileSystem.DeleteFile(geometryFileName);
    }

    using (var writer = new BinaryWriter(application.FileSystem.CreateFile(geometryFileName)))
    {
      string mayaFileNameFixed = FileUtils.FixFileName(mayaFileName);
      byte[] mayaFileData = FileUtils.ReadFile(application.FileSystem, mayaFileNameFixed);
      var mayaFileDataHandle = GCHandle.Alloc(mayaFileData, GCHandleType.Pinned);

      try
      {
        byte[] h6FileBuffer = new byte[10 * 1024 * 1024];
        var h6FileBufferHandle = GCHandle.Alloc(h6FileBuffer, GCHandleType.Pinned);

        try
        {
          aabbs = new float[(1 + 8) * 6]; // $BVS$ Here I know that number of fragments in mesh is limited to 8!

          int h6FileActualLength;

          int subMeshCount = MeshUtils.ConvertStaticMeshGeometry(
            mayaFileDataHandle.AddrOfPinnedObject(),
            mayaFileData.Length,
            h6FileBufferHandle.AddrOfPinnedObject(),
            h6FileBuffer.Length,
            out h6FileActualLength,
            convertTBN,
            numColorChannels,
            (byte)1,
            aabbs
          );

          if (subMeshCount < 0)
          {
            Log.TraceError("Import mesh from \"{0}\" failed with code {1}", resourceName, subMeshCount);
            return 0;
          }
          else if (h6FileActualLength < 0)
          {
            Log.TraceError("Import mesh from \"{0}\" failed with conversion buffer overflow.", resourceName);
            return 0;
          }
          else
          {
            writer.Write(h6FileBuffer, 0, h6FileActualLength);

            return subMeshCount;
          }
        }
        finally
        {
          h6FileBufferHandle.Free();
        }
      }
      catch (Exception)
      {
        Log.TraceError("Import mesh from \"{0}\" failed.", resourceName);
        return 0;
      }
      finally
      {
        mayaFileDataHandle.Free();
      }
    }
  }

  static public void AnalizeMaterials(libdb.IChangeableList<DBPtr<Material>> materialsReferences, out uint convertTBN, out int convertColors)
  {
    convertTBN = 0;
    convertColors = 0;

    foreach (DBPtr<Material> materialReference in materialsReferences)
    {
      Material material = materialReference.Get();
      if (material != null)
        MeshUtils.AnalizeMaterialRequirementsOR(material, ref convertTBN, ref convertColors);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public sealed class StaticMeshImporter : Importer<DBTypes.StaticMesh>
{
	protected override bool KnownDuration { get { return false; } }

	static public bool ImportMayaToIntermediate( DBTypes.StaticMesh staticMesh, IEditorCommonApplication application )
	{
    return ImporterCommon.ImportMayaToIntermediate(application, staticMesh.srcFileName.FileName, staticMesh.mayaFileName, 
                                                   staticMesh.DBId.Name, staticMesh.selection);
	}

	static public bool ImportIntermediateToBin( DBTypes.StaticMesh staticMesh, IEditorCommonApplication application, out float[] aabbs )
	{
    uint convertTBN = 0;
    int numColorChannels = 0;

    ImporterCommon.AnalizeMaterials(staticMesh.materialsReferences, out convertTBN, out numColorChannels);
    int subMeshCount = ImporterCommon.ImportIntermediateToBin(application, staticMesh.mayaFileName, staticMesh.geometryFileName,
                                                              staticMesh.DBId.Name, convertTBN, numColorChannels, out aabbs);
    if (subMeshCount > 0)
    {
      MeshUtils.FixMaterialReference(staticMesh.materialsReferences, subMeshCount);

      staticMesh.aabb.minX = aabbs[0];
      staticMesh.aabb.maxX = aabbs[1];
      staticMesh.aabb.minY = aabbs[2];
      staticMesh.aabb.maxY = aabbs[3];
      staticMesh.aabb.minZ = aabbs[4];
      staticMesh.aabb.maxZ = aabbs[5];
    }

    return subMeshCount > 0;
	}

	protected override bool Process( DBPtr<DBTypes.StaticMesh> resource, IEditorCommonApplication application, bool fast )
	{
		if ( !fast )
		{
			if ( !ImportMayaToIntermediate( resource, application ) )
				return false;
		}

		float[] aabbs = null;
		if ( !ImportIntermediateToBin(resource, application, out aabbs) )
			return false;

		return true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public sealed class DBStaticSceneComponentImporter : Importer<DBTypes.DBStaticSceneComponent>
{
	protected override bool KnownDuration { get { return false; } }

	static public bool ImportMayaToIntermediate(DBTypes.DBStaticSceneComponent staticMesh, IEditorCommonApplication application)
	{
		return ImporterCommon.ImportMayaToIntermediate( application, staticMesh.srcFileName.FileName, staticMesh.mayaFileName,
																							 staticMesh.DBId.Name, staticMesh.selection );
	}

	static public bool ImportIntermediateToBin(DBTypes.DBStaticSceneComponent staticMesh, IEditorCommonApplication application, out float[] aabbs)
	{
    uint convertTBN = 0;
    int numColorChannels = 0;
    ImporterCommon.AnalizeMaterials(staticMesh.materialsReferences, out convertTBN, out numColorChannels);
		int subMeshCount = ImporterCommon.ImportIntermediateToBin( application, staticMesh.mayaFileName, staticMesh.geometryFileName,
																															staticMesh.DBId.Name, convertTBN, numColorChannels, out aabbs );
    if (subMeshCount > 0)
    {
      MeshUtils.FixMaterialReference(staticMesh.materialsReferences, subMeshCount);

			if ( staticMesh.aabb.minX >= staticMesh.aabb.maxX
				&& staticMesh.aabb.minY >= staticMesh.aabb.maxY
				&& staticMesh.aabb.minZ >= staticMesh.aabb.maxZ )
      {
				staticMesh.aabb.minX = aabbs[0];
				staticMesh.aabb.maxX = aabbs[1];
				staticMesh.aabb.minY = aabbs[2];
				staticMesh.aabb.maxY = aabbs[3];
				staticMesh.aabb.minZ = aabbs[4];
				staticMesh.aabb.maxZ = aabbs[5];
      }
    }

		EditorRender.MarkAsDirtyGeometry( staticMesh.geometryFileName );

    return subMeshCount > 0;
  }

	protected override bool Process(DBPtr<DBTypes.DBStaticSceneComponent> resource, IEditorCommonApplication application, bool fast)
	{
		if (!fast)
		{
			if (!ImportMayaToIntermediate(resource, application))
				return false;
		}

		float[] aabbs = null;
		if (!ImportIntermediateToBin(resource, application, out aabbs))
			return false;

		return true;
	}
}

}
