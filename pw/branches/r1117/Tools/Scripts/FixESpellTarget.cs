/*
#about Найти все FixESpellTarget и скорректировать их 
#ref PF_Types.DBTypes.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using libdb.DB;
using libdb.IO;
using libdb.Diagnostics;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using System.Text;
using System.Globalization;
using System.Runtime.InteropServices;

namespace Scripts
{
    public class FixESpellTarget
    {
      public DBResource currentResource;

      public bool IsFieldSuitable(string fieldName)
      {
        if ( currentResource is Ability )
          return ((Ability)currentResource).__parent == null || ((Ability)currentResource).__parent.Get() == null || !((Ability)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is AuraApplicator )
          return ((AuraApplicator)currentResource).__parent == null || ((AuraApplicator)currentResource).__parent.Get() == null || !((AuraApplicator)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is ChainLightningApplicator )
          return ((ChainLightningApplicator)currentResource).__parent == null || ((ChainLightningApplicator)currentResource).__parent.Get() == null || !((ChainLightningApplicator)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is MainBuilding )
          return ((MainBuilding)currentResource).__parent == null || ((MainBuilding)currentResource).__parent.Get() == null || !((MainBuilding)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EvtEnemyDanger )
          return ((EvtEnemyDanger)currentResource).__parent == null || ((EvtEnemyDanger)currentResource).__parent.Get() == null || !((EvtEnemyDanger)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EvtUnitsInRange )
          return ((EvtUnitsInRange)currentResource).__parent == null || ((EvtUnitsInRange)currentResource).__parent.Get() == null || !((EvtUnitsInRange)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EvtAttackedByUnits )
          return ((EvtAttackedByUnits)currentResource).__parent == null || ((EvtAttackedByUnits)currentResource).__parent.Get() == null || !((EvtAttackedByUnits)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is MultipleTargetSelectorFiltered )
          return ((MultipleTargetSelectorFiltered)currentResource).__parent == null || ((MultipleTargetSelectorFiltered)currentResource).__parent.Get() == null || !((MultipleTargetSelectorFiltered)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EventProcessorDamageTransformer )
          return ((EventProcessorDamageTransformer)currentResource).__parent == null || ((EventProcessorDamageTransformer)currentResource).__parent.Get() == null || !((EventProcessorDamageTransformer)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EventProcessorOnDeath )
          return ((EventProcessorOnDeath)currentResource).__parent == null || ((EventProcessorOnDeath)currentResource).__parent.Get() == null || !((EventProcessorOnDeath)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is EventProcessorUnitDieNearMe )
          return ((EventProcessorUnitDieNearMe)currentResource).__parent == null || ((EventProcessorUnitDieNearMe)currentResource).__parent.Get() == null || !((EventProcessorUnitDieNearMe)currentResource).IsFieldDerivedFromParent(fieldName);
        else if ( currentResource is SummonApplicator )
          return ( (SummonApplicator)currentResource ).__parent == null || ( (SummonApplicator)currentResource ).__parent.Get() == null || !( (SummonApplicator)currentResource ).IsFieldDerivedFromParent( fieldName );
        else if ( currentResource is CloneHeroApplicator )
          return ( (CloneHeroApplicator)currentResource ).__parent == null || ( (CloneHeroApplicator)currentResource ).__parent.Get() == null || !( (CloneHeroApplicator)currentResource ).IsFieldDerivedFromParent( fieldName );
        return false;
      }

      public bool VisitorFunctor(ref object obj, DBFieldInfo field)
      {
        ESpellTarget st = obj as ESpellTarget;

        if ( st != null && IsFieldSuitable(field.Name))
        {
          if ( ( st & ESpellTarget.NeutralChampion ) == ESpellTarget.NeutralChampion
          && ( ( st & ESpellTarget.HeroMale ) == ESpellTarget.HeroMale || ( st & ESpellTarget.Creep ) == ESpellTarget.Creep ) )
          {
            st |= ESpellTarget.FactionChampion;
          }
          obj = st;
        }
          //else
            //Log.TraceMessage("{0} {1} {2}", currentResource.DBId.GetFullFileName(), currentResource.DBId.Id, field.Name);

        return true;
      }

        public IEnumerable Main( EditorLib.IEditorCommonApplication application )
        {
            Dictionary<Type, List<DBID>> items;
            Type[] types = new[]
            {
             typeof (Ability), 
             typeof (AuraApplicator), 
             typeof (ChainLightningApplicator),
             typeof (MainBuilding),
             typeof (EvtEnemyDanger),
             typeof (EvtUnitsInRange),
             typeof (EvtAttackedByUnits),
             typeof (MultipleTargetSelectorFiltered),
             typeof (EventProcessorDamageTransformer),
             typeof (EventProcessorOnDeath),
             typeof (EventProcessorUnitDieNearMe),
             typeof (SummonApplicator),
             typeof (CloneHeroApplicator),
            };
            DateTime start = DateTime.Now;
            {
                Log.TraceMessage("Loading database... ");
                ObjectsSelector.CollectObjects(application, "", types, true, true, out items);
            }

            DateTime logTime = DateTime.Now + TimeSpan.FromSeconds(1.0);
            Log.TraceMessage("Fixing ESpellTarget...");

            DataBase.UndoRedoManager.Start("Fix creepType");

            foreach (Type type in items.Keys)
            {
              foreach (DBID dbid in items[type])
              {
                currentResource = DataBase.Get<DBResource>(dbid).Get();
                if ((currentResource is Ability) && (((Ability)currentResource).__parent != null) && (((Ability)currentResource).__parent.Get() != null) && ((Ability)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is AuraApplicator) && (((AuraApplicator)currentResource).__parent != null) && (((AuraApplicator)currentResource).__parent.Get() != null) && ((AuraApplicator)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is ChainLightningApplicator) && (((ChainLightningApplicator)currentResource).__parent != null) && (((ChainLightningApplicator)currentResource).__parent.Get() != null) && ((ChainLightningApplicator)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is MainBuilding) && (((MainBuilding)currentResource).__parent != null) && (((MainBuilding)currentResource).__parent.Get() != null) && ((MainBuilding)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EvtEnemyDanger) && (((EvtEnemyDanger)currentResource).__parent != null) && (((EvtEnemyDanger)currentResource).__parent.Get() != null) && ((EvtEnemyDanger)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EvtUnitsInRange) && (((EvtUnitsInRange)currentResource).__parent != null) && (((EvtUnitsInRange)currentResource).__parent.Get() != null) && ((EvtUnitsInRange)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EvtAttackedByUnits) && (((EvtAttackedByUnits)currentResource).__parent != null) && (((EvtAttackedByUnits)currentResource).__parent.Get() != null) && ((EvtAttackedByUnits)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is MultipleTargetSelectorFiltered) && (((MultipleTargetSelectorFiltered)currentResource).__parent != null) && (((MultipleTargetSelectorFiltered)currentResource).__parent.Get() != null) && ((MultipleTargetSelectorFiltered)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EventProcessorDamageTransformer) && (((EventProcessorDamageTransformer)currentResource).__parent != null) && (((EventProcessorDamageTransformer)currentResource).__parent.Get() != null) && ((EventProcessorDamageTransformer)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EventProcessorOnDeath) && (((EventProcessorOnDeath)currentResource).__parent != null) && (((EventProcessorOnDeath)currentResource).__parent.Get() != null) && ((EventProcessorOnDeath)currentResource).IsDerivedFromParent())
                  continue;
                if ((currentResource is EventProcessorUnitDieNearMe) && (((EventProcessorUnitDieNearMe)currentResource).__parent != null) && (((EventProcessorUnitDieNearMe)currentResource).__parent.Get() != null) && ((EventProcessorUnitDieNearMe)currentResource).IsDerivedFromParent())
                  continue;
                if ( ( currentResource is SummonApplicator ) && ( ( (SummonApplicator)currentResource ).__parent != null ) && ( ( (SummonApplicator)currentResource ).__parent.Get() != null ) && ( (SummonApplicator)currentResource ).IsDerivedFromParent() )
                  continue;
                if ( ( currentResource is CloneHeroApplicator ) && ( ( (CloneHeroApplicator)currentResource ).__parent != null ) && ( ( (CloneHeroApplicator)currentResource ).__parent.Get() != null ) && ( (CloneHeroApplicator)currentResource ).IsDerivedFromParent() )
                  continue;

                FieldsWalker.DepthController depth = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.None, FieldsWalker.ObjectType.None);
                FieldsWalker.VisitFields(currentResource, VisitorFunctor, depth.Functor);

                /*var resource = DataBase.Get<DBResource>(dbId).Get();
                FieldsWalker.DepthController depth = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All);
                DBPtrBase[] ptrs = FieldsWalker.CollectDBPtrs(resource, depth.Functor);
                foreach (DBPtrBase ptr in ptrs)
                {
                  currentResource = ptr.Get<DBResource>();

                  /*if ( ptr.DBId.GetFullFileName().Length > 0 )
                    Log.TraceMessage(ptr.DBId.GetFullFileName());

                  FieldsWalker.DepthController depth1 = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.None, FieldsWalker.ObjectType.List | FieldsWalker.ObjectType.Struct);
                  FieldsWalker.VisitFields(currentResource, VisitorFunctor, depth.Functor);
                }*/
              }
            }
            DataBase.UndoRedoManager.Commit();
            Log.TraceMessage("Fixing ESpellTarget finished in {0:F0}s", (DateTime.Now - start).TotalSeconds);

            yield return true;
        }
    }
}
