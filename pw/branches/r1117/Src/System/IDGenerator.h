#ifndef _IDGENERRATOR_H_
#define _IDGENERRATOR_H_

class IDGenerator
{
  struct Hole
  {
    uint minRange;
    uint maxRange;
  };
  typedef nstl::vector<Hole> HoleContainer;
public:  
  IDGenerator()
  {
    Hole hole = { 0, 0xFFFFFFFF-1 };
    holes.push_back(hole);
  };
  IDGenerator( uint minId, uint maxId )
  {
    Hole hole = { minId, maxId };
    holes.push_back(hole);
  };

  bool HasFreeID() const
  {
    return !holes.empty();
  }
  uint Generate();
  bool Release(uint _id);

private:
  HoleContainer::iterator FindLowestHole(uint _id)
  {
    for (HoleContainer::iterator it=holes.begin();it != holes.end();++it)
    {
      if (_id < it->minRange)
      {
        return it;
      }
    }
    return holes.end();
  }
  HoleContainer holes;
};

#endif