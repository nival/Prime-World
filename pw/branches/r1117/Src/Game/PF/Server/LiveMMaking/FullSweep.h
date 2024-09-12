#ifndef MMAKING_FULLSWEEP_H_INCLUDED
#define MMAKING_FULLSWEEP_H_INCLUDED

#include "Server/LobbyPvx/CommonTypes.h"

namespace mmaking
{

template <class TSampleSlot, class TDraft>
class TFullSweepAlgorithm
{
public:
  //Next methods have to be defined:
  // int TSampleSlot::GetSlotSize() const;
  //
  // void TDraft::PushBack( int teamIndex, const TSampleSlot & slot );
  // void TDraft::PopBack( int teamIndex, const TSampleSlot & slot );
  // void TDraft::CheckOut();

  class Sample {
    friend TFullSweepAlgorithm;
    vector<TSampleSlot> line[2];
    int                 length[2]; //In people-positions, NOT in requests
    vector<int>         positionsLeft[2]; //How many people-positions left in line, NOT counting self

  public:
    Sample()
    {
      length[0] = length[1] = 0;
    }

    void Reserve( int size ) {
      for ( int t = 0; t < 2; ++t )
        line[t].reserve( size );
    }

    void Push( lobby::ETeam::Enum team, const TSampleSlot & slot ) {
      int tidx = lobby::ETeam::Index( team );
      line[tidx].push_back( slot );
      length[tidx] += slot.GetSlotSize();
    }

    int Size( lobby::ETeam::Enum team ) const {
      int tidx = lobby::ETeam::Index( team );
      return line[tidx].size();
    }

    int Length( lobby::ETeam::Enum team ) const {
      int tidx = lobby::ETeam::Index( team );
      return length[tidx];
    }

    const TSampleSlot & GetSlot( lobby::ETeam::Enum team, int index ) const {
      int tidx = lobby::ETeam::Index( team );
      NI_ASSERT( index >= 0 && index < line[tidx].size(), "" );
      return line[tidx][index];
    }
  };



  static void PreprocessSample( Sample & sample )
  {
    NI_PROFILE_FUNCTION;

    for ( int t = 0; t < 2; ++t )
    {
      vector<TSampleSlot> & line = sample.line[t];

      //To optimize full sweep iterations, we should sort sample to put party-requests in a head of the line
      for ( int i = 0; i < line.size(); ++i )
        for ( int j = i + 1; j < line.size(); ++j )
          if ( line[i].GetSlotSize() < line[j].GetSlotSize() )
            swap( line[i], line[j] );

      int slots = 0;

      sample.positionsLeft[t].resize( line.size() );
      for ( int i = line.size() - 1; i >= 0; --i ) {
        slots += line[i].GetSlotSize();
        sample.positionsLeft[t][i] = slots;
      }
    }
  }


  //heterogeneous
  static unsigned FullSweepHetero( const Sample & sample, TDraft & draft, int teamSize )
  {
    NI_PROFILE_FUNCTION;

    return FullSweepIterationHetero( sample, 0, 0, teamSize, draft, teamSize );
  }


  //homogeneous
  //always using only the first part of the line
  static unsigned FullSweepHomo( const Sample & sample, TDraft & draft, int teamSize )
  {
    NI_PROFILE_FUNCTION;
    NI_ASSERT( sample.line[1].empty(), "" );

    return FullSweepIterationHomo( sample, 0, 0, teamSize, teamSize, draft, teamSize );
  }


  //always using only the first part of the line
  static unsigned FullSweepSingleSide( const Sample & sample, TDraft & draft, int teamSize )
  {
    NI_PROFILE_FUNCTION;
    NI_ASSERT( sample.line[1].empty(), "" );

    return FullSweepIterationHomo( sample, 0, 0, teamSize, 0, draft, teamSize );
  }


private:
  static unsigned FullSweepIterationHetero( const Sample & sample, int tidx, int startIdx, int posToPlace, TDraft & draft, int teamSize )
  {
    if ( posToPlace <= 0 )
    {
      if ( tidx == 0 ) //Just finished iterations for first side; Let's run them for another side
        return FullSweepIterationHetero( sample, 1, 0, teamSize, draft, teamSize );

      draft.CheckOut();
      return 1;
    }

    unsigned iterations = 0;
    const vector<TSampleSlot> & line = sample.line[tidx];
    const vector<int> & posLeft = sample.positionsLeft[tidx];

    int limit = line.size();
    for ( int i = startIdx; i < limit; ++i )
    {
      if ( posLeft[i] < posToPlace ) //we need to place more members that left in accessible part of the line
        break;

      const TSampleSlot & slot = line[i];

      int newPosToPlace = posToPlace - slot.GetSlotSize();
      if ( newPosToPlace < 0 ) //That slot is too big to fit
        continue;

      draft.PushBack( tidx, slot );
      iterations += FullSweepIterationHetero( sample, tidx, i + 1, newPosToPlace, draft, teamSize );
      draft.PopBack( tidx, slot );
    }

    return iterations;
  }



  static unsigned FullSweepIterationHomo( const Sample & sample, int tidx, int startIdx, int posToPlace0, int posToPlace1, TDraft & draft, int teamSize )
  {
    unsigned iterations = 0;
    const vector<TSampleSlot> & line = sample.line[0];
    const vector<int> & posLeft = sample.positionsLeft[0];

    int limit = line.size();
    for ( int i = startIdx; i < limit; ++i )
    {
      const int posToPlace = ( tidx == 0 ) ? posToPlace0 : posToPlace1;
      if ( posLeft[i] < posToPlace ) //we want to place more mombers that left in accessible part of the line
        break;

      const TSampleSlot & slot = line[i];

      const int newPosToPlace0 = ( tidx == 0 ) ? ( posToPlace0 - slot.GetSlotSize() ) : posToPlace0;
      const int newPosToPlace1 = ( tidx == 1 ) ? ( posToPlace1 - slot.GetSlotSize() ) : posToPlace1;

      const int newPosToPlace = ( tidx == 0 ) ? newPosToPlace0 : newPosToPlace1;
      if ( newPosToPlace < 0 ) //That slot is too big to fit
        continue;

      draft.PushBack( tidx, slot );

      //first try same team combinations branch
      if ( newPosToPlace > 0 )
        iterations += FullSweepIterationHomo( sample, tidx, i + 1, newPosToPlace0, newPosToPlace1, draft, teamSize );

      //Then try other team's branch
      const int otherNewPostToPlace = ( tidx == 0 ) ? newPosToPlace1 : newPosToPlace0;
      if ( otherNewPostToPlace > 0 ) {
        const int new_tidx = ( tidx == 0 ) ? 1 : 0;
        iterations += FullSweepIterationHomo( sample, new_tidx, i + 1, newPosToPlace0, newPosToPlace1, draft, teamSize );
      }

      if ( newPosToPlace0 <= 0 && newPosToPlace1 <= 0 )
      {
        iterations += 1;
        draft.CheckOut();
      }

      draft.PopBack( tidx, slot );
    }

    return iterations;
  }
};

} //namespace mmaking

#endif //MMAKING_FULLSWEEP_H_INCLUDED
