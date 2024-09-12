#pragma once
#ifndef _LIGHTNINGFX_H_
#define _LIGHTNINGFX_H_

#include "../System/ScopedPtr.h"
#include "../Render/primitive.h"
#include "../Render/RenderComponent.h"

class LightningFX : public Render::RenderComponent
{
public:
	typedef NDb::DBLightningFXParams Params;

public:
	LightningFX();
	~LightningFX();

	void SetMaterial(NDb::LightningMaterial const* pDBMaterial);
	void SetWorldMatrix(Matrix43 const& m) { worldMatrix = m; }
	
	void SetParameters(Params const& newParams);
	Params const& GetParameters() const { return params; }
	
	void SetProgress(float progress);
	float GetProgress() const { return progress; }

	void Enable(bool onoff);
	bool IsEnabled() const { return enabled; }

	void Update(CVec3 const& p1, CVec3 const& p2, float dt);

  Render::BaseMaterial *GetMaterial() { return Get(pMaterial); }
  Render::OcclusionQueries* GetQueries() const { return 0; }

	// From Render::RenderComponent
	virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
	virtual void RenderToQueue( class Render::BatchQueue &queue );

private:
	float MakeLocalTransform(SHMatrix* res, CVec3 const& a, CVec3 const& b);

private:
	static const Params DEFAULT_PARAMS;
	Params params;

	Render::Primitive geo;
	bool enabled;
	float scrollOffset;
	float frameOffset;
	int animFrame;
	float progress;
	CVec4 scaleOffset;

	Matrix43 worldMatrix;
	SHMatrix xform;
	ScopedPtr<Render::BaseMaterial> pMaterial;
};

#endif /* _LIGHTNINGFX_H_ */
