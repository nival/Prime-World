
/*
#about заполнение SocialRoot ссылками на данные
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Xml;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

public class FillQuestSounds
{
    public IEnumerable Main(IEditorCommonApplication app, string[] args)
    {
    string dataPath = args[0];
      string resourcesPrefix = args.Length > 1 ? args[1] : "Tutorial";
      Dictionary<string,string> entries = new Dictionary<string, string>();
      int index = -1;
      List<string> phrasesToDelete = new List<string>();
      Log.TraceDebug( "'{0}' collecting...", dataPath );
      XmlTextReader reader = new XmlTextReader( dataPath );
      while ( reader.Read() )
      {
        switch ( reader.NodeType )
        {
        case XmlNodeType.Element:
          if ( reader.Name == "Entry" )
            index++;

          string phrase = string.Empty;
          string folder = string.Empty;
          string fileName = string.Empty;

          while ( reader.MoveToNextAttribute() )
          {
            if ( reader.Name == "Phrase" )
              phrase = reader.Value;
            if ( reader.Name == "Folder" )
              folder = reader.Value;
            if ( reader.Name == "FileName" )
              fileName = reader.Value;
          }

          if ( !string.IsNullOrEmpty( phrase ) )
          {
            if ( string.IsNullOrEmpty( folder ) || string.IsNullOrEmpty( fileName ) )
            {
              Log.TraceWarning( "Phrase {0}: '{1}' contains empty filename or folder. Skipping", index, phrase );
              break;
            }

            string path = string.Format( "{0}/{1}/{2}", resourcesPrefix, folder, fileName );

            string clrPhrase = GetClearPhrase( phrase );
            if ( string.IsNullOrEmpty( clrPhrase ) )
            {
              Log.TraceWarning( "Phrase {0}: '{1}' empty after braces clear. Skipping", index, phrase );
              break;
            }

            if ( entries.ContainsKey( clrPhrase ) )
            {
              Log.TraceWarning( "Phrase {0}: '{1}' (after clear '{2}') defined more than 1 times. Skipping. Manual editing needed '{3}'", index, phrase, clrPhrase, path );
              phrasesToDelete.Add( clrPhrase );
              break;
            }
            entries.Add( clrPhrase, path );
          }
          break;
        }
      }

      foreach ( var td in phrasesToDelete )
      {
        if ( entries.ContainsKey( td ) )
          entries.Remove( td );
      }

      Log.TraceDebug( "{0} entries collected.", entries.Count );
      Log.TraceDebug( "Collecting dialogs..." );
      List<DBID> dialogs;
      ObjectsSelector.CollectObjects( app, "/Dialog/CastleTutorial", typeof( CastleDialog ), true, false, out dialogs );
      Log.TraceDebug( "{0} dialogs collected.", dialogs.Count );

      List<CastleDialog> castleDialogs = new List<CastleDialog>();
      foreach ( var dialog in dialogs )
      {
        castleDialogs.Add( DataBase.Get<CastleDialog>( dialog ) );
      }

      Log.TraceDebug( "Detecting data collisions..." );
      List<string> stringsCache = new List<string>();
      Dictionary<string,string> phrasesCache = new Dictionary<string, string>();
      Dictionary<string,string> phrasesDups = new Dictionary<string, string>();
      foreach ( var cd in castleDialogs )
      {
        foreach ( var phrase in cd.phrasesA )
        {
          AddCollisionCandidate( phrasesDups, entries, phrasesCache, phrase.textMale.GetText(), string.Format( "\n{0}: {1}", cd.DBId, phrase.caption ) );
          AddCollisionCandidate( phrasesDups, entries, phrasesCache, phrase.textFemale.GetText(), string.Format( "\n{0}: {1}", cd.DBId, phrase.caption ) );
        }

        foreach ( var phrase in cd.phrasesB )
        {
          AddCollisionCandidate( phrasesDups, entries, phrasesCache, phrase.textMale.GetText(), string.Format( "\n{0}: {1}", cd.DBId, phrase.caption ) );
          AddCollisionCandidate( phrasesDups, entries, phrasesCache, phrase.textFemale.GetText(), string.Format( "\n{0}: {1}", cd.DBId, phrase.caption ) );
        }
      }
      Log.TraceDebug( "{0} data collision found", phrasesDups.Count );

      foreach ( var dup in phrasesDups )
      {
        Log.TraceWarning( "Data collision with same text(phrases will be ignored): {0}", dup.Value );
      }

      foreach ( var cd in castleDialogs )
      {
        foreach ( var phrase in cd.phrasesA )
        {
          TryToServePhrase( phrase, cd, entries, phrasesDups );
        }

        foreach ( var phrase in cd.phrasesB )
        {
          TryToServePhrase( phrase, cd, entries, phrasesDups );
        }
      }

      DataBase.Store();
      yield return true;
    }

    private void AddCollisionCandidate( Dictionary<string, string> dups, Dictionary<string, string> entries, Dictionary<string, string> cache, string text, string description )
    {
      if ( entries.ContainsKey( text ) )
      {
        if ( cache.ContainsKey( text ) )
        {
          if ( dups.ContainsKey( text ) )
          {
            dups[text] += description;
          }
          else
            dups.Add( text, cache[text] + description );
        }
        else
          cache.Add( text, description );
      }
    }

    private static void TryToServePhrase( Phrase phrase, CastleDialog cd, Dictionary<string, string> entries, Dictionary<string, string> dups )
    {
      if ( phrase.textMale.GetText() == phrase.textFemale.GetText() )
      {
        Log.TraceWarning( "Skipping. Male and Female texts are the same for {0}: {1}", cd.DBId, phrase.caption );
        return;
      }

      if ( !dups.ContainsKey( phrase.textMale.GetText() ) && entries.ContainsKey( phrase.textMale.GetText() ) )
      {
        phrase.socialSoundMale = entries[phrase.textMale.GetText()];
        Log.TraceDebug( "{0}: {1} socialSoundMale setted to {2}", cd.DBId, phrase.caption, phrase.socialSoundMale );
      }
      if ( !dups.ContainsKey( phrase.textFemale.GetText() ) && entries.ContainsKey( phrase.textFemale.GetText() ) )
      {
        phrase.socialSoundFemale = entries[phrase.textFemale.GetText()];
        Log.TraceDebug( "{0}: {1} socialSoundFemale setted to {2}", cd.DBId, phrase.caption, phrase.socialSoundFemale );
      }
    }
    //private static bool TryToAddElement( List<string> list, string element )
    //{
    //  if ( list.Contains( element ) )
    //  {
    //    Log.TraceWarning( "{0} already added", element );
    //    return false;
    //  }
    //  else
    //  {
    //    list.Add( element );
    //  }
    //  return true;
    //}
    private static string GetClearPhrase( string phrase )
    {
      return Regex.Replace( phrase, @"\(.*?\)", String.Empty );
    }
  }

