#ifndef _BITMAP_H_
#define _BITMAP_H_

/**
Class Bidirectional Map
устанавливает взаимооднозначное соответствие
между элементами множества К1 и К2

метод Set( k1, k2 )
	устанавливает соответствие между элементами K1 и K2
	в случае если k1 или k2 находились в других соответствиях, то старые
	соответствия удаляются в пользу нового

метод Get( k )
	возвращает ассоциированный с k элемент другого множества

метод Del( k )
	удаляет соответствие, в котором участвует k

метод has( k )
	сообщает, существует ли связка для данного объекта k
*/
template<class K1, class K2>
struct CBiMap
{
	typedef hash_map<K1, K2> TMap12;
	typedef hash_map<K2, K1> TMap21;

	TMap12 map12;
	TMap21 map21;

	template<class C1, class C2>
		const C2 &Get( const C1 &k, const hash_map<C1,C2> &M ) const
	{
		hash_map<C1, C2>::const_iterator it = M.find( k );
		if ( it != M.end() )
		{
			return it->second;
		}
		else
		{
			static C2 dummy;
			return dummy;
		}
	}

	const K2 &Get( const K1 &k1 ) const { return Get<K1, K2>( k1, map12 ); }
	const K1 &Get( const K2 &k2 ) const { return Get<K2, K1>( k2, map21 ); }

	template<class C1, class C2>
		bool Has( const C1 &c1, const hash_map<C1,C2> &M ) const
	{
		return M.find(c1) != M.end();
	}

	bool Has( const K1 &k1 ) const { return Has<K1, K2>( k1, map12 ); }
	bool Has( const K2 &k2 ) const { return Has<K2, K1>( k2, map21 ); }

	template<class C1, class C2>
		void Set( const C1 &c1, const C2 &c2, hash_map<C1,C2> &M12, hash_map<C2,C1> &M21 )
	{
		Del( c1 );
		Del( c2 );

		M12[c1] = c2;
		M21[c2] = c1;
	}

	void Set( const K1 &k1, const K2 &k2 ) { Set<K1, K2>( k1, k2, map12, map21 ); }
	void Set( const K2 &k2, const K1 &k1 ) { Set<K2, K1>( k2, k1, map21, map12 ); }

	template<class C1, class C2>
		void Del( const C1 &c1, hash_map<C1,C2> &M12, hash_map<C2,C1> &M21 )
	{
		hash_map<C1, C2>::iterator it = M12.find( c1 );
		if ( it != M12.end() )
		{
			const C2 &c2 = it->second;

			M21.erase( c2 );
			M12.erase( c1 );
		}
	}

	void Del( const K1 &k1 ) { Del<K1, K2>( k1, map12, map21 ); }
	void Del( const K2 &k2 ) { Del<K2, K1>( k2, map21, map12 ); }

	void Clear()
	{
		map12.clear();
		map21.clear();
	}

	void IsEmpty() const
	{
		return map12.empty() /*&& map21.empty()*/;
	}
};

#endif

