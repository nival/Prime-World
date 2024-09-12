#pragma once

namespace NWorld
{

class PFAbilityData;
class PFMultipleTargetSelector;

class PFMicroAICreateParams
{
public:
	bool isAITemp;
  PFMicroAICreateParams(NDb::Ptr<NDb::MicroAI> const &db, const PFAbilityData* ability) : dbPtr(db), pAbility(ability), isAITemp(false) {}
  NDb::Ptr<NDb::MicroAI> dbPtr;
  ConstPtr<PFAbilityData>    pAbility;
};

/////////////////////////////////////////////////////////////////////////////////
class PFMicroAI : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS(0x9E721CC0, PFMicroAI);

protected:

  ZDATA_(PFWorldObjectBase)
	ConstPtr<PFAbilityData> pAbility;
	NDb::Ptr<NDb::MicroAI> pDB;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pAbility); f.Add(3,&pDB); return 0; }

  typedef PFMicroAICreateParams CreateParams;
public:
  PFMicroAI(CreateParams const &cp) 
		: PFWorldObjectBase( cp.isAITemp ? 0 : const_cast<PFWorld*>(cp.pAbility->GetWorld()), 0 )
		, pDB(cp.dbPtr)
		, pAbility(cp.pAbility) {}
	PFMicroAI() {}
	virtual ~PFMicroAI() {}

  bool GetTarget(Target& target) const
  {
    return GetTargetImpl(target, NULL);
  }

  bool GetTarget(Target& target, const ITargetCondition& condition) const
  {
    return GetTargetImpl(target, &condition);
  }

	virtual bool NeedToBeStepped() { return false; }
protected:
  NDb::Ptr<NDb::MicroAI> const& GetDBBase() const { return pDB; }

  virtual bool GetTargetImpl(Target& target, const ITargetCondition* const condition) const { return false; }
};

/////////////////////////////////////////////////////////////////////////////////
class PFBasicMicroAI : public DBLinker<PFMicroAI, NDb::BasicMicroAI>
{
	WORLD_OBJECT_METHODS(0x9E721CC1, PFBasicMicroAI);

protected:
  bool CheckConditions() const;

	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

public:
	PFBasicMicroAI(CreateParams const &cp) : Base(cp) {}
	PFBasicMicroAI() {}
protected:
  virtual bool GetTargetImpl(Target& target, const ITargetCondition* const condition) const;
};

/////////////////////////////////////////////////////////////////////////////////
class PFTargetSelectorMicroAI : public DBLinker<PFBasicMicroAI, NDb::TargetSelectorMicroAI>
{
  WORLD_OBJECT_METHODS(0xF74D3C0, PFTargetSelectorMicroAI);

private:
  PFTargetSelectorMicroAI() {}

  ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

public:
  PFTargetSelectorMicroAI(CreateParams const &cp);
protected:
  virtual bool GetTargetImpl(Target& target, const ITargetCondition* const condition) const;
};

/////////////////////////////////////////////////////////////////////////////////
class PFMultipleTargetSelectorMicroAI : public DBLinker<PFBasicMicroAI, NDb::MultipleTargetSelectorMicroAI>
{
  WORLD_OBJECT_METHODS(0xB75A280, PFMultipleTargetSelectorMicroAI);

private:
  PFMultipleTargetSelectorMicroAI() {}

  ZDATA_(DBLinker)
  CObj<PFMultipleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }
public:
  PFMultipleTargetSelectorMicroAI(CreateParams const &cp);
protected:
  virtual bool GetTargetImpl(Target& target, const ITargetCondition* const condition) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class DBT>
PFMicroAI* CreateMicroAI(DBT const &/*dbAppl*/, PFMicroAICreateParams const &cp)
{
  return new T(cp);
}

} // namespace NWorld

