using EditorNative;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class TcvChangeScaleOperation : TcvChangeOperation
	{
		private readonly Vector3 prevScale;
		private readonly Vector3 newScale;

		internal TcvChangeScaleOperation(
			TerrainController terrainController,
			int markerX,
			int markerY,
			Vector3 prevScale,
			Vector3 newScale
			)
			: base( terrainController, markerX, markerY )
		{
			this.prevScale = prevScale;
			this.newScale = newScale;
		}

		protected override void Undo( ControlableTcvMarker marker )
		{
			marker.Scale = prevScale;
		}

		protected override void Redo( ControlableTcvMarker marker )
		{
			marker.Scale = newScale;
		}
	}
}
