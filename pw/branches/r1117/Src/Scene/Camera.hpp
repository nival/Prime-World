#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCamera : public ICamera
{
	OBJECT_METHODS( 0x1F4A8B14, CCamera );

	// Orientation
	SCameraPosition position;

	// Project matrix parameters
	float fFOV;
  float fFovCorrectionAngle; // for widescreen correction
	float fFOVCorrector;
	float fNear;
	float fFar;
	float fScreenWidth;
	float fScreenHeight;	
	float fViewportWidth;
	float fViewportHeight;	
	int nVersion;

	// Matrixes of transformation
	SHMatrix matView;
	CTransformStack transformStack;

private:
	bool bNeedUpdate;
	void Update();

public:
	// Construction/Destruction
	CCamera();

public:
	// Inherited functions

	// Setting Camera positions
	virtual void SetPosition( const SCameraPosition& position );
	virtual void GetPosition( SCameraPosition *pPosition ) const;

	// Set projection transformation parameters
	virtual void SetPerspectiveTransform( float fFOV, float fWidth, float fHeight, float fNear, float fFar, float fFovCorrectionAngle );
	virtual void SetOrthographicTransform( float fWidth, float fHeight, float fNear, float fFar );

	virtual void SetScreenSize( float fWidth, float fHeight );
	virtual void SetViewportSize( float fWidth, float fHeight );
	virtual void SetFOV( float fFOV );

	virtual float GetFOV() const { return fFOV; }	
	virtual float GetNear() const { return fNear; }	
	virtual float GetFar() const { return fFar; }	
	virtual float GetScreenWidth() const { return fScreenWidth; }
	virtual float GetScreenHeight() const { return fScreenHeight; }
	virtual float GetViewportWidth() const { return fViewportWidth; }
	virtual float GetViewportHeight() const { return fViewportHeight; }
	virtual int GetVersion() const { return nVersion; }

	virtual void SetPlanes(float fNear, float fFar);


	// matrices
	// Is not const because calling update inside
	virtual const SHMatrix& GetViewMatrix();
	virtual const SHMatrix& GetProjectiveMatrix(); 
	virtual CTransformStack& GetTransform();

	// projective ray
	virtual void GetProjectiveRay( CVec3 *pvOrig, CVec3 *pvDir, const CVec2 &vScreenPos );
  virtual void GetProjectiveRayLocal( CVec3 *pvDir, const CVec2 &vScreenPos );
	virtual void GetProjectiveRayPoints( CVec3 *pvNear, CVec3 *pvFar, const CVec2 &vScreenPos );

private:
	float GetCorrectedFOV() const { return fFOV*fFOVCorrector; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}