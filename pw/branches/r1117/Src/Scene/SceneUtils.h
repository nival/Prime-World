#pragma once

namespace NScene
{

_interface IScene;

void EnableEffectsInScene( IScene* _scene, bool _enable );
void EnableEffectsInObject( SceneObject* so, bool _enable );

}
