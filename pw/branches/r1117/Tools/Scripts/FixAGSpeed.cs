/*
#about Скрипт проходится по всем объектам, и собирает наследников DBSceneResource. После чего, анализирует список attached и для всех элементов добавляет флаг UseAGSpeedCoeff в attachFlags.
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using libdb.DB;

namespace Scripts
{
  public class FixAGSpeed
  {
    public IEnumerable Main( EditorLib.IEditorWinApplication app )
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects( app.Application, "/", typeof( DBSceneResource ), true, true, out dbids );
      foreach ( DBID dbid in dbids )
      {
        DBSceneResource obj = DataBase.Get<DBSceneResource>( dbid ).Get();
        foreach ( var attach in obj.attached )
        {
          attach.attachFlags |= EAttachFlags.UseAGSpeedCoeff;
        }
      }

      DataBase.Store();

      yield return true;
    }
  }
}
