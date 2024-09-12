
/*
#about находит все текстуры, не степени двойки
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

public class CheckBadTextureSize
{
  public static bool IsPow2( int i ) { return ( ( i & ( i - 1 ) ) == 0 ); }
  public static int GetRealSize( int size, int mipmaplevel )
  {
    int divided = 1;
    for ( int i = 0; i < mipmaplevel; i++ )
    {
      divided *= 2;
    }
    return size / divided;
  }

  public IEnumerable Main( IEditorCommonApplication app, string[] parameters )
  {
    List<DBID> dbids = new List<DBID>();
    Log.TraceMessage( "Collecting textures..." );
    ObjectsSelector.CollectObjects( app, "", typeof( Texture ), true, true, out dbids );
    Log.TraceMessage( "{0} total textures. Processing...", dbids.Count );
    int counter = 0;
    foreach ( DBID dbid in dbids )
    {
      Texture texture = DataBase.Get<Texture>( dbid ).Get();

      if ( ReferenceEquals( texture, null ) )
        continue;

      if ( texture.GetType() == typeof( Texture ) )
      {
        int realSizeX = GetRealSize( texture.size.width, texture.startMipLevel );
        int realSizeY = GetRealSize( texture.size.height, texture.startMipLevel );
        if ( !IsPow2( realSizeX ) || !IsPow2( realSizeY ) )
        {
          Log.TraceError( "Texture({0}) size({1}x{2}) is not power of 2", dbid.GetFullFileName(), realSizeX, realSizeY );
          counter++;
        }
      }
    }

    Log.TraceMessage( "{0} bad textures.", counter );
    yield return true;
  }
}

