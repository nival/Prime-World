using System;
using System.Collections.Generic;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Console
{
	[CommandName( "checksource", "chsrc", "Check DB for existance of source files of different types." )]
	public sealed class CheckSourceCommand : IConsoleCommand
	{
		[CommandArgument( "textures", "tex", "Textures check" )]
		public bool isTexture = false;

		[CommandArgument( "staticmesh", "stm", "Static meshes check" )]
		public bool isStaticMesh = false;

		[CommandArgument( "skeletons", "skl", "Skeletons check" )]
		public bool isSkeletons = false;

		[CommandArgument( "particles", "prt", "Particles check" )]
		public bool isParticles = false;

		[CommandArgument( "effects", "eff", "Effects textures check" )]
		public bool isEffects = false;

		[CommandArgument( "collision", "col", "Collision geometries check" )]
		public bool isCollision = false;

    int IConsoleCommand.Execute( IEditorCommonApplication application, string[] parameters )
		{
			Dictionary<Type, List<DBID>> objects;
			Type[] toCheck = new Type[6];
			toCheck[0] = new DBTypes.Texture().GetType();
			toCheck[1] = new DBTypes.StaticMesh().GetType();
			toCheck[2] = new DBTypes.Skeleton().GetType();
			toCheck[3] = new DBTypes.ParticleFX().GetType();
			toCheck[4] = new DBTypes.Effect().GetType();
			toCheck[5] = new DBTypes.CollisionGeometry().GetType();

			Log.TraceMessage( "" );
			Log.TraceMessage( "--> Collecting objects" );
			var collected = ObjectsSelector.CollectObjects( application, string.Empty, toCheck, true, true, out objects );
			if ( collected <= 0 )
			{
				Log.TraceMessage( "" );
				Log.TraceMessage( "--> No objects collected" );
				return 0;
			}
			Log.TraceMessage( "--> Objects collected" );

			if ( isTexture )
			{
				List<DBID> textures = objects[toCheck[0]];

				Log.TraceMessage( "" );
				Log.TraceMessage( "--> Source texture files not found for:" );
				foreach ( var dbId in textures )
				{
					DBPtr<DBTypes.Texture> res = DataBase.Get<DBTypes.Texture>( dbId );
					DBTypes.Texture tex = res.Get();

					if ( application.SourceFileSystem.IsFileExists( tex.srcFileName.FileName ) )
					{
						continue;
					}

					// Skip generated textures since they have empty srcFilename
					if ( tex.generatedFileName.Length != 0 )
					{
						continue;
					}

					Log.TraceMessage( "{0} <- {1}", tex.DBId.FileName, tex.srcFileName );
				}
				Log.TraceMessage( "--> Textures check complete" );
			}

			if ( isStaticMesh )
			{
				List<DBID> staticmeshes = objects[toCheck[1]];

				Log.TraceMessage( "" );
		    Log.TraceMessage( "--> Source static mesh files not found for:" );
		    foreach ( var dbId in staticmeshes )
		    {
		      DBPtr<DBTypes.StaticMesh> res = DataBase.Get<DBTypes.StaticMesh>( dbId );
		      DBTypes.StaticMesh stm = res.Get();

					if ( application.SourceFileSystem.IsFileExists( stm.srcFileName.FileName ) )
		      {
		        continue;
		      }

		      Log.TraceMessage( "{0} <- {1}", stm.DBId.FileName, stm.srcFileName );
		    }
				Log.TraceMessage( "--> Static meshes check complete" );
			}

			if ( isSkeletons )
			{
				List<DBID> skeletons = objects[toCheck[2]];

				Log.TraceMessage( "" );
				Log.TraceMessage( "--> Source skeleton files not found for:" );
				foreach ( var dbId in skeletons )
				{
					DBPtr<DBTypes.Skeleton> res = DataBase.Get<DBTypes.Skeleton>( dbId );
					DBTypes.Skeleton skl = res.Get();

					if ( !application.SourceFileSystem.IsFileExists( skl.srcFileName.FileName ) )
					{
						Log.TraceMessage( "{0} <- {1}", skl.DBId.FileName, skl.srcFileName );
					}

					IList<DBTypes.Animation> animations = skl.animations;
					foreach ( var anm in animations )
					{
						if ( application.SourceFileSystem.IsFileExists( anm.srcFileName.FileName ) )
						{
							continue;
						}
						Log.TraceMessage( "-Anim->{0} <- {1}", skl.DBId.FileName, anm.srcFileName );
					}

					IList<DBTypes.FaceFX> faceFXs = skl.faceFXAnims;
					foreach ( var ffx in faceFXs )
					{
						if ( application.SourceFileSystem.IsFileExists( ffx.srcFileName.FileName ) )
						{
							continue;
						}
						Log.TraceMessage( "-Face->{0} <- {1}", skl.DBId.FileName, ffx.srcFileName );
					}

					IList<DBTypes.SkinPartBase> skins = skl.skins;
					foreach ( var skn in skins )
					{
						if ( application.SourceFileSystem.IsFileExists( skn.srcFileName.FileName ) )
						{
							continue;
						}
						Log.TraceMessage( "-Skin->{0} <- {1}", skl.DBId.FileName, skn.srcFileName );
					}
				}
				Log.TraceMessage( "--> Skeletons check complete" );
			}

			if ( isParticles )
			{
				List<DBID> particles = objects[toCheck[3]];

				Log.TraceMessage( "" );
				Log.TraceMessage( "--> Source particle files not found for:" );
				foreach ( var dbId in particles )
				{
					DBPtr<DBTypes.ParticleFX> res = DataBase.Get<DBTypes.ParticleFX>( dbId );
					DBTypes.ParticleFX prt = res.Get();

					if ( application.SourceFileSystem.IsFileExists( prt.srcFileName.FileName ) )
					{
						continue;
					}

					Log.TraceMessage( "{0} <- {1}", prt.DBId.FileName, prt.srcFileName );
				}
				Log.TraceMessage( "--> Particles check complete" );
			}

      if ( isCollision )
			{
				List<DBID> collisions = objects[toCheck[5]];

				Log.TraceMessage( "" );
		    Log.TraceMessage( "--> Source collision geometry files not found for:" );
		    foreach ( var dbId in collisions )
		    {
		      DBPtr<DBTypes.CollisionGeometry> res = DataBase.Get<DBTypes.CollisionGeometry>( dbId );
		      DBTypes.CollisionGeometry col = res.Get();

					if ( application.SourceFileSystem.IsFileExists( col.srcFileName.FileName ) )
		      {
		        continue;
		      }

		      Log.TraceMessage( "{0} <- {1}", col.DBId.FileName, col.srcFileName );
		    }
				Log.TraceMessage( "--> Collision geometries check complete" );
			}

      return 0;
		}
	}
}
