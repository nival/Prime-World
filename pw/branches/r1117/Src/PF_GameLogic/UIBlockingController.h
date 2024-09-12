#pragma once



namespace UI
{
  class FlashContainer2;
}


namespace NGameX
{

class AdventureFlashInterface;


namespace EUnblockType
{
  enum Enum
  {
    Simple,
    TalentBar,
    ActionBar,
    Hero,
    Shop,
    Inventory,
  };
}

class UIBlockingController : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( UIBlockingController, BaseObjectST );

public:
  UIBlockingController();

  void SetFlashContainer( UI::FlashContainer2* _flashContainer ) { flashContainer = _flashContainer; }
  void SetFlashInterface( NGameX::AdventureFlashInterface* _flashInterface ) { adventureFlashInterface = _flashInterface; }

  void SetSaturationColor( const CVec4& _color ) { saturationColor = _color; }
  const CVec4& GetSaturationColor() const { return saturationColor; }

  void BeginBlockSection();
  void AddNonBlockedElement( const char* id, bool bubble );
  void AddNonBlockedElementTalentBar( int column, int row, bool bubble );
  void AddNonBlockedElementActionBar( int slot, bool bubble );
  void AddNonBlockedElementInventory( int slot, bool bubble );
  void AddNonBlockedElementShop( int slot, bool bubble );
  void AddNonBlockedElementHero( int playerId, bool bubble );
  void EndBlockSection( float fadeTime );
  void ClearBlocking( float fadeTime );

  void Update( float deltaTime );

  bool IsBlocked() { return isUIBlocked; }
  float GetFadeValue();

private:

  struct UnblockDesc
  {
    EUnblockType::Enum type;
    int column;
    int row;
    int slot;
    nstl::string name;
    bool bubble;

    UnblockDesc( EUnblockType::Enum _type, const nstl::string& _name, bool _bubble ) : type(_type), column(0), row(0), slot(0), name(_name), bubble(_bubble) { }
    UnblockDesc( EUnblockType::Enum _type, int _column, int _row, bool _bubble ) : type(_type), column(_column), row(_row), slot(0), bubble(_bubble) { }
    UnblockDesc( EUnblockType::Enum _type, int _slot, bool _bubble ) : type(_type), column(0), row(0), slot(_slot), bubble(_bubble) { }
  };

  void SetNonBlockedElement( const UnblockDesc& _desc, bool nonBlocked );

  CVec4 saturationColor;

  bool isUIBlocked;
  bool fadeOut;
  float fadeTime;
  float currentFadeTime;

  Weak<UI::FlashContainer2> flashContainer;
  Weak<NGameX::AdventureFlashInterface> adventureFlashInterface;

  typedef nstl::list<UnblockDesc> UnblockedItems;

  UnblockedItems unblockedItems;
};

}