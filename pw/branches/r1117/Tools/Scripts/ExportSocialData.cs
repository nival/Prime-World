/*
#about Экспорт данных для социального клиента
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
#include CompileQuestUtils.cs
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
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
using System.Windows.Forms;

namespace Utils
{
    public class ExportSocialData
    {
    private static Dictionary<string, string> textures = new Dictionary<string, string>();

    #region Collect types

    private const string CUSTOM_ATTR_NAME = "Social";
    public static bool IsTypeContainsSocialFields( Type checkType )
    {
      DBFieldInfo[] members = TypeUtils.GetFields( checkType, false );
      foreach ( DBFieldInfo member in members )
        if ( IsSocialMember( member ) )
          return true;
      return false;
    }

    public static bool IsSocialType( Type checkType )
    {
      CustomAttribute[] attribs = TypeUtils.GetAttributes<CustomAttribute>( checkType, false );
      foreach ( CustomAttribute it in attribs )
        if ( it.IsMatch( CUSTOM_ATTR_NAME ) )
          return true;
      return false;
    }

    public static bool IsSocialMember( ICustomAttributeProvider checkingMember )
    {
      Object[] attributes = checkingMember.GetCustomAttributes( false );
      foreach ( Object attribute in attributes )
      {
        if ( attribute is CustomAttribute )
          if ( ( attribute as CustomAttribute ).IsMatch( CUSTOM_ATTR_NAME ) )
            return true;
      }
      return false;
    }

    private Dictionary<Type, Type> CollectSocialTypes( ref List<Type> socialTypes, ref List<Type> typesWithSocialFields )
    {
      var result = new Dictionary<Type, Type>();
      bool socialType = false; bool typeWithSocialField = false;

      foreach ( var type in DataBase.KnownTypes )
      {
        var baseType = type;
        while ( baseType != null )
        {
          socialType = IsSocialType( baseType );
          typeWithSocialField = IsTypeContainsSocialFields( baseType );

          if ( ( socialType || typeWithSocialField ) )
          {
            if ( socialType && !socialTypes.Contains( baseType ) )
              socialTypes.Add( baseType );

            if ( typeWithSocialField && !socialType && !typesWithSocialFields.Contains( baseType ) )
              typesWithSocialFields.Add( baseType );

            if ( !result.ContainsKey( type ) )
              result.Add( type, baseType );
            break;
          }

          baseType = baseType.BaseType;
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
      private readonly List<Type> _typesWithSocialFields = new List<Type>();


      public RootPtrCollector( DBResource root, Dictionary<Type, Type> socialTypes, List<Type> typesWithSocialFields, bool isForServer )
      {
        _result.Add( root.DBId, root );
        foreach ( var type in socialTypes )
          _socialTypes.Add( type.Key, type.Value );
        foreach ( var type in typesWithSocialFields )
          _typesWithSocialFields.Add( type );

        if ( isForServer )
          BuildForbiddenTypesDict( socialTypes );
      }

      public void BuildForbiddenTypesDict( Dictionary<Type, Type> socialTypes )
      {
        foreach ( var fType in forbiddenTypes )
        {
          if ( !_forbiddenTypes.Contains( fType ) )
            _forbiddenTypes.Add( fType );
        }


        foreach ( var type in socialTypes.Keys )
        {
          int i = 0;
          if ( type == typeof( HDRColor ) )
            i++;
          foreach ( var fType in forbiddenSubTypes )
          {
            if ( TypeUtils.IsSubclassOf( type, fType ) && !_forbiddenTypes.Contains( type ) )
              _forbiddenTypes.Add( type );
          }
        }

        foreach ( var type in socialTypes )
        {
          if ( _forbiddenTypes.Contains( type.Value ) && !_forbiddenTypes.Contains( type.Key ) )
          {
            _forbiddenTypes.Add( type.Key );
          }
        }
      }

      public bool CheckDepth( object obj, object fieldKeeper, DBFieldInfo field, ref int depth )
      {
        if ( null == obj )
          return false;

        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        if ( ptr.DBId.IsEmpty || _visited.ContainsKey( ptr.DBId ) )
          return false;

        if ( _typesWithSocialFields.Contains( fieldKeeper.GetType() ) )
          if ( !IsSocialMember( field ) )
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
        Type type = ptr.Get<DBResource>().GetType();

        if ( !_result.ContainsKey( ptr.DBId ) && _socialTypes.ContainsKey( type ) && !_forbiddenTypes.Contains( type ) )
          _result.Add( ptr.DBId, ptr.Get<DBResource>() );


        return true;
      }

      public IEnumerable<DBResource> Result { get { return _result.Values; } }
    }

    private List<DBResource> CollectResources( DBResource root, Dictionary<Type, Type> socialTypes,
       List<Type> typesWithSocialFields, bool isForServer )
    {
      var collector = new RootPtrCollector( root, socialTypes, typesWithSocialFields, isForServer );
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

    private void StoreResources( IEnumerable<DBResource> resources, Dictionary<Type, Type> socialTypes, List<Type> typesWithSocialFields, Dictionary<Type, DBXmlSerializer.TypeReplacementFunc> valueResolver, string fileName )
    {
      Log.TraceMessage( "Store {0} objects to \"{1}\"...", GetEnumerableCount( resources ), fileName );

        //Console.WriteLine("StoreResources to FILE: " + fileName);

      var settings = new XmlWriterSettings() { Indent = true, IndentChars = "  " };
      using ( var file = new FileStream( fileName, FileMode.Create, FileAccess.Write ) )
      {
        using ( var writer = XmlWriter.Create( file, settings ) )
        {
          writer.WriteStartDocument();
          writer.WriteStartElement( "CastleData" );
          writer.WriteStartElement( "Objects" );
          foreach ( var res in resources )
          {
              //Console.WriteLine("StoreResources: creating desc for " + res.DBId.ToString());
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

            DBXmlSerializer.Serialize( writer, res, valueResolver, ( DBFieldInfo fi ) =>
            {
              Type baseType;
              if ( socialTypes.TryGetValue( fi.DeclaringType,
                                           out baseType ) )
              {
                if ( typesWithSocialFields.Contains( baseType ) )
                  return IsSocialMember( fi );

                return true;
              }
              return false;
            } );

            writer.WriteEndElement();
          }
          writer.WriteEndElement();
          writer.WriteEndElement();
          writer.WriteEndDocument();
          writer.Flush();
          writer.Close();
        }
      }
    }

    #endregion

    #region Custom types resolvers

    private static object ReplaceTextRef( object obj )
    {
      var value = obj as TextRef;
      return value.ToString();
    }

    private static object ReplaceTexturePtr( object obj )
    {
      Texture texture = ( obj as DBPtrBase ).Get<Texture>();
      if ( texture == null )
        return string.Empty;

      if ( !texture.textureFileName.Contains( copyDataFrom ) )
      {
        Log.TraceMessage( "Texture '{0}' ignored, because doesnt contains copy data path '{1}'",
        texture.textureFileName, copyDataFrom );
        return string.Empty;
      }
      string result = texture.textureFileName;

      //Console.WriteLine("PREPROCESSING texture: " + texture.srcFileName);

      if ( !textures.ContainsKey( result.ToLowerInvariant() ) )
        textures.Add( result.ToLowerInvariant(), result );


      result = FileUtils.Combine( FileUtils.GetFolderName( result ),
                    FileUtils.GetFileNameWithoutExtension( result ) )
                    .TrimStart( '/', '\\' )
                    .ToLowerInvariant();
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

      result = result.Replace( "\"", "'" ); //парсер в замке хочет видеть строковые параметры через одинарные кавычки

      return Regex.Replace( result, "refineScale\\(([\\s\\d.-]*,[\\s\\d.-]*)\\)", "refineScale($1, mRefineRate)" );
    }

    #endregion

    #region Description
    private static Dictionary<string, string> globalSubstitutes = new Dictionary<string, string>();
    private static List<TextRef> rarityValues;
    private static Dictionary<Talent, TalentGroup> groupTalents = new Dictionary<Talent, TalentGroup>();
    private static string ProcessSubstitutes( string text, Talent talent )
    {
      string result = text;
      Regex substituteRegex = new Regex( @"\$\(([^\)]+)\)" );
      MatchCollection substituteMatches = substituteRegex.Matches( result );
      int i = 0;
      foreach ( Match match in substituteMatches )
      {
        string substitute = match.Groups[1].Value;
        string substituteText = string.Empty;

        if ( substitute.StartsWith( "TTRecommended" ) )
          substituteText = string.Format( "<recomended:{0}>", substitute );
        else if ( substitute == "commonDescription" )
        {
          substituteText = talent.commonDescription.ToString();
          i++;
        }
        else
        {
          string globSub;
          if ( globalSubstitutes.TryGetValue( substitute, out globSub ) )
          {
            substituteText = globSub;
            i++;
          }
        }
        result = result.Replace( match.Value, substituteText );

      }
      if ( i > 0 )
        result = ProcessSubstitutes( result, talent );
      return result;
    }
    private static string ProcessDescription( string text, Talent talent )
    {
      text = ProcessSubstitutes( text, talent );
      text = Regex.Replace( text, @"<castle>|</castle>|<session>.*?</session>", string.Empty,
                            RegexOptions.IgnoreCase | RegexOptions.Singleline );
      if ( rarityValues != null )
      {
        Regex rarityRegex = new Regex( "<value=talent.rarityName>" );
        MatchCollection rarityMatches = rarityRegex.Matches( text );
        foreach ( Match match in rarityMatches )
        {
          string style = rarityValues[(int)talent.rarity].ToString();
          text = text.Replace( match.Value, style );
        }
      }
      TalentGroup group;
      groupTalents.TryGetValue( talent, out group );

      Regex groupNameRegex = new Regex( "<value=talent.groupName>" );
      MatchCollection groupNameMatches = groupNameRegex.Matches( text );

      foreach ( Match match in groupNameMatches )
      {
        string groupName = group != null ? group.name.ToString() : string.Empty;
        text = text.Replace( match.Value, groupName );
      }

      Regex groupDescRegex = new Regex( "<value=talent.groupDescription>" );
      MatchCollection groupDescMatches = groupDescRegex.Matches( text );

      foreach ( Match match in groupDescMatches )
      {
        string groupDesc = group != null ? group.description.ToString() : string.Empty;
        text = text.Replace( match.Value, groupDesc );
      }
      text = text.Replace( "talent.isInGroup", group == null ? "false" : "true" );

      text = text.Replace( "talent.if.", "" );
      text = text.Replace( "talent.moneyCost", "sNafta" );
      text = text.Replace( "talent.devPoints", "sDevPoints" );
      text = text.Replace( "talent.manaCost", "mManaCost" );
      text = text.Replace( "talent.cooldown", "mCooldown" );
      text = text.Replace( "const.", "c" );
      text = text.Replace( "talent.", "" );
      return text;
    }
    #endregion

    private enum TextureFormat
    {
      DDS = 0,
      PNG
    }

    private enum VideoFormat
    {
      NONE = 0,
      OGV
    }
    private static List<Type> _forbiddenTypes = new List<Type>();
    private string SocialRootHRef = "/Social.ROOT";
    private static string copyDataFrom = string.Empty;
    private static string copyDataTo = string.Empty;
    private static TextureFormat texturesFormat = TextureFormat.DDS;
    private static VideoFormat videosFormat = VideoFormat.OGV;
    private const string TalentsCollectingRoot = "/Items/";
    private const string uiRootPath = "/UI/UIRoot.xdb";
    private const string uiDataPath = "/UI/Content/_.UIDT.xdb";
    private const string aiLogicPath = "/GameLogic/AILogic.AILP.xdb";

    private static List<Type> forbiddenSubTypes = new List<Type>() { 
              typeof(UnitConstant), 
              typeof(UnitConstantsContainer), 
              typeof(ConditionFormula), 
              typeof(BaseApplicator),               
              //typeof(Consumable), низя, ибо DBPtr<Consumable> petItem;
              //typeof(StatsContainer), 
              typeof(UIFontStyle), 
              typeof(UIBaseMaterial), 
              typeof(BaseUIMaterial),
              typeof(Actor),
              typeof(Dialog),
              typeof(UnitLogicParameters),
              typeof(UnitsLogicParameters),
              typeof(CreepSkin),
              typeof(UIRoot),
              typeof(HighlightItemAction),
              typeof(HighlightMapTypeAction),
              typeof(CastleDialog),
              typeof(HighlightAndOpenBuildingUpgradeAction),
              typeof(HighlightContructionAction),       
              typeof(DialogBase),
              typeof(HDRColor),
              typeof(Color),
              typeof(HighlightAction),
              typeof(OpenWindowAction),
              typeof(OpenPanelAction),
              typeof(SelectHeroAction),
			  typeof(ClientQuestAction),
              typeof(CompleteObjectiveAction),
              typeof(TextRef),
              typeof(DBPtr<Texture>), 
              typeof(DBPtr<TextureBase>),
              typeof(ExecutableFloatString),
              typeof(ExecutableIntString),
              typeof(ExecutableBoolString),
              typeof(EDamageType),
              typeof(DBPtr<ConditionFormula>)
          };
    private static List<Type> forbiddenTypes = new List<Type>() { 
              typeof(Ability),
              typeof(Unit), 
              typeof(Creature),       
              typeof(Tower)       
          };

    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
      bool cleanHeroes = false;
      bool isForServer = false;
      // string copyDataFrom = string.Empty;

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
        else if ( arg.StartsWith( "textures_format=", StringComparison.InvariantCultureIgnoreCase ) )
        {
          var formatString = arg.Substring( "textures_format=".Length );
          try
          {
            texturesFormat = (TextureFormat)Enum.Parse( typeof( TextureFormat ), formatString, true );
          }
          catch ( Exception e ) { Log.TraceWarning( "Invalid input 'textures_format' argument. {0}", e.Message ); }
        }
        else if (arg.StartsWith("videos_format=", StringComparison.InvariantCultureIgnoreCase))
        {
          var formatString = arg.Substring("videos_format=".Length);
          try
          {
            videosFormat = (VideoFormat)Enum.Parse(typeof(VideoFormat), formatString, true);
          }
          catch (Exception e) { Log.TraceWarning("Invalid input 'videos_format' argument. {0}", e.Message); }
        }
        else if ( string.Compare( arg, "test_data", true ) == 0 )
          SocialRootHRef = "/SocialTest.ROOT";
        else if ( string.Compare( arg, "clean_heroes", true ) == 0 )
          cleanHeroes = true;
        else if ( string.Compare( arg, "server", true ) == 0 )
          isForServer = true;
        else
          resultFilePath = arg;
      }

      //Called from editor UI
      if ( string.IsNullOrEmpty( resultFilePath ) )
      {
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        saveFileDialog.InitialDirectory = Convert.ToString( Environment.SpecialFolder.MyDocuments );
        saveFileDialog.Filter = "Xml (*.xml)|*.xml|All Files (*.*)|*.*";
        saveFileDialog.FilterIndex = 1;
        saveFileDialog.FileName = "ExportedSocialData";

        if ( saveFileDialog.ShowDialog() == DialogResult.OK )
          resultFilePath = saveFileDialog.FileName;
        else
          yield break;
      }

      SocialRoot root = DataBase.Get<SocialRoot>( DBID.FromFileName( SocialRootHRef, false ) );

      if ( cleanHeroes )
      {
        Log.TraceMessage( "Cleanup heroes..." );
        var heroes = root.Heroes.Get();
        for ( int i = 0; i < heroes.heroes.Count; ++i )
        {
          var hero = heroes.heroes[i].Get<Hero>();
          if ( hero == null || !hero.legal )
          {
            if ( hero != null ) Log.TraceMessage( "Remove illegal hero {0}", hero.DBId );
            heroes.heroes.RemoveAt( i );
            --i;
          }
          else
          {
            for ( int j = 0; j < hero.heroSkins.Count; ++j )
            {
              var skin = hero.heroSkins[j].Get<HeroSkin>();
              if ( skin == null || !skin.legal )
              {
                if ( skin != null ) Log.TraceMessage( "Remove illegal skin {0} for hero {1}", skin.DBId, hero.DBId );
                hero.heroSkins.RemoveAt( j );
                --j;
              }
            }
          }
        }
      }

      #region Talents cleanup
      Log.TraceMessage( "Talents cleanup..." );
      //Collecting all class talents for legal heroes
      var validClassTalent = new Dictionary<Talent, bool>();
      foreach ( var heroPtr in root.Heroes.Get().heroes )
      {
        var hero = heroPtr.Get();

        foreach (var _ts in hero.defaultTalentsSets)
        {
          TalentsSet ts = _ts.Get();
          if ( ts == null )
            continue;
          foreach ( var level in ts.levels )
          {
            foreach ( var talentDesc in level.talents )
            {
              var talent = talentDesc.talent.Get();
              if ( !talentDesc.talent.IsValid )
                continue;
              if ( talent.rarity == ETalentRarity.Class )
              {
                if ( validClassTalent.ContainsKey( talent ) )
                  Log.TraceWarning( "Class talent defined in more that once default talent set '{0}'", talent.DBId );
                else
                  validClassTalent.Add( talent, true );
              }
            }
          }  
        }
        
      }
      //Collecting all linked to ROOT talents
      var validTalents = new Dictionary<Talent, bool>();
      foreach ( var talentPtr in root.Talents )
      {
        if ( validTalents.ContainsKey( talentPtr.Get() ) )
          Log.TraceWarning( "Talent defined in more that once in root list '{0}'", talentPtr.DBId );
        else
          validTalents.Add( talentPtr.Get(), false );
      }

      //Collecting all created talents and adding them to ROOT after id and legal tests
      var talentsDbids = new List<DBID>();
      ObjectsSelector.CollectObjects( app, TalentsCollectingRoot, typeof( Talent ), true, true, out talentsDbids );
      foreach ( var talentDbid in talentsDbids )
      {
        var talentPtr = DataBase.Get<Talent>( talentDbid );
        Talent talent = talentPtr.Get();
        //IDCheck
        if ( string.IsNullOrEmpty( talent.persistentId ) )
        {
          Log.TraceWarning( "Talent with empty presistentId was skipped '{0}'", talentDbid );
          continue;
        }
        //UnusedHeroChech
        if ( talent.rarity == ETalentRarity.Class && !validClassTalent.ContainsKey( talent ) )
        {
          Log.TraceWarning( "Talent for unlegal hero was removed '{0}'", talentDbid );
          continue;
        }

        //If talent was linked to ROOT and passes 
        //UnusedHeroChech and IDCheck - marking in valid dict or linking to ROOT object
        if ( validTalents.ContainsKey( talent ) )
          validTalents[talent] = true;
        else
        {
          root.Talents.Add( talentPtr );
          Log.TraceMessage( "Talent was linked to ROOT '{0}'", talentDbid );
        }
      }

      for ( int index = 0; index < root.Talents.Count; ++index )
      {
        var valid = false;
        if ( validTalents.TryGetValue( root.Talents[index].Get(), out valid ) && !valid )
        {
          Log.TraceWarning( "Unused talent was removed '{0}'", root.Talents[index].DBId );
          root.Talents.RemoveAt( index );
          --index;
        }
      }
      Log.TraceMessage( "Talents cleanup completed. {0} talents linked to ROOT", root.Talents.Count );
      #endregion

      if ( cleanHeroes )
        root.UIRoot.Get().screens.Clear();

      DataBase.Store();

      if ( isForServer )
      {
        Log.TraceMessage( "Grades count..." );
        var grades = root.Map.Get().Grades;
        foreach ( var grade in grades )
        {
          var sections = grade.Sections.Get();
          if ( sections != null )
          {
            grade.sectionsCount = grade.Sections.Get().Sections.Count;
            grade.Sections.Get().Sections.Clear();
          }
        }
      }

      Log.TraceMessage( "Collect social resources from root \"{0}\"...", root.DBId );
      List<Type> typesWithSocialAttr = new List<Type>();
      List<Type> typesWithSocialFields = new List<Type>();

      var socialTypes = CollectSocialTypes( ref typesWithSocialAttr, ref typesWithSocialFields );
      List<DBResource> resources = CollectResources( root, socialTypes, typesWithSocialFields, isForServer );

      DataBase.UndoRedoManager.Start( "CondCode" );
      List<DBID> processedCond = new List<DBID>();
      if ( root != null )
      {

        if ( CompileQuestUtils.InitGramma() )
        {
          foreach ( var questLine in root.Quests )
          {
            foreach ( var quest in questLine.Get().quests )
            {
              foreach ( var obj in quest.Get().objectives )
              {
                // Condition
                var cond = obj.condition.Get();
                if ( cond is ModelDataCondition )
                {
                  if ( processedCond.Contains( cond.DBId ) )
                  {
                    Log.TraceMessage( "Condition {0} was already processed", cond.DBId );
                  }
                  else
                  {
                    Log.TraceMessage( "Processing condition {0}...", cond.DBId );
                    processedCond.Add( cond.DBId );
                    StringBuilder resultCSCode = new StringBuilder();
                    StringBuilder resultPYCode = new StringBuilder();
                    string id =
                        cond.DBId.Name.Replace( "-", "_" ).Replace( "/", "_" ).Replace( ".", "_" ).
                            Replace( ":", "_" );
                    if (
                        !CompileQuestUtils.FillConditionCode( resultCSCode, resultPYCode,
                                                              cond as ModelDataCondition, id ) )
                    {
                      Log.TraceError( "Parse failed for {0} condition", cond.DBId );
                    }
                    else
                    {
                      ( cond as ModelDataCondition ).code = resultPYCode.ToString();
                    }
                  }
                }

                // autoCompleteCondition
                cond = obj.autoCompleteCondition.Get();
                if ( cond is ModelDataCondition )
                {
                  if ( processedCond.Contains( cond.DBId ) )
                  {
                    Log.TraceMessage( "Condition {0} was already processed", cond.DBId );
                  }
                  else
                  {
                    Log.TraceMessage( "Processing condition {0}...", cond.DBId );
                    processedCond.Add( cond.DBId );
                    StringBuilder resultCSCode = new StringBuilder();
                    StringBuilder resultPYCode = new StringBuilder();
                    string id =
                        cond.DBId.Name.Replace( "-", "_" ).Replace( "/", "_" ).Replace( ".", "_" ).
                            Replace( ":", "_" );
                    if (
                        !CompileQuestUtils.FillConditionCode( resultCSCode, resultPYCode,
                                                              cond as ModelDataCondition, id ) )
                    {
                      Log.TraceError( "Parse failed for {0} condition", cond.DBId );
                    }
                    else
                    {
                      ( cond as ModelDataCondition ).code = resultPYCode.ToString();
                    }
                  }
                }
              }
            }
          }
        }


        UIRoot uiRoot = DataBase.Get<UIRoot>( DBID.FromFileName( uiRootPath, false ) );
        List<UITextSubstitute> uiSubstitutes = new List<UITextSubstitute>( uiRoot.substitutes );
        foreach ( UITextSubstitute uiSubstitute in uiSubstitutes )
        {
          globalSubstitutes.Add( uiSubstitute.id, uiSubstitute.captionText.ToString() );
        }
        DBUIData uiData = DataBase.Get<DBUIData>( DBID.FromFileName( uiDataPath, false ) );
        rarityValues = new List<TextRef>( uiData.rarityValue );
        TalentGroupList talentGroupList = DataBase.Get<AILogicParameters>( DBID.FromFileName( aiLogicPath, false ) ).Get().talentGroups;
        foreach ( var talentGroup in talentGroupList.groups )
        {
          foreach ( var talentPtr in talentGroup.talents )
          {
            Talent talent = talentPtr.Get();
            if ( talent != null )
            {
              if ( groupTalents.ContainsKey( talent ) )
              {
                Log.TraceError( "Talent {0} already added to talent group. Will be used first founded group.", talent.name );
                continue;
              }
              groupTalents.Add( talent, talentGroup );
            }
          }
        }
        foreach ( var talentPtr in root.Talents )
        {
          var talent = talentPtr.Get();
          var desc = ProcessDescription( talent.description.ToString(), talent );
          talent.description.FromString( desc );
        }
      }

      var valueResolver = new Dictionary<Type, DBXmlSerializer.TypeReplacementFunc>();

      if ( isForServer )
      {
          //Console.WriteLine("ADDING VALUE RESOLVERS isForServer");
        foreach ( Type type in forbiddenSubTypes )
        {
          if ( !valueResolver.ContainsKey( type ) )
            valueResolver.Add( type, null );
        }
      }
      else
      {
          //Console.WriteLine("ADDING VALUE RESOLVERS");
        valueResolver.Add( typeof( TextRef ), ReplaceTextRef );
        valueResolver.Add( typeof( DBPtr<Texture> ), ReplaceTexturePtr );
        valueResolver.Add( typeof( DBPtr<TextureBase> ), ReplaceTexturePtr );
        valueResolver.Add( typeof( ExecutableFloatString ), ReplaceExecutableString );
        valueResolver.Add( typeof( ExecutableIntString ), ReplaceExecutableString );
        valueResolver.Add( typeof( ExecutableBoolString ), ReplaceExecutableString );
      }

      StoreResources( resources, socialTypes, typesWithSocialFields, valueResolver, resultFilePath );
      Log.TraceMessage( "Data was succesfully saved to '{0}'", resultFilePath );
      DataBase.UndoRedoManager.Cancel();

      if ( !string.IsNullOrEmpty( copyDataFrom ) && !string.IsNullOrEmpty( copyDataTo ) )
      {
        Log.TraceMessage( "Copy {0} textures to social's folder...", textures.Count );
        copyDataFrom = copyDataFrom.ToLowerInvariant();
        Log.TraceMessage( "Collecting textures from '{0}'...", copyDataTo );
        var filesDds = Directory.GetFiles( copyDataTo, "*.dds", SearchOption.AllDirectories );
        Log.TraceMessage( "{0} DDS textures collected", filesDds.Length );
        var filesPng = Directory.GetFiles( copyDataTo, "*.png", SearchOption.AllDirectories );
        Log.TraceMessage( "{0} PNG textures collected", filesPng.Length );
        var files = new List<string>( filesPng.Length + filesDds.Length);
        files.AddRange( filesDds );
        files.AddRange( filesPng );

        var filteredTextures = new List<string>( textures.Count );
        foreach ( var texture in textures )
          filteredTextures.Add( Path.ChangeExtension(
          texture.Key,
          texturesFormat.ToString().ToLowerInvariant() ) );

        foreach ( var file in files )
        {
          string cutFileName = 
      FileUtils.FixFileName( copyDataFrom + FileUtils.Combine( FileUtils.PathSeparatorString,
                                     file.Substring( copyDataTo.Length ) ) ).ToLowerInvariant();

          //Deleteing files, which are found in target directory but not presented in copying list
          //Changing extension, because files usualy presented in dds format, but will be copied as png
          //cutFileName = Path.ChangeExtension(cutFileName,texturesFormat.ToString().ToLowerInvariant());     
          if ( !filteredTextures.Contains( cutFileName ) )
          {
            File.Delete( file );
            Log.TraceMessage( "File '{0}' was deleted as unused", file );
            if ( File.Exists( file + ".meta" ) )
            {
              File.Delete( file + ".meta" );
              Log.TraceMessage( "Meta file '{0}' was deleted as unused", file );
            }
          }
        }
		foreach ( var texture in textures )
        {
          string textureFileName = Path.Combine( copyDataTo,
            texture.Value.Substring( copyDataFrom.Length ).TrimStart( '/', '\\' ) );
          string textureFilePath = Path.GetDirectoryName( textureFileName );
          if ( !Directory.Exists( textureFilePath ) )
            Directory.CreateDirectory( textureFilePath );
          string savePath = string.Empty;
          if ( !File.Exists( "../Data/" + texture.Value ) )
          {
            Log.TraceWarning( "File '{0}' not exist but trying to copy it.", texture.Value );
            continue;
          }
          if ( texturesFormat == TextureFormat.PNG )
          {
            savePath = Path.ChangeExtension( textureFileName, texturesFormat.ToString().ToLowerInvariant() );
            System.Drawing.Bitmap bitmap = DdsImage.Load( app.FileSystem.OpenFile( texture.Value ) );
            bitmap.Save( savePath, System.Drawing.Imaging.ImageFormat.Png );
          }
          else if ( texturesFormat == TextureFormat.DDS )
          {
            savePath = textureFileName;
            File.WriteAllBytes( savePath, FileUtils.ReadFile( app.FileSystem, texture.Value ) );
          }

          Log.TraceMessage( "Texture '{0}' exported", savePath );
        }
        //Log.TraceMessage("VIDEOPROCESSING: copyDataFrom : " + copyDataFrom + "; curdir = " + Environment.CurrentDirectory);
        //Log.TraceMessage("VIDEOPROCESSING: copyDataTo : " + copyDataTo);
        string srcDir = Environment.CurrentDirectory + "\\..\\Data" + copyDataFrom;
        //Log.TraceMessage("VIDEOPROCESSING: srcDir : " + srcDir);
        var filesOgv = Directory.GetFiles(srcDir, "*.ogv", SearchOption.AllDirectories);
        Log.TraceMessage("Collecting videos from '{0}'...", srcDir);
        Log.TraceMessage("{0} OGV videos collected", filesOgv.Length);
        files = new List<string>(filesOgv.Length);
        files.AddRange(filesOgv);
        foreach (var ogv in files)
        {
            string dest = copyDataTo + ogv.Substring(ogv.IndexOf(copyDataFrom) + copyDataFrom.Length - 1);
            File.Copy(ogv, dest, true);
            Log.TraceMessage("VIDEOPROCESSING: copy from " + ogv + " to " + dest);
        }
      }
      yield return true;
    }
	}
}