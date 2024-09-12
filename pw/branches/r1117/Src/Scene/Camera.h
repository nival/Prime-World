#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/Transform.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCameraPosition
{
	float fPitch, fYaw, fRoll;
	float fRod;
	CVec3 vAnchor;
	CVec3 GetCameraPos() const;
	CVec3 GetCameraUp() const;
	CVec3 GetCameraDir() const;
	SCameraPosition() : fPitch(0), fYaw(0), fRoll(0), vAnchor(1, 0, 0), fRod(20) {}
	void ConvertFromRadToDeg();
	void ConvertFromDegToRad();

	bool operator == ( const SCameraPosition& pos ) const
	{
		return
			fPitch == pos.fPitch &&
			fYaw == pos.fYaw &&
			fRoll == pos.fRoll &&
			fRod == pos.fRod &&
			vAnchor.x == pos.vAnchor.x &&
			vAnchor.y == pos.vAnchor.y &&
			vAnchor.z == pos.vAnchor.z;
	}

	bool operator != ( const SCameraPosition& pos ) const
	{
		return !operator == ( pos );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ICamera : public CObjectBase
{
	// Setting Camera positions
	virtual void SetPosition( const SCameraPosition& position ) = 0;
	virtual void GetPosition( SCameraPosition *pPosition ) const = 0;

	// Set projection transformation parameters
	virtual void SetPerspectiveTransform( float fFOV, float fWidth, float fHeight, float fNear, float fFar, float fFovCorrectionAngle ) = 0;
	virtual void SetOrthographicTransform( float fWidth, float fHeight, float fNear, float fFar ) = 0;

	virtual void SetScreenSize( float fWidth, float fHeight ) = 0;
	virtual void SetViewportSize( float fWidth, float fHeight ) = 0;
	virtual void SetFOV( float fFOV ) = 0;
	virtual void SetPlanes(float fNear, float fFar)=0;

	virtual float GetFOV() const = 0;
	virtual float GetNear() const = 0;
	virtual float GetFar() const = 0;
	virtual float GetScreenWidth() const = 0;
	virtual float GetScreenHeight() const = 0;
	virtual float GetViewportWidth() const = 0;
	virtual float GetViewportHeight() const = 0;
	virtual int GetVersion() const = 0;

	// matrices
	virtual const SHMatrix& GetViewMatrix() = 0;
	virtual const SHMatrix& GetProjectiveMatrix() = 0;
	virtual CTransformStack& GetTransform() = 0;

	// projective ray
	virtual void GetProjectiveRay( CVec3 *pvOrig, CVec3 *pvDir, const CVec2 &vScreenPos ) = 0;
  virtual void GetProjectiveRayLocal( CVec3 *pvDir, const CVec2 &vScreenPos ) = 0;
	virtual void GetProjectiveRayPoints( CVec3 *pvNear, CVec3 *pvFar, const CVec2 &vScreenPos ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICamera* CreateCamera();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}