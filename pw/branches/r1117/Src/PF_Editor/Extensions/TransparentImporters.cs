using System;
using System.Collections.Generic;
using System.Text;
using EditorLib;
using EditorLib.Operations;
using libdb;
using libdb.DB;
using DBTypes;
using EditorLib.Extensions;

namespace PF_Editor
{
  sealed class HierImport
  {
    public List<DBPtrBase> resources = new List<DBPtrBase>();
    public bool Functor(ref DBPtrBase obj)
    {
      if (obj.IsValid)//  DBId.IsInlined) 
        resources.Add(obj);
      return true; 
    }
  }
  [ApplicableForDeriverAttribute]
  public sealed class DBUnitImporter : Importer<DBTypes.Unit>
  {
    static public void ImportInlinesStructs(IOperationContext context, libdb.DB.DBResource resource, IEditorCommonApplication application, bool fast)
    {
      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All);
      HierImport importList = new HierImport();
      FieldsWalker.VisitFields<DBPtrBase>(resource, importList.Functor, depthController.Functor);

      foreach (DBPtrBase res in importList.resources)
      {
        if (application.Extensions.HasImporter(DataBase.Get<DBResource>(res.DBId).Get().GetType()))
        {
          IImporter importer = application.Extensions.CreateImporter(res.DBId, application, fast);
          if(importer != null)
          {
            Type impT = importer.GetType();
            if (impT == typeof(DBUnitImporter) || impT == typeof(DBSpellImporter) || impT == typeof(DBBaseApplicatorImporter))
            {
              importer.Import(context);
            }
          }
        }
      }
    }
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(DBPtr<DBTypes.Unit> resource, IEditorCommonApplication application, bool fast) { DBUnitImporter.ImportInlinesStructs(this.Context, resource, application, fast); return true; }
  }
  [ApplicableForDeriverAttribute]
  public sealed class DBSpellImporter : Importer<DBTypes.Spell>
  {
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(DBPtr<DBTypes.Spell> resource, IEditorCommonApplication application, bool fast) { DBUnitImporter.ImportInlinesStructs(this.Context, resource, application, fast); return true; }
  }
  [ApplicableForDeriverAttribute]
  public sealed class DBBaseApplicatorImporter : Importer<DBTypes.BaseApplicator>
  {
    protected override bool KnownDuration { get { return false; } }
    protected override bool Process(DBPtr<DBTypes.BaseApplicator> resource, IEditorCommonApplication application, bool fast) { DBUnitImporter.ImportInlinesStructs(this.Context, resource, application, fast); return true; }
  }
}
