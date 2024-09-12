/*
#about Пописывает все объекты из UI\FontStyles (рекурсивно) в UIRoot
*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using libdb.DB;
using EditorLib.IO;
using DBTypes;
using libdb.Diagnostics;

namespace Scripts
{
  class UpdateFontStylesInUIRoot
  {
    public IEnumerable Main( EditorLib.IEditorCommonApplication application )
    {
      UIRoot uiRoot = DataBase.Get<UIRoot>( DBID.FromFileName( "UI/UIRoot.xdb", false ) );
      if ( null == uiRoot )
      {
        Log.TraceError( "Unable to find UIRoot" );
        yield return true;
      }

      List<DBID> items;
      ObjectsSelector.CollectObjects( application, "/UI/FontStyles/", typeof( UIFontStyle ), true, true, out items );

      int counter = 0;
      int counterNew = 0;

      List<DBPtr<UIFontStyle>> fontsToAdd = new List<DBPtr<UIFontStyle>>();
      List<int> indicesOfInvalid = new List<int>();

      for ( int i = 0; i < uiRoot.fontStyles.Count; ++i )
      {
        if ( !uiRoot.fontStyles[i].IsValid )
        {
          indicesOfInvalid.Add( i );
          continue;
        }

        var obj = uiRoot.fontStyles[i].Get();
        if ( null == obj )
        {
          indicesOfInvalid.Add( i );
          continue;
        }
      }

      Log.TraceMessage( "Removing {0} invalid entries", indicesOfInvalid.Count );

      for ( int i = indicesOfInvalid.Count - 1; i >= 0; --i )
      {
        uiRoot.fontStyles.RemoveAt( indicesOfInvalid[i] );
      }

      foreach ( var dbId in items )
      {
        DBPtr<UIFontStyle> objPtr = DataBase.Get<UIFontStyle>( dbId );
        var obj = objPtr.Get();

        if ( ReferenceEquals( obj, null ) )
          continue;

        bool found = false;
        foreach ( var rootListItem in uiRoot.fontStyles )
        {
          UIFontStyle rStyle = rootListItem.Get();
          if ( rStyle != null && rStyle.DBId == dbId )
          {
            found = true;
            break;
          }
        }

        if ( !found )
        {
          fontsToAdd.Add( objPtr );
          ++counterNew;
        }

        ++counter;
      }

      foreach ( var ptrNew in fontsToAdd )
      {
        uiRoot.fontStyles.Add( ptrNew );
      }

      Log.TraceMessage( "Done: {0} obejcts, {1} new", counter, counterNew );

      yield return true;
    }
  }
}
