#pragma once

namespace math
{

template <typename T, typename Precision>        
class Filter 
{
    CArray2D<T> intermediate;    
    static const int max_filter_size = 10;
    Precision weights_h[max_filter_size];
    Precision weights_v[max_filter_size];
    T sub_image[max_filter_size];
    const CArray2D<Precision>& filter;

    T FilterItem(const T* src, const Precision* flt, int size)
    {
        Precision sum_f = 0;
        Precision sum_z = 0;

        for (int i = 0; i < size; ++i)
        {
            Precision f = flt[i];;
            Precision z = f * src[i];
            sum_f += f;
            sum_z += z;
        }
        return T(sum_z / sum_f);
    }
    void operator = (const Filter& other) {}

public:
    Filter(int h, int w, const CArray2D<Precision>& filter):
      intermediate(h, w),
          filter(filter)
      {
          int filter_x0 = (filter.GetSizeX()-1)/2;
          int filter_y0 = (filter.GetSizeY()-1)/2;
          filter.CopyRow(weights_h, filter.GetSizeY(), 0, filter_y0);
          filter.CopyColumn(weights_v, filter.GetSizeX(), filter_x0, 0);
      }

	  template <typename TargetType>
      void Process(TargetType& dest, const CArray2D<T>& src)
      {
          assert(intermediate.GetSizeX() == dest.GetSizeX());
          assert(intermediate.GetSizeY() == dest.GetSizeY());
          assert(intermediate.GetSizeX() == src.GetSizeX());
          assert(intermediate.GetSizeY() == src.GetSizeY());
          assert(filter.GetSizeX() <= max_filter_size);
          assert(filter.GetSizeY() <= max_filter_size);
          int filter_x0 = (filter.GetSizeX()-1)/2;
          int filter_y0 = (filter.GetSizeY()-1)/2;

          // horizontal 
          for (int y = 0; y < src.GetSizeX(); y++)
          {
              for (int x = 0; x < src.GetSizeY(); x++)
              {
                  src.CopyRow(sub_image, filter.GetSizeY(), x-filter_x0, y);
                  T value = FilterItem(sub_image, weights_h, filter.GetSizeY());
                  intermediate.Set(x, y, value);
              }
          }

          // vertical 
          for (int x = 0; x < src.GetSizeY(); x++)
          {
              for (int y = 0; y < src.GetSizeX(); y++)
              {
                  intermediate.CopyColumn(sub_image, filter.GetSizeX(), x, y-filter_y0);
                  T value = FilterItem(sub_image, weights_v, filter.GetSizeX());
                  dest.Set(x, y, value);
              }
          }
      }
};

} // math
