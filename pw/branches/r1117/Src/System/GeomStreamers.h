#ifndef GEOMSTREAMERS_H_INCLUDED
#define GEOMSTREAMERS_H_INCLUDED

#include "Geom.h"


inline NLogg::StreamBuffer & operator << (NLogg::StreamBuffer & stream, const CVec2 & v)
{
  stream << "[" << v.x << ", " << v.y << "]";
  return stream;
}

inline NLogg::StreamBuffer & operator << (NLogg::StreamBuffer & stream, const CVec3 & v)
{
  stream << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return stream;
}

inline NLogg::StreamBuffer & operator << (NLogg::StreamBuffer & stream, const CVec4 & v)
{
  stream << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
  return stream;
}

inline NLogg::StreamBuffer & operator << (NLogg::StreamBuffer & stream, const SHMatrix & m)
{
  stream << "Matrix" << endl;
  stream << "|" << m._11 << ",   " << m._12 << ",   " << m._13 << ",   " << m._14 << "|" << endl;
  stream << "|" << m._21 << ",   " << m._22 << ",   " << m._23 << ",   " << m._24 << "|" << endl;
  stream << "|" << m._31 << ",   " << m._32 << ",   " << m._33 << ",   " << m._34 << "|" << endl;
  stream << "|" << m._41 << ",   " << m._42 << ",   " << m._43 << ",   " << m._44 << "|" << endl;
  return stream;
}

#endif //GEOMSTREAMERS_H_INCLUDED
