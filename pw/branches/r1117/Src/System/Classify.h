#ifndef _CLASSIFY_H_
#define _CLASSIFY_H_

#include "Geom.h"

struct IClassify2
{
  virtual bool operator()(CVec2 const& pt) const = 0;
  virtual void GetBounds(CTRect<float>* pBounds) const = 0;
};

struct CClassifyRect : public IClassify2
{
  CTRect<float> rect;

  CClassifyRect(CTRect<float> const& other) : rect(other) {}
  CClassifyRect(CVec2 const& vMin, CVec2 const& vMax) : rect(vMin, vMax) {}

  virtual bool operator()(CVec2 const& pt) const
  {
    return rect.IsInside(pt);
  }

  virtual void GetBounds(CTRect<float>* pBounds) const
  {
    ASSERT(pBounds != 0);
    *pBounds = rect;
  }
};

struct CClassifyCircle : public IClassify2
{
  CCircle circ;

  CClassifyCircle(CCircle const& other) : circ(other) {}
  CClassifyCircle(CVec2 const& center, float radius) : circ(center, radius) {}

  virtual bool operator()(CVec2 const& pt) const
  {
    return circ.IsInside(pt);
  }

  virtual void GetBounds(CTRect<float>* pBounds) const
  {
    ASSERT(pBounds != 0);
    pBounds->Set(circ.center.x - circ.r, circ.center.y - circ.r, circ.center.x + circ.r, circ.center.y + circ.r);
  }
};

struct CClassifyTriangle : public IClassify2
{
  CVec2 a, b, c;

  CClassifyTriangle(CVec2 const& pt1, CVec2 const& pt2, CVec2 const& pt3) : a(pt1), b(pt2), c(pt3) {}

  virtual bool operator()(CVec2 const& pt) const
  {
    return IsPointInsideTriangle(a, b, c, pt);
  }

  virtual void GetBounds(CTRect<float>* pBounds) const
  {
    ASSERT(pBounds != 0);
    pBounds->Set(a, b);
    pBounds->Add(c);
  }
};

#endif /* _CLASSIFY_H_ */
