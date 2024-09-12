using System;
using System.Collections.Generic;
using System.Text;
using libdb.UndoRedo;
using EditorNative;
using libdb.DB;

namespace EditorPlugins.Scene.Editors.Terrain
{
  class NatureMapChangeOperation : IUndoRedoOperation
  {
		private readonly TerrainController terrain;
    private readonly EditorScene scene;
		private readonly int[] elementIds;
    private readonly int fromFaction;
		private readonly int newFaction;
    private int[] oldFactions;

    internal NatureMapChangeOperation(
			TerrainController terrain,
      EditorScene scene,
      int[] elementIds,
      int fromFaction,
      int newFaction
      )
    {
      this.terrain = terrain;
      this.scene = scene;
      this.elementIds = elementIds;
      this.fromFaction = fromFaction;
      this.newFaction = newFaction;
      this.oldFactions = new int[elementIds.Length];
    }

    public void Undo()
    {
      for (int i = 0; i < oldFactions.Length; ++i)
      {
        terrain.Terrain.ChangeFraction(elementIds[i], oldFactions[i] );
      }
      terrain.Terrain.StepNatureMap();
      scene.UpdateAllMSO();
    }

    public void Redo()
    {
      for( int i = 0; i < elementIds.Length; ++i )
      {
        int curFaction = terrain.Terrain.GetFraction( elementIds[i] );
        if ( fromFaction >= 0 && curFaction != fromFaction )
          continue;

        oldFactions[i] = curFaction;
        terrain.Terrain.ChangeFraction(elementIds[i], newFaction);
      }
      terrain.Terrain.StepNatureMap();
      scene.UpdateAllMSO();
    }

    public string DefaultCaption { get { return "Change Nature Map"; } }

    public DBResource GetOwner() { return terrain.Resource; }
  }
}
