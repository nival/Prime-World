using System;
using libdb.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.IO;

namespace EditorPlugins.Importer.Mesh
{
	public sealed class DBWaterSceneComponentImporter : Importer<DBTypes.DBWaterSceneComponent>
	{
		protected override bool KnownDuration { get { return false; } }

		private static bool ImportWaterSpecifics(DBTypes.DBWaterSceneComponent water, float[] aabbs)
		{
			// check materials
			if (water.materialsReferences.Count != 1 || !(water.materialsReferences[0].Get() is DBTypes.WaterMaterial))
			{
				Log.TraceError("DBWaterSceneComponent must reference one and only one WaterMaterial in \"{0}\"", water.DBId.Name);
				return false;
			}

			// check mesh bounds
			if ( water.aabb.minZ != water.aabb.maxZ )
			{
				Log.TraceWarning("Water mesh is not planar (within DBWaterSceneComponent \"{0}\" )", water.DBId.Name);
			}

			// save water level
			water.waterLevel = water.aabb.minZ;
			return true;
		}

		protected override bool Process(DBPtr<DBTypes.DBWaterSceneComponent> resource, IEditorCommonApplication application, bool fast)
		{
			if (!fast)
			{
				if (!DBStaticSceneComponentImporter.ImportMayaToIntermediate(resource, application))
					return false;
			}

			float[] aabbs = null;
			if (!DBStaticSceneComponentImporter.ImportIntermediateToBin(resource, application, out aabbs))
				return false;

			return ImportWaterSpecifics(resource, aabbs);
		}
	}

}
