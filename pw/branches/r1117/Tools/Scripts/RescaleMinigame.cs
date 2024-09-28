/*
#about Рескейл в миниигре
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Drawing;
using DBTypes;
using libdb.DB;
using System.Drawing.Imaging;
using libdb.Diagnostics;

public class RescaleMinigame
{
  public IEnumerable Main(EditorLib.IEditorCommonApplication app)
  {
    FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 10, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All );
    DBPtrBase[] types = FieldsWalker.CollectDBPtrs(DataBase.Get<DBResource>(DBID.FromString("/MiniGames/Minigame02/GameLogic/minigame02")).Get(), depth.Functor);
    foreach (DBPtrBase ptr in types)
    {
      if (ptr == null)
        continue;

      if (!(ptr.Get<DBResource>() is DBEaselPath))
        continue;

      DBEaselPath path = ptr.Get<DBEaselPath>();

      Vec3 translate = path.splineData.endPoint.placement.pos.GetValue(0.0f);
      translate.x = translate.x * 25;
      translate.y = translate.y * 25;
      translate.z = translate.z * 25;
      path.splineData.endPoint.placement.pos.Clear(translate);

//       foreach (var component in sceneObj.attached)
//       {
//         if ( component.placement.scale.Type != libdb.Animated.AnimatedType.None )
//         {
//           Log.TraceMessage("found animated scale");
//           continue;
//         }
//         Vec3 translate = component.placement.pos.GetValue(0.0f);
//         Scale scale = component.placement.scale.GetValue(0.0f);
//         scale.x = scale.x * 5;
//         scale.y = scale.y * 5;
//         scale.z = scale.z * 5;
//         translate.x = translate.x * 5;
//         translate.y = translate.y * 5;
//         translate.z = translate.z * 5;
//         component.placement.scale.Clear( scale );
//         component.placement.pos.Clear(translate);
//       }
    }

    yield return true;
  }
}
