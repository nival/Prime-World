using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using System.Drawing;
using System.IO;
using EditorPlugins.Importer.Texture;
using libdb.Diagnostics;
using libdb.DB;
using libdb.IO;
using EditorLib.IO;
using DBTypes;
using EditorLib;

namespace EditorPlugins.Importer
{
/*  // obsolete [10/19/2009 smirnov]
	public sealed class ParticleInstanceImporter : StructImporter<DBTypes.Effect, DBTypes.ParticleInstance>
	{
		protected override bool KnownDuration { get { return false; } }

		protected override bool Process( ParticleInstance particleInstance, DBPtr<Effect> resource, IEditorCommonApplication application, bool fast )
		{
			Progress( string.Format( "Adding textures to atlas..." ) );
			Atlas atlas = new Atlas();
			for ( int i = 0; i < particleInstance.textures.Count; i++ )
			{
				Stream textureStream = application.SourceFileSystem.OpenFile( particleInstance.textures[i].FileName );
				if ( textureStream == null )
				{
					Log.TraceWarning( "Cannot load texture \"{0}\" ({1})", particleInstance.textures[i], i );
					continue;
				}

				Bitmap bitmap= TgaReader.LoadImage( textureStream );
				if ( bitmap == null )
				{
					Log.TraceWarning( "Cannot load texture \"{0}\" ({1})", particleInstance.textures[i], i );
					continue;
				}

				if ( !atlas.AddBitmap( bitmap, particleInstance.textures[i].FileName ) )
				{
					Log.TraceError( "Cannot add texture \"{0}\" ({1}) to atlas", particleInstance.textures[i], i );
					return false;
				}
			}

			Progress( string.Format( "Building atlas..." ) );
			atlas.BuildAtlas();

			Progress( string.Format( "Generating UV..." ) );
			DBResource owner = particleInstance.GetOwner();
			particleInstance.uvPairs.Clear();
			for ( int i = 0; i < particleInstance.textures.Count; i++ )
			{
				particleInstance.uvPairs.Add( atlas.TryGetUVForBitmap( particleInstance.textures[i].FileName ) );
			}

			DBTypes.ParticleFXMaterial atlasMaterial = particleInstance.material.Get() as DBTypes.ParticleFXMaterial;
			if ( !particleInstance.material.DBId.IsEmpty && !particleInstance.material.DBId.IsInlined )
			{
				Log.TraceWarning( "Found non empty non inlined material" );
				atlasMaterial = null;
			}

			if ( atlasMaterial == null )
			{
				atlasMaterial = new ParticleFXMaterial();
				particleInstance.material = DataBase.Create<ParticleFXMaterial>( DBID.FromDBID( resource.DBId, true ), atlasMaterial );
			}

			if ( atlas.IsEmpty )
			{
				Log.TraceMessage( "No atlas created" );
        //atlasMaterial.DiffuseMapPinValue = DBTypes.BooleanPin.None; @BVS@MATMIGR
				atlasMaterial.DiffuseMap.texture = null;
				return true;
			}

			//atlasMaterial.DiffuseMapPinValue = DBTypes.BooleanPin.Present; @BVS@MATMIGR

			DBTypes.Texture atlasTexture = atlasMaterial.DiffuseMap.texture.Get() as DBTypes.Texture;
			if ( !atlasMaterial.DiffuseMap.texture.DBId.IsEmpty && !atlasMaterial.DiffuseMap.texture.DBId.IsInlined )
			{
				Log.TraceWarning( "Found non empty non inlined texture" );
				atlasTexture = null;
			}

			string resourceRawFileName = FileUtils.GetFileNameWithoutExtension( Path.GetFileName( resource.DBId.FileName ) );
			string textureFileName = atlasTexture != null ? FileUtils.GetFileNameWithoutExtension( atlasTexture.textureFileName ) : string.Empty;
			if ( atlasTexture != null && !string.IsNullOrEmpty( textureFileName ) && textureFileName.IndexOf( resourceRawFileName, StringComparison.InvariantCultureIgnoreCase ) < 0 )
			{
				Log.TraceWarning( "Texture \"{0}\" doesn't belong to resource \"{1}\"", atlasTexture.textureFileName, resource.DBId.Name );
				atlasTexture = null;
			}

			if ( atlasTexture != null && !string.IsNullOrEmpty( atlasTexture.srcFileName.FileName ) )
			{
				Log.TraceWarning( "Texture \"{0}\" doesn't belong to resource \"{1}\"", atlasTexture.textureFileName, resource.DBId.Name );
				atlasTexture = null;
			}

			if ( atlasTexture == null )
			{
				atlasTexture = new DBTypes.Texture();
				atlasMaterial.DiffuseMap.texture = DataBase.Create<DBTypes.Texture>( DBID.FromDBID( resource.DBId, true ), atlasTexture ).GetPtr<DBTypes.TextureBase>();
				atlasTexture.generatedFileName = FileUtils.GetFileNameWithoutExtension( FileUtils.GenerateUniqueFileName( application.FileSystem, Path.GetDirectoryName( resource.DBId.FileName ), resourceRawFileName, ".dds" ) );
				
				// Set convenient defaults
				atlasTexture.pixelFormat = EPixelFormat.DXT5;
        //atlasMaterial.ParticlePinValue = DBTypes.ParticlePin.VertexColorAndDiffuseMapMix; @BVS@MATMIGR
        atlasMaterial.renderState.blendMode = BlendMode.AddColorMulAlpha;
        atlasMaterial.renderState.alphaTest = OnOffState.Off;
			}

			Progress( string.Format( "Saving atlas..." ) );
      if (!DdsImage.Save(application.FileSystem, atlasTexture, atlas.GetAtlas()))
			{
				Log.TraceWarning( "Cannot save texture \"{0}\" with atlas", atlasMaterial.DiffuseMap.texture );
				return false;
			}

      EditorNative.EditorRender.ResetTexture(atlasTexture.textureFileName);
			EditorNative.EditorRender.ReloadPFX();

			return true;
		}
	}
 */
}
