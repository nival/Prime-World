using EditorNative;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class TcvChangeRotationOperation : TcvChangeOperation
	{
		private readonly Quaternion prevRotation;
		private readonly Quaternion newRotation;

		internal TcvChangeRotationOperation(
			TerrainController terrainController,
			int markerX,
			int markerY,
			Quaternion prevRotation,
			Quaternion newRotation
			)
			: base( terrainController, markerX, markerY )
		{
			this.prevRotation = prevRotation;
			this.newRotation = newRotation;
		}

		protected override void Undo( ControlableTcvMarker marker )
		{
			marker.Rotation = prevRotation;
		}

		protected override void Redo( ControlableTcvMarker marker )
		{
			marker.Rotation = newRotation;
		}
	}
}
