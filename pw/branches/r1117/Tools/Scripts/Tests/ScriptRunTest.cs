/*
 *  Скрипт запускает импорт некоторого ресурса.
 * 
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_EditorNative.dll
#ref PF_Editor.exe
*/

using System;
using System.IO;
using System.Collections;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.Diagnostics;
using EditorLib.Wizards;
using System.Windows.Forms;
using EditorNative;

namespace Scripts
{
  public class ScriptRunTest
  {
    public IEnumerable Main(EditorLib.IEditorWinApplication app)
    {
      string logFileName = "EditorTest.log";
      if (File.Exists(logFileName))
      {
        File.Delete(logFileName);
      }

      var fileDumper = new FileDumper(logFileName);
      Log.AttachDumper(fileDumper);
      OpenMapTest(app);
      ImportTest(app);

      //app.Application.Scripts.LoadScript("ImportTest.cs"); // Выполняем тест ImportTest1.cs
      //app.Application.Scripts.LoadScript("OpenMapTest.cs"); // Выполняем тест OpenMapTest.cs

      Log.DetachDumper(fileDumper);

      yield return true;
    }

    private void OpenMapTest(EditorLib.IEditorWinApplication app)
    {
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
    }

    private void ImportTest(EditorLib.IEditorWinApplication app)
    {
      Log.TraceMessage("ImportTest started");

      string importPath = "Primitives/Cube/_.SGEO";                        // Путь до импортируемого объекта (Data/...)
      DBID id = DBID.FromFileName(importPath, false);

      IImporter importer = app.Application.Extensions.CreateImporter(id, app.Application, false);

      importer.Import(null);                                         // Запускаем импорт объекта
      DataBase.Store();

      Log.TraceMessage("ImportTest finished");
    }
  }
}