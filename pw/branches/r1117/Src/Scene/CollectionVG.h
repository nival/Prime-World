#pragma once

#include "../Render/aabb.h"

#include "CollectionList.h"
#include "VoxelGrid.h"

namespace NScene
{

class VoxelGridObj;

/** @brief Array that allows empty spaces

    This is a kind of memory pool. A single allocation for the maximum number
    of blocks is performed at construction. Then user can allocate & deallocate
    blocks. Automatic in-place construction/destruction of objects will be
    performed in those blocks. Allocated block is never moved so passing index or
    pointer to it somewhere is safe.

    @param T type of object stored in one block
*/
template <typename T> class SparseArray
{
public:
  /** @brief Constructor
      @param nMaxElements maximum number of elements in array
  */
  SparseArray(int nMaxElements) : m_size(nMaxElements)
  {
    m_array = new unsigned char[ m_size * sizeof(T) ];
    m_flags = new unsigned char[ m_size ];
    memset(m_flags, 0, sizeof(unsigned char) * m_size);
  }

  /// Destructor
  ~SparseArray()
  {
    // deallocate all allocated units
    for (int i = 0; i < m_size; ++i)
    {
      if (m_flags[i] > 0)
      {
        deallocate(i);
      }
    }

    delete [] m_flags;
    delete [] m_array;
  }

  /** @brief Get array size (maximum number of elements)
      @return maximum number of elements
  */
  int size() { return m_size; }

  /** @brief Check if block is allocated
      @param idx index of the block
      @return true if block is allocated
  */
  bool  isValid(int idx) { return (m_flags[idx] > 0); }
  
  /** @brief Allocate a block

      In-place constructor is called for the object in thiat block automatically.
      
      @return index of newly allocated block (or -1 if no free blocks left)
  */
  int allocate()
  {
    for (int i = 0; i < m_size; ++i)
    {
      if (m_flags[i] == 0)
      {
        // in-place constructor
        new (m_array + i * sizeof(T)) T;
        
        m_flags[i] = 1;
        return i;
      }
    }

    return -1;
  }

  /** @brief Deallocate a block

      Destructor is called for the object in thiat block automatically.
      
      @param idx index of the block
  */
  void deallocate(int idx)
  {
    if (m_flags[idx] == 0)
    {
      return;
    }

    // in-place destructor
    ((T*)(m_array + idx * sizeof(T)))->~T();

    m_flags[idx] = 0;
  }

  /** @brief Access array element by index
      @param idx index
  */
  T &operator[] (int idx) { return *(T*)(m_array + idx * sizeof(T)); }

private:
  int  m_size;   ///< array size (maximum number of elements)
  unsigned char *m_array;  ///< array of objects itself
  unsigned char *m_flags; ///< array of block state flags (0 - free, 1 - allocated)
};

/** @brief Base class for voxel grid collections
*/
class CollectionVGBase
{
public:
  /** @brief Notify collection that object's bounding box changed
      
      This is called by VoxelGridObj so that voxel grid could correct its
      optimization structures according to new object position.

      @param obj pointer to the object that was moved
  */
  virtual void moveObject(VoxelGridObj *obj) = 0;
};

/** @brief Collection that stores objects in a voxel grid

    When creating this collection you specify parameters defining
    a space volume restricted by a bounding box which is divided in
    equal parts by X and Z axes. Each part is called a voxel and
    stores references to all objects whose bounding box intersects
    voxel's space.

    Such structure allows effective processing of groups of objects
    selected by locality principle. Like all objects whose
    bounding boxes intersect specified volume (bounding box, frustum, etc.)

    Basic class for objects that can be put into this collection must be
    inherited from VoxelGridObj.

    <b>Note!</b> To keep internal optimizing structures intact user must
    notify collection about changes in any object's position/orientation
    (anything that changed object's bbox). This is done by calling object's
    move() method.
*/
template <class VGObj> class CollectionVG : public CollectionVGBase
{
public:
  /** @brief This class represents a voxel that contains a list of references to objects
  */
  class Voxel
  {
  public:
    /** @brief Check if voxel is empty
        @return true if voxel is empty
    */
    bool isEmpty() { return (m_objects.size() == 0); }
    
    /** @brief Add object reference to voxel
        @param obj pointer to object
    */
    void addObj(VGObj *obj)
    {
      m_objects.add(obj);
    }

    /** @brief Remove object reference from voxel
        @param obj pointer to object
    */
    void removeObj(VGObj *obj)
    {
      m_objects.remove(obj);
    }

    /** @brief Apply given processor to all objects in voxel
        
        Processor must implement the following operator
        
        @code
        void operator()(VGObj *obj)
        @endcode

        which receives pointer to an object that requires processing.

        @param p processor
    */
    template <class Processor> bool process(Processor &p)
    {
      return m_objects.process(p);
    }

    /** @brief Apply given processor to all objects in voxel whose bbox intersects specified bbox
        
        Processor must implement the following operator
        
        @code
        void operator()(VGObj *obj)
        @endcode

        which receives pointer to an object that requires processing.

        @param p    processor
        @param bbox bounding box
    */
    template <class Processor> bool process(Processor &p, Render::AABB const &bbox)
    {
      VoxelGridObj::ProcessByBBoxProc<Processor> bbp(bbox, p);
      return m_objects.process(bbp);
    }

    /** @brief Apply given processor to all objects in voxel whose bbox intersects specified frustum
        
        Processor must implement the following operator
        
        @code
        void operator()(VGObj *obj)
        @endcode

        which receives pointer to an object that requires processing.

        @param p       processor
        @param frustum frustum
    */
    template <class Processor> bool process(Processor &p, Render::ConvexVolume const &frustum)
    {
      VoxelGridObj::ProcessByFrustumProc<Processor> fp(frustum, p);
      return m_objects.process(fp);
    }

  private:
    CollectionList<VGObj> m_objects; ///< list of objects that belong to this voxel
  };

  enum
  {
    VOXEL_EMPTY = 0xFFFF ///< special voxel index to designate empty voxel cell
  };

  /** @brief A processor that initializes voxel grid cells with "empty" value

      You can pass an instance of this to a process() method of some VoxelGrid.
  */
  class VoxelInitProc
  {
  public:
    /** @brief Writes "empty" value to voxel cell
        @param voxel reference to voxel cell
    */
    void operator()(unsigned short &voxel)
    {
      voxel = VOXEL_EMPTY;
    }
  };

  /** @brief A processor that adds an object reference to voxels

      You can pass an instance of this to a process() method of some VoxelGrid.
  */
  class VoxelAddObjProc : public NonCopyable
  {
  public:
    /** @brief Constructor
        @param voxels array (pool) of voxels we operate on
        @param obj pointer to object
    */
    VoxelAddObjProc(SparseArray<Voxel> &voxels, VGObj *obj) : m_voxels(voxels), m_obj(obj) { }

    /** @brief Adds object reference to given voxel
        @param voxel reference to voxel cell (which stores voxel index in array)
    */
    void operator()(unsigned short &voxel)
    {
      if (voxel == VOXEL_EMPTY)
      {
        voxel = (unsigned short)m_voxels.allocate();
        ASSERT(voxel != VOXEL_EMPTY);
      }

      Voxel &v = m_voxels[voxel];
      v.addObj(m_obj);
    }

  private:
    SparseArray<Voxel> &m_voxels; ///< voxel array (pool) of voxels we operate on
    VGObj              *m_obj;    ///< pointer to object we want to add
  };

  /** @brief A processor that removes an object reference from voxels

      You can pass an instance of this to a process() method of some VoxelGrid.
  */
  class VoxelRemoveObjProc : public NonCopyable
  {
  public:
    /** @brief Constructor
        @param voxels array (pool) of voxels we operate on
        @param obj pointer to object
    */
    VoxelRemoveObjProc(SparseArray<Voxel> &voxels, VGObj *obj) : m_voxels(voxels), m_obj(obj) { }

    /** @brief Adds object reference to given voxel
        @param voxel reference to voxel cell (which stores voxel index in array)
    */
    void operator()(unsigned short voxel)
    {
      ASSERT(voxel != VOXEL_EMPTY);

      // remove object reference from voxel
      Voxel &v = m_voxels[voxel];
      v.removeObj(m_obj);
    }

  private:
    SparseArray<Voxel> &m_voxels; ///< voxel array (pool) of voxels we operate on
    VGObj              *m_obj;    ///< pointer to object we want to add
  };

  /** @brief A processor wrapper that performs processing of objects in voxel

      You can pass an instance of this to a process() method of some collection that contains
      objects inherited from VGObj. This wall cause application of wrapped processor
      only once for each object in collection.

      This is essential for CollectionVG since it can have multiple references to the same object.

      @param Processor type of wrapped processor that will be applied
  */
  template <class Processor> class VoxelProcessObjectsProc : public NonCopyable
  {
  public:
    /** @brief Constructor for processing of all objects in voxel
        @param voxels array (pool) of voxels
        @param proc   processor to apply
    */
    VoxelProcessObjectsProc(SparseArray<Voxel> &voxels, Processor &proc) : m_voxels(voxels), m_proc(proc), m_bbox(NULL), m_frustum(NULL) { }

    /** @brief Constructor for processing objects whose bbox intersects specified bbox
        @param voxels array (pool) of voxels
        @param proc   processor to apply
        @param bbox   bounding box
    */
    VoxelProcessObjectsProc(SparseArray<Voxel> &voxels, Processor &proc, Render::AABB const &bbox) : m_voxels(voxels), m_proc(proc), m_bbox(&bbox), m_frustum(NULL) { }

    /** @brief Constructor for processing objects whose bbox intersects specified frustum
        @param voxels  array (pool) of voxels
        @param proc    processor to apply
        @param frustum frustum
    */
    VoxelProcessObjectsProc(SparseArray<Voxel> &voxels, Processor &proc, Render::ConvexVolume const &frustum) : m_voxels(voxels), m_proc(proc), m_bbox(NULL), m_frustum(&frustum) { }

    /** @brief Applies wrapped processor to all objects in given voxel
        @param voxel voxel info which is voxel index in pool
    */
    void operator()(unsigned short &voxel)
    {
      if (voxel != VOXEL_EMPTY)
      {
        Voxel &v = m_voxels[voxel];
        
        if (m_bbox)
        {
          v.process(m_proc, *m_bbox);
        }
        else if (m_frustum)
        {
          v.process(m_proc, *m_frustum);
        }
        else
        {
          v.process(m_proc);
        }
      }
    }

  private:
    SparseArray<Voxel> &m_voxels;  ///< voxel array (pool) of voxels we operate on
    Processor &m_proc;             ///< processor to apply
    Render::AABB const *m_bbox;    ///< bounding box objects must intersect (can be NULL)
    Render::ConvexVolume const *m_frustum;   ///< frustum objects must intersect (can be NULL)
  };
    
  /** @brief Constructor
      @param bbox     bounding box restricting the space that is divided in voxels
      @param nVoxelsX number of voxels by X axis (all voxels are of equal size)
      @param nVoxelsZ number of voxels by Z axis (all voxels are of equal size)
      @param nMaxNumVoxels maximum number of voxels occupied simultaneously
  */
  CollectionVG(Render::AABB const &bbox, int nVoxelsX, int nVoxelsZ, int nMaxNumVoxels) :
    m_grid(bbox, nVoxelsX, nVoxelsZ),
    m_voxels(nMaxNumVoxels),
    m_processId(0)
  {
    VoxelInitProc p;
    m_grid.process(p);
  }

  /** @brief Destructor
      
      All objects in collection are released here.
  */
  ~CollectionVG()
  {
    // remove all objects from collection
    VoxelGridObj::SetVoxelGridProc p(NULL);
    process(p);
  }

  /** @brief Add object to collection
      
      @param el pointer to object
  */
  bool add(VGObj *el)
  {
    el->setVoxelGrid(this);

    // add object reference to voxels
    VoxelAddObjProc p(m_voxels, el);
		const Render::AABB &bbox = el->GetWorldAABB();
    m_grid.process(p, bbox);
    
    // add voxels reference to object
    m_grid.bboxToVoxels(bbox, el->getVoxels());

    return true;
  }
  
  /** @brief Remove object from collection
      
      @param el pointer to object
  */
  bool remove(VGObj *el)
  {
    ASSERT(el->getVoxelGrid() == this);

    IRect r = el->getVoxels();

    // remove voxels reference from object
    el->getVoxels().clear();

    // remove object reference from voxels (object pointer might become invalid after this)
    VoxelRemoveObjProc rop(m_voxels, el);
    m_grid.process(rop, r);

    el->setVoxelGrid(NULL);

    return true;
  }

  /** @brief Notify collection that object's bounding box changed
      
      This is called by VGObj so that voxel grid could correct its
      optimization structures according to new object position.

      @param obj pointer to the object that was moved
  */
  virtual void moveObject(VoxelGridObj *obj)
  {
    // cast pointer to the specific type of objects stored in this collection
    // we have to do this since otherwise our processing methods can't work
    // on the other hand we can't change parameter type due to virtuality
    VGObj *o = (VGObj*)obj;
    
    // obtain new voxel range for the object
    IRect newRect;
    m_grid.bboxToVoxels(o->GetWorldAABB(), newRect);

    // remove object reference from voxels that object moved out of
    VoxelRemoveObjProc rop(m_voxels, o);
    m_grid.process(rop, o->getVoxels(), newRect);

    // add object reference to voxels that object moved into
    VoxelAddObjProc aop(m_voxels, o);
    m_grid.process(aop, newRect, o->getVoxels());

    // update object -> voxels reference
    o->getVoxels() = newRect;
  }

  /** @brief Apply given processor to all objects in collection
      
      Processor must implement the following operator
      
      @code
      void operator()(SomeBasicType *obj)
      @endcode

      which receives pointer to an object that requires processing.

      If collection contains an object of a class not inherited from SomeBasicType
      applying such processor will cause an error.

      @param p processor
      @param bNewProcess TRUE if you want to initialize new process, FALSE to perform additional
                         processing (skip objects that were processed by previous calls)
  */
  template <class Processor> bool process(Processor &p, bool bNewProcess = true)
  {
    if (bNewProcess)
    {
      ++m_processId;
    }

    VGObj::ProcessUniqueProc<Processor> up(m_processId, p);
    
    for (int i = 0; i < m_voxels.size(); ++i)
    {
      if (m_voxels.isValid(i))
      {
        Voxel &v = m_voxels[i];
        v.process(up);
      }
    }

    return true;
  }

  /** @brief Apply given processor to all objects in collection whose bbox intersects given bbox
      
      Processor must implement the following operator
      
      @code
      void operator()(SomeBasicType *obj)
      @endcode

      which receives pointer to an object that requires processing.

      If collection contains an object of a class not inherited from SomeBasicType
      applying such processor will cause an error.

      @param p processor
      @param bbox bounding box
      @param bNewProcess TRUE if you want to initialize new process, FALSE to perform additional
                         processing (skip objects that were processed by previous calls)
  */
  template <class Processor> bool process(Processor &p, Render::AABB const &bbox, bool bNewProcess = true)
  {
    if (bNewProcess)
    {
      ++m_processId;
    }

    // user processor is wrapped into "unique" processor that prevents multiple processing
    // of the same object
    VGObj::ProcessUniqueProc<Processor> up(m_processId, p);
    
    // "unique" processor wrapped into "objects in voxel" processor that processes
    // all objects in voxel whose bbox intersects given bbox
    VoxelProcessObjectsProc< VGObj::ProcessUniqueProc<Processor> > pop(m_voxels, up, bbox);
    
    return m_grid.process(pop, bbox);
  }

  /** @brief Apply given processor to all objects in collection whose bbox intersects given frustum
      
      Processor must implement the following operator
      
      @code
      void operator()(SomeBasicType *obj)
      @endcode

      which receives pointer to an object that requires processing.

      If collection contains an object of a class not inherited from SomeBasicType
      applying such processor will cause an error.

      @param p processor
      @param frustum frustum
      @param bNewProcess TRUE if you want to initialize new process, FALSE to perform additional
                         processing (skip objects that were processed by previous calls)
  */
  template <class Processor> bool process(Processor &p, Render::ConvexVolume const &frustum, bool bNewProcess = true)
  {
    if (bNewProcess)
    {
      ++m_processId;
    }

    // user processor is wrapped into "unique" processor that prevents multiple processing
    // of the same object
    VGObj::ProcessUniqueProc<Processor> up(m_processId, p);
    
    // "unique" processor wrapped into "objects in voxel" processor that processes
    // all objects in voxel whose bbox intersects given frustum
    VoxelProcessObjectsProc< VGObj::ProcessUniqueProc<Processor> > pop(m_voxels, up, frustum);
    
    return m_grid.process(pop, frustum);
  }

private:
  VoxelGrid<unsigned short>  m_grid;      ///< voxel grid containing indices of voxels
  SparseArray<Voxel>         m_voxels;    ///< array (pool) of voxels
  unsigned int               m_processId; ///< identifier of mass operation currently being performed on objects
};

} // ns NScene
