#pragma once
#ifndef _TRACEEFFECT_H_
#define _TRACEEFFECT_H_

#include "TraceFXGeo.h"
#include "../System/ScopedPtr.h"
#include "../Render/RenderComponent.h"

class TraceFX : public Render::RenderComponent
{
public:
	struct Params
	{
		float maxLength;
    float maxStepLength;
		float speedStart;
		float speedStop;
		Render::HDRColor colorFirst;
		Render::HDRColor colorLast;
		float offsetColor;
		float offsetAlpha;
		float fadeoutSpeed;
		float skewness;
	};

public:
	TraceFX();
	~TraceFX();

	void SetMaterial(NDb::TraceMaterial const* pDBMaterial);
  Render::BaseMaterial* GetMaterial() const { return Get(pMaterial); }
  Render::OcclusionQueries* GetQueries() const { return 0; }
	void SetParameters(Params const& newParams);
  Params const& GetParameters() const { return params; }
	void SetWorldMatrix(Matrix43 const& m) { worldMatrix = m; }

	void Reinit();
  void Enable(bool onoff);
	bool IsEnabled() const { return enabled; }
  bool IsOff() const { return state == STATE_OFF; }

	void Update(CVec3 const& p1, CVec3 const& p2, float dt);

	// From Render::RenderComponent
	virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
	virtual void RenderToQueue( class Render::BatchQueue &queue );

private:
	enum State { STATE_OFF, STATE_ON, STATE_FADEOUT };
  bool UpdateGeometry(CVec3 const& a0, CVec3 const& b0);

private:
	static const Params DEFAULT_PARAMS;
	Params params;

	bool enabled;
	State state;
	float length;
	float fadeout;

	CVec3 a1, b1;	// previous positions
	CVec3 a2, b2;	// positions before previous
	CVec3 da1, db1;	// previous velocities

	Matrix43 worldMatrix;
	ScopedPtr<TraceFXGeo> pGeometry;
	ScopedPtr<Render::BaseMaterial> pMaterial;
};

#endif /* _TRACEEFFECT_H_ */
