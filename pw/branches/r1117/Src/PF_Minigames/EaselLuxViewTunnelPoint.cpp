#include "stdafx.h"

#include "EaselLuxViewTunnelPoint.h"

#include "DBEasel.h"
#include "../Scene/SceneObject.h"

#include "Easel.h"
#include "EaselWorldClientConvertHelper.h"


namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class EaselLuxViewTunnelPoint implementation
//
//////////////////////////////////////////////////////////////////////////
bool EaselLuxViewTunnelPoint::Init( Easel& _easel, const SVector& _point )
{
  const NDb::Ptr<NDb::DBEaselCommon>& commonEaselData = _easel.GetData()->commonParams;

  if(!IsValid( commonEaselData ) || !IsValid(commonEaselData->tunnels.tunnel))
  {
    return false;
  }

  // create placement
  Placement objPlacement = _easel.GetPlacement();

  /// גûםוסעט ג מעהוכüםûי לועמה
  
  CVec3 zeroDist = _easel.GetConvertHelper()->ConvertWorldToClientCoordinates( SVector(0, 0));
  static SVector defaultDirection = SVector(0, 1000);
  CVec3 clientDirection = _easel.GetConvertHelper()->ConvertWorldToClientCoordinates(defaultDirection);

  // [@Irakly <neko.lich> Archangelsky@] TODO: 
  static CVec3 eul = CVec3(FP_PI, FP_PI, FP_PI2);

  SHMatrix matrix;
  SetLookAtZ( &matrix, zeroDist, clientDirection );

  CQuat rotationQuat;
  rotationQuat.FromEulerMatrix( matrix );

  CVec3 eulDecomp;
  rotationQuat.DecompEulerAngles(&eulDecomp.x, &eulDecomp.y, &eulDecomp.z);
  eulDecomp += eul;
  rotationQuat.FromEulerAngles(eulDecomp.x, eulDecomp.y, eulDecomp.z);

  objPlacement.rot = rotationQuat;

  //////////////////////////////////////////////////////////////////////////

  NScene::SceneObject *pSceneObject = MinigameClientObject::Init(NULL,
                                                                _easel.GetScene(),
                                                                commonEaselData->tunnels.tunnel,
                                                                objPlacement,
                                                                false);
  if ( !pSceneObject )
    return false;

  SetPosition( _easel.GetConvertHelper()->ConvertWorldToClientCoordinates( _point ) );

  return true;
}

void EaselLuxViewTunnelPoint::OnLevelStarted()
{
  SetVisible( true );
}

void EaselLuxViewTunnelPoint::OnLevelFinished()
{
  SetVisible( false );
}

}