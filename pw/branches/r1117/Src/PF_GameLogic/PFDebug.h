#pragma once

#include "PFDebugImpl.h"

#define DEBUG_DECLARE()

#define DECLARE_DEBUG_CB_TABLE()                                                    \
  static  NDebug::DebugTableEntry debugCallbacksTable[];                            \
  virtual NDebug::DebugTableEntry const* GetCallbackTable() const { return debugCallbacksTable; }

#define BEGIN_DEBUG_CB_TABLE( CLASSNAME )                                           \
  NDebug::DebugTableEntry CLASSNAME::debugCallbacksTable[] = {

#define END_DEBUG_CB_TABLE()                                                        \
    {NDebug::DebugTableEntry::Terminator, {AutoPtr<NDebug::ICondintion>(NULL), NULL}, NULL}                            \
  } ;

#define PARENT_CB_TABLE( CLASSNAME ) \
  {NDebug::DebugTableEntry::Table, {AutoPtr<NDebug::ICondintion>(NULL), NULL}, CLASSNAME::debugCallbacksTable},

#define DEBUG_CB_ALWAYS(CALLBACK) \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateAlwaysChecker() ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_VARIABLE_VALUE( VAR, VALUE, CALLBACK )                          \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateValueChecker(VAR, VALUE, true) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_VARIABLE_NOT_VALUE( VAR, VALUE, CALLBACK )                      \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateValueChecker(VAR, VALUE, false) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_VARIABLE_VALUE_RANGE( VAR, MIN_VALUE, MAX_VALUE, CALLBACK )     \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateValueRangeChecker(VAR, MIN_VALUE, MAX_VALUE) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_CONSOLE_VARIABLE_VALUE( VAR, VALUE, CALLBACK )                          \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateConsoleValueChecker(VAR, VALUE, true) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_CONSOLE_VARIABLE_NOT_VALUE( VAR, VALUE, CALLBACK )                      \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateConsoleValueChecker(VAR, VALUE, false) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_CONSOLE_VARIABLE_VALUE_RANGE( VAR, MIN_VALUE, MAX_VALUE, CALLBACK )     \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateConsoleValueRangeChecker(VAR, MIN_VALUE, MAX_VALUE) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_FUN_CONDITION( FUN, CALLBACK )     \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateFunChecker( FUN ) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

#define DEBUG_CB_ON_MEMFUN_CONDITION( MEMFUN, CALLBACK )     \
  {NDebug::DebugTableEntry::Callback, { AutoPtr<NDebug::ICondintion>( NDebug::CreateMemFunChecker( MEMFUN ) ), static_cast<NDebug::callback_t>(CALLBACK) }, NULL}, 

namespace Render
{
  _interface IDebugRender;
}

namespace NWorld
{
  class PFApplAura;
  class PFBaseUnit;
  class PFAreaTargetSelector;
}

namespace NDebug
{ 
 
class DebugObject : public CObjectBase
{
  OBJECT_BASIC_METHODS( DebugObject );
public:
  seDECLARE_COBJRING(DebugObject,  objectsRingPart, Ring);
  seDECLARE_CPTRRING(DebugObject,  selectRingPart,  SelectedRing); 

  DebugObject();
  virtual ~DebugObject();

  void Select() { if (!selectRingPart.isLinked()) selectRing.addLast(this); }
  void Deselect() { SelectedRing::safeRemove(this); }
  virtual bool IsSelected() const { return selectRingPart.isLinked(); }

  static void DeselectAll();
  static void ProcessAll(Render::IDebugRender* pRender);
  static void ClearAll();
protected:
  static Ring         objectsRing;
  static SelectedRing selectRing;

  virtual bool Process(Render::IDebugRender* pRender) { return false; };

  virtual bool IsObjectValid() const { return false; }
};

/*
class DebugUser
{
  seDECLARE_RING(DebugUser, dbgUserRingPart,          Ring)
  seDECLARE_RING(DebugUser, dbgUserSelectionRingPart, SelectionRing)
  static DebugUser::Ring          debugUsers;
  static DebugUser::SelectionRing debugSelected;
  static DebugUser::Ring          debugRegister;

  virtual DebugTableEntry const* GetCallbackTable() const = 0;
  void ProcessTable( Render::IDebugRender* pRender, DebugTableEntry const* pTable ) const;
protected:
  virtual void DU_Process(float dt, Render::IDebugRender* pRender ); 
public:
  explicit                       DebugUser();
  virtual                        ~DebugUser();

          void                   DU_AddToSelection() const;
          void                   DU_RemoveFromSelection() const;
  virtual bool                   DU_IsInSelection() const;
  
  static void                    DU_ClearSelection(); 
  static void                    DU_ClearAll();
  static void                    Update( float dt, Render::IDebugRender* pRender );
};
*/
void ShowAuraApplicatorRange(CPtr<NWorld::PFApplAura> const &pAura);
void ShowTargetSelectorRange(CPtr<NWorld::PFBaseUnit> const &pUnit, CPtr<NWorld::PFAreaTargetSelector> const &ts, CVec3 const &pos, float range);

}; // namespace NDebug

