using EditorNative;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class TcvChangeLocationOperation : TcvChangeOperation
	{
		private readonly Vector3 prevLocation;
		private readonly Vector3 newLocation;

		internal TcvChangeLocationOperation(
			TerrainController terrainController,
			int markerX,
			int markerY,
			Vector3 prevLocation,
			Vector3 newLocation
			)
			: base( terrainController, markerX, markerY )
		{
			this.prevLocation = prevLocation;
			this.newLocation = newLocation;
		}

		protected override void Undo( ControlableTcvMarker marker )
		{
			marker.Location = prevLocation;
		}

		protected override void Redo( ControlableTcvMarker marker )
		{
			marker.Location = newLocation;
		}
	}
}
