using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using DBTypes;
using libdb.DB;

namespace EditorPlugins.Importer.Mesh
{
	public static class MeshUtils
	{
		private static System.Drawing.Color[] defaultColors = { System.Drawing.Color.FromArgb( 0x00FF0000 ),
																													  System.Drawing.Color.FromArgb( 0x0000FF00 ),
																													  System.Drawing.Color.FromArgb( 0x000000FF ),
																													  System.Drawing.Color.FromArgb( 0x00FFFF00 ),
																													  System.Drawing.Color.FromArgb( 0x00FF00FF ),
																													  System.Drawing.Color.FromArgb( 0x0000FFFF ),
																													  System.Drawing.Color.FromArgb( 0x00FF8000 ),
																													  System.Drawing.Color.FromArgb( 0x00FF80FF ),
																													  System.Drawing.Color.FromArgb( 0x00FFFFFF ) };

		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertStaticMeshGeometry(IntPtr mayaFileData, int mayaFileDataSize, IntPtr h6FileBuffer, int h6BufferSize, out int h6FileActualLength, uint convertTangentAndBinormal, int convertColors, byte uvChannels, float[] aabbs);

		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertCollisionGeometry( IntPtr mayaFileData, int mayaFileDataSize, IntPtr geometryFileBuffer, int geometryBufferSize, out int geometryFileActualLength );

		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
    public static extern Int32 ConvertSkeletalMeshGeometrySafe(string intermediateFileName, string binFileName, string skeletonInGameFileName, UInt32 convertTangentAndBinormal, Int32 numColorChannels, Byte uvChannels, UInt32 jointsCountPerVertex, float[] aabb);


		public static void FixMaterialReference( IList<DBPtr<Material>> materialsReferences, int subMeshCount )
		{
			while ( materialsReferences.Count > subMeshCount )
				materialsReferences.RemoveAt( materialsReferences.Count - 1 );

			while ( materialsReferences.Count < subMeshCount )
				materialsReferences.Add( new DBPtr<DBTypes.Material>( DBID.Empty, null ) );
		}

    // @BVS@TODO I hope someday I'll move this logic into material code
    public static void AnalizeMaterialRequirements(DBTypes.Material material, out uint convertTBN, out int convertColors)
    {
      convertTBN = 0;
      convertColors = 0;

      if (material is DBTypes.TerrainMaterial)
      {
        convertColors = 2;
      } else if (material is DBTypes.BasicMaterial)
      {
        DBTypes.BasicMaterial basicMaterial = material as DBTypes.BasicMaterial;
        if (basicMaterial.NormalMap.texture.IsValid)
          convertTBN = 1;
      }
      else if (material is DBTypes.DropMaterial)
      {
          DBTypes.DropMaterial dropMaterial = material as DBTypes.DropMaterial;
          if (dropMaterial.NormalMap.texture.IsValid)
              convertTBN = 1;
      }
      else if (material is DBTypes.TerrainMaterial)
      {
          DBTypes.TerrainMaterial terrainMaterial = material as DBTypes.TerrainMaterial;
          if (terrainMaterial.FrozenNormalMap.texture.IsValid ||
              terrainMaterial.NormalNormalMap.texture.IsValid ||
              terrainMaterial.BurnedNormalMap.texture.IsValid)
              convertTBN = 1;
      } 
      else if (material is DBTypes.BasicFXMaterial)
      {
        convertColors = -1; // -1 means "0 or 1 depending on the presence of colors in maya geometry"
      }
    }

    public static void AnalizeMaterialRequirementsOR(DBTypes.Material material, ref uint convertTBN, ref int convertColors)
    {
      uint cnvTBN;
      int cnvColor;
      AnalizeMaterialRequirements(material, out cnvTBN, out cnvColor);
      convertTBN |= cnvTBN;
      
      // sort values
      if (convertColors > cnvColor)
      {
        int t = convertColors;
        convertColors = cnvColor;
        cnvColor = t;
      }

      if (convertColors == -1)
      {
        if (cnvColor >= 1)
        {
          convertColors = cnvColor;
        }
      }
      else
      {
        convertColors = Math.Max(convertColors, cnvColor);
      }
    }
	}
}
