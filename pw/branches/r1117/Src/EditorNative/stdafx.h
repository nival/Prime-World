// stdafx.h
#pragma once

struct _TP_CLEANUP_GROUP{};     // define structure from winnt.h to prevent C4339 warning
struct _TP_POOL{};              // define structure from winnt.h to prevent C4339 warning
struct _TP_CALLBACK_INSTANCE{}; // define structure from winnt.h to prevent C4339 warning
struct _ACTIVATION_CONTEXT{};   // define structure from winnt.h to prevent C4339 warning

struct FMOD_SYSTEM{};           // define structure from fmod.h to prevent C4339 warning
struct FMOD_EVENTSYSTEM{};      // define structure from fmod.h to prevent C4339 warning

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cmath>

#include "../System/systemStdAfx.h"
#include "../System/FileSystem/WinFileSystem.h"
#include "../System/ProfileManager.h"
#include "../System/StrProc.h"
#include "../System/DebugVar.h"

#include "../libdb/stdafx.h"
#include "../libdb/Db.h"
#include "../libdb/XmlSaver.h"
#include "../libdb/DbResourceCache.h"
#include "../libdb/IDbTypesRegistrator.h"

#include "../Scene/stdafx.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Scene/EditorSceneObject.h"
#include "../Scene/AnimSequencer.h"
#include "../Scene/GeometryBuilders.h"
#include "../Scene/DBScene.h"
#include "../Scene/CollisionMap.h"
#include "../Scene/Camera.h"
#include "../Scene/CollisionHull.h"
#include "../Scene/CollisionVolumeNode.h"

#include "../Terrain/TerrainLayerManager.h"
#include "../Terrain/TerrainGeometryManager.h"
#include "../Terrain/BezierSurface.h"
#include "../Terrain/DBTerrain.h"
#include "../Terrain/Terrain.h"

#include "../Render/stdafx.h"
#include "../Render/RenderInterface.h"
#include "../Render/UiRenderer.h"
#include "../Render/DebugRenderer.h"
#include "../Render/MaterialResourceInterface.h"
#include "../Render/renderresourcemanager.h"
#include "../Render/SkeletalMesh.h"

#include "../UI/stdafx.h"

#include "../Sound/SoundScene.h"

#include "Vendor/fmod/api/inc/fmod.hpp"
#include "Vendor/fmod/fmoddesignerapi/api/inc/fmod_event.hpp"
