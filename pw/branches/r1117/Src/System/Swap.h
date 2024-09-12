#ifndef _SYSTEM_SWAP_H_
#define _SYSTEM_SWAP_H_

/**
  @brief Swap objects

  @param lhs first argument far swap operation
  @param rhs second argument far swap operation
*/
template <typename T>
inline void SwapObj(T &lhs, T &rhs)
{
  T t = T(lhs);
  lhs = rhs;
  rhs = t;
}
/**
  @brief Swap pointers

  @param lhs lhs
  @param rhs rhs
*/
template <typename T>
inline void Swap(T * &lhs, T * &rhs)
{
  T * const t = lhs;
  lhs = rhs;
  rhs = t;
}

#endif 	// _SYSTEM_SWAP_H_

