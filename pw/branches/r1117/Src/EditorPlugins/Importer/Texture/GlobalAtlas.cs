using System;
using System.Collections.Generic;
using System.Text;
using libdb.Diagnostics;
using libdb.DB;
using System.Drawing;
using EditorNative;
using EditorLib.Operations;
using EditorLib;
using EditorLib.IO;
using libdb.IO;

using BlendMode = DBTypes.BlendMode;


namespace EditorPlugins.Importer.Texture
{
  public static class GlobalAtlas
  {
    private static DBPtr<DBTypes.Texture> CreateAtlasTexture( Bitmap atlasImage, IFileSystem outputFileSystem, int index )
    {
      string wantedFileName = "atlas_" + index.ToString();

      DBID atlasId;
      DBPtr<DBTypes.Texture> atlasPtr;
      DBTypes.Texture atlasTexture;
      if ( DBID.TryCreateDBID( "/GFX_Textures/Atlases/", wantedFileName, typeof( DBTypes.Texture ), out atlasId ) )
      {
        atlasTexture = new DBTypes.Texture();
        atlasTexture.generatedFileName = wantedFileName;
        atlasTexture.pixelFormat = DBTypes.EPixelFormat.DXT5;
        atlasTexture.startMipLevel = 0;
        atlasTexture.textureType = DBTypes.TextureType.Color;

        atlasPtr = DataBase.Create( atlasId, atlasTexture );
      }
      else
      {
        // resource for atlas already exists, let's get it
        atlasPtr = DataBase.Get<DBTypes.Texture>( atlasId );
        atlasTexture = atlasPtr.Get();
        // resource with wanted atlas name already exists but its type not a texture, warning and create new
        if ( atlasTexture == null || atlasTexture.GetType() != typeof( DBTypes.Texture ) )
        {
          Log.TraceError( "Atlas resource \"{0}\" already exists and its type \"{1}\" not a \"{2}\"", atlasId, DataBase.Get<DBResource>( atlasId ).GetType(), typeof( DBTypes.Texture ) );
          return null;
        }

        if ( !string.IsNullOrEmpty( atlasTexture.srcFileName.FileName ) )
        {
          Log.TraceWarning( "Atlas resource \"{0}\" has setted sourced texture file name \"{1}\"", atlasId, atlasTexture.srcFileName.FileName );
          atlasTexture.srcFileName.SetFileName( string.Empty );
        }
        else if ( string.Compare( atlasTexture.generatedFileName, wantedFileName ) != 0 )
          Log.TraceWarning( "Atlas resource \"{0}\" has modified texture file name \"{1}\" not a \"{2}\"", atlasId, atlasPtr.Get().generatedFileName, wantedFileName );

        atlasTexture.generatedFileName = wantedFileName;
      }

      atlasTexture.size.width = atlasImage.Width >> atlasTexture.startMipLevel;
      atlasTexture.size.height = atlasImage.Height >> atlasTexture.startMipLevel;
      atlasTexture.mipLevelUsage = DBTypes.MipLevel.NoMips;
      TextureImporter.ImportImage( atlasImage, outputFileSystem, atlasTexture.textureFileName, atlasTexture );

      return atlasPtr;
    }

    private static bool UpdateParticleMaterial( Atlas atlas, DBTypes.DBParticleSceneComponent particle, DBPtr<DBTypes.Texture> texture )
    {
      particle.uvPairs.Clear();
      for ( int i = 0; i < particle.textures.Count; i++ )
      {
        particle.uvPairs.Add( atlas.TryGetUVForBitmap( particle.textures[i].FileName ) );
      }

      DBTypes.ParticleFXMaterial atlasMaterial = null;

      if ( !DBID.IsNullOrEmpty( particle.material.DBId ) && !particle.material.DBId.IsInlined )
        Log.TraceWarning( "Particle \"{0}\" reffered not inlined material \"{1}\"", particle.DBId.ToString(), particle.material.DBId );
      else
        atlasMaterial = particle.material.Get<DBTypes.ParticleFXMaterial>();

      if ( atlasMaterial == null )
      {
        atlasMaterial = new DBTypes.ParticleFXMaterial();
        particle.material = DataBase.Create<DBTypes.ParticleFXMaterial>( DBID.FromDBID( particle.DBId, true ), atlasMaterial );
      }

      atlasMaterial.DiffuseMap.texture = texture == null ? null : texture.GetPtr<DBTypes.TextureBase>();
      return true;
    }

    private static bool ProcessResource( DBTypes.DBParticleSceneComponent particle, Atlas atlas, SourceFileSystem sourceFileSystem )
    {
      for ( int i = 0; i < particle.textures.Count; i++ )
      {
        Bitmap bitmap = TextureImporter.LoadImage( sourceFileSystem, particle.textures[i].FileName );
        if ( bitmap == null )
        {
          Log.TraceError( "Cannot load source texture \"{0}\" in \"{1}\"", particle.textures[i].FileName, particle.DBId.GetFullFileName() );
          continue;
        }

        bool clearAlpha = true;
        //int  maxValue = 0;
        for (int x = 0; x < bitmap.Width; x++)
        {
          for (int y = 0; y < bitmap.Height; y++)
          {
            Color pixColor = bitmap.GetPixel(x, y);
            clearAlpha &= (pixColor.A == 0xff);
            //maxValue = Math.Max( maxValue,
            //                     Math.Max(pixColor.A * pixColor.R,
            //                              Math.Max(pixColor.A * pixColor.G, pixColor.A * pixColor.B)));
          }
        }

        DBTypes.ParticleFXMaterial mat = particle.material.Get();
        DBTypes.RenderState rs = mat.renderState;

        //if (clearAlpha) {
        //  if ((rs.blendMode == BlendMode.LerpByAlpha) || (rs.blendMode == BlendMode.PremultipliedLerp))
        //    rs.blendMode = BlendMode.Off;
        //  else
        //  if (rs.blendMode == BlendMode.AddColorMulAlpha)
        //    rs.blendMode = BlendMode.AddColor;
        //}

        float scale = 1.0f;
        if (clearAlpha)
        {
          scale = 0.0f;
          mat.scale = -1.0f;
        }
        else
        {
          mat.scale = 0.0f;
          //if (rs.blendMode == BlendMode.AddColorMulAlpha || rs.blendMode == BlendMode.LerpByAlpha)
          //{
          //  scale = maxValue / (float)(0x0ff * 0x0ff); // NOT 0xff - to account for rounding errors
          //  mat.scale = scale;
          //  scale *= 0.5f; // to separate from "No scale" mode
          //}
        }

        if( !atlas.AddBitmap(bitmap, particle.textures[i].FileName, scale) )
          return false;
      }

      return true;
    }

    private static bool StoreAtlas( Atlas atlas, int index, IEnumerable<DBTypes.DBParticleSceneComponent> resources, IFileSystem fileSystem )
    {
      atlas.BuildAtlas();

      if ( !atlas.IsEmpty )
      {
        DBPtr<DBTypes.Texture> texture = CreateAtlasTexture( atlas.GetAtlas(), fileSystem, index );
        if ( texture != null )
        {
          foreach (DBTypes.DBParticleSceneComponent resource in resources)
            UpdateParticleMaterial(atlas, resource, texture);

          EditorRender.ResetTexture(texture.Get().textureFileName);
          return true;
        }
      }
      return false;
    }

    public static bool Process( IEditorCommonApplication application, IOperationContext context )
    {
      if ( context != null )
        context.Start( true, true );
      if ( context != null )
        context.Progress( "Searching for ParticleSceneComponent..." );
      
      List<DBID> items;
      ObjectsSelector.CollectObjects( application, "", typeof( DBTypes.DBParticleSceneComponent ), true, true, out items );
      if ( items.Count == 0 )
        return true;

      application.UndoRedo.Start( "Create atlas" );
      Atlas atlas = new Atlas();
      int atlasIndex = 0;
      List<DBTypes.DBParticleSceneComponent> resources = new List<DBTypes.DBParticleSceneComponent>();
      for ( int index = 0; index < items.Count; ++index )
      {
        DBTypes.DBParticleSceneComponent resource = DataBase.Get<DBTypes.DBParticleSceneComponent>( items[index] ).Get();

        if (resource.material.Get().DistortionPinValue == DBTypes.BooleanPin.Present)
          continue;

        if ( context != null )
          context.Progress( "Process " + resource.DBId, index * 100 / items.Count );

        if ( ProcessResource( resource, atlas, application.SourceFileSystem ) )
          resources.Add( resource );
        else
        {
          if ( context != null )
            context.Progress( "Store atlas " + atlasIndex.ToString() );
          if ( !StoreAtlas( atlas, atlasIndex, resources, application.FileSystem ) )
            return false;

          atlas = new Atlas();
          ++atlasIndex;
          resources.Clear();

          if ( !ProcessResource( resource, atlas, application.SourceFileSystem ) )
          {
            Log.TraceWarning( "Resource \"{0}\" needs more than one atlas", resource.DBId );
          }
        }
      }
      if ( context != null )
        context.Progress( "Store atlas " + atlasIndex.ToString() );
      if ( !StoreAtlas( atlas, atlasIndex, resources, application.FileSystem ) )
        return false;
      EditorRender.ReloadPFX();
      application.UndoRedo.Commit();

      return true;
    }
  }
}
