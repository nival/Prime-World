#pragma once

#include "Overtips.h"
#include "ScreenUILogicBase.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BaseOvertipsScreenLogic : public ClientScreenUILogicBase, public Overtips::IManager
{
  NI_DECLARE_REFCOUNT_CLASS_1( BaseOvertipsScreenLogic, ClientScreenUILogicBase );

public:
  BaseOvertipsScreenLogic();
  ~BaseOvertipsScreenLogic();

  //Overtips::IManager
  virtual void InitOvertips(NScene::IScene * pScene);
  virtual void StepOvertips();
  virtual int CreateOvertip(const NDb::UIObjectOvertips * pOvertips, Overtips::ITarget * pTarget = 0 );
  virtual bool RemoveOvertip(int id);

  virtual UI::Window * GetOvertipWindow(int id, const Overtips::SOvertipId & overtipId);
  virtual bool UpdateOvertipWorldPosition(int id, const SHMatrix & matrix);
  virtual bool UpdateOvertipAabb(int id, const CVec3 & center, const CVec3 & halfsize);

private:
  struct SOvertipLayout
  {
    Weak<Window>                  window;
    NDb::EUIOvertipBindPoint      bindPoint;
    SOvertipLayout(Window * pWnd = NULL, NDb::EUIOvertipBindPoint _bindPoint = NDb::UIOVERTIPBINDPOINT_NONE) : window(pWnd), bindPoint(_bindPoint) {}
  };

  typedef map<Overtips::SOvertipId, SOvertipLayout>  TLayouts;

  struct SOvertipData
  {
    SOvertipData(const NDb::UIObjectOvertips * _pDbOvertips = NULL, Overtips::ITarget * pTarget = NULL) :
    pDbOvertips(_pDbOvertips), target(pTarget), itHadTarget(pTarget), visibility(true), worldMatrix(CVec3(0, 0, 0)), aabbCenter(0, 0, 0), aabbHalfsize(0, 0, 0)
    {}

    NDb::Ptr<NDb::UIObjectOvertips> pDbOvertips;
    CPtr<Overtips::ITarget>       target;
    bool                          itHadTarget;
    bool                          visibility;
    TLayouts                      layouts;
    SHMatrix                      worldMatrix; //Используется только если target == NULL
    CVec3                         aabbCenter, aabbHalfsize; //Используется только если target == NULL
  };

  typedef map<int, SOvertipData>  TOvertipsData;

  int                   nextId;
  TOvertipsData         overtips;
  CPtr<NScene::IScene>  scene;

  void CleanupOvertip(int id, SOvertipData & overtip);
  static CVec2 GetBindPointAlign(NDb::EUIOvertipBindPoint point);
  void UpdateOvertip(int id, SOvertipData & data, const SHMatrix & projViewMatrix, bool initialSetup);
  bool UpdatePlainOvertip(int id, const SOvertipData & data, const Overtips::SOvertipId & overtipId, Window * pWindow, const SHMatrix & projViewMatrix);
  void Update3DOvertip(int id, const SOvertipData & data, const Overtips::SOvertipId & overtipId, Window * pWindow);
};

} //namespace UI
