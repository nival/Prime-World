#include "stdafx.h"
#include "IDGenerator.h"

bool IDGenerator::Release(uint _id)
{
  HoleContainer::iterator it = FindLowestHole(_id);
  if (it != holes.end())
  {
    if (it->minRange-1 == _id)  // check if value lies on hole bound
    {
      it->minRange -= 1;
      HoleContainer::iterator prev_it = it-1;
      if (prev_it >= holes.begin())  // previous hole exists
      {
        if (prev_it->maxRange+1 == it->minRange)
        {
          prev_it->maxRange = it->maxRange;  // join holes
          holes.erase(it);
        }
      }
    }
    else
    {
      HoleContainer::iterator prev_it = it-1;
      if (prev_it >= holes.begin())  // previous hole exists
      {
        if (prev_it->maxRange+1 == _id) // check if value lies on hole bound
        {
          prev_it->maxRange += 1;
        }
        else
        {
          if (_id < prev_it->minRange || _id > prev_it->maxRange) // check if value is in hole
          {
            HoleContainer::iterator newIt = holes.insert(it); // create new hole
            newIt->minRange = _id;
            newIt->maxRange = _id;
          }
          else
          {
            return false;
          }
        }
      }
      else
      {
        HoleContainer::iterator newIt = holes.insert(it); // create new hole
        newIt->minRange = _id;
        newIt->maxRange = _id;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

uint IDGenerator::Generate()
{
  HoleContainer::iterator it = holes.begin();
  uint result = it->minRange;
  it->minRange += 1;
  if (it->minRange < it->maxRange)
  {
    return result;
  }
  else
  {
    holes.erase(it);
  }
  return result;
}

