#pragma once

#include "nhash_map.h"

/**
Class Bidirectional Multimap
устанавливает соответствие "многие ко многим"
между элементами множества  1 и  2

TContainer1 и TContainer2 должны быть последовательност€ми ( STL Sequence )

метод Add( k1, k2[] )
добавл€ет соответстви€ k1 <-> каждый элемент k2

метод Del( k )
удал€ет все соответстви€ с участием k

метод Get( k )
возвращает ассоциированные с k элементы другого множества

метод Has( k )
сообщает, существует ли хот€ бы одно соответствие дл€ данного объекта k
*/

template<class K1, class K2, class TContainer1 = vector<K1>, class TContainer2 = vector<K2>>
class BiMultimap
{
	ZDATA
	hash_map<K1, TContainer2> map12;
	hash_map<K2, TContainer1> map21;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&map12); f.Add(3,&map21); return 0; } 

	BiMultimap() {}

	void SetElementsNumberEstimate( int nK1Elements, int nK2Elements )
	{
		map12.set_bucket_count( nK1Elements );
		map21.set_bucket_count( nK2Elements );
	}

	void Add( const K1& val1, const TContainer2 &val2 )
	{
		TContainer2 &links = map12[val1]; 
		links.insert( links.end(), val2.begin(), val2.end() );

		for( TContainer2::const_iterator it = val2.begin(); it != val2.end(); ++it )
			map21[*it].push_back( val1 );
	}
	void Add( const K2& val1, const TContainer1 &val2 )
	{
		TContainer1 &links = map21[val1]; 
		links.insert( links.end(), val2.begin(), val2.end() );

		for( TContainer1::const_iterator it = val2.begin(); it != val2.end(); ++it )
			map12[*it].push_back( val1 );
	}
	void Del( const K1& val )
	{
		hash_map<K1, TContainer2>::iterator it = map12.find( val );
		if ( it == map12.end() )
			return;
		TContainer2 &linked = it->second;
		for( TContainer2::const_iterator it = linked.begin(); it != linked.end(); ++it )
		{
			TContainer1 &links = map21[*it];
			links.erase( remove( links.begin(), links.end(), val), links.end() );
		}
		map12.erase( it );
	}
	void Del( const K2& val )
	{
		hash_map<K2, TContainer1>::iterator it = map21.find( val );
		if ( it == map21.end() )
			return;
		TContainer1 &linked = it->second;
		for( TContainer1::const_iterator it = linked.begin(); it != linked.end(); ++it )
		{
			TContainer2 &links = map12[*it];
			links.erase( remove( links.begin(), links.end(), val), links.end() );
		}
		map21.erase( it );
	}
	void Clear()
	{
		map12.clear();
		map21.clear();
	}
	bool Has( const K1 &val ) const
	{
		return	map12.find( val ) != map12.end();
	}
	bool Has( const K2 &val ) const
	{
		return	map21.find( val ) != map21.end();
	}
	const TContainer2 &Get( const K1 &val ) const
	{
		hash_map<K1, TContainer2>::const_iterator it = map12.find( val );
		if ( it != map12.end() )
			return it->second;

		static TContainer2 empty;
		return empty;
	}
	const TContainer1 &Get( const K2 &val ) const
	{
		hash_map<K2, TContainer1>::const_iterator it = map21.find( val );
		if ( it != map21.end() )
			return it->second;

		static TContainer1 empty;
		return empty;
	}
};

