#pragma once

#include <d3d9.h>
#include "DeviceLost.h"
#include "DxIntrusivePtr.h"

namespace Render
{

struct OcclusionQuery
{
  DXQueryRef query;
  enum 
  {
    UNUSED,
    ISSUEDBEGIN,
    ISSUEDEND,
  } state;
public:
  OcclusionQuery(void) : state(UNUSED) {}
};


class OcclusionQueriesBank
{
  StaticArray<OcclusionQuery, 2> queries;
  UINT head;
  UINT lastResult, lastFinishedQuery;
  UINT currentFrame;

  static UINT s_currentFrame;

public:
  enum CameraID
  {
    CID_MAIN,
    CID_SHADOW,
    CID_WATER,
  } cameraID;

  OcclusionQueriesBank(void);
  ~OcclusionQueriesBank(void);

  HRESULT BeginNextQuery();
  HRESULT EndNextQuery();
  int GetLatestResults();

  static void OnFrameStart() { ++s_currentFrame; }
};


class OcclusionQueries : public DeviceLostHandler
{
  typedef vector<OcclusionQueriesBank> VQueries;
  VQueries banks;

protected:
  OcclusionQueries() {}

public:
  // Get (or create) OcclusionQueriesBank for desired camera.
  OcclusionQueriesBank& Get();
  void Clear() { banks.clear(); }

  virtual void OnDeviceLost()  { Clear(); }
  virtual void OnDeviceReset() {}

  enum UseMode
  {
    QUM_NONE = 0,
    QUM_CHECK = 1,
    QUM_ISSUE = QUM_CHECK<<1,
    QUM_CHECK_AND_ISSUE = QUM_CHECK | QUM_ISSUE
  };

  static void SetUseMode(UseMode _useMode);
  static UseMode GetUseMode();

  //static UseMode s_useMode;
  static void SetCurrentCameraID(OcclusionQueriesBank::CameraID _id);
};

};