#pragma once

namespace NDebug
{

void SetFrameTime( float frameTime );
void SetSteps( int recieveStep, int nextStep, float dt, int bufferLimit );
void ShowTime();
void ShowFPS();
void DumpSystemStatistics();
void SetSrv2ClientTimeDelta(int timeDelta);
void ShowSrvTime(bool _showSrvTime);

} // namespace NDebug


namespace debugDisplay
{
  struct Align
  {
    int   hor, ver;

    Align() :
    hor( -1 ), ver( -1 )
    {}

    Align( int _hor, int _ver ) :
    hor( Sign( _hor ) ), ver( Sign( _ver ) )
    {}

  private:
    int Sign( int i );
  };

  namespace Color
  {
    enum Enum { White, Red, Green, Blue, Cyan, Yellow };
  }

  struct GraphInfo
  {
    int           uiheight;
    Color::Enum   graphColor, textColor;
    int           limit;
    bool needRenderGraph;

    GraphInfo( int _uiheight, int _limit, Color::Enum _graphColor, Color::Enum _textColor, bool _needRenderGraph ) :
    uiheight( _uiheight ), limit( _limit ),
    graphColor( _graphColor ), textColor( _textColor ), needRenderGraph( _needRenderGraph )
    {}

    GraphInfo( int _uiheight, int _limit, bool _needRenderGraph ) :
    uiheight( _uiheight ), limit( _limit ),
    graphColor( Color::Green ), textColor( Color::White ), needRenderGraph( _needRenderGraph )
    {}
  };

  void UserControlImpulse();
  void Render();

  void AddText( const char * id, const Align & align, const char * text, Color::Enum color = Color::White, bool bigFont = false );
  void AddValue( const char * id, const Align & align, double value, Color::Enum color = Color::White, bool bigFont = false );
  void AddGraph( const char * id, const Align & align, int value, const GraphInfo & info = GraphInfo( 32, 100, true ) );
  void SetNewGraphInfo( const char * id, const GraphInfo & info );

  void Remove( const char * id );

  void Cleanup();

  void SetTopMargin( int topMargin );
} //namespace debugDisplay
