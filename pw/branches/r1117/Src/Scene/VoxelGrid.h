#pragma once

#include "../Render/ConvexVolume.h"

namespace NScene
{

/** @brief 2D integer rectangle

    This class represents 2D rectangle in X-Z plane with integer coordinates.
    It is intended to represent rectangular groups of cells of square grid.
    Therefore it is considered to include its boundaries.

    The state when upper boundary is numerically less than lower boundary (on
    any axis) is treated as <i>empty</i>.

    @note X-Z is meant to be horizontal plane. Since in engine X-Y is horizontal
    plane we use x and y components from outside data structures (like BBox etc.)
*/
class IRect
{
public:
  /// Clear rectangle (make it empty)
  void clear() { xMin = 1; xMax = 0; zMin = 1; zMax = 0; }
  
  /** @brief Check if rectangle is empty (zero square)
      @return true if rectangle is empty
  */
  bool isEmpty() const { return ((xMin > xMax) || (zMin > zMax)); }
  
  /** @brief Check if specified point lies inside rectangle
      @param x x coordinate of the point
      @param z z coordinate of the point
      @return true if point lies inside rectangle
  */
  bool isPointIn(int x, int z) const { return (xMin <= x && x <= xMax && zMin <= z && z <= zMax); }

  int xMin; ///< lower X boundary
  int zMin; ///< lower Z boundary
  int xMax; ///< upper X boundary
  int zMax; ///< upper Z boundary
};

/** @brief This class incapsulates 2D voxel grid abstraction

    This class stores information about space division in voxels and a 2D array
    of elements of customizable type. Voxel grid is 2D and lies in X-Z plane.
    This class provides methods to find voxels by world coordinates and to process
    voxels by different schemes.

    @param T voxel type
*/
template <typename T> class VoxelGrid
{
public:
  /** @brief Constructor
      @param bbox     bounding box restricting the space that is divided in voxels
      @param nVoxelsX number of voxels by X axis (all voxels are of equal size)
      @param nVoxelsZ number of voxels by Z axis (all voxels are of equal size)
  */
  VoxelGrid(Render::AABB const &bbox, int nVoxelsX, int nVoxelsZ) :
      m_bbox(bbox), m_nVoxelsX(nVoxelsX), m_nVoxelsZ(nVoxelsZ),
      m_voxelSizeX(2.0 * bbox.halfSize.x / m_nVoxelsX),
      m_voxelSizeZ(2.0 * bbox.halfSize.y / m_nVoxelsZ)
  {
    m_grid = new T[m_nVoxelsX * m_nVoxelsZ];
  }

  /// Destructor
  ~VoxelGrid()
  {
    delete [] m_grid;
  }

  /** @brief Get voxel by 2D index
      @param x index by X axis
      @param z index by Z axis
      @return reference to voxel
  */
  T &voxel(int x, int z) { return m_grid[z * m_nVoxelsX + x]; }
  
  /** @brief Find voxel where specified point lies
      @param[in]  x x coordinate of the point
      @param[in]  z z coordinate of the point
      @param[out] vx index of the voxel by X axis
      @param[out] vz index of the voxel by Z axis
      @return true if found voxel (false if point falls outisde of voxel grid)
  */
  bool findVoxel(float x, float z, int &vx, int &vz)
  {
    float dx = x - m_bbox.center.x,
          dz = z - m_bbox.center.y;

    if (dx < -m_bbox.halfSize.x || dx > m_bbox.halfSize.x ||
        dz < -m_bbox.halfSize.y || dz > m_bbox.halfSize.y)
    {
      return false;
    }

    vx = (int)floor((dx + m_bbox.halfSize.x) / m_voxelSizeX);
    vy = (int)floor((dz + m_bbox.halfSize.y) / m_voxelSizeZ);

    if (vx >= m_nVoxelsX)
    {
      vx = m_nVoxelsX - 1;
    } 

    if (vz >= m_nVoxelsZ)
    {
      vz = m_nVoxelsZ - 1;
    } 

    return true;
  }

  /** @brief Find voxel where specified point lies
  
      The difference from findVoxel() is that point coordinates are clamped
      into voxel grid range. So if point falls outside of voxel grid we 
      end up with the closest voxel.
      
      @param[in]  x x coordinate of the point
      @param[in]  z z coordinate of the point
      @param[out] vx index of the voxel by X axis
      @param[out] vz index of the voxel by Z axis
  */
  void findVoxelClamp(float x, float z, int &vx, int &vz)
  {
    vx = (int)/*Round*/((x - m_bbox.center.x + m_bbox.halfSize.x) / m_voxelSizeX);
    vz = (int)/*Round*/((z - m_bbox.center.y + m_bbox.halfSize.y) / m_voxelSizeZ);

    vx = ClampFast(vx, 0, m_nVoxelsX - 1);
    vz = ClampFast(vz, 0, m_nVoxelsZ - 1);
  }

  /** @brief Find voxel range intersecting given bounding box
  
      @param[in]  bbox bounding box to intersect
      @param[out] rect rectangle in voxel grid coords
  */
  void bboxToVoxels(Render::AABB const &bbox, IRect &rect)
  {
    findVoxelClamp(bbox.center.x - bbox.halfSize.x, bbox.center.y - bbox.halfSize.y, rect.xMin, rect.zMin);
    findVoxelClamp(bbox.center.x + bbox.halfSize.x, bbox.center.y + bbox.halfSize.y, rect.xMax, rect.zMax);
  }

  /** @brief Apply given processor to all voxels
      
      Processor must implement the following operator
      
      @code
      void operator()(T &voxel)
      @endcode

      which receives reference to voxel that requires processing.

      @param p    processor
      @param rect rectangle in voxel grid coords
  */
  template <class Processor> bool process(Processor &p)
  {
    int x, z;

    for (z = 0; z < m_nVoxelsZ; ++z)
    {
      for (x = 0; x < m_nVoxelsX; ++x)
      {
        p(voxel(x, z));
      }
    }

    return true;
  }

  /** @brief Apply given processor to all voxels in given range
      
      Processor must implement the following operator
      
      @code
      void operator()(T &voxel)
      @endcode

      which receives reference to voxel that requires processing.

      @param p    processor
      @param rect rectangle in voxel grid coords
  */
  template <class Processor> bool process(Processor &p, IRect const &rect)
  {
    int x, z;

    for (z = rect.zMin; z <= rect.zMax; ++z)
    {
      for (x = rect.xMin; x <= rect.xMax; ++x)
      {
        p(voxel(x, z));
      }
    }

    return true;
  }

  /** @brief Apply given processor to all voxels that intersect given bbox
      
      Processor must implement the following operator
      
      @code
      void operator()(T &voxel)
      @endcode

      which receives reference to voxel that requires processing.

      @param p processor
      @param bbox bounding box
  */
  template <class Processor> bool process(Processor &p, Render::AABB const &bbox)
  {
    IRect r;

    findVoxelClamp(bbox.center.x - bbox.halfSize.x, bbox.center.y - bbox.halfSize.y, r.xMin, r.zMin);
    findVoxelClamp(bbox.center.x + bbox.halfSize.x, bbox.center.y + bbox.halfSize.y, r.xMax, r.zMax);

    process(p, r);

    return true;
  }

  /** @brief Apply given processor to all voxels that belong to rectangle #1 and don't belong rectangle #2
      
      Processor must implement the following operator
      
      @code
      void operator()(T &voxel)
      @endcode

      which receives reference to voxel that requires processing.

      @param p processor
      @param inRect  rectangle that voxels must belong to
      @param outRect rectangle that voxels must not belong to
  */
  template <class Processor> bool process(Processor &p, IRect const &inRect, IRect const &outRect)
  {
    if (inRect.isEmpty())
    {
      return true;
    }

    if (outRect.isEmpty())
    {
      return process(p, inRect);
    }
    
    int x, z;
    
    for (z = inRect.zMin; z <= inRect.zMax; ++z)
    {
      for (x = inRect.xMin; x <= inRect.xMax; ++x)
      {
        // skip voxels that belong to rectangle #2
        if (outRect.isPointIn(x, z))
        {
          continue;
        }

        p(voxel(x, z));
      }
    }

    return true;
  }

  /** @brief Apply given processor to all voxels that intersect given frustum
      
      Processor must implement the following operator
      
      @code
      void operator()(T &voxel)
      @endcode

      which receives reference to voxel that requires processing.

      @note Currently works loosely - processes all voxels that intersect frustum's bbox.

      @param p processor
      @param frustum frustum
  */
  template <class Processor> bool process(Processor &p, Render::ConvexVolume const &frustum)
  {
    /// @todo implement precise culling by frustum

    // for now just process all voxels
    return process(p);
  }

private:
  Render::AABB  m_bbox;  ///< bounding box of space divided in voxels
  T      *m_grid;        ///< 2D array of voxels
  int     m_nVoxelsX;    ///< number of voxels by X axis
  int     m_nVoxelsZ;    ///< number of voxels by Z axis
  float   m_voxelSizeX;  ///< size of voxel by X axis
  float   m_voxelSizeZ;  ///< size of voxel by Z axis
};

} // ns NScene
