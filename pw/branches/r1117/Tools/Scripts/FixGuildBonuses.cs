/*
#ref PF_Types.DBTypes.dll
#ref PF_EditorC.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using System.Xml;
using System.IO;
using System.Globalization;
using PF_EditorC;

public class FixGuildBonuses
{
    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        bool saveDB = true;
        
        Log.TraceMessage("Collecting bonuses...");
        List<DBID> buffsDbids;
        ObjectsSelector.CollectObjects( app, "/Items/GuildBuffs", typeof( GuildBuff ), true, false, out buffsDbids );
        Log.TraceMessage("{0} bonuses collected", buffsDbids.Count);

        foreach (var buffDbid in buffsDbids)
        {
            // filling talents
          GuildBuff buff = DataBase.Get<GuildBuff>( buffDbid );
          Log.TraceMessage( "proceed buff {0} ({1} bonuses)", buff.persistentId, buff.bonuses.Count );
          foreach ( var bonusPtr in buff.bonuses )
          {
            GuildShopItemBonus bonus = bonusPtr.Get();
            if ( bonus == null )
              continue;
            
            //пробуем копировать героев
            HeroBonusBase heroBonus = bonus as HeroBonusBase;
            if (heroBonus != null )
            {
              TargetHeroes th = bonus.targetHeroes.Get();
              if ( th != null && th.heroes.Count > 0 )
              {
                heroBonus.heroes = th.heroes;
                Log.TraceMessage( "\tcopy heroes {0}", heroBonus.heroes.Count );
              }
            }

            SessionBonus sessionBonus = bonus as SessionBonus;
            if ( sessionBonus != null )
            {
              Log.TraceMessage( "\tcopy game settings" );
              sessionBonus.gameSettings.sessionType = bonus.sessionType;
              sessionBonus.gameSettings.mapType = bonus.mapType;


            }

            SessionValueBonus sessionVBonus = bonus as SessionValueBonus;
            if ( sessionVBonus != null )
            {
              Log.TraceMessage( "\tcopy modifiers" );
              sessionVBonus.modifiers.additiveValue = bonus.additiveValue;
              sessionVBonus.modifiers.multiplicativeValue = bonus.multiplicativeValue;
            }

            StatChangeBonus statChangeBonus = bonus as StatChangeBonus;
            if ( statChangeBonus != null )
            {
              Log.TraceMessage( "\tcopy modifiers in stat bonuses" );
              foreach (var statBonus in statChangeBonus.statBonuses)
              {
                Log.TraceMessage( "\t\t stat {0}", statBonus.statType.ToString() );
                statBonus.modifiers.additiveValue = statBonus.additiveValue;
                statBonus.modifiers.multiplicativeValue = statBonus.multiplicativeValue;
              }
            }
          }
        }

        if (saveDB)
        {
          Log.TraceMessage("Saving {0} items...", buffsDbids.Count);
            
          DataBase.Store();
          Log.TraceMessage("Succesfully saved");
        }
        
        yield return true;
    }
}

