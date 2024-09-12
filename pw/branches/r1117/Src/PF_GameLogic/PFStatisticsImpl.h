#ifndef PFSTATISTICSIMPL_H_INCLUDED
#define PFSTATISTICSIMPL_H_INCLUDED
//
//Internal Statistics implementation header
//( Sensitive to include order )
//NEVER include it from other header file
//

namespace NWorld
{

namespace StatisticsStuff
{

// v1 -= v2;
// of course, we assume that there are no duplicates neither in v1 nor in v2 (i.e. both v1 and v2 are "sets").
template <typename T> void Minus_(vector<T> &v1, vector<T> const &v2)
{
  for (vector<T>::const_iterator it2 = v2.begin(), end2 = v2.end(); it2 != end2; ++it2)
  {
    vector<T>::iterator it1 = find(v1.begin(), v1.end(), *it2);
    if (it1 != v1.end())
    {
      v1.erase(it1);      
    }
    // due to assumption, we continue loop by it2.
    // otherwise, we should find next *it2.
  }
}

// v3 = v1 U v2;
// we assume that intersection of v1 and v2 is empty
template <typename T> void Unite_(vector<T> const &v1, vector<T> const &v2, vector<T> &v3)
{
  for (vector<T>::const_iterator it1 = v1.begin(), end1 = v1.end(); it1 != end1; ++it1)
  {
    v3.push_back(*it1);
  }
  for (vector<T>::const_iterator it2 = v2.begin(), end2 = v2.end(); it2 != end2; ++it2)
  {
    v3.push_back(*it2);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void UpdateArray_(float *arr, int arrSize, float val)
{
  for (int i = arrSize - 1; i > 0; --i)
  {
    arr[i] = arr[i - 1];
  }
  arr[0] = val;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ClearArray_(float *arr, int arrSize)
{
  for (int i = arrSize - 1; i >= 0; --i)
  {
    arr[i] = -1;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int GetChainLength_(const vector<float>& arr, float val)
{
  const int len = arr.size();
  int i;
  for (i = 0; i < len - 1; ++i)
  {
    if (arr[i + 1] == -1.f || arr[i] - arr[i + 1] > val)
    {
      break;
    }
  }
  return i+1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsBoss(class PFBaseUnit const *pUnit)
{
  return pUnit->GetUnitType() == NDb::UNITTYPE_NEUTRALBOSS;
}

} //namespace StatisticsStuff

} //namespace NWorld

#endif //PFSTATISTICSIMPL_H_INCLUDED
