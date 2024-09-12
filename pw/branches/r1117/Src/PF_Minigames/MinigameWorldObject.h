#pragma once

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IClientNotifyCallback : public IObjectBase
{
  virtual void OnClientNotification(const char * eventId) = 0;
};


class MinigameBase;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigameWorldObject : public CObjectBase 
{
	OBJECT_BASIC_METHODS( MinigameWorldObject )

public:
	MinigameWorldObject();
	virtual ~MinigameWorldObject();

  void InitWorldObject( MinigameBase * _minigame );

	virtual void Step( float deltaTime );
	virtual bool OnClick();
  virtual bool ReceiveClicks() { return true; }
	virtual bool OnTouched( MinigameWorldObject* _other );
  virtual void OnBuyCommand();

  virtual void Clear();

	void SetObjectID( int _objectID ) { objectID = _objectID; }
	int GetObjectID() const { return objectID; }

  MinigameBase * GetMinigame() const { return IsValid( minigame ) ? minigame : 0; }

	void SetPlacement( const Placement& _placement ) { placement = _placement; }
	const Placement& GetPlacement() const { return placement; }

  virtual const Placement& GetTarget( bool& goInstantly ) const { goInstantly = true; return GetPlacement(); }
  virtual float GetLinearVelocity() const { return 0.f; }

	virtual void SetName( const nstl::wstring& _name ) { name = _name; }
  virtual const wstring & GetNameRaw() const { return name; }
	virtual wstring GetName() const { return wstring(); }
  virtual wstring GetDescription() const { return wstring(); }

  void SetClientNotify( IClientNotifyCallback * pNotify ) { clientNotify = pNotify; }
  void NotifyClient(const char * eventId);

protected:
	Placement placement;

private:
  ZDATA
  ZNOPARENT(CObjectBase)
	int objectID;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&objectID); return 0; }
private:
	nstl::wstring name;
  CPtr< IClientNotifyCallback > clientNotify;
  CPtr< MinigameBase > minigame;
};

} // namespace PF_Minigames

