#pragma once

namespace PF_Minigames {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Number of non-zero elements in vector.
template <class T> int CountChoices( const vector<T> &data )
{
	int nChoices = 0;
	for ( int i = 0; i < data.size(); i++ )
	{
		if ( IsValid(data[i] ) )
			nChoices += 1;
	}

	return nChoices;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RandomGenerator
{
private:
	int randomSeed;
	int Random();
	static const double fMaxInt;
public:
	RandomGenerator( int _randomSeed = 0 ) : randomSeed(_randomSeed) {}

	// current random seed.
	int GetRandomSeed() const { return randomSeed; }
	void SetRandomSeed( int seed ) { randomSeed = seed; }
	// generate seed from timestamp
	void TrueRandomize();

	// Random in range [0..max-1]
	unsigned int Random( const unsigned int max )
	{
		if ( max == 0 )
			return 0;
		return (unsigned int)Random() % max;
	}

	// Random in range [min..max], must be (min <= max)!
	int Random( const int min, const int max )
	{ 
		return min + Random( (unsigned int)(max - min + 1) );
	}

	// Random in range [min..max], must be (min <= max)!
	float Random( const float min, const float max )
	{
		return min + float( double( (unsigned int)Random() / fMaxInt ) * double(max - min) );
	}

	float RandomNormal( const float min, const float max );
	int RollDices( int dices, int faces );

	// Random choose from vector with 0 elements.
	template <class T> int RandomChoose( const vector<T> &data )
	{
		int nChoices = CountChoices( data );
		if ( nChoices == 0 )
			return -1;

		int nChoose = 0;
		if ( nChoices > 1 )
			nChoose = Random( nChoices );

		nChoices = 0;
		for ( int i = 0; i < data.size(); i++ )
		{
			if ( IsValid(data[i] ) )
			{
				if ( nChoices == nChoose )
					return i;

				nChoices += 1;
			}
		}

		return -1;
	}

	static RandomGenerator& GetDefault();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace PF_Minigames