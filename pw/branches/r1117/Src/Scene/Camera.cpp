#include "StdAfx.h"

#include "Camera.hpp"

#include "../System/GeomMisc.h"
#include <float.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 SCameraPosition::GetCameraPos() const
{
	CVec3 vForward;
	CQuat q = CQuat( fYaw, V3_AXIS_Z ) * CQuat( fPitch, V3_AXIS_X )* CQuat( fRoll, V3_AXIS_Y );
	q.GetYAxis( &vForward );
	return vAnchor - vForward * fRod;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 SCameraPosition::GetCameraUp() const
{
	CVec3 vUp;
	CQuat q = CQuat( fYaw, V3_AXIS_Z ) * CQuat( fPitch, V3_AXIS_X )* CQuat( fRoll, V3_AXIS_Y );
	q.GetZAxis( &vUp );
	return vUp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 SCameraPosition::GetCameraDir() const
{
	CVec3 vForward;
	CQuat q = CQuat( fYaw, V3_AXIS_Z ) * CQuat( fPitch, V3_AXIS_X )* CQuat( fRoll, V3_AXIS_Y );
	q.GetYAxis( &vForward );
	return vForward;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SCameraPosition::ConvertFromDegToRad()
{
	this->fYaw /= 180.0f / FP_PI;
	this->fPitch /= 180.0f / FP_PI;
	this->fRoll /= 180.0f / FP_PI;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SCameraPosition::ConvertFromRadToDeg()
{
	this->fYaw *= 180.0f / FP_PI;
	this->fPitch *= 180.0f / FP_PI;
	this->fRoll *= 180.0f / FP_PI;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCamera::CCamera()
{
	fFOV = 32.0f;
  fFovCorrectionAngle = 66.f;
	fNear = 5.0f;
	fFar = 500.0f;
	nVersion = 0;
	fFOVCorrector = 1.0f;
  fScreenWidth = 1280.0f;
  fScreenHeight = 1024.0f;
	fViewportWidth = 0.0f;
	fViewportHeight = 0.0f;

	bNeedUpdate = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::Update()
{
	if (!bNeedUpdate)
		return;

  float fRad = 3.14159265f / 180.0f;

  // calculate FOV coefficient
	// using fScreenWidth, fScreenHeight, fViewportWidth, fViewportHeight, and general FOV
	if( fViewportWidth > 0.01f && fViewportHeight > 0.01f )
	{
		// Diagonal Fov case
		//float fScreenD = fabs( fScreenWidth, fScreenHeight );
		//float fViewportD = fabs( fViewportWidth, fViewportHeight );
		//float fScreenFOV = atanf( fScreenD * tanf( fFOV / 2 * fRad) / fViewportD ) / fRad * 2;

		// FovX case
		float fScreenFOV = atanf( fScreenHeight * tanf( fFOV / 2 * fRad) / fViewportHeight ) / fRad * 2;

		fFOVCorrector = fScreenFOV / fFOV;
	}
	else
	{
		fFOVCorrector = 1;
	}

  // FOV aspect correction
  float A0 = 4.f / 3.f; // base aspect
  float A1 = fScreenWidth / fScreenHeight; // current aspect
  float tgA = tan( ToRadian( fFovCorrectionAngle ) );
  float tgFov0 = tanf( ToRadian( fFOV / 2 ) );
  float Fov1 = atanf( tgFov0 * ( 1.f + A0 * tgA ) / ( 1.f + A1 * tgA ) );

  Fov1 = ToDegree( Fov1 ) * 2;

  fFOVCorrector *= Fov1 / fFOV;

	// build projection matrix
	transformStack.Clear();
	if ( fFOV == 0 )
		transformStack.MakeParallel( fScreenWidth, fScreenHeight, fNear, fFar );
	else
		transformStack.MakeProjective( CVec2(fScreenWidth, fScreenHeight), GetCorrectedFOV(), fNear, fFar );

	if ( fabs( position.fRod ) < EPS_VALUE )
		CreateViewMatrixRH(&matView, position.vAnchor, position.vAnchor + position.GetCameraDir(), -position.GetCameraUp() );
	else
		CreateViewMatrixRH(&matView, position.GetCameraPos(), position.vAnchor, -position.GetCameraUp() );

	transformStack.SetCamera( matView );

	++nVersion;
	bNeedUpdate = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetPosition( const SCameraPosition& _position )
{
	NI_ASSERT( _finite( _position.fYaw ) && _finite( _position.fPitch ) && _finite( _position.fRod ) && _finite( _position.fRoll )
		&& _finite( _position.vAnchor.x ) && _finite( _position.vAnchor.y ) && _finite( _position.vAnchor.z ), "Invalid position" );
	position = _position;
	bNeedUpdate = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::GetPosition( SCameraPosition *pPosition ) const
{
	if ( pPosition )
		*pPosition = position;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetPerspectiveTransform( float _fFOV, float _fWidth, float _fHeight, float _fNear, float _fFar, float _fFovCorrectionAngle)
{
	if ( fFOV != _fFOV || fScreenWidth != _fWidth || fScreenHeight != _fHeight ||	fNear != _fNear || fFar != _fFar )
	{
		fFOV = _fFOV;
		fScreenWidth = _fWidth;
		fScreenHeight = _fHeight;
		fNear = _fNear;
		fFar = _fFar;

		bNeedUpdate = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetOrthographicTransform( float _fWidth, float _fHeight, float _fNear, float _fFar )
{
	SetPerspectiveTransform( 0.0f, _fWidth, _fHeight, _fNear, _fFar, fFOVCorrector );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetPlanes(float _fNear, float _fFar) {
	fNear = _fNear;
	fFar = _fFar;
	bNeedUpdate = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetFOV( float _fFOV )
{
	SetPerspectiveTransform( _fFOV, fScreenWidth, fScreenHeight, fNear, fFar, fFOVCorrector );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetScreenSize( float _fWidth, float _fHeight )
{
	SetPerspectiveTransform( fFOV, _fWidth, _fHeight, fNear, fFar, fFOVCorrector );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::SetViewportSize( float _fWidth, float _fHeight )
{
	if ( fViewportWidth != _fWidth || fViewportHeight !=_fHeight )
	{
		fViewportWidth = _fWidth;
		fViewportHeight = _fHeight;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SHMatrix& CCamera::GetViewMatrix()
{
	Update();
	return matView;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SHMatrix& CCamera::GetProjectiveMatrix() 
{
	Update();
	return transformStack.GetProjection().forward;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTransformStack& CCamera::GetTransform()
{
	Update();
	return transformStack;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::GetProjectiveRayLocal( CVec3 *pvDir, const CVec2 &vScreenPos )
{
  Update();

  float fDepth = fScreenHeight * 0.5f / tan( ToRadian(GetCorrectedFOV()) * 0.5f );
  pvDir->Set( vScreenPos.x - fScreenWidth / 2, -vScreenPos.y + fScreenHeight / 2, fDepth );
  if ( fabs2( *pvDir ) < 1e-8f )
    *pvDir = CVec3( 0,0,1 );
  else
    Normalize( pvDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::GetProjectiveRay( CVec3 *pvOrig, CVec3 *pvDir, const CVec2 &vScreenPos )
{
	Update();

	*pvOrig = position.GetCameraPos();

  CVec3 direction;
  GetProjectiveRayLocal(&direction, vScreenPos);

	SHMatrix invView;
	InvertMatrix( &invView, matView ); // smirnov [2009/7/14]: cache inverse matrix which is needed so often!
	invView.RotateVector( pvDir, direction );

	Normalize( pvDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCamera::GetProjectiveRayPoints( CVec3 *pvNear, CVec3 *pvFar, const CVec2 &vScreenPos )
{
	CVec3 vOrig, vDir;
	GetProjectiveRay( &vOrig, &vDir, vScreenPos );
	if ( vDir == VNULL3 )
	{
		*pvNear = vOrig;
		*pvFar = vOrig;
	}
	else
	{
		*pvNear = vOrig + vDir * fNear;
		*pvFar = vOrig + vDir * fFar;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICamera * CreateCamera()
{
	CCamera *pCamera = new CCamera();
	return pCamera;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace NScene;
BASIC_REGISTER_CLASS( ICamera )
REGISTER_SAVELOAD_CLASS( CCamera )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
