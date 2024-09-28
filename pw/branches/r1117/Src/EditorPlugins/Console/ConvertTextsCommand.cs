//using System;
//using System.Collections.Generic;
//using System.Text;
//using EditorLib.Plugin;
//using DBTypes;
//using libdb.DB;
//using EditorLib.IO;
//using libdb.Diagnostics;
//using EditorLib;

//namespace EditorPlugins.Console
//{
//  [CommandName( "converttexts", "convtxts", "Convert old string texts to TextRef texts with creating .txt files for them." )]
//  public sealed class ConvertTextsCommand : IConsoleCommand
//  {
//    IEditorConApplication application;
//    Dictionary<Type, List<DBID>> items;

//    private T GetObject<T>( DBID dbid ) where T : DBResource
//    {
//      T obj = DataBase.Get<T>( dbid ).Get();
//      if ( obj == null )
//        return null;
//      Log.TraceMessage( "-->   {0}: {1}", typeof(T).ToString(), dbid.Name );
//      return obj;
//    }

//    private void ConvertText<T>( DBID dbid, T obj, string fromField, string toField )
//    {
//      ConvertText<T>( dbid, obj, fromField, toField, string.Empty );
//    }

//    private void ConvertText<T>( DBID dbid, T obj, string fromField, string toField, string prefix )
//    {
//      Type type = obj.GetType();
//      System.Reflection.PropertyInfo info = DBTypeUtils.GetProperty( type, fromField );
//      if ( info == null )
//      {
//        Log.TraceMessage( "-->     invalid source field name {0} in type {1}!", fromField, type.ToString() );
//        System.Console.ReadKey( true );
//        return;
//      }
//      if ( info.PropertyType != typeof( string ) )
//      {
//        Log.TraceMessage( "-->     non-string ({2}) source field {0} in type {1}!", fromField, type.ToString(), info.PropertyType.ToString() );
//        System.Console.ReadKey( true );
//        return;
//      }
//      if ( DBTypeUtils.GetProperty( type, toField ) == null )
//      {
//        Log.TraceMessage( "-->     invalid destination field name {0} in type {1}!", toField, type.ToString() );
//        System.Console.ReadKey( true );
//        return;
//      }

//      string text = info.GetValue( obj, null ).ToString();
//      if ( text.Length <= 0 ) // don't create .txt files for empty texts
//        return;

//      if ( dbid.FileName.Length <= 0 )
//      {
//        Log.TraceMessage( "-->     empty resource file name ({0})!", dbid.FileName );
//      }

//      string fileName = dbid.FileName;
//      int pos = fileName.LastIndexOf( ".xdb" );
//      if ( pos >= 0 )
//      {
//        if ( pos != fileName.Length - 4 )
//        {
//          Log.TraceMessage( "-->     invalid position of .xdb extension in resource file name ({0})!", dbid.FileName );
//          System.Console.ReadKey( true );
//          return;
//        }
//        fileName = fileName.Remove( pos );
//      }
//      else
//      {
//        Log.TraceMessage( "-->     not found .xdb extension in resource file name ({0})!", dbid.FileName );
//        System.Console.ReadKey( true );
//        return;
//      }
			
//      if ( prefix.Length > 0 )
//        fileName += prefix;
//      else
//        fileName += "_";

//      fileName += toField;
//      if ( dbid.Id.Length > 0 )
//        fileName += "_" + dbid.Id;
//      fileName += ".txt";

//      if ( application.Application.FileSystem.FileExists( fileName ) )
//        application.Application.FileSystem.DeleteFile( fileName );

//      using ( var stream = application.Application.FileSystem.CreateFile( fileName ) )
//      {
//        if ( ReferenceEquals( stream, null ) )
//        {
//          Log.TraceMessage( "-->     failed to create file {0}!", fileName );
//          System.Console.ReadKey( true );
//          return;
//        }

//        stream.WriteByte( 255 );
//        stream.WriteByte( 254 );

//        for ( int i = 0; i < text.Length; ++i )
//        {
//          UInt16 chr = (UInt16)text[i];
//          stream.WriteByte( (byte)( chr & 0xff ) );
//          stream.WriteByte( (byte)( chr >> 8 ) );
//        }
//      }

//      Log.TraceMessage( "-->     convert to field {0} of {1}:{2}, text={3}, filename={4}", toField, dbid.FileName, dbid.Id, text, fileName );
//    }

//    void IConsoleCommand.Execute( IEditorConApplication _application, string[] parameters )
//    {
//      application = _application;

//      Log.TraceMessage( "" );
//      Log.TraceMessage( "--> Collecting objects..." );

//      Type[] types = new Type[]
//      {
//        typeof( UILayout ),
//        typeof( ImageLabelLayout ),
//        typeof( Artifact ),
//        typeof( ArtifactModifier ),
//        typeof( Building ),
//        typeof( TownBuilding ),
//        typeof( Faction ),
//        typeof( HeroBasicClass ),
//        typeof( Creature ),
//        typeof( CreatureAbility ),
//        typeof( CreatureUpgrade ),
//        typeof( Monster ),
//        typeof( Teleport ),
//        typeof( Power ),
//        typeof( Enchant ),
//        typeof( Spell ),
//        typeof( CutScene ),
//        typeof( AdvMap ),
//      };

//      ObjectsSelector.CollectObjects( application.Application, string.Empty, types, true, true, out items );

//      Log.TraceMessage( "" );
//      Log.TraceMessage( "--> Processing objects..." );

//      int objectsCount = 0;
//      foreach( var type in types )
//      {
//        var dbids = items[ type ];
//        foreach( var dbid in dbids )
//        {
//          ++objectsCount;

//          if ( type == typeof( UILayout ) )
//          {
//            var layout = GetObject<UILayout>( dbid );
//            if ( layout != null )
//            {
//              ConvertText( dbid, layout, "defaultTooltip", "tooltipText" );

//              int count = layout.relatedTexts.Count;
//              for ( int i = 0; i < count; ++i )
//              {
//                string prefix = "_relatedTexts(" + i.ToString() + ")-";
//                ConvertText( dbid, layout.relatedTexts[i], "text", "relatedText", prefix );
//              }
//            }
//          }

//          if ( type == typeof( ImageLabelLayout ) )
//          {
//            var imageLabel = GetObject<ImageLabelLayout>( dbid );
//            if ( imageLabel != null )
//            {
//              ConvertText( dbid, imageLabel, "Text", "captionText" );
//            }
//          }

//          if ( type == typeof( Artifact ) )
//          {
//            var artifact = GetObject<Artifact>( dbid );
//            if ( artifact != null )
//            {
//              ConvertText( dbid, artifact, "artifactName", "nameText" );
//              ConvertText( dbid, artifact, "artifactDesc", "descText" );
//            }
//          }

//          if ( type == typeof( ArtifactModifier ) )
//          {
//            var mod = GetObject<ArtifactModifier>( dbid );
//            if ( mod != null )
//            {
//              ConvertText( dbid, mod, "description", "descText" );
//            }
//          }

//          if ( type == typeof( Building ) )
//          {
//            var building = GetObject<Building>( dbid );
//            if ( building != null )
//            {
//              ConvertText( dbid, building, "visitMessage", "nameText" );
//              ConvertText( dbid, building, "description", "descText" );

//              int count = building.visitActions.Count;
//              for ( int i = 0; i < count; ++i )
//              {
//                string prefix = "_visitActions(" + i.ToString() + ")-";
//                ConvertText( dbid, building.visitActions[i], "buttonText", "nameText", prefix );
//                ConvertText( dbid, building.visitActions[i], "description", "descText", prefix );
//              }
//            }
//          }

//          if ( type == typeof( TownBuilding ) )
//          {
//            var townBld = GetObject<TownBuilding>( dbid );
//            if ( townBld != null )
//            {
//              ConvertText( dbid, townBld, "buildingName", "nameText" ); // overwrite Building's
//            }
//          }

//          if ( type == typeof( Faction ) )
//          {
//            var faction = GetObject<Faction>( dbid );
//            if ( faction != null )
//            {
//              ConvertText( dbid, faction, "factionName", "nameText" );
//            }
//          }

//          if ( type == typeof( Power ) )
//          {
//            var power = GetObject<Power>( dbid );
//            if ( power != null )
//            {
//              string prefix = "_visualInfo-";
//              ConvertText( dbid, power.visualInfo, "Name", "nameText", prefix );
//              ConvertText( dbid, power.visualInfo, "Description", "descText", prefix );
//            }
//          }

//          if (type == typeof( Enchant ))
//          {
//            var enchant = GetObject<Enchant>( dbid );
//            if ( enchant != null )
//            {
//              string prefix = "_visualInfo-";
//              ConvertText( dbid, enchant.visualInfo, "Name", "nameText", prefix );
//              ConvertText( dbid, enchant.visualInfo, "Description", "descText", prefix );
//            }
//          }

//          if (type == typeof( Spell ))
//          {
//            var spell = GetObject<Spell>( dbid );
//            if ( spell != null )
//            {
//              string prefix = "_visualInfo-";
//              ConvertText( dbid, spell.visualInfo, "Name", "nameText", prefix );
//              ConvertText( dbid, spell.visualInfo, "Description", "descText", prefix );
//            }
//          }

//          var cutScene = GetObject<CutScene>( dbid );
//          if ( cutScene != null )
//          {
//            int count = cutScene.subtitles.Count;
//            for (int i = 0; i < count; ++i)
//            {
//              string prefix = "_subtitles(" + i.ToString() + ")-";
//              ConvertText( dbid, cutScene.subtitles[i], "text", "subtitleText", prefix );
//            }
//          }

//          if ( type == typeof( Creature ) )
//          {
//            var cr = GetObject<Creature>( dbid );
//            if ( cr != null )
//            {
//              ConvertText( dbid, cr, "creatureName", "nameText" );
//              ConvertText( dbid, cr, "creatureDesc", "descText" );
//            }
//          }

//          if ( type == typeof( CreatureAbility ) )
//          {
//            var crAbility = GetObject<CreatureAbility>( dbid );
//            if ( crAbility != null )
//            {
//              ConvertText( dbid, crAbility, "abilityName", "nameText" );
//              ConvertText( dbid, crAbility, "abilityDesc", "descText" );
//            }
//          }

//          if ( type == typeof( CreatureUpgrade ) )
//          {
//            var crUpgrade = GetObject<CreatureUpgrade>( dbid );
//            if ( crUpgrade != null )
//            {
//              ConvertText( dbid, crUpgrade, "description", "nameText" );
//              ConvertText( dbid, crUpgrade, "creatureDesc", "descText" );
//            }
//          }

//          if ( type == typeof( Monster ) )
//          {
//            var monster = GetObject<Monster>( dbid );
//            if ( monster != null )
//            {
//              ConvertText( dbid, monster, "visitMessage", "nameText" );
//            }
//          }

//          if ( type == typeof( Teleport ) )
//          {
//            var teleport = GetObject<Teleport>( dbid );
//            if ( teleport != null )
//            {
//              ConvertText( dbid, teleport, "visitMessage", "nameText" );
//              ConvertText( dbid, teleport, "visitDisabledMessage", "nameDisabledText" );
//            }
//          }

//          if ( type == typeof( AdvMap ) )
//          {
//            var advMap = GetObject<AdvMap>( dbid );
//            if ( advMap != null )
//            {
//              ConvertText( dbid, advMap, "mapName", "mapNameText" );
//              ConvertText( dbid, advMap, "mapDescription", "mapDescriptionText" );

//              int count = advMap.Objectives.playerSpecific.Count;
//              for ( int i = 0; i < count; ++i )
//              {
//                string prefix1 = "_Objectives-playerSpecific(" + i.ToString() + ")-";

//                int count2 = advMap.Objectives.playerSpecific[i].objectives.Count;
//                for ( int j = 0; j < count2; ++j )
//                {
//                  string prefix2 = prefix1 + "objectives(" + j.ToString() + ")-";

//                  ConvertText( dbid, advMap.Objectives.playerSpecific[i].objectives[j], "Name", "nameText", prefix2 );
//                  ConvertText( dbid, advMap.Objectives.playerSpecific[i].objectives[j], "Description", "descText", prefix2 );

//                  int count3 = advMap.Objectives.playerSpecific[i].objectives[j].WaysToComplete.Count;
//                  for ( int k = 0; k < count3; ++k )
//                  {
//                    // ConvertText( dbid, advMap.Objectives.playerSpecific[i].objectives[j].WaysToComplete[k], "WaysToComplete[" + k.ToString() + "]", "waysToCompleteTexts(" + k.ToString() + ")", prefix2 );
//                  }
//                }
//              }

//              count = advMap.NPCActions.Count;
//              for ( int i = 0; i < count; ++i )
//              {
//                string prefix = "_NPCActions(" + i.ToString() + ")-";

//                ConvertText( dbid, advMap.NPCActions[i], "buttonText", "nameText", prefix );
//                ConvertText( dbid, advMap.NPCActions[i], "description", "descText", prefix );
//              }

//              count = advMap.ScriptMessageBoxes.Count;
//              for ( int i = 0; i < count; ++i )
//              {
//                string prefix = "_ScriptMessageBoxes(" + i.ToString() + ")-";

//                ConvertText( dbid, advMap.ScriptMessageBoxes[i], "text", "descText", prefix );
//              }
//            }
//          }

//        }
//      }

//      Log.TraceMessage( "--> {0} objects processed", objectsCount );

//      libdb.DB.DataBase.Store();
//      application.Application.FileSystem.Store();

//      Log.TraceMessage( "" );
//      Log.TraceMessage( "--> Finished" );
//      System.Console.ReadKey( true );
//    }
//  }
//}
