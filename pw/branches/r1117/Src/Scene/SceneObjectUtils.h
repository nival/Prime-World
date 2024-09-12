#pragma once

#include "../Render/RenderComponent.h"

namespace Render
{
	class BaseMaterial;
}

namespace NScene
{

_interface IScene;
class SceneObject;

struct MaterialUpdater : public Render::IMaterialProcessor
{
  float dt;

  MaterialUpdater(float dt_) : dt(dt_) {}
  virtual void operator()(Render::BaseMaterial &material);
};

struct MaterialColorChanger : public Render::IMaterialProcessor, public NonCopyable
{
	Render::HDRColor mul;
	Render::HDRColor add;

	MaterialColorChanger(const Render::HDRColor &mul_, const Render::HDRColor &add_) : mul(mul_), add(add_) {}
	virtual void operator()(Render::BaseMaterial &material);
};

struct MaterialColorAndOpacityChanger : public MaterialColorChanger
{
  bool specialTransparency;
	MaterialColorAndOpacityChanger(const Render::HDRColor &mul_, const Render::HDRColor &add_) : MaterialColorChanger(mul_, add_), specialTransparency(false) {}
	virtual void operator()(Render::BaseMaterial &material);
};

struct MaterialColorAndOpacityChangerWithBlend : public Render::IMaterialProcessor, public NonCopyable
{
  Render::HDRColor mul;
  Render::HDRColor add;
  NDb::BlendMode blendMode;
  bool specialTransparency;
  bool isSetDefaultBlendMode;

  MaterialColorAndOpacityChangerWithBlend(const Render::HDRColor &mul_, const Render::HDRColor &add_, 
    NDb::BlendMode blendMode, bool isSetDefaultBlendMode) 
  : mul(mul_), add(add_), blendMode(blendMode), specialTransparency(false), 
    isSetDefaultBlendMode(isSetDefaultBlendMode) {}
  virtual void operator()(Render::BaseMaterial &material);
};



struct MaterialPriorityChanger : public Render::IMaterialProcessor
{
	int priority;
	MaterialPriorityChanger(int pr) : priority(pr) {}
	virtual void operator()(Render::BaseMaterial &material);
};

// Basic functions
void ForAllMaterials(SceneObject &object, Render::IMaterialProcessor &proc);
void ForAllComponentMaterials(SceneObject &object, const nstl::string &_componentID, Render::IMaterialProcessor &proc);

// Derived functions
void ModifySceneObjectColors(SceneObject &object, const Render::HDRColor &_multiplier, const Render::HDRColor &add);
void ModifySceneComponentColors(SceneObject &_object, const nstl::string &_componentID, 
                                const Render::HDRColor &_multiplier, const Render::HDRColor &add);
void ModifySceneObjectOpacity(SceneObject &object, float opacity);

}
