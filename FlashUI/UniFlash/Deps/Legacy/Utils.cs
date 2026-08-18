using System;
using System.Collections.Generic;
using System.IO;
using CastleTypes;
using Flash;
using Lobby.Configs;
using Lobby.Model;
using ModelData;
using NivalCLI;
using NivalCLI.Log;
using UnityEngine;
using Object = UnityEngine.Object;
using Resources = ResourcesManager.Resources;
using Transform = UnityEngine.Transform;

namespace Lobby.Tools
{

  public static class Utils
  {
    public static void DeleteAllOutOfDateFiles(string directory, DateTime date)
    {
      if(!Directory.Exists( directory ))
        return;
      var directories = Directory.GetDirectories( directory );
      foreach ( var dir in directories )
      {
        if ( Directory.GetLastWriteTime( dir ) < date )
          Directory.Delete( dir, true );
      }
    }

    public static bool IsEquals( ConstructionPosition a, ConstructionPosition b )
    {
      return a.X == b.X && a.Y == b.Y && a.Pitch == b.Pitch;
    }

    public static bool IsEquals( int[] a, ConstructionPosition b )
    {
      return a[0] == b.X && a[1] == b.Y && a[2] == b.Pitch;
    }

    public static Vector3 Convert( Vec3 vec )
    {
      return new Vector3( vec.x, vec.y, vec.z );
    }

    public static Vector2 Convert( Vec2 vec )
    {
      return new Vector2( vec.x, vec.y );
    }

    public static Vector2 Convert( IntVec2 vec )
    {
      return new Vector2( vec.x, vec.y );
    }

    /// <summary>
    /// Collecting all objects from specified resources directory
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public static List<T> LoadAllObjects<T>( string directoryPath ) where T : class
    {
      List<T> objects = new List<T>();
      try
      {
        Object[] loaded = Resources.LoadAll( directoryPath );
        LogMissingScriptsInLoaded( loaded, directoryPath );
        foreach ( var o in loaded )
          if ( o is T )
            objects.Add( o as T );
      }
      catch (Exception ex)
      {
        CLI.Error("Load resources from path '{0}' error: {1}", directoryPath, ex.Message);
      }
      //Sorting like unity resources system(alphabetically)
      //models.Sort( ( a, b ) => string.Compare( a.name, b.name ) );
      return objects;
    }

    private static void LogMissingScriptsInLoaded( Object[] loaded, string directoryPath )
    {
#if UNITY_EDITOR
      for ( int i = 0; i < loaded.Length; i++ )
      {
        if ( loaded[i].GetType() != typeof( GameObject ) )
          continue;
        GameObject go = (GameObject)loaded[i];
        Transform[] nodes = go.GetComponentsInChildren<Transform>( true );
        for ( int n = 0; n < nodes.Length; n++ )
        {
          int missing = UnityEditor.GameObjectUtility.GetMonoBehavioursWithMissingScriptCount( nodes[n].gameObject );
          if ( missing > 0 )
            CLI.Error( "Missing script x{0}: prefab '{1}', node '{2}', dir '{3}'", missing, go.name, nodes[n].name, directoryPath );
        }
      }
#endif
    }

    public static bool[,] GetSections( CastleTypes.SectionsSet unit )
    {
      List<KeyValuePair<int,int>> b = new List<KeyValuePair<int, int>>();

      int width = 0;
      int height = 0;
      if ( unit != null )
        foreach ( IntVec2 vec in unit.Sections )
        {
          b.Add( new KeyValuePair<int, int>( vec.x, vec.y ) );
          if ( vec.x >= width )
            width = 1 + vec.x;

          if ( vec.y >= height )
            height = 1 + vec.y;
        }

      bool[,] result = new bool[width, height];
      //Initialize array
      for ( int i = 0; i < result.GetLength( 0 ); i++ )
        for ( int j = 0; j < result.GetLength( 1 ); j++ )
          result[i, j] = false;
      //Setting active sections

      foreach ( var match in b )
      {
        result[match.Key, match.Value] = true;
      }

      return result;
    }

    public static byte[,] GetConstructionSections( CastleTypes.Constructon unit )
    {
      List<KeyValuePair<int,int>> b = new List<KeyValuePair<int, int>>();
      List<KeyValuePair<int,int>> d = new List<KeyValuePair<int, int>>();

      int width = 0;
      int height = 0;
      if ( unit.SectionsLockedForBuilding != null )
        foreach ( IntVec2 vec in unit.SectionsLockedForBuilding.Sections )
        {
          b.Add( new KeyValuePair<int, int>( vec.x, vec.y ) );
          if ( vec.x > width )
            width = vec.x;

          if ( vec.y > height )
            height = vec.y;
        }
      if ( unit.SectionsLockedForDecorations != null )
        foreach ( IntVec2 vec in unit.SectionsLockedForDecorations.Sections )
        {
          d.Add( new KeyValuePair<int, int>( vec.x, vec.y ) );
          if ( vec.x > width )
            width = vec.x;

          if ( vec.y > height )
            height = vec.y;

          //if ( vec.x > width || vec.y > height )
          //{
          //  CLI.DataAssert( "Decoration section is out of bulding sections in construction '{0}' ('{1}').", unit.persistentId, unit.Caption );
          //  return null;
          //}
        }

      byte[,] result = new byte[width + 1, height + 1];
      foreach ( var match in b )
      {
        result[match.Key, match.Value] = 1;
      }

      foreach ( var match in d )
      {
        result[match.Key, match.Value] = 2;
      }


      return result;
    }

    public static bool IsShippingAssembly()
    {
      return ( AssemblyInfoAccessor.Configuration == "shipping" );
    }

    public static Level GetCurrentLogLevel()
    {
      if ( !CLI.IsDebugVersion() )
      {
        return System.Environment.GetEnvironmentVariable( CLI.FULL_LOG_LEVEL_ENV_NAME ) != null ? Level.All : Config.CastleLogLevel;
      }
      return Level.All;
    }

    public static KeyValuePair<int, int> ConstructionToMapIndexesAddendums( int x, int y, int pitch )
    {
      int n_i = x;
      int n_j = y;
      if ( pitch == 0 )
      {
        n_i = x;
        n_j = +y;
      }

      if ( pitch == 90 )
      {
        n_i = y;
        n_j = -x;
      }

      if ( pitch == 180 )
      {
        n_i = -x;
        n_j = -y;
      }

      if ( pitch == 270 )
      {
        n_i = -y;
        n_j = x;
      }

      return new KeyValuePair<int, int>( n_i, n_j );
    }
    public readonly static Vector3 Right = new Vector3( 1, 0, 0 );
    public readonly static Vector3 Forward = new Vector3( 0, 0, 1 );

    public static Vector3 GetKeySectionWorldPosition( Transform transform, Vector3 offset )
    {
      //Debug.Log( transoform.right + "    " + transoform.forward );
      Vector3 result = transform.position - offset.x * transform.right - offset.z * transform.forward;
      return result;
    }

    public static Vector3 GetKeySectionWorldPosition( Vector3 position, Vector3 offset )
    {
      //Debug.Log( transoform.right + "    " + transoform.forward );
      Vector3 result = position - offset.x * Right - offset.z * Forward;
      return result;
    }

    public static Vector3 GetKeySectionWorldPosition( Vector3 position, Vector3 right, Vector3 forward, Vector3 offset )
    {
      Vector3 result = position - offset.x * right - offset.z * forward;
      return result;
    }

    public static Vector3 GetOffset( CastleTypes.Constructon construction, PlayerFraction fraction, float sectionSize )
    {
      Vector3 offset = Convert( construction.OffsetA );
      if ( fraction == PlayerFraction.B )
        offset = Convert( construction.OffsetB );

      if ( offset.x == 0 && offset.z == 0 )
      {
        float ss = sectionSize / 2;
        byte[,] s = GetConstructionSections( construction );

        offset = new Vector3( ss * s.GetLength( 0 ) - ss, offset.y, ss * s.GetLength( 1 ) - ss );
      }
      return offset + Utils.Convert( StaticDataCache.SocialRoot.CommonConstructionsSettings.Offset );
    }


    public static Quaternion GetConstructionWorldRotation( Construction unit )
    {
      Quaternion res = Quaternion.Euler( 0, unit.Position.Pitch, 0 );
      return res;
    }

    /// <summary>
    /// Gets construction prefab wich can be placed on stage. Excluding building effects and etc.
    /// </summary>
    /// <returns></returns>
    public static GameObject GetClearConstrucionPrefab( GameObject prefab )
    {
      if ( prefab == null )
        return null;
      if ( prefab.transform.Find( "Construction" ) != null )
        return prefab.transform.Find( "Construction" ).gameObject;
      return prefab;
    }

    public static CastleTypes.Constructon GetPlan( Construction construction )
    {
      return StaticDataCache.Get<CastleTypes.Constructon>( construction.PersistentId );
    }

    public static ConstructionLevel GetConstructionLevel( Construction construction )
    {
      Constructon c = GetPlan( construction );
      if ( construction.Level < c.Levels.Count )
        return c.Levels[construction.Level];

      CLI.DataAssert( "Requesting '{0}' grade, but StaticData contains only '{1}' grades.", construction.Level,
                      c.Levels.Count );
      return null;
    }

    public static ConstructionPosition RotateTroughCenter( Construction unit )
    {
      byte[,] sections = GetConstructionSections( StaticDataCache.Get<CastleTypes.Constructon>( unit.PersistentId ) );

      int w = sections.GetLength( 0 );
      int h = sections.GetLength( 1 );
      ConstructionPosition result = new ConstructionPosition( null, null );

      result.X = unit.Position.X;
      result.Y = unit.Position.Y;
      result.Pitch = unit.Position.Pitch;

      result.Pitch += 90;
      if ( result.Pitch > 270 )
        result.Pitch = 0;

      if ( result.Pitch == 0 )
      {
        result.X -= w - 1;
      }
      if ( result.Pitch == 90 )
      {
        result.Y += h - 1;
      }
      if ( result.Pitch == 180 )
      {
        result.X += w - 1;
      }
      if ( result.Pitch == 270 )
      {
        result.Y -= h - 1;
      }

      return result;
    }

    public static bool IsDecoration( Constructon construction )
    {
      return typeof( Decoration ).IsAssignableFrom( construction.GetType() );
    }

    public static bool IsDecoration( ModelData.Construction construction )
    {
      return typeof( Decoration ).IsAssignableFrom( StaticDataCache.Get<CastleTypes.Constructon>( construction.PersistentId ).GetType() );
    }

    public static GameObject GetLocator( GameObject parent )
    {
      Transform[] ts = parent.GetComponentsInChildren<Transform>();
      foreach ( Transform t in ts )
        if ( t.tag == "ConstructionOvertype" )
          return t.gameObject;
      return parent;
    }

    public static void ToBitSurface( List<KeyValuePair<int, int>> arr, ref BitSurface result )
    {
      result.FillAreaSafe( 0, 0, result.Width, result.Height, true );
      foreach ( var v in arr )
      {
        result.SetSafe( v.Key, v.Value, !true );
      }
    }

    public static List<Transform> GetChildsWithTag( Transform target, string tag, bool recursively )
    {
      List<Transform> result = new List<Transform>();
      foreach ( Transform child in target )
      {
        if ( child.tag == tag )
          result.Add( child );
        if ( recursively )
          result.AddRange( GetChildsWithTag( child, tag, recursively ) );
      }
      return result;
    }

    public static HTTPSocketComponent GetHTTPComponent()
    {
      GameObject componentObj = GameObject.Find( "HTTPSocket" );
      if ( componentObj == null )
      {
        componentObj = new GameObject( "HTTPSocket" );
        componentObj.AddComponent<HTTPSocketComponent>();
        Object.DontDestroyOnLoad( componentObj );
      }
      return componentObj.GetComponent<HTTPSocketComponent>();
    }
  }
}
