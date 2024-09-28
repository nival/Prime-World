#pragma once

#include "CollectionVG.h"

namespace NScene
{

#define DEF_RGROUP(_value_) static RenderGroups SGetRenderGroup() { return _value_; }
#define INIT_RGROUP  m_group = SGetRenderGroup()

/** @brief Base class for objects that can be put into voxel grid
*/
class VoxelGridObj : public Render::IAABB
{
public:
  enum
  {
    PROCESS_ID_NONE = 0xFFFFFFFF ///< process id value to indicate that no process was performed
  };

  enum RenderGroups
  {
    RG_DEFAULT = 0, // This is a MUST
    RG_ROADS,
    NUM_GROUPS // This also means "all groups"
  };

  DEF_RGROUP(RG_DEFAULT)

  /** @brief A processor that sets voxel grid for the object
  */
  class SetVoxelGridProc : public NonCopyable
  {
  public:
    SetVoxelGridProc(CollectionVGBase *grid) : m_grid(grid) {}

    template <class VGObj> void operator()(VGObj &obj)
    {
      obj.setVoxelGrid(m_grid);
    }

    RenderGroups getRenderGroup() const { return NUM_GROUPS; }
  private:
    CollectionVGBase *m_grid;
  };
  
  /** @brief A processor wrapper that performs processing only once for each object

      You can pass an instance of this to a process() method of some collection that contains
      objects inherited from VoxelGridObj. This wall cause application of wrapped processor
      only once for each object in collection.

      This is essential for CollectionVG since it can have multiple references to the same object.

      @param Processor type of wrapped processor that will be applied
  */
  template <class Processor> class ProcessUniqueProc : public NonCopyable
  {
  public:
    /** @brief Constructor
        @param processId unique identifier of the process (operation) being performed
        @param proc      processor to apply
    */
    ProcessUniqueProc(int processId, Processor &proc) : m_processId(processId), m_proc(proc) { }

    RenderGroups getRenderGroup() const { return m_proc.getRenderGroup(); }
    
    /** @brief Applies wrapped processor to given object if wasn't already processed
        @param obj pointer to object
    */
    template <class VGObj> void operator()(VGObj &obj)
    {
      if (obj.getLastProcessId() != m_processId)
      {
        obj.process(m_processId);
        m_proc(obj);
      }
    }

  private:
    int   m_processId; ///< unique identifier of the process (operation) being performed
    Processor &m_proc;      ///< processor to apply
  };

  /** @brief A processor wrapper that performs processing only if object's bbox intersects specified bbox

      You can pass an instance of this to a process() method of some collection that contains
      objects inherited from VoxelGridObj. This wall cause application of wrapped processor
      to each object in collection whose bbox intersects specified bbox.

      @param Processor type of wrapped processor that will be applied
  */
  template <class Processor> class ProcessByBBoxProc : public NonCopyable
  {
  public:
    /** @brief Constructor
        @param bbox bounding box object's bounding box must intersect
        @param proc processor to apply
    */
    ProcessByBBoxProc(Render::AABB const &bbox, Processor &proc) : m_bbox(bbox), m_proc(proc) { }

    RenderGroups getRenderGroup() const { return m_proc.getRenderGroup(); }
    
    /** @brief Applies wrapped processor to given object if its bbox intersects specified bbox
        @param obj pointer to object
    */
    template <class VGObj> void operator()(VGObj &obj)
    {
      const Render::AABB &bbox = obj.GetWorldAABB();
      if (!m_bbox.IsIntersectedBy(bbox))
      {
        return;
      }

      m_proc(obj);
    }

  private:
    Render::AABB const &m_bbox; ///< bounding box object's bounding box must intersect
    Processor  &m_proc; ///< processor to apply
  };

  /** @brief A processor wrapper that performs processing only if object's bbox intersects specified frustum

      You can pass an instance of this to a process() method of some collection that contains
      objects inherited from VoxelGridObj. This wall cause application of wrapped processor
      to each object in collection whose bbox intersects specified frustum.

      @param Processor type of wrapped processor that will be applied
  */
  template <class Processor> class ProcessByFrustumProc : public NonCopyable
  {
  public:
    /** @brief Constructor
        @param frustum frustum object's bounding box must intersect
        @param proc    processor to apply
    */
    ProcessByFrustumProc(Render::ConvexVolume const &frustum, Processor &proc) : m_frustum(frustum), m_proc(proc) { }

    RenderGroups getRenderGroup() const { return m_proc.getRenderGroup(); }
    
    /** @brief Applies wrapped processor to given object if its bbox intersects specified frustum

        @param obj pointer to object
    */
    template <class VGObj> void operator()(VGObj &obj)
    {
      if (!m_frustum.IntersectBox( obj.GetWorldAABB() ))
      {
        return;
      }

      m_proc(obj);
    }

  private:
    Render::ConvexVolume const &m_frustum; ///< frustum object's bounding box must intersect
    Processor                  &m_proc;    ///< processor to apply
  };

  /// Constructor
  VoxelGridObj() : m_voxelGrid(NULL), m_lastProcessId((unsigned int)PROCESS_ID_NONE) { INIT_RGROUP; }

  /// Destructor
  ~VoxelGridObj() { ASSERT(m_voxelGrid == NULL); }

  /** @brief Get voxel grid the object resides in

      This method is intended for internal use by voxel grid.

      @return pointer to voxel grid
  */      
  CollectionVGBase *getVoxelGrid() { return m_voxelGrid; }

  /** @brief Set voxel grid the object now resides in

      This method is intended for internal use by voxel grid.

      @param voxelGrid pointer to voxel grid
  */      
  void setVoxelGrid(CollectionVGBase *voxelGrid)
  {
    m_voxelGrid = voxelGrid;
    m_lastProcessId = (unsigned int)PROCESS_ID_NONE;
  }

  /** @brief Notify object that it was repositioned in the world

      Call this method whenever you change position/orientation of the object
      so that this change cause change of bounding box.
  */      
  void move() { if (m_voxelGrid) m_voxelGrid->moveObject(this); }

  /** @brief Access list of voxels object belongs to

      This method is intended for internal use by voxel grid.

      @return rectangle in voxel grid coords
  */      
  IRect &getVoxels() { return m_voxels; }

  /** @brief Get identifier of the last mass operation performed on this object
      @return process id
  */      
  int getLastProcessId() { return m_lastProcessId; }
  RenderGroups GetRenderGroup() const { return m_group; }

  /** @brief Notify object that a mass operation was performed on it
      @param processId unique identifier of the process (operation)
  */      
  void     process(unsigned int processId) { m_lastProcessId = processId; }

private:
  CollectionVGBase *m_voxelGrid; ///< pointer to voxel grid object resides in (can be NULL)
  IRect             m_voxels;    ///< range of voxels the object belongs to (specified in voxel grid coords)

  /** @brief Identifier of the last mass operation performed on this object

      Since CollectionVG can have multiple references to the same object this is
      necessary to avoid performing the same operation multiple times.
  */
  unsigned int  m_lastProcessId;
protected:
  RenderGroups  m_group;
};

} // ns NScene
