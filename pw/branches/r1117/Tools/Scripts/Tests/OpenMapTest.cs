/*
 *  Скрипт открывает редактор некоторого ресурса.
 * 
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_EditorNative.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.Diagnostics;
using EditorNative;

namespace Scripts
{
  public class OpenMapTest
  {
    public IEnumerable Main(EditorLib.IEditorWinApplication app)
    {
      //Log.AttachDumper(new EditorLib.OutputPanel.OutputFileDumper("EditorTest.log"));

      Log.TraceMessage("OpenMapTest started");

      string path = "/Maps/Multiplayer/PFmap/pf.ADMP";        // Путь до открываемого объекта (Data/...)
      DBID id = DBID.FromFileName(path, false);
      AbstractEditor editor = app.Application.Extensions.OpenEditor(id, app, null, false); // Открываем объект

      string screenShotFileNameJpg = "pf.ADMP.jpg";
      EditorRender.DumpScreenShoot(screenShotFileNameJpg);    // Делаем скриншот Jpg

      if (editor != null)
      {
        Log.TraceMessage(String.Format("OpenMapTest finished: {0} is opened successfully, see pf.ADMP.jpg", path));
      }
      else
      {
        Log.TraceError(String.Format("OpenMapTest finished: {0} open is failed", path));
      }
      yield return true;
    }
  }
}