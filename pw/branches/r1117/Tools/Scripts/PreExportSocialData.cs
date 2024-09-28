/*
#about Подготовка данных для экспорта для социального клиента и сервера
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#include SimpleCalc.cs
 */

using DBTypes;
using EditorLib;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;
using SimpleCalc;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace Scripts
{
  public class PreExportSocialData
  {
    private class TalentWrapper : FunctionsList
    {
      private int _level = 1;

      public TalentWrapper( Talent talent )
      {
        if ( talent.constants.Get() != null )
        {
          foreach ( var constant in talent.constants.Get().vars )
            AddAlias( 'c' + constant.Get().name, constant.Get().var.sString );
        }

        AddFunction( "refineScale", ( float value, float increment ) => { return value + increment * (_level - 1); } );
      }

      public void SetLevel( int level )
      {
        _level = level;
      }
    }

    private List<T> GetItems<T>( IEditorCommonApplication app, string path, bool recursive, bool driven ) where T : DBResource, new()
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects( app, path, typeof( T ), recursive, driven, out dbids );

      var result = new List<T>();
      foreach ( var dbid in dbids )
        result.Add( DataBase.Get<T>( dbid ).Get() );

      return result;
    }

    private void RegisterCppConstants( StringProcessor processor )
    {
      processor.AddVariable( "true", () => { return true; } );
      processor.AddVariable( "false", () => { return false; } );
      processor.AddFunction( "floor", ( float f ) => { return Math.Floor( f ); } );
      processor.AddFunction( "ceil", ( float f ) => { return Math.Ceiling( f ); } );
    }

    private void RegisterAILogicParameters( StringProcessor processor, AILogicParameters aiLogicParameters )
    {
      foreach ( var constant in aiLogicParameters.globalConstants.Get().vars )
      {
        //Log.TraceMessage( "Add constant: {0} = {1}", constant.Get().name, constant.Get().var.sString );
        processor.AddAlias( 'c' + constant.Get().name, constant.Get().var.sString );
      }

      foreach ( var condition in aiLogicParameters.conditionFormulas )
      {
        //Log.TraceMessage( "Add condition: {0} = {1}", condition.Get().name, condition.Get().condition.sString );
        processor.AddAlias( condition.Get().name, condition.Get().condition.sString );
      }
    }

    private static float Calc( StringProcessor processor, string expression, params FunctionsList[] functions )
    {
      return processor.Parse( expression, functions ).Calculate().Float;
    }

    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
      AILogicParameters aiLogicParameters = DataBase.Get<AILogicParameters>( DBID.FromString( "/GameLogic/AILogic.AILP" ) ).Get();
      var statsBudgetContainer = aiLogicParameters.statsBudget.Get();
      var forceParameters = aiLogicParameters.forceParameters.Get();

      var calc = new StringProcessor();
      RegisterCppConstants( calc );
      RegisterAILogicParameters( calc, aiLogicParameters );

      List<Hero> heroes = GetItems<Hero>( app, "/Heroes", true, false );
      foreach ( var hero in heroes )
      {
        float totalStatsBudget = 0.0f;
        foreach ( var stat in hero.stats.Get().stats )
        {
          stat.calcValue = Calc( calc, stat.value.sString );
          stat.calcIncrement = Calc( calc, stat.increment.sString );
          foreach ( var statBudget in statsBudgetContainer.stats )
          {
            if ( statBudget.stat == stat.statId && statBudget.upgradesWithForce )
            {
              totalStatsBudget += stat.calcIncrement / statBudget.budget;
              break;
            }
          }
        }
        hero.totalStatsBudget = totalStatsBudget;
      }

      var talents = GetItems<Talent>( app, "/Items/Talents", true, false );
      foreach ( var talent in talents )
      {
        TalentWrapper talentVars = new TalentWrapper( talent );
        Dictionary<EStat, float[]> stats = new Dictionary<EStat, float[]>();
        foreach ( var applicator in talent.passiveApplicators )
        {
          var statModApp = applicator.Get() as PermanentStatModApplicator;
          if ( statModApp == null )
            continue;

          if ( !String.IsNullOrEmpty( statModApp.modifier.variable ) )
            continue;

          if ( !string.IsNullOrEmpty( statModApp.enabled.sString ) && statModApp.enabled.sString != "true" && !Regex.IsMatch( statModApp.enabled.sString, @"^1?$|^1?\.\d$" ) )
            continue;

          float[] values = new float[5];
          for ( int i = 1; i <= 5; ++i )
          {
            talentVars.SetLevel( i );
            values[i-1] = Calc( calc, statModApp.modifier.addValue.sString, talentVars );
          }

          float[] oldValues;
          if ( stats.TryGetValue( statModApp.modifier.stat, out oldValues ) )
          {
            for ( int i = 0; i < 5; ++i )
              oldValues[i] += values[i];
          }
          else
            stats.Add( statModApp.modifier.stat, values );

          //Log.TraceMessage( "stat = {0}, values = {1}", statModApp.modifier.stat, string.Join( "; ", new List<float>( values ).ConvertAll<string>( f => f.ToString() ).ToArray() ) );
        }

        talent.talentStats.Clear();
        foreach ( var stat in stats )
        {
          talent.talentStats.Add( new TalentStats() );
          var talentStats = talent.talentStats[talent.talentStats.Count - 1];
          talentStats.stat = stat.Key;
          foreach ( var value in stat.Value )
            talentStats.values.Add( value );
        }

        talent.forceBonus = forceParameters.talentLevelBonusPercent[talent.minLevel];
      }

      DataBase.Store();
      yield return true;
    }
	}
}