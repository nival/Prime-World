#pragma once


namespace PF_Minigames
{

class Easel;
class EaselWorld;
class EaselLuxView;
class EaselPaintView;
class EaselViewEffects;
class EaselDebugView;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main class for all views and landscape view logic
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselView : public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC3, EaselView );
public:
	EaselView( Easel * _easel, bool local = true );
  virtual ~EaselView();


  virtual bool Step( float deltaTime, EaselWorld* _world ); 
  virtual void Update( float deltaTime, EaselWorld* _world );  

	virtual void Reset();

  void InitAfterWorld( EaselWorld* _world );
  void ReleaseAfterWorld( EaselWorld* _world );

  EaselViewEffects* GetEffects() { return effects; }

private:
	CObj<EaselLuxView> luxorView;
  CObj<EaselPaintView> paintView;
  CObj<EaselViewEffects> effects;

protected:
  EaselView() {}
  CPtr<Easel> easel;
};

//////////////////////////////////////////////////////////////////////////
//
// null view object, operates on local remote easel copy instance
// does nothing
//
//////////////////////////////////////////////////////////////////////////
class EaselNullView : public EaselView
{
  OBJECT_METHODS( 0x9D6BBCC0, EaselNullView );
public:
  EaselNullView( Easel* _easel ) : EaselView( _easel, false ) {};
  ~EaselNullView() {};

  virtual void Init(Easel& _easel) { easel = &_easel; };

  virtual bool Step( float deltaTime ) { return true; }; 
  virtual void Update(float deltaTime) {};  

  virtual void Reset() {}

private:
  EaselNullView() {}
  EaselNullView(const EaselNullView &rhs);
  EaselNullView& operator=(const EaselNullView &rhs);

protected:

};

} // PF_Minigames
