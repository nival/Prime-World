#include "stdafx.h"
#include "SceneObject.h"
#include "Scene.hpp"

#include "SceneObjectUtils.h"

using namespace Render;

namespace NScene
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialUpdater::operator()(BaseMaterial &_material)
{
  Render::BaseMaterial* material = _material.GetAlternativeMaterial() ? static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial()) : &_material;

  if (material->Need2CallUpdate())
    material->Update(dt); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialColorChanger::operator()(Render::BaseMaterial &_material)
{
  Render::BaseMaterial* material = _material.GetAlternativeMaterial() ? static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial()) : &_material;

  material->ModifyColor(mul, add);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialColorAndOpacityChanger::operator()(Render::BaseMaterial &_material)
{
	MaterialColorChanger::operator()(_material);

  Render::BaseMaterial* material = _material.GetAlternativeMaterial() ? static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial()) : &_material;

  if (mul.A < 1.0f)
    material->SetSpecialTransparency(specialTransparency);
	material->ModifyOpacity(mul.A);
}

void MaterialColorAndOpacityChangerWithBlend::operator()( Render::BaseMaterial &_material )
{
  Render::BaseMaterial* material = &_material;
  if(_material.GetAlternativeMaterial())
  {
    material = static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial());
  }

  material->ModifyColor(mul, add);
  if (mul.A < 1.0f)
    material->SetSpecialTransparency(specialTransparency);
  material->ModifyOpacity(mul.A);
  if(1.0f != mul.A)
    material->ModifyBlendMode(blendMode, isSetDefaultBlendMode);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialPriorityChanger::operator()(Render::BaseMaterial &_material)
{
  Render::BaseMaterial* material = _material.GetAlternativeMaterial() ? static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial()) : &_material;

	material->SetPriority(priority);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForAllMaterials(SceneObject &object, IMaterialProcessor &proc)
{
	struct Func : public FullTraverser, NonCopyable
	{
		IMaterialProcessor &proc;
		Func(IMaterialProcessor &f) : proc(f) {}
		void operator()(SceneComponent *pSC)
		{
			pSC->ForAllMaterials(proc);
		}
	} func(proc);

  object.Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForAllComponentMaterials(SceneObject &object, const nstl::string &_componentID, Render::IMaterialProcessor &proc)
{
  struct Func : public FullTraverser, NonCopyable
  {
    IMaterialProcessor &proc;
    nstl::string componentID;
    Func(IMaterialProcessor &f,const nstl::string &_componentID) : proc(f), componentID(_componentID) {}
    void operator()(SceneComponent *pSC)
    {
      if(pSC->GetId() == componentID)
        pSC->ForAllMaterials(proc);
    }
  } func(proc,_componentID);

  object.Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifySceneObjectColors(NScene::SceneObject &object, const HDRColor &multiplier, const HDRColor &add)
{
  struct Func : public FullTraverser, NonCopyable
  {
    const Render::HDRColor &mul;
    const Render::HDRColor &add;
    Func(const Render::HDRColor &_multiplier, const Render::HDRColor &_add) : mul(_multiplier), add(_add) {}
    void operator()(SceneComponent *pSC)
    {
      pSC->ModifyColor(mul, add);
    }
  } func(multiplier, add);

  object.Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifySceneComponentColors(NScene::SceneObject &_object, const nstl::string &_componentID, 
                                const Render::HDRColor &_multiplier, const Render::HDRColor &_add)
{
  struct Func : public FullTraverser, NonCopyable
  {
    nstl::string componentID;
    const Render::HDRColor &mul;
    const Render::HDRColor &add;
    Func(const nstl::string &_componentID, const Render::HDRColor &_multiplier, const Render::HDRColor &_add) : componentID(_componentID), mul(_multiplier), add(_add) {}
    void operator()(SceneComponent *pSC)
    {
      if(pSC->GetId() == componentID)
        pSC->ModifyColor(mul, add);
    }
  } func(_componentID,_multiplier,_add);

  _object.Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifySceneObjectOpacity(NScene::SceneObject &object, float opacity)
{
	struct MProc : public IMaterialProcessor, public NonCopyable
	{
		float opacity;

		MProc(float o) : opacity(o) {}
		virtual void operator()(BaseMaterial &material)
		{
			material.ModifyOpacity(opacity);
		}
	} proc(opacity);

	ForAllMaterials(object, proc);
}

} //namespace NScene
