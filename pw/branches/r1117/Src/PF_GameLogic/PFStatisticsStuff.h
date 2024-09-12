#ifndef PFSTATISTICSSTUFF_H_INCLUDED
#define PFSTATISTICSSTUFF_H_INCLUDED

//#include "PFHero.h"
#include "PFBaseUnit.h"
#include "DBStats.h"

namespace NWorld
{
  class PerHeroStatistics;
  class PFBaseHero;
  class PFStatistics;
};


namespace NWorld
{

namespace StatisticsStuff
{

template <class _Tp>
class circular_buffer
{
public:
  typedef _Tp     value_type;

private:
  ZDATA
  vector <value_type >data;
  int front;
  int rear;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&data); f.Add(3,&front); f.Add(4,&rear); return 0; }
  circular_buffer() : front(0), rear(0)
  { 
    data.resize(1);
  }

  void create( int cap )
  {
    data.resize(cap);
  }

  ~circular_buffer()
  { 
    data.empty();
  }

  void push( const value_type& val )
  {
    int nextRear = ( rear + 1 ) % data.size();

    if ( nextRear == front )
      pop();

    data[rear] = val;
    rear = nextRear;
  }

  void pop()
  {
    NI_VERIFY( front != rear, "Queue underflow", return );
    front = ( front + 1 ) % data.size();
  }

  void clear()
  {
    front = rear = 0;
  }

  bool empty() const 
  { 
    return front == rear; 
  }
  int size() const
  {
    return (rear - front + data.size()) % data.size(); // almost equal to "rear - front"
  }
  bool full() const 
  { 
    return front == ( rear + 1 ) % data.size(); 
  }

  const value_type& top() const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
    return data[front];
  }

  const value_type& back() const
  {
    NI_ASSERT( !empty(), "Queue underflow" );
    return data[(rear - 1 + data.size()) % data.size()]; // previous (= data[rear-1] in most cases)
  }

  value_type& back()
  {
    NI_ASSERT( !empty(), "Queue underflow" );
    return data[(rear - 1 + data.size()) % data.size()]; // previous (= data[rear-1] in most cases)
  }

  int fit_index(int &pos) const
  {
    if ( pos < 0 )
      pos = 0;
    if ( size() <= pos )
      pos = size() - 1;
    return pos;
  }

  const value_type& top( int pos ) const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
    NI_ASSERT( 0 <= pos && pos < size(), "Index is out of bounds" );
    int dif = ( front + pos ) % data.size();
    return data[dif];
  }

  const value_type& back( int pos ) const
  {
    NI_ASSERT( front != rear, "Queue underflow" );
    NI_ASSERT( 0 <= pos && pos < size(), "Index is out of bounds" );
    int dif = (rear - 1 - pos + data.size()) % data.size(); // almost equal to "(rear-1) - pos"
    return data[dif];
  }

  // direct access to underlying data structure, need for fast algorithms
  int raw_top_index() const { return front; }
  int raw_rear_index() const { return rear; }
  value_type* raw_data() { return data; }

  template< typename Pred >
  void ForAll( Pred pred ) const
  {
    for( int pos = 0; pos < size(); ++pos )
    {
      value_type const& cur = top(pos);

      if( pred(cur) )
        break;
    }
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LinearFunction
{
public:
  LinearFunction(vector<int> const &v)
  {
    NI_ASSERT(v.size() == 2, "too bad");
    m = v[1]; // mult
    NI_ASSERT(m > 0, "");
    a = v[0] - m; // initial
    NI_ASSERT(a >= 0, "");
  }
  LinearFunction(int m_, int a_): m(m_), a(a_ - m_)
  {
    NI_ASSERT(m > 0, "");
    NI_ASSERT(a >= 0, "");
  }
  int operator()(int arg) const
  {
    return (max(arg - a, 0)) / m;
  }
private:
  int m, a;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HeroPosition
{
  HeroPosition() {}
  HeroPosition(int heroId, CVec3 const &pos): heroId(heroId), pos(pos) {}

  int heroId;
  CVec3 pos;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HeroDeathInstance
{
  HeroDeathInstance() {}
  HeroDeathInstance(CPtr<NWorld::PFBaseHero> pVictim, CPtr<NWorld::PFBaseHero> pSlayer, float time): pVictim(pVictim), pSlayer(pSlayer), time(time) {}
  ZDATA;
  CPtr<NWorld::PFBaseHero> pVictim;
  CPtr<NWorld::PFBaseHero> pSlayer; // killer or assistant
  float time;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pVictim); f.Add(3,&pSlayer); f.Add(4,&time); return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HeroAssistInstance: public HeroDeathInstance
{
  HeroAssistInstance() {}
  HeroAssistInstance(CPtr<NWorld::PFBaseHero> pVictim, CPtr<NWorld::PFBaseHero> pAssistant, float time): HeroDeathInstance(pVictim, pAssistant, time) {}
  ZDATA_(HeroDeathInstance);
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroDeathInstance*)this); return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HeroKillInstance: public HeroDeathInstance
{
  HeroKillInstance() {}
  HeroKillInstance(CPtr<NWorld::PFBaseHero> pVictim, CPtr<NWorld::PFBaseHero> pKiller, float time, NWorld::PFStatistics &statistics);
  ZDATA_(HeroDeathInstance);
  vector<HeroPosition> heroPositions;
  CVec3 victimPosition;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroDeathInstance*)this); f.Add(2,&heroPositions); f.Add(3,&victimPosition); return 0; }
};  

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} //namespace StatisticsStuff

} //namespace NWorld

#endif //PFSTATISTICSSTUFF_H_INCLUDED
