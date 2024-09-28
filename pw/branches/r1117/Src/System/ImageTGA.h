#pragma once

#include "Stream.h"
#include "2Darray.h"

namespace NImage
{
  // store image as RGB (without A!) into specified stream
  void WriteImageTGA( Stream* stream, const CArray2D<Render::Color>& image );
} //namespace NImage
