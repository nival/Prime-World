#define TALENTS_CONTAINER
/*
#about Collect information about game's entities to single xml file
#ref Types.DBTypes.dll
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref EditorPlugins.dll
#ref PF_EditorC.exe
*/

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
using PF_EditorC;
using DBTypes;

namespace Scripts
{
  public class ScriptCommand
  {
    #region public static class TalentsContainer
    public static class TalentsContainer
    {
      private static Dictionary<string, DBTypes.Talent> _talents = new Dictionary<string, DBTypes.Talent>();
      private static Dictionary<DBTypes.Talent, DBTypes.Hero> _classTalents = new Dictionary<DBTypes.Talent, DBTypes.Hero>();

      public static void Initialize( IEditorCommonApplication app, DBTypes.HeroesDB heroes, string talentsPath )
      {
        foreach ( var heroPtr in heroes.heroes )
        {
          var hero = heroPtr.Get();
          if ( !hero.legal )
            continue;

		  foreach ( var _ts in hero.defaultTalentsSets )
		  {
			  var ts = _ts.Get();
			  if ( ts == null )
				continue;
		
			  foreach ( var level in ts.levels )
			  {
				foreach ( var talentPtr in level.talents )
				{
				  var talent = talentPtr.talent.Get();
				  if ( talent != null && talent.rarity == DBTypes.ETalentRarity.Class && !_classTalents.ContainsKey( talent ) )
					_classTalents.Add( talent, hero );
				}
			  }
		  }
        }

        List<DBID> talentsDbids;
        ObjectsSelector.CollectObjects( app, talentsPath, typeof( DBTypes.Talent ), true, false, out talentsDbids );

        foreach ( var talentDbid in talentsDbids )
        {
          var talent = DataBase.Get<DBTypes.Talent>( talentDbid ).Get();
          if ( string.IsNullOrEmpty( talent.persistentId ) )
            continue;
          if ( talent.rarity == DBTypes.ETalentRarity.Class && !_classTalents.ContainsKey( talent ) )
            continue;

          if ( !string.IsNullOrEmpty( talent.persistentId ) )
            _talents.Add( talent.persistentId, talent );
        }
      }

      public static DBTypes.Talent GetTalent( string id )
      {
        DBTypes.Talent result;
        if ( _talents.TryGetValue( id, out result ) )
          return result;

        return null;
      }

      public static DBTypes.Hero GetHero( DBTypes.Talent talent )
      {
        DBTypes.Hero result;
        if ( _classTalents.TryGetValue( talent, out result ) )
          return result;

        return null;
      }

      public static IEnumerable<DBTypes.Talent> Talents { get { return _talents.Values; } }
    }

    #endregion

    #region public static class FormulaCalculator

    public class FormulaCalculator
    {
      private const int REFINE_RATE = 1;
      private const int MAX_REFINE_RATE = 5;
      private static int _refineRate = REFINE_RATE;

      private Dictionary<string, StringProcessor.Expression> _global = new Dictionary<string, StringProcessor.Expression>();
      private Dictionary<string, KeyValuePair<float, float>> _constants = new Dictionary<string, KeyValuePair<float, float>>();
      private Dictionary<string, StringProcessor.Expression> _globalConditions = new Dictionary<string, StringProcessor.Expression>();
      private DBTypes.AbilityAndDamageScalingParams _scales;

      private Dictionary<string, StringProcessor.Expression> _values;
      private Dictionary<string, StringProcessor.Expression> _conditions;
      private DBTypes.AILogicParameters _aiLogicParams;
      private DBTypes.Ability _ability;
      private DBTypes.TalentGroup _group;
      private List<int> _naftaCostsByLvl = new List<int>();

      private Dictionary<DBTypes.Talent, TalentKit> _talentsToKits;
      private Dictionary<DBTypes.Talent, TalentPack> _talentsToPacks;

      public AILogicParameters AILogic
      {
        get { return _aiLogicParams; }
      }
      public List<int> NaftaCostByLevel
      {
        get { return _naftaCostsByLvl; }
      }

      private bool _maximize = false;
      private DBTypes.EFaction _faction = DBTypes.EFaction.Neutral;

      public FormulaCalculator( DBTypes.AILogicParameters aiLogic, DBTypes.UnitLogicParameters unitLogic )
      {
        _aiLogicParams = aiLogic;
        _scales = _aiLogicParams.abilityAndDamageScalingParams;
        foreach ( var cost in _aiLogicParams.talentNaftaCostByLevel )
        {
          _naftaCostsByLvl.Add( cost );
        }

        foreach ( DBTypes.UnitConstant globConst in _aiLogicParams.globalConstants.Get().vars )
          _global.Add( globConst.name, new StringProcessor.Expression( globConst.var.sString, Get ) );

        foreach ( DBTypes.UnitStat heroStat in unitLogic.defaultStats.Get().stats )
          _global.Add( heroStat.statId.ToString(), new StringProcessor.Expression( heroStat.value.sString, Get ) );

        _constants.Add( "NaftaLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "sNaftaLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "rNaftaLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "RefineRate", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "isBought", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "ABILITYTYPE_SIMPLE", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "ABILITYTYPE__INVALID", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "ABILITYTYPE__ACTIVE", new KeyValuePair<float, float>( 1.0f, 1.0f ) );
        _constants.Add( "ABILITYTYPE__MULTIACTIVE", new KeyValuePair<float, float>( 2.0f, 2.0f ) );
        _constants.Add( "ABILITYTYPE__PASSIVE", new KeyValuePair<float, float>( 3.0f, 3.0f ) );
        _constants.Add( "ABILITYTYPE__AUTOCASTABLE", new KeyValuePair<float, float>( 4.0f, 4.0f ) );
        _constants.Add( "ABILITYTYPE__SWITCHABLE", new KeyValuePair<float, float>( 5.0f, 5.0f ) );
        _constants.Add( "ABILITYTYPE__CHANNELLING", new KeyValuePair<float, float>( 6.0f, 6.0f ) );
        _constants.Add( "HeroLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "sHeroLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "rHeroLevel", new KeyValuePair<float, float>( 1.0f, 36.0f ) );
        _constants.Add( "sTerrainType", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "pMisc", new KeyValuePair<float, float>( 0.0f, 0.0f ) );
        _constants.Add( "GLOBAL", new KeyValuePair<float, float>( 0.0f, 6.0f ) );

        foreach ( var condition in _aiLogicParams.conditionFormulas )
          _globalConditions.Add( condition.Get().name, new StringProcessor.Expression( condition.Get().condition.sString, GetCondition ) );

        InitalizeFunctions();
      }
/*
#insert FillCompiledTooltips.cs
*/
      #region Helper functions
      private bool TryGetBoolean( string name, DBTypes.EFaction faction, out bool result )
      {
        switch ( name )
        {
        case "true":
          result = true;
          break;
        case "false":
          result = false;
          break;
        case "fctnA":
        case "FCTN_A":
          result = ( faction == DBTypes.EFaction.Freeze );
          break;
        case "fctnB":
        case "FCTN_B":
          result = ( faction == DBTypes.EFaction.Burn );
          break;
        default:
          result = false;
          return false;
        }

        return true;
      }

      private bool TryGetFloat( string name, DBTypes.EFaction faction, out float result )
      {
        bool boolResult;
        if ( TryGetBoolean( name, faction, out boolResult ) )
        {
          result = boolResult ? 1.0f : 0.0f;
          return true;
        }

        if ( float.TryParse( name, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out result ) )
          return true;

        if ( name == "sFctn" || name == "sOriginalFctn" )
        {
          switch ( faction )
          {
          case DBTypes.EFaction.Neutral:
            result = 0.0f;
            break;
          case DBTypes.EFaction.Freeze:
            result = 1.0f;
            break;
          case DBTypes.EFaction.Burn:
            result = 2.0f;
            break;
          }

          return true;
        }

        result = 0.0f;
        return false;
      }

      private bool TryGetStat( string name, bool maximize, Dictionary<string, StringProcessor.Expression> expressions, out float result )
      {
        result = 0.0f;

        if ( string.IsNullOrEmpty( name ) || name[0] != 's' )
          return false;

        int startIndex = 1;
        if ( name.StartsWith( "sMax" ) )
          startIndex = 4;
        else if ( name.StartsWith( "sBase" ) )
          startIndex = 5;

        string statName = name.Substring( startIndex );
        if ( !TryCalculateExpression( statName, expressions, out result ) )
          return false;

        if ( !maximize )
          return true;

        float modifier;
        if ( !TryCalculateExpression( "StatModifier", expressions, out modifier ) )
          return true;

        float multiplier = 1.0f;
        if ( statName != "Life" && statName != "Energy" || !TryCalculateExpression( "LifeEnergyMultiplier", expressions, out multiplier ) )
          multiplier = 1.0f;
        result += modifier * multiplier;

        return true;
      }

      private bool TryCalculateExpression( string name, Dictionary<string, StringProcessor.Expression> expressions, out float result )
      {
        if ( expressions == null )
        {
          result = 0.0f;
          return false;
        }

        StringProcessor.Expression expression;
        if ( !expressions.TryGetValue( name, out expression ) )
        {
          result = 0.0f;
          return false;
        }

        result = expression.Calculate();
        return true;
      }

      private float Get( string name )
      {
        float result = 0.0f;
        if ( name.StartsWith( "sender." ) || name.StartsWith( "receiver." ) )
          return result;

        if ( name.StartsWith( "talent.const." ) || name.StartsWith( "const." ) )
          name = name.Substring( name.IndexOf( "const." ) + "const.".Length );
        else if ( name.StartsWith( "talent.if." ) || ( name.StartsWith( "if." ) ) )
        {
          name = name.Substring( name.IndexOf( "if." ) + "if.".Length );
        }
        else if ( name.StartsWith( "talent." ) )
          name = name.Substring( name.IndexOf( "talent." ) + "talent.".Length );


        if ( TryGetFloat( name, _faction, out result ) )
          return result;

        KeyValuePair<float, float> constant;
        if ( _constants.TryGetValue( name, out constant ) )
          return _maximize ? constant.Value : constant.Key;

        if ( TryGetStat( name, _maximize, _global, out result ) )
          return result;

        if ( TryCalculateExpression( name, _values, out result ) )
          return result;

        if ( TryCalculateExpression( name, _global, out result ) )
          return result;

        if ( _ability == null )
          Log.TraceWarning( "Cannot resolve variable \"{0}\"", name );
        else
          Log.TraceWarning( "Cannot resolve variable \"{0}\" from talent \"{1}\"", name, _ability.DBId );

        return 0.0f;
      }

      public float GetCondition( string name )
      {
        if ( name.StartsWith( "talent.if." ) || ( name.StartsWith( "if." ) ) )
        {
          name = name.Substring( name.IndexOf( "if." ) + "if.".Length );
        }
        bool boolResult;
        if ( TryGetBoolean( name, _faction, out boolResult ) )
          return boolResult ? 1.0f : 0.0f;

        float result;
        if ( TryCalculateExpression( name, _conditions, out result ) )
          return result;

        if ( TryCalculateExpression( name, _globalConditions, out result ) )
          return result;

        return Get( name );
      }

      public string EvaluateMinMax( string expression, int precision )
      {
        _maximize = false;
        float min = (float)Math.Round( Evaluate( expression ), precision );
        _maximize = true;
        float max = (float)Math.Round( Evaluate( expression ), precision );

        if ( min == max )
          return min.ToString();

        if ( min > max )
        {
          float temp = max;
          max = min;
          min = temp;
        }

        return string.Format( "{0}..{1}", min.ToString(), max.ToString() );
      }

      public float Evaluate( string expression )
      {
        try
        {
          return new StringProcessor.Expression( expression, Get ).Calculate();
        }
        catch ( StringProcessor.EvaluationException e )
        {
          if ( _ability == null )
            Log.TraceWarning( "Cannot resolve expression. {0}", e.Message );
          else
            Log.TraceWarning( "Cannot resolve expression from talent '{0}'. {1}", _ability.DBId, e.Message );

          return 0.0f;
        }
      }

      public void AssignFaction( DBTypes.EFaction faction )
      {
        _faction = faction;
      }

      public void AssignGroup( DBTypes.TalentGroup group )
      {
        _group = group;
      }

      public DBTypes.Ability AssignAbility( DBTypes.Ability ability )
      {
        var result = _ability;
        _ability = ability;
        DBTypes.Talent talent = null;
        if ( _ability is DBTypes.Talent )
          talent = _ability as DBTypes.Talent;

        if ( ability == null )
        {
          _values = null;
          _conditions = null;
          return result;
        }

        _values = new Dictionary<string, StringProcessor.Expression>();
        if ( ability.constants.IsValid )
        {
          foreach ( var constantPtr in ability.constants.Get().vars )
          {
            if ( !constantPtr.IsValid )
              continue;

            string constant = constantPtr.Get().name;
            if ( _values.ContainsKey( constant ) )
              Log.TraceWarning( "Constant \"{0}\" already defined twice talent \"{1}\"", constant, ability.DBId );
            else
              _values.Add( constant, new StringProcessor.Expression( constantPtr.Get().var.sString, Get ) );
          }
        }

        _values.Add( "Cooldown", new StringProcessor.Expression( ability.cooldownTime.sString, Get ) );
        _values.Add( "ManaCost", new StringProcessor.Expression( ability.manaCost.sString, Get ) );
        _values.Add( "AbilityType", new StringProcessor.Expression( ( (int)ability.type ).ToString(), Get ) );

        _values.Add( "manaCost", new StringProcessor.Expression( ability.manaCost.sString, Get ) );
        _values.Add( "cooldown", new StringProcessor.Expression( ability.cooldownTime.sString, Get ) );

        if ( talent != null )
        {
          TalentKit kit = GetTalentKit( talent );
          TalentPack pack = GetTalentPack( talent );
          int talNaftaCost = talent.naftaCost;
          if ( talNaftaCost < 0 )
            talNaftaCost = _naftaCostsByLvl[talent.minLevel];
          _values.Add( "NaftaCost", new StringProcessor.Expression( talNaftaCost.ToString(), Get ) );
          _values.Add( "DevPoints", new StringProcessor.Expression( talent.devPoints.ToString(), Get ) );
          _values.Add( "TalentLevel", new StringProcessor.Expression( talent.minLevel.ToString(), Get ) );
          _values.Add( "TalentDevPoints", new StringProcessor.Expression( talent.devPoints.ToString(), Get ) );
          _values.Add( "moneyCost", new StringProcessor.Expression( talNaftaCost.ToString(), Get ) );
          _values.Add( "devPoints", new StringProcessor.Expression( talent.devPoints.ToString(), Get ) );

          _values.Add( "ConsumptionBonusConst", new StringProcessor.Expression( talent.consumptionBonus.constant.ToString(), Get ) );
          _values.Add( "ConsumptionBonusPercent", new StringProcessor.Expression( talent.consumptionBonus.percent.ToString(), Get ) );
          _values.Add( "mConsumptionBonusConst", new StringProcessor.Expression( talent.consumptionBonus.constant.ToString(), Get ) );
          _values.Add( "mConsumptionBonusPercent", new StringProcessor.Expression( talent.consumptionBonus.percent.ToString(), Get ) );

          _values.Add( "isClass", new StringProcessor.Expression( talent.rarity == ETalentRarity.Class ? "1" : "0", Get ) );
          _values.Add( "isOrdinary", new StringProcessor.Expression( talent.rarity == ETalentRarity.ordinary ? "1" : "0", Get ) );
          _values.Add( "isGood", new StringProcessor.Expression( talent.rarity == ETalentRarity.good ? "1" : "0", Get ) );
          _values.Add( "isExcellent", new StringProcessor.Expression( talent.rarity == ETalentRarity.excellent ? "1" : "0", Get ) );
          _values.Add( "isMagnificent", new StringProcessor.Expression( talent.rarity == ETalentRarity.magnificent ? "1" : "0", Get ) );
          _values.Add( "isExclusive", new StringProcessor.Expression( talent.rarity == ETalentRarity.exclusive ? "1" : "0", Get ) );

          _values.Add( "force", new StringProcessor.Expression( GetTalentForce( talent, _aiLogicParams.forceParameters, _aiLogicParams.talentBaseStatBudget ).ToString(), Get ) );
          _values.Add( "isInKit", new StringProcessor.Expression( kit != null ? "1" : "0", Get ) );
          _values.Add( "isSpecialInKit", new StringProcessor.Expression( kit != null && kit.special.Get() == talent ? "1" : "0", Get ) );
          _values.Add( "totalInKit", new StringProcessor.Expression( kit != null ? kit.talents.Count.ToString() : "0", Get ) );
          _values.Add( "activatedInKit", new StringProcessor.Expression( "0", Get ) );
          _values.Add( "isInPack", new StringProcessor.Expression( pack != null ? "1" : "0", Get ) );

          _values.Add( "kitName", new StringProcessor.Expression( kit != null ? kit.name.GetText() : string.Empty, Get ) );
          _values.Add( "packIcon", new StringProcessor.Expression( pack != null ? pack.iconStyle : string.Empty, Get ) );

          _values.Add( "isInGroup", new StringProcessor.Expression( _group != null ? "1" : "0", Get ) );

          _values.Add( "spendsLife", new StringProcessor.Expression( ( talent.flags & EAbilityFlags.SpendLifeInsteadEnergy ) != 0 ? "1" : "0", Get ) );

          //sBaseAttack hack
          DBTypes.Hero hero = TalentsContainer.GetHero( talent );
          if ( hero != null )
          {
            foreach ( var stat in hero.stats.Get().stats )
            {
              if ( stat.statId == DBTypes.EStat.BaseAttack )
              {
                _values.Add( "sBaseAttack", new StringProcessor.Expression( stat.value.sString, Get ) );
                break;
              }
            }
          }
        }
        else if ( ability is DBTypes.Consumable )
        {
          var consumable = ability as DBTypes.Consumable;
          _values.Add( "NaftaCost", new StringProcessor.Expression( consumable.naftaCost.ToString(), Get ) );
          _values.Add( "moneyCost", new StringProcessor.Expression( consumable.naftaCost.ToString(), Get ) );
        }

        _conditions = new Dictionary<string, StringProcessor.Expression>();
        foreach ( var conditionPtr in ability.conditionFormulas )
        {
          if ( !conditionPtr.IsValid )
            continue;


          string condition = conditionPtr.Get().name;
          if ( _conditions.ContainsKey( condition ) )
            Log.TraceWarning( "Condition \"{0}\" already defined twice talent \"{1}\"", condition, ability.DBId );
          else
            _conditions.Add( condition, new StringProcessor.Expression( conditionPtr.Get().condition.sString, GetCondition ) );
        }

        return result;
      }
      #endregion
    }

    #endregion

    #region public static class TextProcessor

    public static class TextProcessor
    {
      private static Dictionary<string, string> _global = new Dictionary<string, string>();
      private static FormulaCalculator _formulaCalculator;

      public static void Initiliaze( DBTypes.UIRoot uiRoot, FormulaCalculator formulaCalculator )
      {
        _formulaCalculator = formulaCalculator;
        foreach ( var substitute in uiRoot.substitutes )
          _global.Add( substitute.id, substitute.captionText.ToString() );
      }

      public static string ProcessSubstitutes( string text, string commonDescription, bool useGlobal )
      {
        var result = text;
        var substitutes = Regex.Matches( result, @"\$\(([^\)]+)\)" );

        bool substituteFound = false;
        foreach ( Match substituteMatch in substitutes )
        {
          string substitute = substituteMatch.Groups[1].Value;
          string substituteText = string.Empty;

          if ( substitute.StartsWith( "TTRecommended" ) )
            substituteText = string.Format( "<castle:{0}>", substitute );
          else if ( substitute == "commonDescription" )
            substituteText = commonDescription;
          else if ( useGlobal )
          {
            if ( !_global.TryGetValue( substitute, out substituteText ) )
              substituteText = string.Empty;
          }

          result = result.Replace( substituteMatch.Value, substituteText );
          if ( !string.IsNullOrEmpty( substituteText ) )
            substituteFound = true;
        }

        if ( substituteFound )
          result = ProcessSubstitutes( result, commonDescription, useGlobal );
        return result;
      }

      private static int FindNearest( string text, int startIndex, out int patternIndex, params string[] patterns )
      {
        patternIndex = -1;
        int result = -1;
        for ( int i = 0; i < patterns.Length; ++i )
        {
          int index = text.IndexOf( patterns[i], startIndex );
          if ( index >= 0 && ( result == -1 || index < result ) )
          {
            result = index;
            patternIndex = i;
          }
        }

        return result;
      }

      public static string ProcessConditions( string text )
      {
        int startPos = -1;
        int elsePos = -1;
        int count = -1;
        int index = 0;
        while ( index >= 0 && index < text.Length )
        {
          int pattern;
          int pos = FindNearest( text, index, out pattern, "<if=", "<else>", "</if>" );
          if ( pos >= 0 )
          {
            switch ( pattern )
            {
            case 0:
              ++count;
              if ( count == 0 )
                startPos = pos;
              pos += 1;
              break;
            case 1:
              if ( count == 0 )
                elsePos = pos;
              pos += 1;
              break;
            case 2:
              if ( count == 0 )
              {
                if ( elsePos == -1 )
                  elsePos = pos;

                int startEndPos = text.IndexOf( ">", startPos + 5 );
                string conditionText = text.Substring( startPos + 4, startEndPos - startPos - 4 ).Trim();
                bool condition = false;
                if ( conditionText.StartsWith( "talent.if." ) )
                  condition = _formulaCalculator.GetCondition( conditionText.Substring( conditionText.IndexOf( "if." ) + "if.".Length ) ) != 0.0f;
                else
                  condition = _formulaCalculator.GetCondition( conditionText ) != 0.0f;

                string value = string.Empty;
                if ( condition )
                  value = text.Substring( startEndPos + 1, elsePos - startEndPos - 1 );
                else if ( elsePos != pos )
                  value = text.Substring( elsePos + 6, pos - elsePos - 6 );

                if ( !string.IsNullOrEmpty( value ) )
                  value = ProcessConditions( value );

                text = text.Substring( 0, startPos ) + value + text.Substring( pos + 5 );
                pos = startPos - 1;
                startPos = -1;
                elsePos = -1;
              }
              pos += 1;
              --count;
              break;
            }
          }

          index = pos;
        }

        if ( count >= 0 )
          throw new ArgumentException( "Found unclosed if tags" );

        return text;
      }

      private static string ProcessValue( string value, int precision, string rarityName, string talentName, string groupName, string groupDescription )
      {
        switch ( value )
        {
        case "talent.rarityName":
          return rarityName;
        case "talent.abilityName":
        case "abilityName":
          return talentName;
        case "talent.groupName":
          return groupName;
        case "talent.groupDescription":
          return groupDescription;
        }

        return _formulaCalculator.EvaluateMinMax( value, precision );
      }

      public static string ProcessValues( string text, string rarityName, string talentName, string groupName, string groupDescription )
      {
        int index = 0;
        while ( index < text.Length )
        {
          index = text.IndexOf( "<value=", index );
          if ( index < 0 )
            break;

          int endPos = text.IndexOf( '>', index );
          int cutPos = endPos;
          int formatPos = text.IndexOf( " format=", index );
          int precision = 0;
          if ( formatPos >= 0 && formatPos < endPos )
          {
            int formatDotPos = text.IndexOf( '.', formatPos );
            if ( formatDotPos >= 0 && formatDotPos < endPos )
              int.TryParse( text.Substring( formatDotPos + 1, endPos - formatDotPos - 1 ).Trim(), out precision );

            endPos = formatPos;
          }

          string expression = text.Substring( index + "<value=".Length, endPos - index - "<value=".Length ).Trim();
          text = text.Substring( 0, index ) + ProcessValue( expression, precision, rarityName, talentName, groupName, groupDescription ) + text.Substring( cutPos + 1 );
          index += 1;
        }

        return text;
      }

      public static string ProcessImages( string text, ImagesCollector images )
      {
        int index = 0;
        while ( index < text.Length )
        {
          index = text.IndexOf( "<image:", index );
          if ( index < 0 )
            break;
          int pattern;
          int endPos = FindNearest( text, index, out pattern, " ", ">" );
          if ( endPos > index )
          {
            string styleName = text.Substring( index + "<image:".Length, endPos - index - "<image:".Length ).Trim();
            string imageName = images.AddStyle( styleName );
            text = text.Substring( 0, index + "<image:".Length ) + imageName + text.Substring( endPos );
          }
          index += "<image:".Length;
        }

        return text;
      }

      public static string Parse( string text, string commonDescription, bool useGlobal, string rarityName, string talentName, ImagesCollector images )
      {
        return Parse( text, commonDescription, useGlobal, rarityName, talentName, string.Empty, string.Empty,
                      images );
      }

      public static string Parse( string text, string commonDescription, bool useGlobal, string rarityName, string talentName, string groupName, string groupDescription, ImagesCollector images )
      {
        return ProcessImages( ProcessValues( ProcessConditions( ProcessSubstitutes( text, commonDescription, useGlobal ) ), rarityName, talentName, groupName, groupDescription ), images );
      }

      public static string CleanUp( string text )
      {
        StringBuilder result = new StringBuilder( text.Length );
        int startIndex = 0;
        bool whiteSpace = true;
        for ( int i = 0; i < text.Length; ++i )
        {
          char c = text[i];
          if ( c == '\t' || c == '\r' || c == '\n' || c == ' ' )
          {
            if ( !whiteSpace )
            {
              result.Append( text.Substring( startIndex, i - startIndex ) );
              result.Append( ' ' );
              whiteSpace = true;
            }
          }
          else if ( whiteSpace )
          {
            startIndex = i;
            whiteSpace = false;
          }
        }
        if ( !whiteSpace )
          result.Append( text.Substring( startIndex ) );

        return result.ToString().Trim();
      }
    }

    #endregion

    #region public class ImagesCollector

    public class ImagesCollector
    {
      private readonly Dictionary<string, string> _images = new Dictionary<string, string>();
      private readonly Dictionary<string, object> _usedNames = new Dictionary<string, object>();
      private readonly Dictionary<string, DBTypes.Texture> _styles = new Dictionary<string, DBTypes.Texture>();

      private void MarkAsUsed( string fileName )
      {
        _usedNames.Add( fileName.ToLower(), null );
      }

      private bool IsUsed( string fileName )
      {
        return _usedNames.ContainsKey( fileName.ToLower() );
      }

      public string AddImage( DBTypes.Texture texture, string suffix )
      {
        if ( texture == null )
          return string.Empty;
        string imagePath = texture.textureFileName;
        return AddImage( imagePath, suffix );
      }

      public string AddImage( string imagePath, string suffix )
      {
        if ( String.IsNullOrEmpty( imagePath ) )
          return String.Empty;

        string fileName = Path.GetFileNameWithoutExtension( imagePath );
        if ( !string.IsNullOrEmpty( suffix ) )
          fileName += "_" + suffix;
        string extension = Path.GetExtension( imagePath );
        string lowerCase = FileUtils.FixFileName( imagePath ).ToLower();
        string result;
        if ( _images.TryGetValue( lowerCase, out result ) )
          return result + ".png";

        result = fileName;
        if ( !IsUsed( result ) )
        {
          _images.Add( lowerCase, result );
          MarkAsUsed( result );
          return result + ".png";
        }

        int i = 0;
        do
        {
          ++i;
          result = fileName + "_" + i.ToString();
        } while ( IsUsed( result ) );

        _images.Add( lowerCase, result );
        MarkAsUsed( result );
        return result + ".png";
      }

      public void LoadStyles( IEnumerable<DBTypes.UIStyleAlias> styles )
      {
        foreach ( var style in styles )
        {
          var material = style.material.Get<DBTypes.UIBaseMaterial>();
          if ( material == null )
            continue;
          var texture = material.DiffuseMap.texture.Get<DBTypes.Texture>();
          if ( texture == null )
            continue;
          _styles.Add( style.name, texture );
        }
      }

      public string AddStyle( string styleName )
      {
        DBTypes.Texture texture;
        if ( !_styles.TryGetValue( styleName, out texture ) )
          return string.Empty;

        return AddImage( texture, string.Empty );
      }

      public void StoreImages( IEditorCommonApplication app, string folder, List<string> sourceFolders )
      {
        if ( !Directory.Exists( folder ) )
          Directory.CreateDirectory( folder );
        foreach ( var image in _images )
        {
          string fileName = app.FileSystem.GetRealFileName( image.Key );
          try
          {
            string sourcePath = image.Key;
            bool fileFound = app.FileSystem.FileExists( sourcePath );
            Log.TraceMessage( string.Format( "Store file '{0}'...", sourcePath ) );

            //File.Copy( fileName, Path.Combine(folder[1], image.Value) + ".png", true );)
            if ( !fileFound )
            {
              foreach ( var f in sourceFolders )
              {
                sourcePath = Path.Combine( f, image.Key );
                Log.TraceMessage( string.Format( "Look in {0}...", sourcePath ) );
                fileFound = app.FileSystem.FileExists( sourcePath );
                if ( fileFound )
                  break;
              }
            }
            if ( fileFound )
            {
              var destPath = Path.Combine( folder, image.Value ) + ".png";
              if ( Path.GetExtension( sourcePath ) == ".png" )
                File.Copy( sourcePath, destPath, true );
              else
              {
                System.Drawing.Bitmap bitmap = DdsImage.Load( app.FileSystem.OpenFile( sourcePath ) );
                bitmap.Save( destPath, System.Drawing.Imaging.ImageFormat.Png );
              }
            }
            else
              Log.TraceMessage( string.Format( "File '{0}' was not found", image.Key ) );
          }
          catch ( Exception e )
          {
            Log.TraceError( "Cannot copy file \"{0}\" (\"{1}\"). {2}", fileName, image.Key, e.Message );
          }
        }
      }
    }

    #endregion

    #region Special Types for Export
    private class Talent
    {
      public string PersistentID;
      public string Name;
      public int Level;
      public DBTypes.ETalentRarity Rarity;
      public string HeroA = string.Empty;
      public string HeroB = string.Empty;
      public DBTypes.EAbilityType Type;
      public int Cost;
      public string ManaCost;
      public string Cooldown;
      public int DevPoints;
      public string DescriptionA;
      public string DescriptionB;
      public string IconPath;
      public float ForceBonus;
      public float MinLevelForce;
      public float MaxLevelForce;

      public Talent()
      {
      }

      public Talent( DBTypes.Talent talent, ImagesCollector images, string[] rarityNames, TalentGroup group, FormulaCalculator fc )
      {
        PersistentID = talent.persistentId;
        Name = talent.name.ToString();
        Level = talent.minLevel;
        Rarity = talent.rarity;
        ForceBonus = talent.forceBonus;

        MinLevelForce = fc.GetTalentForce( talent, fc.AILogic.forceParameters, fc.AILogic.talentBaseStatBudget, 0 );
        MaxLevelForce = fc.GetTalentForce( talent, fc.AILogic.forceParameters, fc.AILogic.talentBaseStatBudget, 4 );
        var hero = TalentsContainer.GetHero( talent );
        if ( hero != null )
        {
          HeroA = hero.heroNameA.ToString();
          HeroB = hero.heroNameB.ToString();
        }
        else if ( talent.rarity == DBTypes.ETalentRarity.Class )
          Log.TraceWarning( "Class talent \"{0}\" not assigned to any hero", talent.DBId );
        Type = talent.type;

        int talNaftaCost = talent.naftaCost;
        if ( talNaftaCost < 0 )
          talNaftaCost = fc.NaftaCostByLevel[talent.minLevel];
        Cost = talNaftaCost;
        DevPoints = talent.devPoints;
        IconPath = images.AddImage( talent.image.Get(), hero == null ? string.Empty : hero.id );

        fc.AssignGroup( group );
        fc.AssignAbility( talent );
        ManaCost = fc.EvaluateMinMax( talent.manaCost.sString, 1 );
        Cooldown = fc.EvaluateMinMax( talent.cooldownTime.sString, 1 );

        var groupName = group != null ? group.name.ToString() : "";
        var groupDescription = group != null ? group.description.ToString() : "";

        fc.AssignFaction( DBTypes.EFaction.Freeze );
        DescriptionA = TextProcessor.CleanUp( TextProcessor.Parse( talent.description.ToString(), talent.commonDescription.ToString(), true, rarityNames[(int)talent.rarity], talent.name.ToString(), groupName, groupDescription, images ) );
        fc.AssignFaction( DBTypes.EFaction.Burn );
        DescriptionB = TextProcessor.CleanUp( TextProcessor.Parse( talent.description.ToString(), talent.commonDescription.ToString(), true, rarityNames[(int)talent.rarity], talent.name.ToString(), groupName, groupDescription, images ) );
      }
    }

    private class Consumable
    {
      public string Name;
      public int Cost;
      public string Cooldown;
      public string Description;
      public string IconPath;

      public Consumable()
      {
      }

      public Consumable( DBTypes.Consumable consumable, ImagesCollector images, FormulaCalculator fc )
      {
        Name = "";
        Cost = 0;
        Cooldown = "";
        Description = "";
        IconPath = "";

        Name = consumable.name.ToString();
        Cost = consumable.naftaCost;

        fc.AssignAbility( consumable );
        Cooldown = fc.EvaluateMinMax( consumable.cooldownTime.sString, 1 );
        Description = TextProcessor.CleanUp( TextProcessor.Parse( consumable.description.ToString(), "", true, "", consumable.name.ToString(), images ) );
        IconPath = images.AddImage( consumable.image.Get(), string.Empty );
      }
    }

    private class Achievement
    {
      public string Name;
      public string Description;
      public string IconPath;

      public Achievement()
      {
      }

      public Achievement( DBTypes.AchievBase achievement, ImagesCollector images )
      {
        Name = achievement.name.ToString();
        Description = achievement.tooltip.ToString();
        IconPath = images.AddImage( achievement.image.Get(), string.Empty );
      }
    }

    private class Building
    {
      public string Description;
      public int Fraction;
      public string IconPath;

      public Building()
      {
      }

      public Building( DBTypes.Building building, ImagesCollector images )
      {
        Description = building.description.ToString();
        Fraction = (int)building.faction;
        IconPath = images.AddImage( building.image.Get(), string.Empty );
      }
    }

    private class Hero
    {
      public string PersistentID;
      public string HeroClassName;
      public string HeroNameA;
      public string HeroImageA;
      public string HeroRenderA;
      public string HeroDescriptionA;
      public string HeroBiographyA;
      public string HeroNameB;
      public string HeroImageB;
      public string HeroRenderB;
      public string HeroDescriptionB;
      public string HeroBiographyB;
      public bool IsHeroHiredByDefaultMale;
      public bool IsHeroHiredByDefaultFemale;
      public ExportStats Stats;
      public string Classes;
      public ExportResourcesTable CostMale;
      public ExportResourcesTable CostFemale;
      public int LevelRequireFemale;
      public int LevelRequireMale;

      public Hero()
      {
      }

      public Hero( DBTypes.Hero hero, Dictionary<HeroClassEnum, HeroClassInfo> classes, ImagesCollector images )
      {
        PersistentID = hero.persistentId;
        HeroClassName = classes[hero.lobbyData.Classes].Name.GetText();
        HeroNameA = hero.heroNameA.GetText();
        HeroImageA = images.AddImage( hero.heroImageA.Get(), string.Empty );
        HeroRenderA = images.AddImage( hero.lobbyData.heroRenderA.Get(), string.Empty );
        HeroDescriptionA = hero.lobbyData.heroDescriptionA.ToString();
        HeroBiographyA = hero.lobbyData.heroBiographyA.ToString();
        HeroNameB = hero.heroNameB.GetText();
        HeroImageB = images.AddImage( hero.heroImageB.Get(), string.Empty );
        HeroRenderB = images.AddImage( hero.lobbyData.heroRenderB.Get(), string.Empty );
        HeroDescriptionB = hero.lobbyData.heroDescriptionB.ToString();
        HeroBiographyB = hero.lobbyData.heroBiographyB.ToString();
        IsHeroHiredByDefaultMale = hero.lobbyData.IsHeroHiredByDefaultMale;
        IsHeroHiredByDefaultFemale = hero.lobbyData.IsHeroHiredByDefaultFemale;
        Classes = hero.lobbyData.Classes.ToString();
        Stats = new ExportStats( hero.stats.Get().stats );
        CostMale = new ExportResourcesTable( hero.lobbyData.CostMale );
        CostFemale = new ExportResourcesTable( hero.lobbyData.CostFemale );
        LevelRequireFemale = hero.lobbyData.LevelRequireFemale;
        LevelRequireMale = hero.lobbyData.LevelRequireMale;
      }
    }

    public class ExportStats
    {
      public string Health;
      public string Mana;
      public string Strength;
      public string Intellect;
      public string Agility;
      public string Cunning;
      public string Fortitude;
      public string Will;
      public string Speed;

      public ExportStats( libdb.IChangeableList<DBTypes.UnitStat> stats )
      {
        Health = stats[0].value.sString;
        Mana = stats[1].value.sString;
        Strength = stats[2].value.sString;
        Intellect = stats[3].value.sString;
        Agility = stats[5].value.sString;
        Cunning = stats[4].value.sString;
        Fortitude = stats[6].value.sString;
        Will = stats[7].value.sString;
        Speed = stats[10].value.sString;
      }
    }

    public class ExportResourcesTable
    {
      public int Resource1;
      public int Resource2;
      public int Resource3;
      public int Resource1_Rare;
      public int Resource2_Rare;
      public int Resource3_Rare;
      public int Perl;
      public int Silver;
      public int Gold;
      public int Population;
      public ExportResourcesTable( DBTypes.ResourcesTable res )
      {
        Resource1 = res.Resource1;
        Resource2 = res.Resource2;
        Resource3 = res.Resource3;
        Resource1_Rare = res.Resource1_Rare;
        Resource2_Rare = res.Resource2_Rare;
        Resource3_Rare = res.Resource3_Rare;
        Perl = res.Perl;
        Silver = res.Silver;
        Gold = res.Gold;
        Population = res.Population;
      }
    }

    public class ExportConstructionLevel
    {
      public int Fame;
      public ExportResourcesTable Price;

      public ExportConstructionLevel( DBTypes.ConstructionLevel level )
      {
        Fame = level.fame;
        Price = new ExportResourcesTable( level.price );
      }
    }

    public class ExportBathLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public int HeroesCount;
      public float PassiveEnergyRecoveryBoost;
      public List<ExportBathCycleType> BathCycles = new List<ExportBathCycleType>();
      public float RecoveryPriceDiscount;

      public ExportBathLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }
    }

    public class ExportProductionLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public List<ExportCycleType> Cycles = new List<ExportCycleType>();

      public ExportProductionLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }

    }

    public class ExportStorageLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public DBTypes.ResourcesTable AdditionalStorage;

      public ExportStorageLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }
    }

    public class ExportHouseLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public int CurrentMaxPopulation;
      public ExportCycleType Cycle;

      public ExportHouseLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }
    }

    public class ExportTransmutationLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public int PerlForBonuse;
      public ExportTransmutationLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }

    }

    public class ExportLibraryLevel : ExportConstructionLevel
    {
      public int CurrentLevel;
      public int AdditionalTalentSlots;

      public ExportLibraryLevel( DBTypes.ConstructionLevel level )
        : base( level )
      {

      }
    }

    public class ExportCycleType
    {
      public DBTypes.ResourcesTable PriceToStart;
      public ExportResourcesTable ResourcesToProduce;
      public ExportTimeBlock Timeblock;
    }

    public class ExportTimeBlock
    {
      public int Time;
      public int Gold;

      public ExportTimeBlock()
      {
      }

      public ExportTimeBlock( DBTypes.TimeBlock block )
      {
        Time = block.time;
        Gold = block.gold;
      }
    }

    public class ExportBathCycleType
    {
      public float cycleDuration;
      public string specialCycle;
      public string cycleTitle;
      public int restoringEnergy;

      public ExportBathCycleType( DBTypes.BathCycleType cycle )
      {
        cycleDuration = cycle.cycleDuration;
        specialCycle = cycle.specialCycle.ToString();
        restoringEnergy = cycle.restoringEnergy;
        cycleTitle = cycle.cycleTitle.ToString();
      }
    }

    private class Construction
    {
      public string PersistentID;
      public string DescriptionA;
      public string DescriptionB;
      public string IconPathA;
      public string IconPathB;
      public string CaptionA;
      public string CaptionB;
      public string TooltipA;
      public string TooltipB;
      public string UpgradeTooltipA;
      public string UpgradeTooltipB;
      public int SectionsSize;
      public float SellPricePercent;
      public List<ExportConstructionLevel> Levels = new List<ExportConstructionLevel>();


      public Construction()
      {
      }

      public Construction( DBTypes.Constructon constructon, ImagesCollector images, FormulaCalculator fc )
      {
        //FormulaCalculator.AssignAbility(consumable);
        PersistentID = constructon.persistentId;
        fc.AssignFaction( DBTypes.EFaction.Freeze );
        DescriptionA = TextProcessor.CleanUp( TextProcessor.Parse( constructon.Description.ToString(), "", true, "", constructon.CaptionA.ToString(), images ) );
        fc.AssignFaction( DBTypes.EFaction.Burn );
        DescriptionB = TextProcessor.CleanUp( TextProcessor.Parse( constructon.Description.ToString(), "", true, "", constructon.CaptionB.ToString(), images ) );
        CaptionA = constructon.CaptionA.ToString();
        String pathA = "";
        String pathB = "";
        if ( !String.IsNullOrEmpty( constructon.IconPathA ) )
          pathA = constructon.IconPathA + ".png";
        if ( !String.IsNullOrEmpty( constructon.IconPathB ) )
          pathB = constructon.IconPathA + ".png";
        IconPathA = images.AddImage( pathA, string.Empty );
        CaptionB = constructon.CaptionB.ToString();
        IconPathB = images.AddImage( pathB, string.Empty );
        fc.AssignFaction( DBTypes.EFaction.Freeze );
        TooltipA = TextProcessor.CleanUp( TextProcessor.Parse( constructon.Tooltip.ToString(), "", true, "", constructon.CaptionA.ToString(), images ) );
        fc.AssignFaction( DBTypes.EFaction.Burn );
        TooltipB = TextProcessor.CleanUp( TextProcessor.Parse( constructon.Tooltip.ToString(), "", true, "", constructon.CaptionB.ToString(), images ) );
        fc.AssignFaction( DBTypes.EFaction.Freeze );
        UpgradeTooltipA = TextProcessor.CleanUp( TextProcessor.Parse( constructon.UpgradeTooltip.ToString(), "", true, "", constructon.CaptionA.ToString(), images ) );
        fc.AssignFaction( DBTypes.EFaction.Burn );
        UpgradeTooltipB = TextProcessor.CleanUp( TextProcessor.Parse( constructon.UpgradeTooltip.ToString(), "", true, "", constructon.CaptionB.ToString(), images ) );
        SectionsSize = constructon.SectionsSize;
        SellPricePercent = constructon.SellPricePercent;

        if ( constructon is DBTypes.Bath )
        {
          var bath = constructon as DBTypes.Bath;
          for ( int i = 0; i < bath.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = bath.Levels[i];

            ExportBathLevel bathLevel = new ExportBathLevel( level );

            bathLevel.HeroesCount = GetInterpolatedValue( bath.BathLevels, i, _level => _level.currentLevel, _level => _level.heroesCount );
            bathLevel.PassiveEnergyRecoveryBoost = GetInterpolatedValue( bath.BathLevels, i, _level => _level.currentLevel, _level => _level.passiveEnergyRecoveryBoost );
            bathLevel.RecoveryPriceDiscount = GetInterpolatedValue( bath.BathLevels, i, _level => _level.currentLevel, _level => _level.recoveryPriceDiscount );
            for ( int j = 0; j < bath.BathCycles.Count; j++ )
            {
              bathLevel.BathCycles.Add( new ExportBathCycleType( bath.BathCycles[j] ) );
            }

            Levels.Add( bathLevel );
          }
        }

        else if ( constructon is DBTypes.ProductionBuilding )
        {
          var prod = constructon as DBTypes.ProductionBuilding;
          for ( int i = 0; i < prod.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = prod.Levels[i];

            ExportProductionLevel prodLevel = new ExportProductionLevel( level );

            int cyclesCount = prod.ProductionLevels[0].cycles.Count;
            for ( int j = 0; j < cyclesCount; j++ )
            {
              var cycle = new ExportCycleType();
              cycle.PriceToStart = GetInterpolatedValue( prod.ProductionLevels, i, _level => _level.currentLevel,
                                                        _level => _level.cycles[j].priceToStart );
              cycle.ResourcesToProduce =
                new ExportResourcesTable( GetInterpolatedValue( prod.ProductionLevels, i, _level => _level.currentLevel,
                                                              _level => _level.cycles[j].resourcesToProduce ) );
              cycle.Timeblock = new ExportTimeBlock();
              cycle.Timeblock.Gold = GetInterpolatedValue( prod.ProductionLevels, i, _level => _level.currentLevel,
                                                         _level => _level.cycles[j].timeblock.Get().gold );
              cycle.Timeblock.Time = GetInterpolatedValue( prod.ProductionLevels, i, _level => _level.currentLevel,
                                                         _level => _level.cycles[j].timeblock.Get().time );
              prodLevel.Cycles.Add( cycle );
            }

            Levels.Add( prodLevel );
          }
        }
        else if ( constructon is DBTypes.LibraryBuilding )
        {
          var lib = constructon as DBTypes.LibraryBuilding;
          for ( int i = 0; i < lib.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = lib.Levels[i];

            ExportLibraryLevel libLevel = new ExportLibraryLevel( level );
            libLevel.AdditionalTalentSlots = GetInterpolatedValue( lib.LibraryLevels, i, _level => _level.currentLevel, _level => _level.additionalTalentSlots );
            libLevel.CurrentLevel = GetInterpolatedValue( lib.LibraryLevels, i, _level => _level.currentLevel, _level => _level.currentLevel );


            Levels.Add( libLevel );
          }
        }
        else if ( constructon is DBTypes.HouseBuilding )
        {
          var house = constructon as DBTypes.HouseBuilding;
          for ( int i = 0; i < house.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = house.Levels[i];

            ExportHouseLevel houseLevel = new ExportHouseLevel( level );
            houseLevel.CurrentMaxPopulation = GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                                   _level => _level.currentMaxPopulation );
            houseLevel.CurrentLevel = GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                           _level => _level.currentLevel );

            houseLevel.Cycle = new ExportCycleType();
            houseLevel.Cycle.PriceToStart = GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                                   _level => _level.cycle.priceToStart );
            houseLevel.Cycle.ResourcesToProduce = new ExportResourcesTable( GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                                   _level => _level.cycle.resourcesToProduce ) );
            houseLevel.Cycle.Timeblock = new ExportTimeBlock();
            houseLevel.Cycle.Timeblock.Gold = GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                       _level => _level.cycle.timeblock.Get().gold );
            houseLevel.Cycle.Timeblock.Time = GetInterpolatedValue( house.HouseLevels, i, _level => _level.currentLevel,
                                                       _level => _level.cycle.timeblock.Get().time );
            Levels.Add( houseLevel );
          }
        }
        else if ( constructon is DBTypes.TransmutationBuilding )
        {
          var trans = constructon as DBTypes.TransmutationBuilding;
          for ( int i = 0; i < trans.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = trans.Levels[i];

            ExportTransmutationLevel transLevel = new ExportTransmutationLevel( level );
            transLevel.PerlForBonuse = GetInterpolatedValue( trans.TransmutationLevels, i, _level => _level.currentLevel, _level => _level.perlForBonuse );
            transLevel.CurrentLevel = GetInterpolatedValue( trans.TransmutationLevels, i, _level => _level.currentLevel, _level => _level.currentLevel );

            Levels.Add( transLevel );
          }
        }
        else if ( constructon is DBTypes.StorageBuilding )
        {
          var storage = constructon as DBTypes.StorageBuilding;
          for ( int i = 0; i < storage.Levels.Count; i++ )
          {
            DBTypes.ConstructionLevel level = storage.Levels[i];

            ExportStorageLevel storageLevel = new ExportStorageLevel( level );
            storageLevel.AdditionalStorage = GetInterpolatedValue( storage.StorageLevels, i, _level => _level.currentLevel, _level => _level.additionalStorage );
            storageLevel.CurrentLevel = GetInterpolatedValue( storage.StorageLevels, i, _level => _level.currentLevel, _level => _level.currentLevel );

            Levels.Add( storageLevel );
          }
        }
      }
    }
    #endregion

    #region Helper Functions
    private delegate int GetLevelIndexFunc<T>( T level ) where T : class;
    private static T[] GetLevelInterpolate<T>( IEnumerable<T> levels, int level, GetLevelIndexFunc<T> func ) where T : class
    {
      T first = null;
      T second = null;

      foreach ( var curLevel in levels )
      {
        int curIndex = func( curLevel );
        if ( level >= curIndex )
          first = curLevel;
        if ( level <= curIndex )
        {
          second = curLevel;
          break;
        }
      }

      return new T[] { first, second };
    }

    private delegate T GetLevelValueFunc<TLevel, T>( TLevel level ) where TLevel : class;
    private static T GetInterpolatedValue<TLevel, T>( IEnumerable<TLevel> levels, int level, GetLevelIndexFunc<TLevel> levelFunc, GetLevelValueFunc<TLevel, T> valueFunc ) where TLevel : class
    {
      var findLevels = GetLevelInterpolate( levels, level, levelFunc );
      if ( findLevels[0] != null && findLevels[1] != null )
      {
        if ( levelFunc( findLevels[0] ) == levelFunc( findLevels[1] ) )
        {
          return valueFunc( findLevels[0] );
        }

        T value1 = valueFunc( findLevels[0] );
        T value2 = valueFunc( findLevels[1] );
        int index1 = levelFunc( findLevels[0] );
        int index2 = levelFunc( findLevels[1] );

        return Interpolate( level, index1, index2, value1, value2 );
      }
      return default( T );
    }

    private static float Interpolate( int level, int index1, int index2, float value1, float value2 )
    {
      float coeff = GetCoeff( level, index1, index2 );
      float value = value1 + ( value2 - value1 ) * coeff;
      return value;
    }

    private static int Interpolate( int level, int index1, int index2, int value1, int value2 )
    {
      float coeff = GetCoeff( level, index1, index2 );
      int value = RoundFloatToInt( ( value1 + ( value2 - value1 ) * coeff ) );
      return value;
    }

    private static DBTypes.ResourcesCoefTable Interpolate( int level, int index1, int index2, DBTypes.ResourcesCoefTable value1, DBTypes.ResourcesCoefTable value2 )
    {
      DBTypes.ResourcesCoefTable finalprice = new DBTypes.ResourcesCoefTable();

      float coeff = GetCoeff( level, index1, index2 );
      finalprice.Gold = value1.Gold + ( value2.Gold - value1.Gold ) * coeff;
      finalprice.Perl = value1.Perl + ( value2.Perl - value1.Perl ) * coeff;
      finalprice.Resource1 = value1.Resource1 + ( value2.Resource1 - value1.Resource1 ) * coeff;
      finalprice.Resource2 = value1.Resource2 + ( value2.Resource2 - value1.Resource2 ) * coeff;
      finalprice.Resource3 = value1.Resource3 + ( value2.Resource3 - value1.Resource3 ) * coeff;
      finalprice.Silver = value1.Silver + ( value2.Silver - value1.Silver ) * coeff;
      finalprice.Population = value1.Population + ( value2.Population - value1.Population ) * coeff;
      finalprice.Resource1_Rare = value1.Resource1_Rare + ( value2.Resource1_Rare - value1.Resource1_Rare ) * coeff;
      finalprice.Resource2_Rare = value1.Resource2_Rare + ( value2.Resource2_Rare - value1.Resource2_Rare ) * coeff;
      finalprice.Resource3_Rare = value1.Resource3_Rare + ( value2.Resource3_Rare - value1.Resource3_Rare ) * coeff;
      return finalprice;
    }

    private static T Interpolate<T>( int level, int index1, int index2, T value1, T value2 )
    {
      if ( typeof( T ) == typeof( int ) )
      {
        return (T)(object)Interpolate( level, index1, index2, (int)(object)value1, (int)(object)value2 );
      }
      if ( typeof( T ) == typeof( float ) )
      {
        return (T)(object)Interpolate( level, index1, index2, (float)(object)value1, (float)(object)value2 );
      }
      if ( typeof( T ) == typeof( DBTypes.ResourcesTable ) )
      {
        return (T)(object)GetFinalPrice( index1, index2, (DBTypes.ResourcesTable)(object)value1, (DBTypes.ResourcesTable)(object)value2, level );
      }
      if ( typeof( T ) == typeof( DBTypes.ResourcesCoefTable ) )
      {
        return (T)(object)Interpolate( level, index1, index2, (DBTypes.ResourcesCoefTable)(object)value1, (DBTypes.ResourcesCoefTable)(object)value2 );
      }


      return default( T );
    }

    public static int RoundFloatToInt( float number )
    {
      return (int)Math.Floor( number + 1e-5f );
    }

    public static float GetCoeff( int level, int first, int second )
    {
      return (float)( level - first ) / (float)( second - first );
    }

    public static DBTypes.ResourcesTable GetFinalPrice( int prLevelFirst, int prLevelSecond, DBTypes.ResourcesTable price1, DBTypes.ResourcesTable price2, int level )
    {
      DBTypes.ResourcesTable finalprice = new DBTypes.ResourcesTable();
      if ( prLevelFirst == prLevelSecond )
        return price1;

      float coeff = GetCoeff( level, prLevelFirst, prLevelSecond );
      finalprice.Gold = RoundFloatToInt( price1.Gold + ( price2.Gold - price1.Gold ) * coeff );
      finalprice.Perl = RoundFloatToInt( price1.Perl + ( price2.Perl - price1.Perl ) * coeff );
      finalprice.Resource1 = RoundFloatToInt( price1.Resource1 + ( price2.Resource1 - price1.Resource1 ) * coeff );
      finalprice.Resource2 = RoundFloatToInt( price1.Resource2 + ( price2.Resource2 - price1.Resource2 ) * coeff );
      finalprice.Resource3 = RoundFloatToInt( price1.Resource3 + ( price2.Resource3 - price1.Resource3 ) * coeff );
      finalprice.Silver = RoundFloatToInt( price1.Silver + ( price2.Silver - price1.Silver ) * coeff );
      finalprice.Population = RoundFloatToInt( price1.Population + ( price2.Population - price1.Population ) * coeff );
      finalprice.Resource1_Rare = RoundFloatToInt( price1.Resource1_Rare + ( price2.Resource1_Rare - price1.Resource1_Rare ) * coeff );
      finalprice.Resource2_Rare = RoundFloatToInt( price1.Resource2_Rare + ( price2.Resource2_Rare - price1.Resource2_Rare ) * coeff );
      finalprice.Resource3_Rare = RoundFloatToInt( price1.Resource3_Rare + ( price2.Resource3_Rare - price1.Resource3_Rare ) * coeff );
      return finalprice;
    }
    #endregion

    #region Serialization functions
    private static void SerializeObject( object obj, string name, XmlWriter writer )
    {
      writer.WriteStartElement( name );
      DBXmlSerializer.Serialize( writer, obj, null );
      writer.WriteEndElement();
    }

    private static void SerializeList( IEnumerable objs, string listName, string name, XmlWriter writer )
    {
      writer.WriteStartElement( listName );
      foreach ( var obj in objs )
        SerializeObject( obj, name, writer );
      writer.WriteEndElement();
    }
    #endregion

    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
      if ( args.Length == 0 )
      {
        Log.TraceError( "Usage: PF_EditorC.exe run ../Tools/Scripts/ExportItems.cs <xml_file_path> <images_folder> [<image_lookup_folder1> <image_lookup_folder2> ... <image_lookup_folderN>]" );
        yield break;
      }

      string XML_FILE_PATH = args[0];
      string IMAGES_FOLDER = args.Length > 1 ? args[1] : string.Empty;
      List<string> LOOK_FOLDERS = new List<string>();
      for ( int i = args.Length - 1; i > 1; i-- )
        LOOK_FOLDERS.Add( args[i] );




      Log.TraceMessage( "Initialize database..." );
      var uiRoot = DataBase.Get<DBTypes.UIRoot>( DBID.FromString( "/UI/UIRoot" ) ).Get();
      var fc = new FormulaCalculator( DataBase.Get<DBTypes.AILogicParameters>( DBID.FromString( "/GameLogic/AILogic.AILP" ) ), DataBase.Get<DBTypes.UnitLogicParameters>( DBID.FromString( "/GameLogic/Hero.UNLP" ) ) );
      TextProcessor.Initiliaze( uiRoot, fc );
      TalentsContainer.Initialize( app, DataBase.Get<DBTypes.HeroesDB>( DBID.FromString( "/Heroes/_.HRDB" ) ).Get(), "/Items/Talents" );

      SocialRoot socialRoot = DataBase.Get<DBTypes.SocialRoot>( DBID.FromString( "/Social.ROOT" ) );
      var uiData = DataBase.Get<DBTypes.DBUIData>( DBID.FromString( "/UI/Content/_.UIDT" ) ).Get();
      var rarityNames = new List<TextRef>( DataBase.Get<DBTypes.DBUIData>( DBID.FromString( "/UI/Content/_.UIDT" ) ).Get().rarityValue ).ConvertAll<string>( ( TextRef str ) => { return str.ToString(); } ).ToArray();
      TalentGroupList talentGroupList = DataBase.Get<AILogicParameters>( DBID.FromFileName( "/GameLogic/AILogic.AILP.xdb", false ) ).Get().talentGroups;
      var groupTalents = new Dictionary<DBTypes.Talent, TalentGroup>();
      foreach ( var talentGroup in talentGroupList.groups )
      {
        foreach ( var talentPtr in talentGroup.talents )
        {
          var talent = talentPtr.Get();
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

      ImagesCollector images = new ImagesCollector();
      images.LoadStyles( uiRoot.styleAliases );

      List<DBID> dbids;
      Log.TraceMessage( "Collect talents..." );
      var talents = new List<Talent>();
      foreach ( var talent in TalentsContainer.Talents )
      {
        TalentGroup group;
        groupTalents.TryGetValue( talent, out group );
        talents.Add( new Talent( talent, images, rarityNames, group, fc ) );
      }

      Log.TraceMessage( "Collect consumables..." );
      var consumables = new List<Consumable>();
      ObjectsSelector.CollectObjects( app, "/Items/Consumables", typeof( DBTypes.Consumable ), true, false, out dbids );
      foreach ( var dbid in dbids )
        consumables.Add( new Consumable( DataBase.Get<DBTypes.Consumable>( dbid ).Get(), images, fc ) );
      ObjectsSelector.CollectObjects( app, "/Items/Scrolls", typeof( DBTypes.Consumable ), true, false, out dbids );
      foreach ( var dbid in dbids )
        consumables.Add( new Consumable( DataBase.Get<DBTypes.Consumable>( dbid ).Get(), images, fc ) );

      Log.TraceMessage( "Collect achievements..." );
      var achievements = new List<Achievement>();
      foreach ( var achievementPtr in DataBase.Get<DBTypes.ScoringTable>( DBID.FromString( "/GameLogic/Scoring.SCTB" ) ).Get().achievementsList )
        achievements.Add( new Achievement( achievementPtr.Get(), images ) );

      Log.TraceMessage( "Collect buildings..." );
      var buildings = new List<Building>();
      ObjectsSelector.CollectObjects( app, "/Buildings", typeof( DBTypes.Building ), true, true, out dbids );
      foreach ( var dbid in dbids )
        buildings.Add( new Building( DataBase.Get<DBTypes.Building>( dbid ).Get(), images ) );
      Log.TraceMessage( "Collect constructions..." );
      var constructions = new List<Construction>();
      ObjectsSelector.CollectObjects( app, "/Social/Constructions", typeof( DBTypes.Constructon ), true, true, out dbids );
      foreach ( var dbid in dbids )
      {
        constructions.Add( new Construction( DataBase.Get<DBTypes.Constructon>( dbid ).Get(), images, fc ) );
      }

      Log.TraceMessage( "Collect heroes..." );
      var heroClasses = new Dictionary<HeroClassEnum, HeroClassInfo>();
      foreach ( var hci in socialRoot.HeroClassesTable.Get().HeroClasses )
        if ( !heroClasses.ContainsKey( hci.Class ) )
          heroClasses.Add( hci.Class, hci );

      var heroes = new List<Hero>();
      ObjectsSelector.CollectObjects( app, "/Heroes", typeof( DBTypes.Hero ), true, true, out dbids );
      foreach ( var dbid in dbids )
      {
        var hero = DataBase.Get<DBTypes.Hero>( dbid ).Get();
        if ( !hero.legal )
          continue;
        heroes.Add( new Hero( hero, heroClasses, images ) );
      }

      Log.TraceMessage( "Store xml to '{0}'...", XML_FILE_PATH );
      var dirPath = new FileInfo( XML_FILE_PATH ).DirectoryName;
      if ( !Directory.Exists( dirPath ) )
        Directory.CreateDirectory( dirPath );
      using ( var stream = File.Open( XML_FILE_PATH, FileMode.Create, FileAccess.Write ) )
      {
        using ( var xml = XmlWriter.Create( stream, new XmlWriterSettings { CloseOutput = true, Encoding = Encoding.UTF8, Indent = true, IndentChars = "  ", NewLineOnAttributes = false } ) )
        {
          xml.WriteStartDocument();
          xml.WriteStartElement( "Items" );
          SerializeList( talents, "Talents", "Talent", xml );
          SerializeList( consumables, "Consumables", "Consumable", xml );
          SerializeList( achievements, "Achievements", "Achievement", xml );
          SerializeList( buildings, "Buildings", "Building", xml );
          SerializeList( constructions, "Constructions", "Construction", xml );
          SerializeList( heroes, "Heroes", "Hero", xml );
          xml.WriteEndElement();
          xml.WriteEndDocument();
        }
      }

      if ( !string.IsNullOrEmpty( IMAGES_FOLDER ) )
      {
        Log.TraceMessage( "Store images in folder '{0}'...", IMAGES_FOLDER );
        images.StoreImages( app, IMAGES_FOLDER, LOOK_FOLDERS );
      }
      Log.TraceMessage( "Script work is done" );
      yield return true;
    }
  }
}
