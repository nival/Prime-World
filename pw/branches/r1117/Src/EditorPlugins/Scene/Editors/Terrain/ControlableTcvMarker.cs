using System;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.Terrain;
using libdb.DB;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class ControlableTcvMarker : TcvMarker, IObjectTransformController
	{
		#region Private static members.

		private static readonly TransformParameters rotationParameters = new TransformParameters( (float)( -Math.PI / 4 ), (float)( Math.PI / 4 ) );

		#endregion

		#region Private members.

		private readonly TerrainController terrainController;
		private readonly int markerX;
		private readonly int markerY;

		#endregion

		#region Initialization.

		internal ControlableTcvMarker( TerrainController terrainController, int markerX, int markerY )
			: base( markerY, markerX )
		{
			this.terrainController = terrainController;
			this.markerX = markerX;
			this.markerY = markerY;
		}

		#endregion

		#region Internal methods.

		internal int MarkerX
		{
			get { return markerX; }
		}

		internal int MarkerY
		{
			get { return markerY; }
		}

		#endregion

		#region IObjectTransformController Members

		TransformParameters IObjectTransformController.MovingX
		{
			get { return new TransformParameters( -2 + CalculateLocation( markerX ), 2 + CalculateLocation( markerX ) ); }
		}

		TransformParameters IObjectTransformController.MovingY
		{
			get { return new TransformParameters( -2 + CalculateLocation( markerY ), 2 + CalculateLocation( markerY ) ); }
		}

		TransformParameters IObjectTransformController.MovingZ
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.RotationPitch
		{
			get { return rotationParameters; }
		}

		TransformParameters IObjectTransformController.RotationRoll
		{
			get { return rotationParameters; }
		}

		TransformParameters IObjectTransformController.RotationYaw
		{
			get { return rotationParameters; }
		}

		TransformParameters IObjectTransformController.ScalingX
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.ScalingY
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.ScalingZ
		{
			get { return TransformParameters.FullEnabled; }
		}

		Vector3 IObjectTransformController.Location
		{
			get { return base.Location; }
			set
			{
				DataBase.AddOperation(
					new TcvChangeLocationOperation(
						terrainController,
						markerX,
						markerY,
						Location,
						value
						)
					);
			}
		}

		Quaternion IObjectTransformController.Rotation
		{
			get { return base.Rotation; }
			set
			{
				DataBase.AddOperation(
					new TcvChangeRotationOperation(
						terrainController,
						markerX,
						markerY,
						Rotation,
						value
						)
					);
			}
		}

	  Vector3 IObjectTransformController.Scale
		{
			get { return base.Scale; }
			set
			{
				DataBase.AddOperation(
					new TcvChangeScaleOperation(
						terrainController,
						markerX,
						markerY,
						Scale,
						value
						)
					);
			}
		}

    bool IObjectTransformController.IsCommonCenter { get; set; }

		#endregion

		#region Private helper methods.

		private static float CalculateLocation( int markerIndex )
		{
			return markerIndex * TerrainUtils.PatchSize;
		}

		#endregion
	}
}
