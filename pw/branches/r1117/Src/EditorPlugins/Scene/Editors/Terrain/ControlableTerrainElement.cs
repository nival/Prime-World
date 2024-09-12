using System;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.Terrain;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class ControlableTerrainElement
		: TerrainElement,
			IObjectTransformController,
			IController<DBTypes.TerrainElementInstance>
	{
		private DBTypes.TerrainElementInstance instance;
		private Quaternion tempRotation = Quaternion.Identity;

		internal ControlableTerrainElement( DBTypes.TerrainElementInstance instance )
			: base(
					new Vector3( instance.position.x, instance.position.y, instance.position.z ),
					instance.angle,
					instance.terrainObject.DBId
					)
		{
			this.instance = instance;
			instance.angle_Changed += OnAngleChanged;
			instance.terrainObject_Changed += OnTerrainObjectChanged;
		}

		public void Unsubscribe()
		{
			instance.angle_Changed -= OnAngleChanged;
			instance.terrainObject_Changed -= OnTerrainObjectChanged;
		}

		private void OnAngleChanged( object sender, EventArgs e )
		{
			Angle = instance.angle;
		}

		private void OnTerrainObjectChanged( object sender, EventArgs e )
		{
			SetMeshId( instance.terrainObject.DBId );
		}

		public DBTypes.TerrainElementInstance Resource
		{
			get { return instance; }
		}

		#region IObjectTransformController Members

		Vector3 IObjectTransformController.Location
		{
			get { return base.Location; }
			set { base.Location = Location = value; }
		}

		Quaternion IObjectTransformController.Rotation
		{
			get { return tempRotation; }
			set
			{
				tempRotation = value;
				bool dummy;
				instance.angle = Utility.CalculateDiscreetAngle( tempRotation, out dummy ) * (float)(180 / Math.PI);
			}
		}

	  Vector3 IObjectTransformController.Scale
		{
			get { return Vector3.Ones; }
			set { }
		}

		TransformParameters IObjectTransformController.MovingX
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.MovingY
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.MovingZ
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.RotationPitch
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.RotationRoll
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.RotationYaw
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.ScalingX
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.ScalingY
		{
			get { return TransformParameters.Disabled; }
		}

		TransformParameters IObjectTransformController.ScalingZ
		{
			get { return TransformParameters.Disabled; }
		}

    bool IObjectTransformController.IsCommonCenter { get; set; }

		#endregion
	}
}
