#ifndef STATISTICSSTREAK_H_INCLUDED
#define STATISTICSSTREAK_H_INCLUDED

namespace Statistics
{

//
// Счетчик увеличивается только монотонно возрастающими значениями индекса
// Пропуски номеров могут быть допустимы или нет (в последнем случае случается сброс)
//

//FIXME: Этот класс частично повторяет функционал StatisticsStuff::LinearFunction и StatisticsStuff::Ruller
//TODO: REFACTOR: Заменить вышеупомянутые классы на этот, при необходисомти дописать функционал

namespace EStreakCounterMode
{
  enum Enum
  {
    Continuous = 0, WithGaps,
    Force32Bit = MAXUINT
  };
};

class StreakIndexedCounter
{
public:
  explicit StreakIndexedCounter( EStreakCounterMode::Enum _mode = EStreakCounterMode::WithGaps, int _displayThreshold = 1 ) :
    mode( _mode ),
    length( 0 ),
    lastIndex( 0 ),
    displayThreshold( _displayThreshold )
    {
    }

  void SetDisplayThreshold( int threshold )
  {
    displayThreshold = threshold;
  }

  bool IsOn() const { return length > 0; }

  int Length() const { return length; }

  int DisplayLength() const { return ( length >= displayThreshold ) ? ( length - displayThreshold + 1 ) : 0; }

  int LastIndex() const { return lastIndex; }

  void Reset()
  {
    length = 0;
    lastIndex = 0;
  }

  void ResetTo( int newIndex )
  {
    length = 1;
    lastIndex = newIndex;
  }

  void CheckOut( int index )
  {
    if ( length > 0 )
    {
      if ( index <= lastIndex )
      {
        ResetTo( index );
        return;
      }

      if ( ( mode == EStreakCounterMode::Continuous ) && ( index != lastIndex + 1 ) )
      {
        ResetTo( index );
        return;
      }
    }

    ++length;
    lastIndex = index;
    return;
  }

private:
  ZDATA;
  EStreakCounterMode::Enum mode;
  int   length;
  int   lastIndex;
  int   displayThreshold;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mode); f.Add(3,&length); f.Add(4,&lastIndex); f.Add(5,&displayThreshold); return 0; }
};

};

#endif //STATISTICSSTREAK_H_INCLUDED
