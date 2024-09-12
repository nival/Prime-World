// stdafx.h
#pragma once

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
#include "../EditorNative/stdafx.h"
