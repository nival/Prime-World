#pragma once

#include "Db.h"
#include "XmlSaver.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enum and its helper for serialization
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum AnimatedType
{
	ANIMATED_NONE,
	ANIMATED_CLAMP,
	ANIMATED_WRAP,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
struct KnownEnum<AnimatedType>
{
	enum { isKnown = 1 };

	static const char *ToString( const AnimatedType value )
	{
		switch( value )
		{
		case ANIMATED_NONE:
			return "None";
		case ANIMATED_CLAMP:
			return "Clamp";
		case ANIMATED_WRAP:
			return "Wrap";
		};

		NI_ALWAYS_ASSERT( NI_STRFMT( "Invalid value %d for enum AnimatedType", (int)value ) );
		return "Invalid";
	}
	static const AnimatedType ToEnum( const string &value )
	{
		if ( value == "None" || value == "ANIMATED_NONE" )
			return ANIMATED_NONE;
		if ( value == "Clamp" || value == "ANIMATED_CLAMP" )
			return ANIMATED_CLAMP;
		if ( value == "Wrap" || value == "ANIMATED_WRAP" )
			return ANIMATED_WRAP;

		NI_ALWAYS_ASSERT( NI_STRFMT( "Invalid value %s for enum AnimatedType", value ) );
		return ANIMATED_NONE;
	}

	static const int SizeOf() { return 3; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaration
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
class Animated
{
public:

	struct KeyValue
	{
		float key;
		T value;

		KeyValue() : key( 0 ), value( T() ) { }
		KeyValue( const T& _value ) : key( 0 ), value( _value ) { }
		KeyValue( float _key, const T& _value ) : key( _key ), value( _value ) { }

		int operator&( IXmlSaver& saver );
    KeyValue& operator = ( const KeyValue& source ) { key = source.key; value = source.value; return *this; }
	};

	typedef vector<KeyValue> TValues;
	typedef typename TValues::const_iterator const_iterator;
	typedef T TAnimatedType;
	typedef TAlgorithm TAnimatedAlgorithm;
  typedef Animated<T, TAlgorithm> TSelf;

	Animated() : type( ANIMATED_NONE ), length( 0 ) { values.push_back( KeyValue( T() ) );	}
	Animated( const T& value ) : type( ANIMATED_NONE ), length( 0 ) { values.push_back( KeyValue( value ) ); }

	int operator&( IXmlSaver& saver );

	operator const T&() const { return values[0].value; }
	bool IsAnimated() const { return type != ANIMATED_NONE; }
	float GetLength() const { return length; }

	typename TAlgorithm::template ReturnType<T>::return_type GetValue( float key ) const;
	typename TAlgorithm::template ReturnType<T>::return_type GetValue( float key, const_iterator left, const_iterator right ) const;

	typename TAlgorithm::template ReturnType<T>::return_type GetDiff( float key ) const;
	typename TAlgorithm::template ReturnType<T>::return_type GetDiff( const_iterator left, const_iterator right ) const;

  float ShiftKey( float key, float dt, const_iterator* pLeft, const_iterator* pRight ) const;

  const_iterator begin() const { return values.begin(); }
  const_iterator end() const { return values.end(); }
	const_iterator find( float key ) const;

  const CVec2 GetPoint( const_iterator iter ) const { return CVec2( iter->key, iter->value ); }
  const CVec2 GetPoint( const int i ) const { return GetPoint( begin() + i ); }
  const int Count() const { return values.size(); }

  TSelf& operator = ( const TSelf& source ) { type = source.type; length = source.length; values = source.values; return *this; }
private:
	AnimatedType type;
	float length;
	TValues values;

	void SimpleDeserialization( IXmlSaver& saver );
	void FullDeserialization( IXmlSaver& saver );

	float Clamp( float t ) const;
	float Wrap( float t ) const;
	float GetKey( float t ) const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
int Animated<T, TAlgorithm>::KeyValue::operator&( IXmlSaver& saver )
{
	saver.Add( "Key", &key );
	saver.Add( "Value", &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
int Animated<T, TAlgorithm>::operator&( IXmlSaver& saver )
{
	//NI_VERIFY( saver.IsReading(), "Animated<T> doesn't support serialization", return 0 );
	if (!saver.IsReading())
		return 0; 

	if ( !saver.HasAnimatedAttr() )
		SimpleDeserialization( saver );
	else
		FullDeserialization( saver );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
typename TAlgorithm::template ReturnType<T>::return_type Animated<T, TAlgorithm>::GetValue( float key ) const
{
	const float calculatedKey = GetKey( key );
	const_iterator left = find( calculatedKey );
	const_iterator right = left + 1;
	if ( right == values.end() )
		right = left;

	return GetValue( key, left, right );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
typename TAlgorithm::template ReturnType<T>::return_type Animated<T, TAlgorithm>::GetValue( float key, const_iterator left, const_iterator right ) const
{
	return TAlgorithm::template Calculate<T>( key, left, right );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
typename TAlgorithm::template ReturnType<T>::return_type Animated<T, TAlgorithm>::GetDiff( float key ) const
{

  NI_VERIFY( Count() > 1, NI_STRFMT( "Can't calculate differential when only %d points!", Count() ), return 0.0f );

  const float calculatedKey = GetKey( key );
	const_iterator left = find( calculatedKey );
	const_iterator right = left + 1;

  if ( right == values.end() )
  {
    right--;
    left--;
  }

	return GetDiff( left, right );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
typename TAlgorithm::template ReturnType<T>::return_type Animated<T, TAlgorithm>::GetDiff( const_iterator left, const_iterator right ) const
{
  float x1 = left->key;
  float x2 = right->key;

  NI_VERIFY( abs( x1 - x2 ) >= 1e-7, "Can't calculate differential when points's \"x\" coordinates is equal!", return 0.0f );

  typename TAlgorithm::template ReturnType<T>::return_type y1 = left->value;
  typename TAlgorithm::template ReturnType<T>::return_type y2 = right->value;

	return ( y2 - y1 ) / ( x2 - x1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
float Animated<T, TAlgorithm>::ShiftKey( float key, float dt, const_iterator* pLeft, const_iterator* pRight ) const
{
	float result = GetKey( key + dt );

	if ( dt == 0 || dt > length || result < (*pLeft)->key )
	{
		*pLeft = find( result );
		*pRight = *pLeft + 1;
		if ( *pRight == values.end() )
			*pRight = *pLeft;
	}
	else if ( result > (*pRight)->key )
	{
		do
		{
			++(*pLeft);
			++(*pRight);
		} while ((*pRight) != values.end() && result >= (*pRight)->key );
		
		if ( *pRight == values.end() )
			*pRight = *pLeft;
	}

	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
typename Animated<T, TAlgorithm>::const_iterator Animated<T, TAlgorithm>::find( float key ) const
{
	const int size = values.size() - 1;
	int left = 0;
	int right = size;
	int index = 0;

	while ( right != left )
	{
		index = ( left + right ) / 2;
		if ( values[index].key > key )
			right = index;
		else if ( values[index + 1].key < key )
			left = index + 1;
		else if ( values[index + 1].key == key )
			return &values[index + 1];
		else
			return &values[index];
	}

	return &values[left];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
void Animated<T, TAlgorithm>::SimpleDeserialization( IXmlSaver& saver )
{
	values.clear();

	T value;
	saver.Add( "", &value );
	
	values.push_back( KeyValue( value ) );
	type = ANIMATED_NONE;
	length = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
void Animated<T, TAlgorithm>::FullDeserialization( IXmlSaver& saver )
{
	saver.Add( "Type", &type );
	saver.Add( "Values", &values );

	if ( values.size() < 2 || values.back().key == 0 )
	{
		type = ANIMATED_NONE;
		length = 0;
		values.push_back( KeyValue( T() ) );
	}
	else
		length = values.back().key;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
float Animated<T, TAlgorithm>::GetKey( float t ) const
{
	switch( type )
	{
	case ANIMATED_CLAMP:
		return Clamp( t );
	case ANIMATED_WRAP:
		return Wrap( t );
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
float Animated<T, TAlgorithm>::Clamp( float t ) const
{
	if ( t < 0 )
		return 0;
	if ( t > length )
		return length;
	return t;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, class TAlgorithm>
float Animated<T, TAlgorithm>::Wrap( float t ) const
{
	if ( length == 0 )
		return 0;
	if ( t < 0 )
		return length + fmod( t, length ); 

	return fmod( t, length ); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NDb

