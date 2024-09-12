using System;
using System.Collections.Generic;
using System.Text;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

namespace PF_EditorC.Extensions
{
  [CommandName("define_aggro_dispatches", "", "Set dispatches Aggressive flag according to applicators they apply.")]
  class DefineAggressiveDispatches : IConsoleCommand
  {
    [CommandArgumentAttribute("root_path", "rp", "")]
    public string root_path = string.Empty;

    public int Execute(IEditorCommonApplication application, string[] parameters)
    {
      List<DBID> dispatches = new List<DBID>();

      Log.TraceMessage("Collecting dispatches...");

      ObjectsSelector.CollectObjects(application, root_path, typeof(DBTypes.Dispatch), true, true, out dispatches);

      Log.TraceMessage("Updating aggressive dispatches...");

      foreach (var dbid in dispatches)
      {
        var dispatch = DataBase.Get<DBTypes.Dispatch>(dbid).Get();

        if ((dispatch.flags & DBTypes.EDispatchFlags.Upgradable) != 0)
        {
          Log.TraceMessage("{0} [{1}]", dbid.GetFullFileName(), dbid);

          dispatch.flags |= DBTypes.EDispatchFlags.Aggressive;
        }
      }

      Log.TraceMessage("Saving changes...");

      DataBase.Store();

      return 0;
    }
  }
}
