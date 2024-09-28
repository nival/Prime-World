using System;
using libdb;
using libdb.DB;
using libdb.UndoRedo;
using EditorLib;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal abstract class TcvChangeOperation : IUndoRedoOperation
	{
		private readonly TerrainController terrainController;
		private readonly int markerX;
		private readonly int markerY;

		protected TcvChangeOperation(	TerrainController terrainController, int markerX, int markerY )
		{
			this.terrainController = terrainController;
			this.markerX = markerX;
			this.markerY = markerY;
		}

		protected abstract void Undo( ControlableTcvMarker marker );
		protected abstract void Redo( ControlableTcvMarker marker );

		private void PerformOperation( Operation<ControlableTcvMarker> operation )
		{
			var marker = Array.Find( terrainController.Markers, m => m.MarkerX == markerX && m.MarkerY == markerY );
			if ( !ReferenceEquals( marker, null ) )
			{
				operation( marker );
				terrainController.Terrain.Changed = true;
			}
      terrainController.Terrain.Owner.ReplaceAllObjectsOnTerrain();
		}

		public void Undo()
		{
			PerformOperation( marker => Undo( marker ) );
      terrainController.Terrain.Owner.ReplaceAllObjectsOnTerrain();
    }

		public void Redo()
		{
			PerformOperation( marker=> Redo( marker ) );
      terrainController.Terrain.Owner.ReplaceAllObjectsOnTerrain();
    }

		public string DefaultCaption	{	get { return "Change TCV"; } }

		public DBResource GetOwner() { return terrainController.Resource;	}
	}
}
