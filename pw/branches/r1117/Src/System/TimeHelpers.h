#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Класс позволяет сгладить изменения некоторой величины. Вместо изменения скачком, после 
// вызова метода Set, значение будет изменятся плавно и равномерно
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
class ValueChangeSmoother
{
public:
  ValueChangeSmoother() { SetTmmediately(0); } 

  ValueChangeSmoother( T _curValue, T _diffPerTick ) 
  {
    Init( _curValue, _diffPerTick );
  }
  
  void Init( T _curValue, T _diffPerTick )
  {
    curValue = destValue = _curValue;
    diffPerTick = _diffPerTick;
  }

  void SetTmmediately( T val ) { curValue = destValue = val; } 

  void Set( T val ) 
  { 
    destValue = val; 
    correctDiffPerTick();
  } 
  
  void SetSpeed( T _diffPerTick )
  {
    diffPerTick = _diffPerTick;
    correctDiffPerTick();
  }

  T Get() const { return curValue; }

  T Tick()
  {
    if( curValue != destValue )
      curValue = CalcNextVal( diffPerTick );

    return Get();
  }
  
  T Tick( float deltaTime )
  {
    if( curValue != destValue )
      curValue = CalcNextVal( diffPerTick * deltaTime );

    return Get();
  }
 
private:
  void correctDiffPerTick()
  {
    if( (destValue >= curValue) != (diffPerTick > 0) )
      diffPerTick = -diffPerTick;
  }

  T CalcNextVal( float diff ) const
  {
    const T nextValue = curValue + diff;

    return (curValue < destValue) != (nextValue > destValue ) ? 
           nextValue : destValue;
  }
  
private:
  T curValue;
  T destValue;
  T diffPerTick;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
// Универсальный таймер процессов длящихся определенное время или повторяющихся
// с определенной периодичностью.
// Помогает в реализации индикатора выполнения.
//////////////////////////////////////////////////////////////////////////////////////
class SimpleTimer
{   
public:
  SimpleTimer() { Reset(); }    

  //Сбросить таймер в исходное положение
  void Reset() { curTime = totalTime = FLT_MIN; }

  //Запустить таймер на срабатывание через time секунд
  void Start( float time ) { ASSERT(time >= 0); curTime = totalTime = time; }
   
  //Остановить таймер
  void Stop() { curTime = FLT_MIN; }
    
  //Запущен ли таймер в текущий момент и время срабатывания ещё не наступило
  bool IsInProgress() const { return curTime != FLT_MIN; }
  
  //Перезапустить со значением от предыдущего вызова Start
  void Restart() { ASSERT(time >= 0); curTime = totalTime; }
  
  //Установить время сохраненное в предыдущем вызове Start, что позволяет вместо 
  //в дальнейшем вместо Start вызвать Restart
  //Эквивалентно Start(time); Stop();
  void SetTotalTime( float time ) { ASSERT(time >= 0); totalTime = time;  } 
  
  //Время, на которое был запущен таймер в последний раз
  float GetTotalTime() const { return totalTime; }
  
  //Время до срабатывания таймера
  float GetTimeToAlarm() const { return curTime; }
  
  //Прошёл интервал времени deltaTime.
  //Если функция возвращает true, значит интервал времени прошёл. Для того
  //чтобы снова запустить таймер нужно вызвать Start() или Restart()
  bool Tick( float deltaTime )
  {          
    if ( IsInProgress() )
    {
      curTime -= deltaTime;

      if ( curTime <= 0 ) 
      { 
        Stop();      
        return true;
      }
    }

    return false;
  } 

  //Аналогична функции Tick, но автоматически перезапускает таймер 
  //на то же время после его срабатывания
  bool TickWithRestart( float deltaTime )
  {
    if ( IsInProgress() )
      return TickWithRestartNonStop( deltaTime );

    return false;
  }

  //Аналогична функции TickWithRestart, но требует чтобы при вызове 
  //таймер был запущен. Благодаря этому работает быстрее.
  bool TickWithRestartNonStop( float deltaTime )
  {
    ASSERT( IsInProgress() );

    curTime -= deltaTime;

    if ( curTime <= 0 ) 
    { 
      //Для повышения точности учитываем время, оставшееся с прошлого срабатывания
      curTime += totalTime;      
      return true;
    }

    return false;
  }

private:
  float curTime;   
  float totalTime;     
};

//Сколько времени прошло с начала работы таймера до срабатывания в процентах
inline float GetPercentProgress( const SimpleTimer &t )
{
  return (t.GetTotalTime() - t.GetTimeToAlarm()) * 100 / t.GetTotalTime(); 
}
