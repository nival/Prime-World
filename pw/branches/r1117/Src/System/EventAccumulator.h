#ifndef EVENTFREQUENCECALC_H_INCLUDED
#define EVENTFREQUENCECALC_H_INCLUDED

#include "CyclicBuffer.h"

class EventAccumulator : public NonCopyable
{
public:
  EventAccumulator( timer::Time _histDuration, size_t _histCells, timer::Time _now ) :
  histCells( _histCells ),
  histCellDuration( _histDuration / _histCells ),
  history( _histCells ),
  lastUpdate( _now ),
  currentEvents( 0 ),
  currentValue( 0 ),
  totalEvents( 0 ),
  totalValue( 0 ),
  totalDuration( 0 ),
  newValues( false )
  {
  }


  void Poll( timer::Time _now )
  {
    if ( _now <= lastUpdate + histCellDuration )
      return;

    timer::Time deltaTime = _now - lastUpdate;

    if ( history.Size() >= history.Capacity() )
      if ( !history.Empty() )
      {
        HistCell & cell = history.AtTail();
        totalEvents -= cell.totalEvents;
        totalValue -= cell.totalValue;
        totalDuration -= cell.duration;
        history.PopTail();
      }

    history.PushAtHead( HistCell( currentEvents, currentValue, deltaTime ) );

    totalEvents += currentEvents;
    totalValue += currentValue;
    totalDuration += deltaTime;

    newValues = true;

    currentEvents = 0;
    currentValue = 0;
    lastUpdate = _now;
  }


  void AddEvent( unsigned _number = 1, double _value = 0.0 )
  {
    currentEvents += _number;
    currentValue += _number * _value;
  }


  double AvgRate() const { return ( totalDuration > 0 ) ? ( totalEvents / totalDuration ) : 0; }
  double AvgValue() const { return ( totalEvents > 0 ) ? ( totalValue / totalEvents ) : 0; }
  bool HasNewValues() const { return newValues; }
  void ResetNewValuesFlag() { newValues = false; }

private:
  struct HistCell
  {
    unsigned  totalEvents;
    double    totalValue;
    timer::Time duration;
    HistCell() : totalEvents( 0 ), totalValue( 0 ), duration( 0 ) {}
    HistCell( unsigned _events, double _value, timer::Time _duration ) : totalEvents( _events ), totalValue( _value ), duration( _duration ) {}
  };

  size_t histCells;
  const timer::Time histCellDuration;
  CyclicBuffer<HistCell>  history;
  timer::Time lastUpdate;
  unsigned currentEvents;
  double currentValue;
  unsigned totalEvents;
  double totalValue;
  timer::Time totalDuration;
  bool newValues;
};


#endif //EVENTFREQUENCECALC_H_INCLUDED
