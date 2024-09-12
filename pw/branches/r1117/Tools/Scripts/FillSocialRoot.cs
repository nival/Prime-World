
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

public class FillSocialRoot
{
	 private const string SocialRootHRef = "/Social.ROOT";
    private const string TalentsCollectingRoot = "/Items/";
    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
      bool saveDB = false;

      foreach (string parametr in parameters)
      {
        saveDB = saveDB || parametr == "save";
      }
      SocialRoot root = DataBase.Get<SocialRoot>( DBID.FromFileName( SocialRootHRef, false ) );
      List<DBID> dbids = new List<DBID>();
      Log.TraceMessage( "Clearing Talents list in {0}", SocialRootHRef );
      root.Talents.Clear();
      Log.TraceMessage("Talents list cleared");
      Log.TraceMessage("Collecting talents...");
      ObjectsSelector.CollectObjects(app, TalentsCollectingRoot, typeof(Talent), true, true, out dbids);
      Log.TraceMessage("{0} founded. Processing...", dbids.Count);
      foreach (DBID dbid in dbids)
      {
        Log.TraceMessage("Processing {0}...", dbid.ToString());
        Talent r = DataBase.Get<Talent>(dbid).Get();
        if (System.String.IsNullOrEmpty(r.persistentId))
        {
          Log.TraceWarning("Skipping talent {0} because persistentId is empty", dbid.ToString());
          continue;
        }
        root.Talents.Add(new DBPtr<Talent>(r.DBId, r));
        Log.TraceMessage("Talent {0} ({1}) added", r.persistentId, dbid.ToString());
      }

      if (saveDB)
      {
        Log.TraceMessage( "Saving {0}...", SocialRootHRef );
        DataBase.Store();
        Log.TraceMessage("Successfully saved");
      }

      yield return true;
    }
  }

