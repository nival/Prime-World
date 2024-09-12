#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
namespace AnimatedAlgorithms
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Discrete
{
	template<typename T>
	struct ReturnType
	{
		typedef const T& return_type;
	};

	template<typename T>
	static const T& Calculate( float key, typename Animated<T, Discrete>::const_iterator left, typename Animated<T, Discrete>::const_iterator right )
	{
		return left->value;
	}
};


template<>
inline const CQuat& Discrete::Calculate<CQuat>( float key, Animated<CQuat, Discrete>::const_iterator left, Animated<CQuat, Discrete>::const_iterator right )
{
  return left->value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Linear
{
	template<typename T>
	struct ReturnType
	{
		typedef const T return_type;
	};

	template<typename T>
	static const T Calculate( float key, typename Animated<T, Linear>::const_iterator left, typename Animated<T, Linear>::const_iterator right )
	{
		if ( left == right )
			return left->value;

		return left->value + (T)((right->value - left->value)*(key - left->key)/(right->key - left->key));
	}
};

template<>
inline const CQuat Linear::Calculate( float key, Animated<CQuat, Linear>::const_iterator left, Animated<CQuat, Linear>::const_iterator right )
{
  if ( left == right )
    return left->value;

  float factor = (key - left->key)/(right->key - left->key);

  CQuat result;
  result.Slerp( factor, left->value, right->value );
  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // AnimatedAlgorithms
}; // namespace NDb
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
