#pragma once
#ifndef _TRACEEFFECTGEO_H_
#define _TRACEEFFECTGEO_H_

#include "../System/nqueue.h"
#include "../Render/dipdescriptor.h"
#include "../Render/renderableprimitive.h"
#include "../Render/dxutils.h"

class TraceFXGeo : public Render::IRenderablePrimitive
{
public:
	static const int MAX_SEGMENTS = 50;

public:
  TraceFXGeo();
	~TraceFXGeo();

	void SetOffsets(float offColor, float offAlpha) { offsetColor = offColor; offsetAlpha = offAlpha; }
	CVec4 const& GetScaleOffset() const { return scaleOffset; }

	void Clear();
	void Begin(float t, float dt);
	void Append(CVec3 const& a, float ta, CVec3 const& b, float tb);
  bool ReplaceLast(CVec3 const& a, float ta, CVec3 const& b, float tb);
	void End();

	// From Render::IRenderablePrimitive
	virtual void Bind() const;
	virtual void Draw() const;
  virtual Render::GeometryBuffers  GetBuffers() const { Render::GeometryBuffers res = {0}; return res; }
  virtual Render::GeometryStatistics GetStats() const
  { 
    return Render::GeometryStatistics(dipDescr.primitiveCount, dipDescr.numVertices); 
  }

private:
	// final geometry
  Render::SpaceHolder vertexDataHolder;
  Render::DipDescriptor dipDescr;

	struct Segment
	{
		CVec3 a;
		float ta;
    float uva;
		CVec3 b;
		float tb;
    float uvb;
		Segment() {}
		Segment(CVec3 a_, float ta_, CVec3 b_, float tb_) : a(a_), ta(ta_), b(b_), tb(tb_), uva(0.0f), uvb(1.0f) {}
	};
	nstl::circular_buffer1<Segment, MAX_SEGMENTS> segments;
	bool adding;
	float offsetColor;
	float offsetAlpha;
	CVec4 scaleOffset;
};

#endif /* _TRACEEFFECTGEO_H_ */
