using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorPlugins.Importer.Texture;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;

namespace PF_EditorC
{
  public partial class ScriptCommand : IConsoleCommand
  {
    private static Dictionary<string, string> textures = new Dictionary<string, string>();

    #region Collect types

    public static bool IsSocialType( Type checkType )
    {
      CustomAttribute[] attribs = TypeUtils.GetAttributes<CustomAttribute>( checkType, false );
      foreach ( CustomAttribute it in attribs )
      {
        if ( it.IsMatch( "Social" ) )
        {
          return true;
        }
      }

      return false;
    }

    private Dictionary<Type, Type> CollectSocialTypes()
    {
      var result = new Dictionary<Type, Type>();
      foreach ( var type in DataBase.KnownTypes )
      {
        if ( IsSocialType( type ) )
          result.Add( type, type );
      }

      foreach ( var type in DataBase.KnownTypes )
      {
        if ( !IsSocialType( type ) )
        {
          var baseType = type.BaseType;
          while ( baseType != null )
          {
            if ( IsSocialType( baseType ) )
            {
              result.Add( type, baseType );
              break;
            }
            baseType = baseType.BaseType;
          }
        }
      }

      return result;
    }

    #endregion

    #region Collect ptrs

    private class RootPtrCollector
    {
      private readonly Dictionary<DBID, DBResource> _result = new Dictionary<DBID, DBResource>();
      private readonly Dictionary<DBID, object> _visited = new Dictionary<DBID, object>();
      private readonly Dictionary<Type, object> _socialTypes = new Dictionary<Type, object>();

      public RootPtrCollector( DBResource root, IEnumerable<Type> socialTypes )
      {
        _result.Add( root.DBId, root );
        foreach ( var type in socialTypes )
          _socialTypes.Add( type, null );
      }

      public bool CheckDepth( object obj, ref int depth )
      {
        if ( null == obj )
          return false;

        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        if ( ptr.DBId.IsEmpty || _visited.ContainsKey( ptr.DBId ) )
          return false;

        _visited.Add( ptr.DBId, null );
        return true;
      }
      public bool Collect( ref DBPtrBase ptr )
      {
        if ( ptr.DBId.IsEmpty /*|| ptr.DBId.IsInlined*/ )
          return true;

        if ( !DataBase.IsExists( ptr.DBId ) || ptr.Get<DBResource>() == null )
          return true;

        if ( !_result.ContainsKey( ptr.DBId ) && _socialTypes.ContainsKey( ptr.Get<DBResource>().GetType() ) )
          _result.Add( ptr.DBId, ptr.Get<DBResource>() );

        return true;
      }

      public IEnumerable<DBResource> Result { get { return _result.Values; } }
    }

    private List<DBResource> CollectResources( DBResource root, IEnumerable<Type> socialTypes )
    {
      var collector = new RootPtrCollector( root, socialTypes );
      FieldsWalker.VisitFields<DBPtrBase>( root, collector.Collect, collector.CheckDepth );

      var result = new List<DBResource>( collector.Result );
      result.Sort( ( DBResource a, DBResource b ) => { return DBID.Compare( a.DBId, b.DBId ); } );

      return result;
    }

    #endregion

    #region Store resources

    private int GetEnumerableCount( IEnumerable<DBResource> resources )
    {
      int result = 0;
      foreach ( var res in resources )
        ++result;

      return result;
    }

    private void StoreResources( IEnumerable<DBResource> resources, Dictionary<Type, Type> socialTypes, Dictionary<Type, DBXmlSerializer.TypeReplacementFunc> valueResolver, string fileName )
    {
      Log.TraceMessage( "Store {0} objects to \"{1}\"...", GetEnumerableCount( resources ), fileName );

      var settings = new XmlWriterSettings() { Indent = true, IndentChars = "  " };
      using ( var writer = XmlWriter.Create( new FileStream( fileName, FileMode.Create, FileAccess.Write ), settings ) )
      {
        writer.WriteStartDocument();
        writer.WriteStartElement( "CastleData" );

        writer.WriteStartElement( "Objects" );
        foreach ( var res in resources )
        {
          writer.WriteStartElement( socialTypes[res.GetType()].Name );
          writer.WriteStartAttribute( "dbid" );
          writer.WriteString( res.DBId.ToString() );
          writer.WriteEndElement();
        }
        writer.WriteEndElement();

        writer.WriteStartElement( "Data" );
        foreach ( var res in resources )
        {
          writer.WriteStartElement( "ObjData" );
          writer.WriteStartAttribute( "dbid" );
          writer.WriteString( res.DBId.ToString() );
          writer.WriteEndAttribute();
          DBXmlSerializer.Serialize( writer, res, valueResolver );
          writer.WriteEndElement();
        }
        writer.WriteEndElement();

        writer.WriteEndElement();
        writer.WriteEndDocument();

        writer.Flush();
        writer.Close();
      }
    }

    #endregion

    #region Custom types resolvers

    private static object ReplaceTextRef( object obj )
    {
      var value = obj as TextRef;
      return value.GetText();
    }

    private static object ReplaceTexturePtr( object obj )
    {
      Texture texture = ( obj as DBPtrBase ).Get<Texture>();
      if ( texture == null )
        return string.Empty;

      string result = texture.textureFileName;
      if ( !textures.ContainsKey( result.ToLowerInvariant() ) )
        textures.Add( result.ToLowerInvariant(), result );

      result = FileUtils.Combine( FileUtils.GetFolderName( result ), FileUtils.GetFileNameWithoutExtension( result ) ).TrimStart( '/', '\\' );
      if ( result.Contains( "Fairy" ) )
        return result;
      return result;
    }

    private static string ReplaceFloatSimbols( string str )
    {
      string result = string.Empty;
      bool isDigit = false;
      for ( int it = 0; it < str.Length; ++it )
      {
        if ( char.IsDigit( str[it] ) )
        {
          result += str[it];
          isDigit = true;
        }
        else
        {
          if ( !isDigit || ( str[it] != 'f' && str[it] != 'F' ) )
            result += str[it];

          isDigit = false;
        }
      }

      return result;
    }

    private static object ReplaceExecutableString( object obj )
    {
      BaseExecutableString value = obj as BaseExecutableString;

      string result = ReplaceFloatSimbols( value.sString );

      result = result.Replace( "sender.", "s" );
      result = result.Replace( "sender->", "s" );
      result = result.Replace( "receiver.", "r" );
      result = result.Replace( "receiver->", "r" );
      result = result.Replace( "appl.", "m" );
      result = result.Replace( "appl->", "m" );

      return result;
    }

    #endregion
    
    private const string SocialRootHRef = "/Social.ROOT";
    private const string TalentsCollectingRoot = "/Items/";
    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
      bool cleanHeroes = false;
      string copyDataFrom = string.Empty;
      string copyDataTo = string.Empty;
      string resultFilePath = string.Empty;

      foreach ( var arg in args )
      {
        if ( arg.StartsWith( "copy_data=", StringComparison.InvariantCultureIgnoreCase ) )
        {
          var paths = arg.Substring( "copy_data=".Length ).Split( ',' );
          if ( paths.Length == 2 )
          {
            copyDataFrom = FileUtils.Combine( FileUtils.PathSeparatorString, FileUtils.FixFolderName( paths[0] ) );
            copyDataTo = paths[1];
          }
        }
        else if ( string.Compare( arg, "clean_heroes", true ) == 0 )
          cleanHeroes = true;
        else
          resultFilePath = arg;
      }

      //Called from editor UI
      //if ( string.IsNullOrEmpty( resultFilePath ) )
      //{
      //  SaveFileDialog saveFileDialog = new SaveFileDialog();
      //  saveFileDialog.InitialDirectory = Convert.ToString( Environment.SpecialFolder.MyDocuments );
      //  saveFileDialog.Filter = "Xml (*.xml)|*.xml|All Files (*.*)|*.*";
      //  saveFileDialog.FilterIndex = 1;
      //  saveFileDialog.FileName = "ExportedSocialData";

      //  if ( saveFileDialog.ShowDialog() == DialogResult.OK )
      //    resultFilePath = saveFileDialog.FileName;
      //  else
      //    yield break;
      //}

      SocialRoot root = DataBase.Get<SocialRoot>( DBID.FromFileName( SocialRootHRef, false ) );

      Log.TraceMessage( "Fix heroes..." );
      var heroes = root.Heroes.Get();
      for ( int i = 0; i < heroes.heroes.Count; ++i )
      {
        var hero = heroes.heroes[i].Get<Hero>();
        if ( hero == null || ( cleanHeroes && !hero.legal ) )
        {
          heroes.heroes.RemoveAt( i );
          --i;
        }
      }

      // заполянем все DefaultTalentSet для героев
      var validClassTalent = new Dictionary<Talent, bool>();
      Log.TraceMessage( "Update class talents..." );
      foreach ( var heroPtr in root.Heroes.Get().heroes )
      {
        var hero = heroPtr.Get();
        foreach ( var ts in hero.defaultTalentsSets )
        {
          foreach ( var level in ts.Get().levels )
          {
            foreach ( var talentDesc in level.talents )
            {
              var talent = talentDesc.talent.Get();
              if ( !talentDesc.talent.IsValid )
                continue;
              if ( talent.rarity == ETalentRarity.Class && !validClassTalent.ContainsKey( talent ) )
              {
                validClassTalent.Add( talent, true );
              }
            }
          }
        }
      }

      var validTalents = new Dictionary<Talent, bool>();
      foreach ( var talentPtr in root.Talents )
        validTalents.Add( talentPtr.Get(), false );

      var talentsDbids = new List<DBID>();
      ObjectsSelector.CollectObjects( app, TalentsCollectingRoot, typeof( Talent ), true, true, out talentsDbids );
      foreach ( var talentDbid in talentsDbids )
      {
        var talentPtr = DataBase.Get<Talent>( talentDbid );
        Talent talent = talentPtr.Get();
        if ( string.IsNullOrEmpty( talent.persistentId ) )
        {
          Log.TraceWarning( "Skip talent with empty persistentId {0}", talentDbid );
          continue;
        }

        if ( talent.rarity == ETalentRarity.Class && !validClassTalent.ContainsKey( talent ) )
        {
          Log.TraceWarning( "Skip class talent for unused hero {0}", talentDbid );
          continue;
        }

        if ( validTalents.ContainsKey( talent ) )
          validTalents[talent] = true;
        else
          root.Talents.Add( talentPtr );
      }

      for( int index = 0; index < root.Talents.Count; ++index )
      {
        var valid = false;
        if ( validTalents.TryGetValue( root.Talents[index].Get(), out valid ) && !valid )
        {
          Log.TraceWarning( "Remove unused talent {0}", root.Talents[index].DBId );
          root.Talents.RemoveAt( index );
          --index;
        }
      }

      root.UIRoot.Get().screens.Clear();

      Log.TraceMessage( "Collect social resources from root \"{0}\"...", root.DBId );
      var socialTypes = CollectSocialTypes();
      var resources = CollectResources( root, socialTypes.Keys );

      //if ( root != null )
      //{
      //  CompileQuest compile = new CompileQuest();
      //  if ( compile.InitGramma() )
      //  {
      //    foreach ( var questLine in root.Quests )
      //    {
      //      foreach ( var quest in questLine.Get().quests )
      //      {
      //        foreach ( var obj in quest.Get().objectives )
      //        {
      //          var cond = obj.condition.Get();
      //          if ( cond is ModelDataCondition )
      //          {
      //            Log.TraceMessage( "Processing condition {0}...", cond.DBId );
      //            StringBuilder resultCSCode = new StringBuilder();
      //            StringBuilder resultPYCode = new StringBuilder();
      //            string id = cond.DBId.Name.Replace( "-", "_" ).Replace( "/", "_" ).Replace( ".", "_" ).Replace( ":", "_" );
      //            if ( !compile.FillConditionCode( resultCSCode, resultPYCode, cond as ModelDataCondition, id ) )
      //            {
      //              Log.TraceError( "Parse failed for {0} condition", cond.DBId );
      //            }
      //            else
      //            {
      //              ( cond as ModelDataCondition ).code = resultPYCode.ToString();
      //            }
      //          }
      //        }
      //      }
      //    }
      //  }
      //}

      var valueResolver = new Dictionary<Type, DBXmlSerializer.TypeReplacementFunc>();
      valueResolver.Add( typeof( TextRef ), ReplaceTextRef );
      valueResolver.Add( typeof( DBPtr<Texture> ), ReplaceTexturePtr );
      valueResolver.Add( typeof( DBPtr<TextureBase> ), ReplaceTexturePtr );
      valueResolver.Add( typeof( ExecutableFloatString ), ReplaceExecutableString );
      valueResolver.Add( typeof( ExecutableIntString ), ReplaceExecutableString );
      valueResolver.Add( typeof( ExecutableBoolString ), ReplaceExecutableString );
      StoreResources( resources, socialTypes, valueResolver, resultFilePath );
      Log.TraceMessage( "Data was succesfully saved to '{0}'", resultFilePath );

      if ( !string.IsNullOrEmpty( copyDataFrom ) && !string.IsNullOrEmpty( copyDataTo ) )
      {
        Log.TraceMessage( "Copy {0} textures to social's folder...", textures.Count );
        Dictionary<string, string> filteredTextures = new Dictionary<string, string>();
        copyDataFrom = copyDataFrom.ToLowerInvariant();
        foreach ( var texture in textures )
        {
          if ( texture.Key.StartsWith( copyDataFrom ) )
            filteredTextures.Add( texture.Key, texture.Value );
        }
        var files = Directory.GetFiles( copyDataTo, "*.dds", SearchOption.AllDirectories );
        var filesToDelete = new List<string>();
        foreach ( var file in files )
        {
          string cutFileName = FileUtils.FixFileName( copyDataFrom + FileUtils.Combine( FileUtils.PathSeparatorString, file.Substring( copyDataTo.Length ) ) ).ToLowerInvariant();
          if ( !filteredTextures.ContainsKey( cutFileName ) )
          {
            File.Delete( file );
            if ( File.Exists( file + ".meta" ) )
              File.Delete( file + ".meta" );
          }
        }
        foreach ( var texture in filteredTextures )
        {
          string textureFileName = Path.Combine( copyDataTo, texture.Value.Substring( copyDataFrom.Length ).TrimStart( '/', '\\' ) );
          string textureFilePath = Path.GetDirectoryName( textureFileName );
          if ( !Directory.Exists( textureFilePath ) )
            Directory.CreateDirectory( textureFilePath );
          File.WriteAllBytes( textureFileName, FileUtils.ReadFile( app.FileSystem, texture.Value ) );
        }
        var folders = new List<string>();
        int index = 0;
        folders.Add( copyDataTo );
        while ( index < folders.Count )
        {
          folders.AddRange( Directory.GetDirectories( folders[index] ) );
          ++index;
        }
        for ( index = folders.Count - 1; index >= 0; --index )
        {
          if ( Directory.GetDirectories( folders[index] ).Length == 0 && Directory.GetFiles( folders[index] ).Length == 0 )
          {
            Directory.Delete( folders[index] );
            if ( File.Exists( folders[index] + ".meta" ) )
              File.Delete( folders[index] + ".meta" );
          }
        }
      }
      yield return true;
    }


    private bool IsTalentsContains( libdb.IChangeableList<DBPtr<Talent>> talents, DBID dbid )
    {
      foreach ( var talent in talents )
      {
        if ( talent.DBId == dbid )
          return true;
      }
      return false;
    }
  }
}
