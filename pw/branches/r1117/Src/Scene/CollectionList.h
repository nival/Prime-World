#pragma once

#include "../System/nlist.h"
#include "../System/fixedvector.h"

#define NESTED_PROCESS_MAX_DEPTH 2

namespace NScene
{

/** @brief Collection that stores a list of elements
*/
template <class Element> class CollectionList
{
public:
  typedef list<Element*> List;

  CollectionList() {}

  /** @brief Destructor
      
      All objects in collection are released here.
  */
  ~CollectionList()
  {
  }

  /** @brief Add object to collection
      
      @param el pointer to object
  */
  bool add(Element *el)
  {
    m_lists[el->GetRenderGroup()].push_back(el);
    return true;
  }
  
  /** @brief Remove object from collection
      
      @param el pointer to object
  */
  bool remove(Element *el)
  {
    if (m_processes.size() > 0)
    {
      List::iterator &next = m_processes[m_processes.size() - 1];
      if (*next == el)
      {
        ++next;
      }
    }
    m_lists[el->GetRenderGroup()].remove(el);
    return true;
  }

  /** @brief Apply given processor to all objects of given group in collection (in order of addition)

  Processor must implement the following operator

  @code
  DiVoid operator()(SomeBasicType *obj)
  @endcode

  which receives pointer to an object that requires processing.

  If collection contains an object of a class not inherited from SomeBasicType
  applying such processor will cause an error.

  @param p processor
  */
  template <class Processor> bool process(Processor &p, int group)
  {
    NI_ASSERT(m_processes.size() < NESTED_PROCESS_MAX_DEPTH, "Max depth of nested process calls exceeded");

    List& curList = m_lists[group];
    List::iterator &next = m_processes.push_back();
    //List::iterator const end = curList.end();
    for(next = curList.begin(); next != curList.end();) {
      Element *el = *(next++);
      p(*el);
    }
    m_processes.setsize(m_processes.size() - 1);
    return true;
  }

  /** @brief Apply given processor to all objects in collection (in order of addition)
      
      Processor must implement the following operator
      
      @code
      DiVoid operator()(SomeBasicType *obj)
      @endcode

      which receives pointer to an object that requires processing.

      If collection contains an object of a class not inherited from SomeBasicType
      applying such processor will cause an error.

      @param p processor
  */
  template <class Processor> bool process(Processor &p)
  {
    const typename Element::RenderGroups group = p.getRenderGroup();
    if(group == Element::NUM_GROUPS) {
      for(int currGroup = Element::RG_DEFAULT; currGroup != Element::NUM_GROUPS; ++currGroup)
        process(p, currGroup);
    }
    else
        process(p, group);

    return true;
  }

private:
  List m_lists[Element::NUM_GROUPS]; ///< lists containing pointers to objects
  FixedVector<typename List::iterator, NESTED_PROCESS_MAX_DEPTH> m_processes;
};

} // ns NScene
