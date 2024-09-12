/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using System.Text;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;

public class GetAllResources
{
  private IEditorCommonApplication application;
  
  public IEnumerable Main(EditorLib.IEditorCommonApplication application)
  {
    this.application = application;
    this.application.OperationExecutor.Start(Work);

    yield return true;
  }

  private bool Work(IOperationContext context)
  {
    context.Start(false, false);
    var dbids = new List<DBID>();
    ObjectsSelector.CollectObjects(null, "/", typeof(DBResource), true, true, out dbids);
    dbids.ForEach(d => Log.TraceMessage("{0}, hashcode = {1}, crc32 = {2}",
                                        d.Name, d.GetHashCode(), (int)Crc32ChecksumGenerator.GenerateChecksum(Encoding.ASCII.GetBytes(d.Name)) ));
    return true;
  }
}
