using System.Collections.Generic;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using DBTypes;
using libdb.Animated;

namespace EditorPlugins.Console
{
 // [CommandName( "convert", "c", "Types conversion." )]
 // public sealed class ConvertDBCommand : IConsoleCommand
 // {
 //   private const string PREFIX = "/PF_";

 //   #region IConsoleCommand Members

 //   public void Execute( IEditorCommonApplication application, string[] parameters )
 //   {
 //     List<DBID> items;
 //     ObjectsSelector.CollectObjects( application, "", typeof( DBResource ), true, true, out items );

 //     int counter = 0;

 //     foreach ( var dbId in items )
 //     {
 //       var obj = DataBase.Get<DBResource>( dbId ).Get();

 //       if ( ReferenceEquals( obj, null ) )
 //         continue;

 ///*       if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( DBSceneResource ) ) )
 //       {
 //         Log.TraceDebug( "Converting {0}...", obj.DBId );
 //         DBSceneResource res = obj as DBSceneResource;
 //         foreach ( AttachedSceneComponent comp in res.attached )
 //         {
 //           FixAnim( comp.placement.pos );
 //           FixAnim( comp.placement.rot );
 //           FixAnim( comp.placement.scale );
 //         }
 //       }
 //       else if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( DecalMaterial ) ) )
 //       {
 //         Log.TraceDebug( "Converting {0}...", obj.DBId );
 //         DecalMaterial res = obj as DecalMaterial;
 //         FixAnim( res.opacity );
 //       }
 //       else if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( BasicFXMaterial ) ) )
 //       {
 //         Log.TraceDebug( "Converting {0}...", obj.DBId );
 //         BasicFXMaterial res = obj as BasicFXMaterial;
 //         FixAnim( res.opacity );
 //         FixAnim( res.uOffset1 );
 //         FixAnim( res.vOffset1 );
 //       }
 //       else
 //       {
 //         continue;
 //       }*/

 //       ++counter;
 //     }

 //     Log.TraceDebug( "Done: {0} obejcts", counter );

 //     DataBase.Store();
 //   }

 //   /*private void FixAnim( IAnimated animatedParam )
 //   {
 //     float maxLength = 0.0f;

 //     if ( animatedParam.Type == AnimatedType.None )
 //       return;

 //     for ( int i = 0; i < animatedParam.TracksCount; ++i )
 //     {
 //       IAnimatedTrack track = animatedParam.GetObjectTrack( i );

 //       for ( int j = 0; j < track.KeysCount; ++j )
 //       {
 //         float keyTime = track.GetKey( j );
 //         if ( keyTime > maxLength )
 //           maxLength = keyTime;
 //       }
 //     }

 //     if ( animatedParam.Length != maxLength )
 //     {
 //       Log.TraceDebug( "Adjusted length {0} to {1}", animatedParam.Length, maxLength );
 //       animatedParam.Length = maxLength;
 //     }
 //   }*/

 //   #endregion
 // }
}
