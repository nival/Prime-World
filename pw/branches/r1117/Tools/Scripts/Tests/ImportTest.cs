/*
 *  Скрипт запускает импорт некоторого ресурса.
 * 
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_EditorNative.dll
#ref PF_Editor.exe
#ref MayaExeInteraction.dll
*/

using System;
using System.Collections;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.Diagnostics;
using EditorLib.Wizards;
using EditorLib.Operations;

namespace Scripts
{
  public class ImportTest
  {
    public IEnumerable Main(EditorLib.IEditorWinApplication app)
    {
      //Log.AttachDumper(new EditorLib.OutputPanel.OutputFileDumper("EditorTest.log"));

      Log.TraceMessage("ImportTest started");

      string path = "Primitives/Cube/_.SGEO";                        // Путь до импортируемого объекта (Data/...)
      DBID id = DBID.FromFileName(path, false);

      IImporter importer = app.Application.Extensions.CreateImporter(id, app.Application, false);

      importer.Import(null);                                         // Запускаем импорт объекта

      Log.TraceMessage("ImportTest finished");

      DataBase.Store();

      yield return true;
    }
  }
}