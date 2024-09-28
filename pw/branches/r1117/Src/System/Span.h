#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Span
{
	T minValue;
	T maxValue;

public:
	//	Constructors (default copyctor)
	Span() :
		minValue( 0 ),
		maxValue( 0 )
	{}
	Span( T _minValue, T _maxValue ) :
		minValue( _minValue ),
		maxValue( _maxValue )
	{
		ASSERT( minValue <= maxValue );
	}
	//	Accessors
	T GetMin() const { return minValue; }
	void SetMin( T _minValue )
	{
		ASSERT( _minValue <= maxValue );
		minValue = _minValue;
	}
	T GetMax() const { return maxValue; }
	void SetMax( T _maxValue )
	{
		ASSERT( minValue <= _maxValue );
		maxValue = _maxValue;
	}
	//	Info
	T GetLength() const { return maxValue - minValue; }
	bool IsVoid() const { return minValue >= maxValue; }
	bool Touchs( T value ) const
	{
		return minValue <= value && value <= maxValue;
	}
	bool Holds( T value ) const
	{
		return minValue < value && value < maxValue;
	}
	bool Touchs( const Span	&span ) const
	{
		return minValue <= span.maxValue && maxValue >= span.minValue;
	}
	bool Intersects( const Span &span ) const
	{
		return minValue < span.maxValue && maxValue > span.minValue;
	}
	bool Holds( const Span &span ) const
	{
		return minValue <= span.minValue && span.maxValue <= maxValue;
	}
	bool HoldsIn( const Span &span ) const
	{
		return minValue < span.minValue && span.maxValue < maxValue;
	}
	T Clamp( T value ) const
	{
		if ( value <= minValue )
			return minValue;
		if ( value >= maxValue )
			return maxValue;
		return value;
	}
	template <class T1>
	T1 Interpolate( T value, const T1 &left, const T1 &right ) const
	{
		if ( value <= minValue )
			return left;
		if ( value >= maxValue )
			return right;
		T1 result = ( ( maxValue - value ) * left + ( value - minValue ) * right ) / GetLength();
		return result;
	}

	//	Operators
	Span	&operator&=( const Span	&span )
	{
		minValue = max( minValue, span.minValue );
		maxValue = min( maxValue, span.maxValue );
		if ( minValue > maxValue )
			maxValue = minValue;
		return *this;
	}
	Span	operator&( const Span	&span ) const
	{
		Span	result = *this;
		result &= span;
		return result;
	}
	Span	&operator|=( const Span	&span )
	{
		if ( IsVoid() )
			*this = span;
		else
		{
			minValue = min( minValue, span.minValue );
			maxValue = max( maxValue, span.maxValue );
		}
		return *this;
	}
	Span	operator|( const Span	&span ) const
	{
		Span	result = *this;
		result |= span;
		return result;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, int infiniteValue>
class InfiniteSpan
{
	T minValue;
	T maxValue;

public:
	//	Constructors (default copyctor)
	InfiniteSpan() :
		minValue( infiniteValue ),
		maxValue( infiniteValue )
	{}
	InfiniteSpan( T _minValue, T _maxValue ) :
		minValue( _minValue ),
		maxValue( _maxValue )
	{
		ASSERT( minValue == infiniteValue || maxValue == infiniteValue ||  minValue <= maxValue );
	}
	//	Accessors
	T GetMin() const { return minValue; }
	void SetMin( T _minValue )
	{
		if ( _minValue != infiniteValue && maxValue != infiniteValue &&  _minValue > maxValue )
			minValue = maxValue;
		else
			minValue = _minValue;
	}
	T GetMax() const { return maxValue; }
	void SetMax( T _maxValue )
	{
		if( minValue != infiniteValue && _maxValue != infiniteValue && minValue > _maxValue )
			maxValue = minValue;
		else
			maxValue = _maxValue;
	}

	bool IsVoid() const 
	{ 
		return minValue != infiniteValue && maxValue != infiniteValue && minValue >= maxValue; 
	}
	bool Touchs( T value ) const
	{
		return ( minValue == infiniteValue || minValue <= value ) && ( maxValue == infiniteValue || value <= maxValue );
	}
	bool Holds( T value ) const
	{
		return ( minValue == infiniteValue || minValue < value ) && ( maxValue == infiniteValue || value < maxValue );
	}

	// span starts after value 
	bool StartsAfter( T value ) const 
	{
		return minValue != infiniteValue && value < minValue;
	}
 	// span ends before value 
	bool EndsBefore( T value ) const 
	{
		return maxValue != infiniteValue && value >= maxValue;
	}

	T Clamp( T value ) const
	{
		if ( minValue != infiniteValue && value <= minValue )
			return minValue;
		if ( maxValue != infiniteValue && value >= maxValue )
			return maxValue;
		return value;
	}

	//	Operators
	InfiniteSpan& operator&=( const InfiniteSpan &span )
	{
		if ( minValue == infiniteValue )
			minValue = span.minValue;
		else if ( span.minValue == infiniteValue )
			minValue = minValue;
		else
			minValue = max( minValue, span.minValue );

		if ( maxValue == infiniteValue )
			maxValue = span.maxValue;
		else if ( span.maxValue == infiniteValue )
			maxValue = maxValue;
		else
			maxValue = min( maxValue, span.maxValue );

		if ( minValue != infiniteValue && maxValue != infiniteValue && minValue > maxValue )
			maxValue = minValue;
		return *this;
	}
	InfiniteSpan operator&( const InfiniteSpan  &span ) const
	{
		InfiniteSpan  result = *this;
		result &= span;
		return result;
	}
	InfiniteSpan& operator|=( const InfiniteSpan  &span )
	{
		if ( IsVoid() )
			*this = span;
		else
		{
			minValue = minValue == infiniteValue || span.minValue == infiniteValue ? infiniteValue : min( minValue, span.minValue );

			maxValue = maxValue == infiniteValue || span.maxValue == infiniteValue ? infiniteValue : max( maxValue, span.maxValue );
		}
		return *this;
	}
	InfiniteSpan operator|( const InfiniteSpan  &span ) const
	{
		InfiniteSpan result = *this;
		result |= span;
		return result;
	}
};
