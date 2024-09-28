using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using libdb.DB;
using EditorLib;
using System.Runtime.InteropServices;
using libdb.Diagnostics;
using System.IO;
using libdb.IO;

using System.Drawing;
using EditorPlugins.Importer.Texture;
using EditorLib.IO;
using DBTypes;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Importer.Mesh
{
	public sealed class ParticleFXImporter : Importer<DBTypes.ParticleFX>
	{
		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertParticleSafe( string intermediateFileName, string gameFileName );

		[DllImport( "MeshConverter", CallingConvention = CallingConvention.StdCall )]
		public static extern Int32 ConvertParticleFromMemory( IntPtr mayaFileData, int mayaFileDataSize, IntPtr binFileBuffer, int binFileBufferSize, out int binFileActualLength, out uint maxSpriteID );

		protected override bool KnownDuration { get { return false; } }

		private static bool ImportMayaToIntermediate( DBPtr<DBTypes.ParticleFX> resource, IEditorCommonApplication application )
		{
			DBTypes.ParticleFX pFX = resource.Get();

			if ( string.IsNullOrEmpty( pFX.srcFileName.FileName ) )
			{
				Log.TraceError( "Source file not specified in resource \"{0}\"", resource.DBId.Name );
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( pFX.srcFileName.FileName ) );
			if ( !File.Exists( srcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist", srcFileName );
				return false;
			}

			string tempFileName = FileUtils.FixFileName( Path.GetTempFileName() );

			if ( !MayaOperationsUtility.LaunchParticleFxImportScript( srcFileName, pFX.selection, tempFileName, pFX.compression ) )
			{
				Log.TraceError( "Maya exporter returned error" );
			}

			string mayaFileName = FileUtils.FixFileName( pFX.mayaFileName );
			application.FileSystem.AddFile( tempFileName, mayaFileName );

			return true;
		}

		private static bool ImportIntermediateToBin( DBPtr<DBTypes.ParticleFX> resource, IEditorCommonApplication application )
		{
			DBTypes.ParticleFX pFX = resource.Get();

			byte[] mayaFileData = FileUtils.ReadFile( application.FileSystem, pFX.mayaFileName );
			GCHandle mayaFileDataHandle = GCHandle.Alloc( mayaFileData, GCHandleType.Pinned );

			byte[] binFileBuffer = new byte[16 * 1024 * 1024];
			GCHandle binFileBufferHandle = GCHandle.Alloc( binFileBuffer, GCHandleType.Pinned );

			int binFileActualLength = 0;
      uint maxSpriteID = 0;
			int result = ConvertParticleFromMemory( mayaFileDataHandle.AddrOfPinnedObject(), mayaFileData.Length,
        binFileBufferHandle.AddrOfPinnedObject(), binFileBuffer.Length, out binFileActualLength, out maxSpriteID );

			if ( result >= 0 )
			{
				Stream stream = application.FileSystem.CreateFile( pFX.fxFileName );
				if ( stream == null )
				{
					Log.TraceError( "Cannot create file \"{0}\"", pFX.fxFileName );
					result = -1;
				}
				else
				{
					stream.Write( binFileBuffer, 0, binFileActualLength );
					stream.Close();
				}
			}

			binFileBufferHandle.Free();
			mayaFileDataHandle.Free();

			return result >= 0;
		}

		protected override bool Process( DBPtr<DBTypes.ParticleFX> resource, IEditorCommonApplication application, bool fast )
		{
			if ( !fast )
			{
				if ( !ImportMayaToIntermediate( resource, application ) )
					return false;
			}

			if ( !ImportIntermediateToBin( resource, application ) )
				return false;

			EditorNative.EditorRender.ReloadPFX();

			return true;
		}
	}

  [ApplicableForDeriver]
	public sealed class DBParticleSceneComponentImporter : Importer<DBTypes.DBParticleSceneComponent>
	{
		[DllImport("MeshConverter", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 ConvertParticleSafe(string intermediateFileName, string gameFileName);

		[DllImport("MeshConverter", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 ConvertParticleFromMemory(IntPtr mayaFileData, int mayaFileDataSize, IntPtr binFileBuffer, int binFileBufferSize, out int binFileActualLength, out uint maxSpriteID);

		protected override bool KnownDuration { get { return false; } }

		private static bool ImportMayaToIntermediate(DBPtr<DBTypes.DBParticleSceneComponent> resource, IEditorCommonApplication application)
		{
			DBTypes.DBParticleSceneComponent pFX = resource.Get();

			if ( string.IsNullOrEmpty( pFX.srcFileName.FileName ) )
			{
				Log.TraceError("Source file not specified in resource \"{0}\"", resource.DBId.Name);
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( pFX.srcFileName.FileName ) );
			if (!File.Exists(srcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist", srcFileName);
				return false;
			}

			string tempFileName = FileUtils.FixFileName(Path.GetTempFileName());

			if (!MayaOperationsUtility.LaunchParticleFxImportScript(srcFileName, pFX.selection, tempFileName, pFX.compression))
			{
				Log.TraceError("Maya exporter returned error");
			}

			string mayaFileName = FileUtils.FixFileName(pFX.mayaFileName);
			application.FileSystem.AddFile(tempFileName, mayaFileName);

			return true;
		}

		private static bool ImportIntermediateToBin(DBPtr<DBTypes.DBParticleSceneComponent> resource, IEditorCommonApplication application, out uint maxSpriteID)
		{
			DBTypes.DBParticleSceneComponent pFX = resource.Get();

			byte[] mayaFileData = FileUtils.ReadFile(application.FileSystem, pFX.mayaFileName);
			GCHandle mayaFileDataHandle = GCHandle.Alloc(mayaFileData, GCHandleType.Pinned);

			byte[] binFileBuffer = new byte[16 * 1024 * 1024];
			GCHandle binFileBufferHandle = GCHandle.Alloc(binFileBuffer, GCHandleType.Pinned);

			int binFileActualLength = 0;
			int result = ConvertParticleFromMemory(mayaFileDataHandle.AddrOfPinnedObject(), mayaFileData.Length,
				binFileBufferHandle.AddrOfPinnedObject(), binFileBuffer.Length, out binFileActualLength, out maxSpriteID );

			if (result >= 0)
			{
				Stream stream = application.FileSystem.CreateFile(pFX.fxFileName);
				if (stream == null)
				{
					Log.TraceError("Cannot create file \"{0}\"", pFX.fxFileName);
					result = -1;
				}
				else
				{
					stream.Write(binFileBuffer, 0, binFileActualLength);
					stream.Close();
				}
			}

			binFileBufferHandle.Free();
			mayaFileDataHandle.Free();

			return result >= 0;
		}

		private static bool ImportMaterials(DBPtr<DBTypes.DBParticleSceneComponent> resource, IEditorCommonApplication application, uint maxSpriteID)
		{
      DBTypes.DBParticleSceneComponent particleInstance = resource.Get();

			Atlas atlas = new Atlas();
			for (int i = 0; i < particleInstance.textures.Count; i++)
			{
				Stream textureStream = application.SourceFileSystem.OpenFile(particleInstance.textures[i].FileName);
				if (textureStream == null)
				{
					Log.TraceWarning("Cannot load texture \"{0}\" ({1})", particleInstance.textures[i], i);
					continue;
				}

        Bitmap bitmap = null;
        string extension = Path.GetExtension(particleInstance.textures[i].FileName);
        if ( extension.ToLower() != ".tga" )
        {
          bitmap = new Bitmap(textureStream);
        }
        else
        {
          bitmap = TgaReader.LoadImage(textureStream);
        }

				if (bitmap == null)
				{
					Log.TraceWarning("Cannot load texture \"{0}\" ({1})", particleInstance.textures[i], i);
					continue;
				}

        if (!atlas.AddBitmap(bitmap, particleInstance.textures[i].FileName, 1.0f))
				{
					Log.TraceError("Cannot add texture \"{0}\" ({1}) to atlas", particleInstance.textures[i], i);
					return false;
				}
			}

			atlas.BuildAtlas();

			DBResource owner = resource.GetOwner();
			particleInstance.uvPairs.Clear();
			for (int i = 0; i < particleInstance.textures.Count; i++)
			{
				particleInstance.uvPairs.Add(atlas.TryGetUVForBitmap(particleInstance.textures[i].FileName));
			}

      if ( maxSpriteID >= particleInstance.uvPairs.Count )
      {
        Log.TraceError( "Found wrong spriteNumPP = " + maxSpriteID.ToString() + " in " + particleInstance.fxFileName );
        return false;
      }

			DBTypes.ParticleFXMaterial atlasMaterial = particleInstance.material.Get() as DBTypes.ParticleFXMaterial;
      if (atlasMaterial != null)
        atlasMaterial.scale = 0.0f;

			if (!particleInstance.material.DBId.IsEmpty && !particleInstance.material.DBId.IsInlined)
			{
				Log.TraceWarning("Found non empty non inlined material");
				atlasMaterial = null;
			}

			if (atlasMaterial == null)
			{
				atlasMaterial = new ParticleFXMaterial();
				particleInstance.material = DataBase.Create<ParticleFXMaterial>(DBID.FromDBID(resource.DBId, true), atlasMaterial);
        atlasMaterial.renderState.blendMode = BlendMode.AddColorMulAlpha;
        atlasMaterial.renderState.alphaTest = OnOffState.Off;
      }

			if (atlas.IsEmpty)
			{
				Log.TraceMessage("No atlas created");
				//atlasMaterial.DiffuseMapPinValue = DBTypes.BooleanPin.None; @BVS@MATMIGR
				atlasMaterial.DiffuseMap.texture = null;
				return true;
			}

      //atlasMaterial.DiffuseMapPinValue = DBTypes.BooleanPin.Present; @BVS@MATMIGR

			DBTypes.Texture atlasTexture = atlasMaterial.DiffuseMap.texture.Get() as DBTypes.Texture;
			if (!atlasMaterial.DiffuseMap.texture.DBId.IsEmpty && !atlasMaterial.DiffuseMap.texture.DBId.IsInlined)
			{
				Log.TraceWarning("Found non empty non inlined texture");
				atlasTexture = null;
			}

			string resourceRawFileName = FileUtils.GetFileNameWithoutExtension(Path.GetFileName(resource.DBId.FileName));
			string textureFileName = atlasTexture != null ? FileUtils.GetFileNameWithoutExtension(atlasTexture.textureFileName) : string.Empty;
			if (atlasTexture != null && !string.IsNullOrEmpty(textureFileName) && textureFileName.IndexOf(resourceRawFileName, StringComparison.InvariantCultureIgnoreCase) < 0)
			{
				Log.TraceWarning("Texture \"{0}\" doesn't belong to resource \"{1}\"", atlasTexture.textureFileName, resource.DBId.Name);
				atlasTexture = null;
			}

      //if ( atlasTexture != null && !string.IsNullOrEmpty( atlasTexture.srcFileName.FileName ) )
      //{
      //  Log.TraceWarning("Texture \"{0}\" doesn't belong to resource \"{1}\"", atlasTexture.textureFileName, resource.DBId.Name);
      //  atlasTexture = null;
      //}

			if (atlasTexture == null)
			{
				atlasTexture = new DBTypes.Texture();
        atlasMaterial.DiffuseMap.texture = DataBase.Create<DBTypes.Texture>(DBID.FromDBID(resource.DBId, true), atlasTexture).GetPtr<DBTypes.TextureBase>();
				atlasTexture.generatedFileName = FileUtils.GetFileNameWithoutExtension(FileUtils.GenerateUniqueFileName(application.FileSystem, Path.GetDirectoryName(resource.DBId.FileName), resourceRawFileName, ".dds"));

				// Set convenient defaults
        atlasTexture.pixelFormat = EPixelFormat.DXT5;
        //atlasMaterial.ParticlePinValue = DBTypes.ParticlePin.VertexColorAndDiffuseMapMix; @BVS@MATMIGR
			}

      if (!DdsImage.Save(application.FileSystem, atlasTexture, atlas.GetAtlas()))
			{
				Log.TraceWarning("Cannot save texture \"{0}\" with atlas", atlasMaterial.DiffuseMap.texture);
				return false;
			}

      EditorNative.EditorRender.ResetTexture(atlasTexture.textureFileName);
			EditorNative.EditorRender.ReloadPFX();

			return true;
		}

		protected override bool Process(DBPtr<DBTypes.DBParticleSceneComponent> resource, IEditorCommonApplication application, bool fast)
		{
			if (!fast)
			{
				if (!ImportMayaToIntermediate(resource, application))
					return false;
			}
      uint maxSpriteID = 0;
      if ( !ImportIntermediateToBin( resource, application, out maxSpriteID ) )
        return false;

      if ( !ImportMaterials( resource, application, maxSpriteID ) )
				return false;

      EditorNative.EditorRender.MarkAsDirtyPFX( resource.Get().fxFileName );
			EditorNative.EditorRender.ReloadPFX();

			return true;
		}
	}

}
