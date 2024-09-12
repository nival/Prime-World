#include "stdafx.h"
#include "batch.h"
#include "RenderComponent.h"
#include "Material.h"
#include "sceneconstants.h"

static bool  s_enableWaterLevel = false;
static float s_WaterLevel = 0.0f;

namespace Render
{

  void RenderComponent::FillOBB(const AABB& _localAABB, const Matrix43& _transform, CVec3 * __restrict _pBox)
  {
    //CVec3 size = 2.0f * sc.GetLocalAABB().halfSize;
    CVec3 size = 2.0f * _localAABB.halfSize;
    //Matrix43 mtxWorld;
    //sc.GetWorldPlacement().GetMatrix(&mtxWorld);
    CVec3 basis[3] = { CVec3(size.x * _transform._11, size.x * _transform._21, size.x * _transform._31),
                       CVec3(size.y * _transform._12, size.y * _transform._22, size.y * _transform._32),
                       CVec3(size.z * _transform._13, size.z * _transform._23, size.z * _transform._33) };
    CVec3 pivot = _localAABB.center - _localAABB.halfSize;
    pivot = Transform(pivot, _transform);
  
    _pBox[0] = pivot;
    _pBox[1] = pivot + basis[0];
    _pBox[2] = _pBox[1] + basis[1];
    _pBox[3] = pivot + basis[1];
    _pBox[4] = _pBox[3] + basis[2];
    _pBox[5] = pivot + basis[2];
    _pBox[6] = _pBox[1] + basis[2];
    _pBox[7] = _pBox[2] + basis[2];
  }

  void RenderComponent::FillOBBH(const AABB& _localAABB, const SHMatrix& _transform, CVec4 * __restrict _pBox)
  {
    CVec3 size = 2.0f * _localAABB.halfSize;

    CVec4 basis[3] = { CVec4(size.x * _transform._11, size.x * _transform._21, size.x * _transform._31, size.x * _transform._41),
                       CVec4(size.y * _transform._12, size.y * _transform._22, size.y * _transform._32, size.y * _transform._42),
                       CVec4(size.z * _transform._13, size.z * _transform._23, size.z * _transform._33, size.z * _transform._43) };
    CVec4 pivot(_localAABB.center - _localAABB.halfSize, 1.f);
    _transform.RotateHVector(&pivot, pivot);
  
    _pBox[0] = pivot;
    _pBox[1] = pivot + basis[0];
    _pBox[2] = _pBox[1] + basis[1];
    _pBox[3] = pivot + basis[1];
    _pBox[4] = _pBox[3] + basis[2];
    _pBox[5] = pivot + basis[2];
    _pBox[6] = _pBox[1] + basis[2];
    _pBox[7] = _pBox[2] + basis[2];
  }

}