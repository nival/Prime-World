#ifndef BINSAVERSTATSCOLLECTOR_H_2B810EE
#define BINSAVERSTATSCOLLECTOR_H_2B810EE

#include "LokiTypeInfo.h"

class BinSaverStatsCollector
{
public:
  BinSaverStatsCollector()
  {
    Reset();
  }
  
  ~BinSaverStatsCollector()
  {
    Reset();
  }

  void Reset();

  template<class T>
  void StartType( const T &t )
  {
    StartTypeImpl( typeid(T) );
  }
  
  template<class T>
  void FinishType( const T &t )
  {
    FinishTypeImpl( typeid(T) );
  }
  
  template<class T>
  void StartTypePoly( const T &t )
  {
    StartTypeImpl( typeid(t) );
  }

  template<class T>
  void FinishTypePoly( const T &t )
  {
    FinishTypeImpl( typeid(t) );
  }
  
  void DataWrited( size_t size );
  
  void DumpData();
  
  void StartDataGathering() 
  { 
    NI_ASSERT( !isDataGathering, "" );
    isDataGathering = true; 
  }
 
private:
  struct Node;
  typedef map<Loki::TypeInfo, Node> ChildredNodes;
  typedef ni_detail::UInt64 TTickCount;

  struct NodeBase
  {
    size_t count;
    size_t selfSize;
    size_t totalSize;
    TTickCount workedTime;
    
    NodeBase(): count(1), selfSize(0), totalSize(0), workedTime(0) {}
    
    NodeBase &operator+=( const NodeBase & node )
    {
      count += node.count;
      selfSize += node.selfSize;
      totalSize += node.totalSize;
      workedTime += node.workedTime;
      
      return *this;
    }
  };

  struct Node: NodeBase
  {
    explicit Node(): 
      pChildren(0) {}
        
    //map создаёт в конструкторе value_type (зачем?) и если попытаться хранить
    //просто ChildredNodes это приводит к бесконечной рекурсии
    ChildredNodes *pChildren;
  };

  struct StackItem
  {
    ChildredNodes::value_type *pNode;
    TTickCount startTypeTime;
    
    explicit StackItem( ChildredNodes::value_type *pNode = 0, TTickCount startTypeTime = 0 ):
       pNode(pNode), startTypeTime(startTypeTime) {}
  };
  
  typedef vector<StackItem> CallStack;
  typedef map<Loki::TypeInfo, NodeBase> FlateredNodes;
  
private:
   void StartTypeImpl( const std::type_info &ti );
   void FinishTypeImpl( const std::type_info &ti );
   size_t CollectDataRecursive( ChildredNodes::value_type &cur );
   void CollectSize();
   void FlatterProfileRecursive( const ChildredNodes::value_type &cur, FlateredNodes &out ) const;
   void DumpDataRecursize( int level, const ChildredNodes::value_type &cur ) const;
   void ResetRecursive( ChildredNodes::value_type &cur );
   void DumpFlattered( const FlateredNodes &flatNodes ) const;
   
   static TTickCount GetCpuTickCount();
   static double TickToMSec ( TTickCount tc );
 
private:
  BinSaverStatsCollector( const BinSaverStatsCollector & );
  BinSaverStatsCollector &operator=( const BinSaverStatsCollector & );
 
private:
  ChildredNodes::value_type root;
  CallStack callStack;
  bool isDataGathering;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BinSaverDummyStatsCollector
{
public:
  static void Reset() {}
  template<class T> static void StartType( const T & ) {}
  template<class T> static void FinishType( const T & ) {}
  template<class T> static void StartTypePoly( const T & ) {}
  template<class T> static void FinishTypePoly( const T & ) {}
  static void DataWrited( size_t ) {}
  static void DumpData() {}
  static void StartDataGathering() {}
};


#endif //#define BINSAVERSTATSCOLLECTOR_H_2B810EE