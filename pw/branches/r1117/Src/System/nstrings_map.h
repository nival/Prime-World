#ifndef _NSTRINGS_MAP_H_
#define _NSTRINGS_MAP_H_

// Strings.h
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class strings_map
	{
		struct Node
		{
			ZDATA
			string key;
			T element;
			ZEND int operator&( IBinSaver &f ) { f.Add(2,&key); f.Add(3,&element); return 0; }
		};

		ZDATA
			vector<vector<Node> > buckets;
	public:
		ZEND int operator&( IBinSaver &f ) { f.Add(2,&buckets); return 0; }
		strings_map()
		{
			buckets.clear();
			buckets.resize( 256 );
		}

		bool Add( const char *key, const T & element )
		{
			if ( !key )
				return false;
			if ( Find( (T*)0, key ) )
				return false; // failed: already added

			vector<Node> & nodes = buckets[ key[0] ];
			nodes.push_back();
			nodes.back().key = key+1; // empty strings supported
			nodes.back().element = element;
			return true; // success: added
		}

		bool Find( T *p, const char *key ) const
		{
			if ( !key )
				return false;
			const vector<Node> & nodes = buckets[ key[0] ];
			for ( int i = 0; i < nodes.size(); ++i )
			{
				if ( strcmp( nodes[i].key.c_str(), key+1 ) == 0 )
				{
					if ( p )
						*p = nodes[i].element;
					return true;
				}
			}
			return false;
		}

		bool Find( T **p, const char *key )
		{
			if ( !key )
				return false;
			vector<Node> & nodes = buckets[ key[0] ];
			for ( int i = 0; i < nodes.size(); ++i )
			{
				if ( strcmp( nodes[i].key.c_str(), key+1 ) == 0 )
				{
					if ( p )
						*p = &nodes[i].element;
					return true;
				}
			}
			return false;
		}

		T& Demand( const char *key ) 
		{
			vector<Node> & nodes = buckets[ key[0] ];
			for ( int i = 0; i < nodes.size(); ++i )
			{
				if ( strcmp( nodes[i].key.c_str(), key+1 ) == 0 )
				{
					return nodes[i].element;
				}
			}
			nodes.push_back();
			nodes.back().key = key+1; // empty strings supported
			return nodes.back().element;
		}

		bool Delete(  const char *key )
		{
			if ( !key )
				return false;
			vector<Node> & nodes = buckets[ key[0] ];
			for ( int i = 0; i < nodes.size(); ++i )
			{
				if ( strcmp( nodes[i].key.c_str(), key+1 ) == 0 )
				{
					nodes.erase( nodes.begin() + i );
					return true;
				}
			}
			return false;
		}
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class StringsBucket
	{
		struct Leaf
		{
			string suffix;
			T element;
		};

		struct Branch
		{
			string prefix;
			StringsBucket *p;

			Branch(): p(0) {}
			~Branch() { if (p) { delete p; p = 0; } }
			const Branch & operator = ( const Branch & b )
			{
				prefix = b.prefix;
				p = 0;
				if ( b.p ) { p = new StringsBucket<T>(); *p = *b.p; }
				return *this;
			}
			Branch( const Branch & b ) { *this = b; }

			int Check( const char *s )
			{
				if ( !s )
					return 0;
				const int ln = prefix.size();
				for ( int i = 0; i < ln; ++i )
					if ( !s[i] || s[i] != prefix[i] )
						return 0;
				return ln;
			}
		};

		vector<Leaf> leafs;
		vector<Branch> branches;

		int FindLeaf( char startChar, bool bLast )
		{
			for ( int i = 0; i < leafs.size(); ++i )
			{
				const char *suffix = leafs[i].suffix.c_str();
				if ( suffix && suffix[0] == startChar && bLast == (suffix[1]==0) )
					return i;
			}
			return -1;
		}

		void AddLeaf( const char *suffix, const T & element )
		{
			Leaf leaf;
			leaf.suffix = suffix;
			leaf.element = element;
			leafs.push_back( leaf );
		}

		void RemoveLeaf( int index )
		{
			NI_VERIFY( index >= 0 && index < leafs.size(), "Invalid index!", return );
			leafs.erase( leafs.begin() + index );
		}

		StringsBucket *AddBranch( char startChar )
		{
			StringsBucket<T> *p = new StringsBucket<T>();
			if ( !p )
				return 0;

			char s[2];
			s[0] = startChar;
			s[1] = 0;

			branches.push_back();
			branches.back().prefix = s;
			branches.back().p = p;

			return p;
		}

	public:
		bool Add( const char *s, const T & element )
		{
			if ( !s || !s[0] )
				return false; // failed: no key

			if ( !s[1] )
			{
				if ( FindLeaf( s[0], true ) != -1 )
					return false; // failed: already added
				AddLeaf( s, element );
				return true;
			}

			int moveLeaf = FindLeaf( s[0], false );

			if ( moveLeaf == -1 )
			{
				for ( int i = 0; i < branches.size(); ++i )
					if ( int d = branches[i].Check( s ) )
						return branches[i].p->Add( s+d, element );

				AddLeaf( s, element );
				return true;
			}

			if ( strcmp( leafs[ moveLeaf ].suffix.c_str(), s ) == 0 )
				return false; // failed: already added

			StringsBucket *p = AddBranch( s[0] );
			if ( !p )
				return false; // failed: bad alloc

			p->AddLeaf( leafs[ moveLeaf ].suffix.c_str()+1, leafs[ moveLeaf ].element );
			RemoveLeaf( moveLeaf );

			return p->Add( s+1, element );
		}

		void Defragment()
		{
			for ( int i = 0; i < branches.size(); ++i )
			{
				StringsBucket *p = branches[i].p;
				while ( p && p->leafs.empty() && p->branches.size() == 1 )
				{
					branches[i].prefix += p->branches[0].prefix;
					branches[i].p = p->branches[0].p;
					p->branches[0].p = 0;
					delete p;
					p = branches[i].p;
				}

				p->Defragment();
			}
		}

		bool Find( T *p, const char *s ) const
		{
			if ( !s || !s[0] )
				return false;

			for ( int i = 0; i < leafs.size(); ++i )
			{
				const char *suffix = leafs[i].suffix.c_str();
				if ( suffix && strcmp( suffix, s ) == 0 )
				{
					if ( p ) 
						*p = leafs[i].element;
					return true;
				}
			}

			for ( int i = 0; i < branches.size(); ++i )
				if ( int d = branches[i].Check( s ) )
					return branches[i].p->Find( p, s+d );

			return false;
		}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/*
//--------------------
#include "Strings.h"
#include "../System/HPTimer.h"

class XXX
{
public:
	XXX();
};
struct YYY
{
	int z;
};
XXX t;
XXX::XXX()
{
	StringsBucket<YYY> t[256];
	strings_map<YYY> strs;
	YYY e;
	e.z = 5;

	const char *ss[] = {
		"mana",
		"manaMax",
		"movePoints",
		"movePointsMax",
		"name",
		"class",
		"exp",
		"level",
		"skills",
		"abilities",
		"pos",
		"army",
		"player",
		"town",
		"warMachines",
		"visited",
		"movemode",
		"avenger",
		"aiparams",
		"spells",
		"holder",
		"kills",
		"justfled",
		"deaths",
		"triggers",
		"puton",
		"backpack",
		"microArtifacts",
		"allows",
		"denies",
		"talisman",
		"skillsMemory",
		"minStats",
		"baseStats",
		"bonusStats",
		"battleEffects",
	};
	const int ssn = sizeof(ss)/sizeof(ss[0]);

	vector<string> z;
	for ( int i = 0; i < ssn; ++i )
		z.push_back( ss[i] );

	for ( int i = 0; i < ssn; ++i )
	{
		e.z  = i;
		t[ ss[i][0] ].Add( ss[i]+1, e );
	}

	for ( int i = 0; i < 256; ++i )
		t[i].Defragment();

	for ( int i = 0; i < ssn; ++i )
	{
		e.z = i;
		strs.Add( ss[i], e );
	}


	NHPTimer::STime t0;
	NHPTimer::STime t1;
	const int maxCycles = 10000;

	NHPTimer::GetTime( &t0 );
	for ( int cycles = 0; cycles < maxCycles; ++cycles )
	{
		for ( int i = 0; i < z.size(); ++i )
		{
			if ( strcmp( z[i].c_str(), ss[cycles % ssn] ) == 0 )
				break;
		}
	}
	NHPTimer::GetTime( &t1 );
	int T1 = int(t1-t0);

	NHPTimer::GetTime( &t0 );
	for ( int cycles = 0; cycles < maxCycles; ++cycles )
	{
		YYY e;
		const int z = cycles % ssn;
		const char *s = ss[z];
		if ( t[ s[0] ].Find( &e, s+1 ) )
		{
			NI_ASSERT( e.z == z, "Invalid find!" );
		}
		else
		{
			NI_ASSERT( 0, "Oops!" );
		}
	}
	NHPTimer::GetTime( &t1 );
	int T2 = int(t1-t0);

	NHPTimer::GetTime( &t0 );
	for ( int cycles = 0; cycles < maxCycles; ++cycles )
	{
		YYY e;
		const int z = cycles % ssn;
		if ( strs.Find( &e, ss[z] ) )
		{
			NI_ASSERT( e.z == z, "Invalid find!" );
		}
		else
		{
			NI_ASSERT( 0, "Oops!" );
		}
	}
	NHPTimer::GetTime( &t1 );
	int T3 = int(t1-t0);

	T1 = 0;
}
//--------------------
*/

#endif // _NSTRINGS_MAP_H_

