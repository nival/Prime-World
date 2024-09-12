#ifndef DEBUGVAR_H_
#define DEBUGVAR_H_

#include "HPTimer.h"
#include "interlocked.h"

#ifdef WIN32
  #define NOVTABLE    __declspec(novtable)
#else
  #define NOVTABLE
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDebug
{
class Plotter
{
  float* vals;
  float* times;

  int count;
  float timeLimit;

  NHPTimer::STime lastTime;
  int curIdx;
public:
  // count - количество отсчетов по которым сторится график
  Plotter( int _count = 64, float _timeLimit = 0.0f )
  {
    count = _count;
    timeLimit = _timeLimit;
    if ( count == 0 )
    {
      vals = 0;
      times = 0;
      return;
    }
    vals = new float[count];
    times = new float[count];
    for ( int i = 0; i < count; i++ )
    {
      vals[i] = 0;
      times[i] = 0;
    }
    curIdx = 0;
    NHPTimer::GetTime( lastTime );
  }

  ~Plotter()
  {
    delete [] vals;
    delete [] times;
  }

  void AddValue( float val )
  {
    if ( count == 0 )
    {
      return;
    }

    double timePassed = NHPTimer::GetTimePassedAndUpdateTime( lastTime );
    if ( curIdx < count )
    {
      vals[curIdx] = val;
      times[curIdx] = timePassed;
    }
    else
    {
      curIdx = 0;
      vals[curIdx] = val;
      times[curIdx] = timePassed;
    }
    curIdx++;
  }

  void FillInfo( nstl::vector<float>& _vals, nstl::vector<float>& _times ) const
  {
    _vals.clear();
    _times.clear();

    if ( count == 0 )
    {
      return;
    }

    int internalIdx = curIdx;
    for ( int i = 0; i < count; i++ )
    {
      if ( internalIdx > count-1 )
      {
        internalIdx = 0;
      }
      _vals.push_back( vals[internalIdx] );
      _times.push_back( times[internalIdx] );
      internalIdx++;
    }
  }

  float TimeLimit() const
  {
    return timeLimit;
  }

  int Count() const
  {
    return count;
  }
};



class IDebugVar;

_interface IDebugVarWatcher : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IDebugVarWatcher, IBaseInterfaceST );

  virtual void OnDebugVarEvent( IDebugVar * debugVar ) = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DebugVarType
{
  enum Enum
  {
    None = 0,
    Bool = 1,
    Byte = 2,
    Int16 = 3,
    UInt16 = 4,
    Int32 = 5,
    UInt32 = 6,
    Int64 = 7,
    UInt64 = 8,
    Float = 9,
    Double = 10,
    String = 11
  };
};

class IDebugVar
{
public:
  virtual ~IDebugVar() {}
	
  virtual bool IsWarning() const = 0;
	virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const = 0;

  virtual const wchar_t * GetName() const = 0;
  virtual const byte GetType() const { return DebugVarType::None; };

  virtual void Reset( float deltaTime ) = 0;

  virtual const Plotter* GetPlotter() const = 0;
  virtual const Plotter* GetSecondPlotter() const = 0;

  virtual void AddChangeWatcher( IDebugVarWatcher * _watcher ) = 0;
  virtual void RemoveChangeWatcher( IDebugVarWatcher * _watcher ) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IDebugVar * FindDebugVar( const wchar_t * name );
vector< IDebugVar * > FindDebugVars( const wchar_t * mask );
void GetDebugVarValue( const wchar_t * name, wstring * pResult );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BaseDebugVar : public IDebugVar
{
public:
  BaseDebugVar( const char * name, bool resetOnFrame );
  ~BaseDebugVar();

  const wchar_t * GetName() const { return name; }

  virtual void Reset( float deltaTime ) {}

  virtual const Plotter* GetPlotter() const { return 0; }
  virtual const Plotter* GetSecondPlotter() const { return 0; }

  virtual void AddChangeWatcher( IDebugVarWatcher * _watcher );
  virtual void RemoveChangeWatcher( IDebugVarWatcher * _watcher );

protected:
  void NotifyAboutChange();

private:
  wchar_t name[64];

  typedef list< Weak< IDebugVarWatcher > > TWatchers;
  TWatchers  changeWatchers;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void FormatString( T* buffer, const int bufferSize, const T* format, va_list va );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void FormatString<char>( char* buffer, const int bufferSize, const char* format, va_list va );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void FormatString<wchar_t>( wchar_t* buffer, const int bufferSize, const wchar_t* format, va_list va );


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DebugVar<T>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class DebugVar : public BaseDebugVar
{
	T value;
	bool warning;

public:
  DebugVar( const char* name, const char* screen ) :
  BaseDebugVar( name, false ),
  value( T() ), warning( false ) { }

	void AddValue( const T& _value ) { value += _value; }
	void DecValue( const T& _value ) { value -= _value; }
	void SetValue( const T& _value ) {
    value = _value;
    warning = false;
    NotifyAboutChange();
  }
	const T& GetValue() const { return value; }
	//void SetValue( const T& _value, bool _warning ) { value = _value; warning = _warning; }

	virtual bool IsWarning() const { return warning; }
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const { return NStr::ToWString<T>( value, pBuffer, bufferLen ); }
};


template<typename T>
T GetDebugVarValue(const wchar_t* name)
{
  if( IDebugVar* const pVar = NDebug::FindDebugVar(name) )
    return static_cast<NDebug::DebugVar<T>*>(pVar)->GetValue();
  else
    return T();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
class DebugVar<float> : public BaseDebugVar
{
  float value;
  bool warning;
  Plotter plotter;

public:
  DebugVar( const char* name, const char* screen, bool resetOnFrame = false, int count = 0, float timeLimit = 0.0f ) :
  BaseDebugVar( name, resetOnFrame ),
  value( 0.0f ), warning( false ), plotter(count, timeLimit)
  {
    plotter.AddValue( value );
  }

  void AddValue( float _value ) 
  { 
    value += _value; 
    plotter.AddValue( value );
  }
  void DecValue( float _value ) 
  { 
    value -= _value; 
    plotter.AddValue( value );
  }
  void SetValue( float _value ) 
  { 
    value = _value; 
    plotter.AddValue( value );
    warning = false;
    NotifyAboutChange();
  }
  void SetValue( float _value, bool _warning ) 
  { 
    value = _value; 
    warning = _warning; 
    plotter.AddValue( value );
    NotifyAboutChange();
  }
  float GetValue() const { return value; }
  const Plotter* GetPlotter() const 
  { 
    if ( plotter.Count() )
      return &plotter;

    return 0;
  }

	virtual void Reset( float ) { value = 0.0f; }
  virtual bool IsWarning() const { return warning; }
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const { return NStr::ToWString<float>( value, pBuffer, bufferLen ); }
  virtual const byte GetType() const { return DebugVarType::Float; };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
class DebugVar<int> : public BaseDebugVar
{
  volatile int value;
  bool warning;
  Plotter plotter;

public:
  DebugVar( const char* name, const char* screen, bool resetOnFrame = false, int count = 0, float timeLimit = 0.0f ) :
  BaseDebugVar( name, resetOnFrame ),
  value( 0 ), warning( false ), plotter(count, timeLimit)
  {
    plotter.AddValue( value );
  }

  void AddValue( int _value ) 
  { 
    value += _value; 
    plotter.AddValue( value );
  }
  void DecValue( int _value ) 
  { 
    value -= _value; 
    plotter.AddValue( value );
  }
  void SetValue( int _value ) 
  { 
    SetValue(_value, false);
  }
  void SetValue( int _value, bool _warning ) 
  { 
    value = _value; 
    warning = _warning; 
    plotter.AddValue( value );
    NotifyAboutChange();
  }
  int GetValue() const { return value; }
  const Plotter* GetPlotter() const 
  { 
    if ( plotter.Count() )
      return &plotter;

    return 0;
  }

	virtual void Reset( float ) { value = 0; }
  virtual bool IsWarning() const { return warning; }
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const { int val = (int)value; return NStr::ToWString<int>( val, pBuffer, bufferLen ); }
  virtual const byte GetType() const { return DebugVarType::Int32; };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
class DebugVar<volatile int> : public BaseDebugVar
{
  volatile long value;
  bool warning;
  Plotter plotter;

public:
  DebugVar( const char* name, const char* screen, bool resetOnFrame = false, int count = 0, float timeLimit = 0.0f ) :
      BaseDebugVar( name, resetOnFrame ),
        value( 0 ), warning( false ), plotter(count, timeLimit)
      {
        plotter.AddValue( value );
      }

      void AddValue( int _value ) 
      { 
        nival::interlocked_exchange_add(value, (long)_value);
        plotter.AddValue( value );
      }
      void DecValue( int _value ) 
      { 
        nival::interlocked_exchange_add(value, -(long)_value);
        plotter.AddValue( value );
      }
      void SetValue( int _value ) 
      { 
        SetValue(_value, false);
      }
      void SetValue( int _value, bool _warning ) 
      { 
        nival::interlocked_exchange(value, (long)_value);
        warning = _warning; 
        plotter.AddValue( value );
        NotifyAboutChange();
      }
      int GetValue() const { return value; }
      const Plotter* GetPlotter() const 
      { 
        if ( plotter.Count() )
          return &plotter;

        return 0;
      }

      virtual void Reset( float ) { value = 0; }
      virtual bool IsWarning() const { return warning; }
      virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const { int val = (int)value; return NStr::ToWString<int>( val, pBuffer, bufferLen ); }
      virtual const byte GetType() const { return DebugVarType::Int32; };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StringDebugVar<class TChar, int length>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StringDebugVar : public BaseDebugVar
{
	enum { BUFFER_LENGTH = 128 };

	wchar_t buffer[BUFFER_LENGTH];

public:
  StringDebugVar( const char* name, const char* screen ) :
  BaseDebugVar( name, false )
  {
  	buffer[0] = 0;
  }

	void SetValue( const char* format, ... );
	void SetValue( const wchar_t* format, ... );

	template<typename TChar>
	void SetValue( const basic_string<TChar>& value ) { SetValue( value.c_str() ); } // bug here: percents will be interpreted like commands (with values missing!) [1/25/2011 paul.smirnov]

  const wchar_t* GetValue() const { return &buffer[0]; }

	virtual bool IsWarning() const { return false; }
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const { return NStr::ToWString<wchar_t const*>( buffer, pBuffer, bufferLen ); }
  virtual const byte GetType() const { return DebugVarType::String; };
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AverageCalculator<TNumber>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TNumber, int HISTORY_DEPTH = 64>
class AverageCalculator
{
	TNumber minValue;
	TNumber maxValue;
	TNumber avgValue;
	TNumber values[HISTORY_DEPTH];
	int valuesCount;
	int valuesOffset;

public:
	AverageCalculator( const TNumber& value ) : minValue( value ), maxValue( value ), avgValue( value ), valuesCount( 0 ), valuesOffset( 0 )
	{
		values[valuesOffset] = value;
	}
	AverageCalculator() : minValue( TNumber() ), maxValue( TNumber() ), avgValue( TNumber() ), valuesCount( -1 ), valuesOffset( -1 )
	{
	}

	void SetValue( const TNumber& value )
	{
		++valuesCount;
		++valuesOffset;
		valuesOffset %= HISTORY_DEPTH;

		values[valuesOffset] = value;

		minValue = values[0];
		maxValue = values[0];
		double tempAvg = (double)values[0];
		const int maxValuesCount = Min( (int)HISTORY_DEPTH, valuesCount + 1 );
		for( int i = 1; i < maxValuesCount; ++i )
		{
			minValue = Min( values[i], minValue );
			maxValue = Max( values[i], maxValue );
			tempAvg += values[i];
		}
		
		tempAvg /= maxValuesCount;
		avgValue = (TNumber)tempAvg;
	}

	const TNumber& GetMin() const { return minValue; }
	const TNumber& GetMax() const { return maxValue; }
	const TNumber& GetAvg() const { return avgValue; }
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PerformanceDebugVar<maxMallocs, maxMSecs>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PerformanceDebugVar : public BaseDebugVar
{
	int mallocs;
	int mallocsStart;

	double msecs;
	NHPTimer::STime msecsStart;

	AverageCalculator<int> mallocsAvg;
	AverageCalculator<double> msecsAvg;

  bool isResetOnFrame;

	int maxMallocs;
	double maxMSces;

  bool trackMallocs;
  bool trackMallocsStarted;

  Plotter timeplotter;
  Plotter mallocplotter;

public:
	PerformanceDebugVar( const char* name, const char* screen, const int _maxMallocs, const double _maxMSces, 
    const bool resetOnFrame, int count = 0, float timeLimit = 0.0f  ) :
  BaseDebugVar( name, resetOnFrame ),
    mallocs( 0 ), mallocsStart( 0 ), msecs( 0 ), msecsStart( 0 ), mallocsAvg( 0 ), msecsAvg( 0 ),
    isResetOnFrame( resetOnFrame ), maxMallocs( _maxMallocs ), maxMSces( _maxMSces ), trackMallocs( false ), trackMallocsStarted( false ),
    timeplotter( count, timeLimit ), mallocplotter( count, timeLimit ) { }

	void Start();
	void Start( const bool reset ) { if ( reset ) Reset( 0.0f ); Start(); }
	void Stop();

	int GetMallocs() const { return mallocs; }
	double GetMSecs() const { return msecs; }
  int GetMaxMallocs() const { return mallocsAvg.GetMax(); }
  double GetMaxMSecs() const { return msecsAvg.GetMax(); }
	
	virtual void Reset( float deltaTime );
  void Reset();

  const Plotter* GetPlotter() const 
  { 
    if ( timeplotter.Count() )
      return &timeplotter;

    return 0;
  }

  const Plotter* GetSecondPlotter() const 
  { 
    if ( mallocplotter.Count() )
      return &mallocplotter;

    return 0;
  }

	virtual bool IsWarning() const { return mallocs > maxMallocs || msecs > maxMSces; }
	virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const;

  void TrackMallocs( bool enable ) { trackMallocs = enable; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PerformanceDebugVarGuard
{
	PerformanceDebugVar& debugVar;

	DUMMY_ASSIGNMENT( PerformanceDebugVarGuard );
public:
	PerformanceDebugVarGuard( PerformanceDebugVar& _debugVar, const bool reset ) : debugVar( _debugVar )
  {
    debugVar.Start( reset );
  }
	~PerformanceDebugVarGuard() { debugVar.Stop(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PerformanceGuard
{
  NHPTimer::STime start;
  const double limit;
  const NLogg::ELevel level;
  const char* message;

	DUMMY_ASSIGNMENT( PerformanceGuard );
public:
  PerformanceGuard( const double limit, const NLogg::ELevel level, const char* message );
  ~PerformanceGuard();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Moving average, window size = AverageCalculator::VALUES_COUNT
template<typename T>
class AverageDebugVar : public BaseDebugVar
{
	AverageCalculator<T> averageCalc;

public:
  AverageDebugVar( const char* name, const char* screen ) : BaseDebugVar( name, false ) { }

	void AddValue( const T& _value ) 
	{ 
		averageCalc.SetValue( _value );
    NotifyAboutChange();
	}

	const AverageCalculator<T>& GetAverage() const { return averageCalc; }

	virtual bool IsWarning() const { return false; }
	virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AsynchDebugVar<T>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
class AsynchDebugVar: AverageDebugVar< T >
{
  T curValue;
public:
  AsynchDebugVar( const char* name, const char* screen ) : AverageDebugVar< T >( name, screen ), curValue( T() ){ }

  void AddValue( const T& _value ) { curValue += _value; }
  void DecValue( const T& _value ) { curValue -= _value; }

  void SetValue( const T& _value )
  {
    AverageDebugVar< T >::AddValue(curValue);
    curValue = _value;
    this->NotifyAboutChange();
  }

  T const& GetImmValue() const     {return curValue;}        
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Moving average of value per second, window size ~ AverageCalculator::VALUES_COUNT * averageGran seconds
template<typename T>
class AveragePerSecondDebugVar : public BaseDebugVar
{
	T valueAcc;
	NHPTimer::STime accStartTime;
	double averageGran;

	T totalValue;
	AverageCalculator<T> averageCalc;

public:
  AveragePerSecondDebugVar( const char* name, const char* screen, double _averageGran = 1.0 ) :
  BaseDebugVar( name, false ),
	valueAcc( T() ), totalValue( T() ), accStartTime( 0 ), averageGran( _averageGran ) 
	{
		NHPTimer::GetTime( accStartTime );
	}

	void AddValue( const T& _value ) 
	{ 
		valueAcc += _value; 
		totalValue += _value;
		NHPTimer::STime curTime(accStartTime);
		double timePassed = NHPTimer::GetTimePassedAndUpdateTime( curTime );
		if ( timePassed >= averageGran )
		{
			averageCalc.SetValue( valueAcc / timePassed );
			accStartTime = curTime;
			valueAcc = T();
		}

    NotifyAboutChange();
	}

	const AverageCalculator<T>& GetAverage() const { return averageCalc; }
	const T& GetTotal() const { return totalValue; }

	virtual bool IsWarning() const { return false; }
	virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Moving average of value per second, window size ~ AverageCalculator::VALUES_COUNT * averageGran seconds
template<typename T>
class AveragePerSecondDebugVar2 : BaseDebugVar
{
  T valueAcc;

  T totalValue;
  AverageCalculator<T> averageCalc;

public:
  AveragePerSecondDebugVar2( const char* name, const char* screen ) :
  BaseDebugVar( name, true ),
  valueAcc( T() ), totalValue( T() ) { }

  virtual void Reset( float deltaTime )
  {
    if ( deltaTime <= 0.0f )
      return;
    averageCalc.SetValue( valueAcc / deltaTime );
    valueAcc = T();
  }

  void AddValue( const T& _value ) 
  { 
    valueAcc += _value; 
    totalValue += _value;

    NotifyAboutChange();
  }

  const AverageCalculator<T>& GetAverage() const { return averageCalc; }
  const T& GetTotal() const { return totalValue; }

  virtual bool IsWarning() const { return false; }
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// call this function every frame to reset perfomance counters
void ResetDebugVarsOnFrame( float deltaTime );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// iterate through debug vars 
#ifdef WIN32
typedef void (__stdcall* TProcessEveryDebugVarsFunc)( const wchar_t* screen, const wchar_t* name, const NDebug::IDebugVar* var, void* pData );
#else
typedef void (*TProcessEveryDebugVarsFunc)( const wchar_t* screen, const wchar_t* name, const NDebug::IDebugVar* var, void* pData );
#endif
void ProcessAllDebugVars( TProcessEveryDebugVarsFunc func, void* pData );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NDebug

#endif

