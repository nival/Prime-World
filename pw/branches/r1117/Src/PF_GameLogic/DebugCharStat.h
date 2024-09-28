#pragma once

namespace NWorld
{
  class PFBaseUnit;
}

namespace UI
{
  class Window;
  class ImageLabel;
}

namespace NDb
{
  struct DBUIData;
}

namespace NGameX
{
class DebugCharStat:public CObjectBase
{
  OBJECT_BASIC_METHODS(DebugCharStat);
  DebugCharStat() {}
public:
  DebugCharStat(UI::Window * _window, NDb::Ptr<NDb::DBUIData> _statNames);

  void Update();
  void SetUnit(const NWorld::PFBaseUnit * _unit);

private:
  void UpdateAdvancedParams();

  struct AdvancedParams
  {
  public :
    typedef nstl::pair< Weak<UI::ImageLabel>, Weak<UI::ImageLabel> > TStatType;
    typedef vector< TStatType > TStatsContainer;

  public :
    AdvancedParams(){};
    void Init( UI::Window * _statWindow );

  public :
    void UpdateVisibility(  );
    void Add( wstring const &name, wstring const &value, string const & valueStyle );
    int  GetNumStats() const { return statCount; }

  private :
    Weak<UI::Window>  background;
    TStatsContainer   statWindows;
    int               statCount, statHeight;
  };

  string  styleNormal;
  string  styleBonus;
  string  stylePenalty;

  NDb::Ptr<NDb::DBUIData> dbStatParams;

  AdvancedParams    advancedParams;
  Weak<UI::Window>  window;
  ConstPtr<NWorld::PFBaseUnit> unit;
};

}