#ifndef LOADINGPROGRESS_H_INCLUDED
#define LOADINGPROGRESS_H_INCLUDED

#include "Thread.h"

class LoadingProgress : public CObjectBase
{
  OBJECT_BASIC_METHODS( LoadingProgress );

public:
  LoadingProgress() {}

  void InitPartialWeight( int id, float weight ); //any positive value number
  void SetPartialProgress( int id, float t ); // 0...1
  float GetTotalProgress() const;

private:
  struct SItem
  {
    float   currentProgress;
    float   weight;

    SItem( float _weight = 0 ) : currentProgress( 0 ), weight( _weight ) {}
  };

  typedef map<int, SItem> TItems;

  threading::Mutex  mutex;
  TItems  items;
};

#endif //LOADINGPROGRESS_H_INCLUDED
