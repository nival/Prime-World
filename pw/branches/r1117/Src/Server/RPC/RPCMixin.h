#pragma once

#include "RPC/RPC.h"
#include <System/TestAssertDumper.h>
#include <System/TestSuite.h>
#include <System/AddressOf.h>
#include <System/sleep.h>
#include <System/ported/types.h>
#include <System/ported/cwfn.h>

#pragma warning( disable: 4512 ) //assignment operator could not be generated   

namespace nstl 
{
  template <typename T>
  struct BaseTyper 
  {
    BaseTyper(T InitValue):value(InitValue) {}
    operator T & () { return value; }
    operator T() const { return value; }
  protected:
    T value;
  };

  template <bool InitValue>
  struct Bool : BaseTyper<bool> 
  {
    Bool() : BaseTyper<bool>(InitValue) {}
    void operator = (bool _value) { value = _value; }
  };

} // nstl

namespace nstl
{
    struct ConstantBlockInfo {
        union {
            const void* memory;
            const void* data;
        };

        uint size;

        ConstantBlockInfo():memory(0), size(0) {}
        ConstantBlockInfo(const void* memory, uint size):memory(memory), size(size) {}
    };
    
    struct BlockInfo {
        union {
            void* memory;
            void* data;
        };

        uint size;

        BlockInfo():memory(0), size(0) {}
        BlockInfo(void* memory, uint size):memory(memory), size(size) {}
    };
    struct BlockCollector {
        nstl::vector<BlockInfo> chunks;

        char* append(ConstantBlockInfo info) {
            return append(info.memory, info.size);
        }

        char* append(const void* data, uint size) {
            char* memory = new char[size];
            memcpy(memory, data, size);
            chunks.push_back(BlockInfo(memory, size));
            return memory;
        }

        ~BlockCollector()  
        {
            clear();
        }

        void clear()
        {
            for (int i=0;i<chunks.size();++i) {
                delete [] (char*)chunks[i].memory;
            }
            chunks.resize(0);
        }

        uint getSize() {
            int size = 0;
            for (int i=0;i<chunks.size();++i) {
                size += chunks[i].size;
            }
            return size;
        }

        void flush(void* memory) {
            char* ptr = (char*)memory;
            for (int i=0;i<chunks.size();++i) {
                memcpy(ptr, chunks[i].memory, chunks[i].size);
                ptr += chunks[i].size;
            }
        }

        uint size() {
            return chunks.size();
        }
    };
}

struct TestChannel : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestChannel, BaseObjectMT );

public:
  TestChannel(uint lag, bool& _isBlocked) :
  id(0), frame(0), maxLag(lag), isBlocked(_isBlocked)
  {
  }

  void Poll()
  {
    frame--;
  }

  void send(uint id, const byte* data, int size )
  {
    if (isBlocked) 
      return;
    threading::MutexLock locker(lock);
    frame = maxLag;
    getCollector(id, false).append( data, size );
  }

  bool recieve(uint id, int index, byte** data, int* size )
  {
    if (isBlocked) 
    {
      *data = 0;
      *size = 0;
      return false;
    }
    threading::MutexLock locker(lock);
    if (frame <= 0)
    {
      BlockCollector& collector = getCollector(id, true);

      if (index >= collector.chunks.size())
        return false;

      *data = (byte*) collector.chunks[index].data;
      *size = collector.chunks[index].size;
      return true;
    } else
    {
      *data = 0;
      *size = 0;
      return false;
    }
  }

  uint registerEndPoint()
  {
    threading::MutexLock locker(lock);
    return id++;
  }

  void clear(uint id)
  {
    threading::MutexLock locker(lock);
    if (frame <= 0)
    {
      getCollector(id, true).clear();
    }
  }
private:
  BlockCollector& getCollector(uint id, bool recieve)
  {
    if (id == 0) 
    {
      return recieve?c1_0:c0_1;
    } 
    else
    {
      return recieve?c0_1:c1_0;
    }
  }
  int maxLag;
  int frame;
  uint id;
  BlockCollector c0_1;
  BlockCollector c1_0;
  threading::Mutex lock;
  bool& isBlocked;
};

namespace test
{
struct IPacketProcessor
{
  virtual void OnSend(byte* data, uint size)=0;
};
};

struct TestPacketPipe : public rpc::IPacketPipe, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TestPacketPipe, rpc::IPacketPipe, BaseObjectMT );

  TestPacketPipe(TestChannel * channel, const char* _srcName=0, const char* dstName=0):
  channel(channel),
  processor(0)
  {
    id = channel->registerEndPoint();
    if (dstName)
    {
      name = dstName;
    } else
    {
      char buffer[16];
      NStr::Printf(buffer, 16, "node(%p)", this);
      name = buffer;
    }
    if (_srcName)
    {
      srcName = _srcName;
    }
  }

  ~TestPacketPipe()
  {}

  virtual void Send( const byte* data, int size, bool force )
  {
    threading::MutexLock lock(locker);
    if (processor)
    {
      cache.resize(size);
      memcpy(&cache[0], data, size);
      processor->OnSend(&cache[0], size);
      channel->send(id, &cache[0], size );
    } 
    else
    {
      channel->send(id, data, size );
    }

  }

  virtual bool Recieve(int index, byte** data, int* size, Transport::MessageMiscInfo& recieveTime )
  {
    threading::MutexLock lock(locker);
    bool result = channel->recieve(id, index, data, size );
    return result;
  }

  virtual void Reset() {
    threading::MutexLock lock(locker);
    channel->clear(id);
  }

  virtual const char* GetName() const 
  { 
    return name.c_str(); 
  }

  virtual IPacketPipe::PipeInfo GetInfo() const 
  { 
    rpc::IPacketPipe::PipeInfo info = {rpc::IPacketPipe::PipeInfo::Connected, id}; 
    return info; 
  }

  void SetProcessor(test::IPacketProcessor* _processor)
  {
    processor = _processor;
  }

  StrongMT<TestChannel> channel;
  nstl::string name;
  nstl::string srcName;
  uint id;
  threading::Mutex locker;
  test::IPacketProcessor* processor;
  nstl::vector<byte> cache;
};

struct RPCMixin
{
    template <typename T, typename TC>
    T* waitForEntity(rpc::Node* c, uint entityId, TC& tc)
    {
        do
        {
            tc.Poll();
            T* o = c->get<T>(entityId);
            if (o) {
                return o;
            }
        } while (true);    
    }

    template <typename T, typename TC>
    T* waitForEntityTimeout(rpc::Node* c, uint entityId, TC& tc, uint timeout )
    {
      do
      {
        tc.Poll();
        T* o = c->get<T>(entityId);
        if (o) {
          return o;
        }
        nival::sleep( 1 );
      } while (--timeout > 0 );    
      return 0;
    }

    
    template <typename T, typename TC>
    void waitForMissedEntity(rpc::Node* c, uint entityId, TC& tc)
    { 
        do
        {
            tc.Poll();
            T* o = c->get<T>(entityId);
            if (!o) {
                return;
            }
        } while (true);    
    }
};

struct Nodes
{
  StrongMT<rpc::Node> f_s;
  StrongMT<rpc::Node> s_f;
  bool isConnected() { return f_s->IsReady() && s_f->IsReady(); }
};

struct Gates
{
  void push_back(rpc::Gate& gate)
  {
    items.push_back( nival::getaddressof( gate ) );
  }

  void Poll()
  {
    for (int i=0;i<items.size();++i)
    {
      items[i]->Poll();
    }
  }
  nstl::vector<StrongMT<rpc::Gate> > items;
};

struct ManyToManyCase
{
  struct Gate2GateNodeInfo
  {
    StrongMT<rpc::Node> s2d;
    StrongMT<rpc::Node> d2s;
    StrongMT<TestPacketPipe> pipe_s2d;
    StrongMT<TestPacketPipe> pipe_d2s;
  };
  struct GateLink
  {
    StrongMT<rpc::Node> node;
    StrongMT<TestPacketPipe> pipe;
  };
  struct GateInfo
  {
    StrongMT<rpc::Gate> gate0;
    StrongMT<rpc::Gate> gate1;
    Gate2GateNodeInfo nodes;
  };
  typedef nstl::vector< GateInfo > NodesContainer;

  bool IsConnected() const 
  {
    for (NodesContainer::const_iterator it = nodes.begin();it != nodes.end(); ++it)
    {
      if (!it->nodes.s2d->IsReady())
      {
        return false;
      }
      if (!it->nodes.d2s->IsReady())
      {
        return false;
      }
    }
    return true;
  }

  void Block()
  {
    isBlocked = true;
  }

  void Poll() 
  { 
    gates.Poll(); 
    for (int i=0;i<channels.size();++i)
    {
      channels[i]->Poll();
    }
  }
  ManyToManyCase():isBlocked(false) {}

  ~ManyToManyCase()
  {
    _gates.clear();
    gates.items.clear();

    channels.clear();
  }

  int FindGateKey(rpc::Gate& gate0, rpc::Gate& gate1, bool& isSwapped)
  {
    for (int i=0;i<nodes.size();++i)
    {
      if (nodes[i].gate0 == nival::getaddressof( gate0 ))
      {
        if (nodes[i].gate1 == nival::getaddressof( gate1 ))
        {
          isSwapped = false;
          return i;
        }
      } else 
      if (nodes[i].gate0 == nival::getaddressof( gate1 ))
      {
        if (nodes[i].gate1 == nival::getaddressof( gate0 ))
        {
          isSwapped = true;
          return i;
        }
      }
    }
    return -1;
  }

  rpc::Gate* FindGateByID(const GUID& id)
  {
    for (int i=0;i<_gates.size();++i)
    {
      if (_gates[i]->GetID() == id)
      {
        return _gates[i];
      }
    }
    return 0;
  }

  GateLink GetGateLink(rpc::Gate& gate0, rpc::Gate& gate1)
  {
    NI_PROFILE_FUNCTION;
    bool isSwapped = false;
    int index = FindGateKey(gate0, gate1, isSwapped);
    if (index < 0)
    {
      NI_STOP(); // gates not connected
    }
    if (!isSwapped)
    {
      GateLink link = {nodes[index].nodes.s2d, nodes[index].nodes.pipe_s2d};
      return link;
    } else 
    {
      GateLink link = {nodes[index].nodes.d2s, nodes[index].nodes.pipe_d2s};
      return link;
    }
  }
  

  void DisconnectGates(rpc::Gate& gate0, rpc::Gate& gate1)
  {
    NI_PROFILE_FUNCTION;
    bool isSwapped = false;
    int index = FindGateKey(gate0, gate1, isSwapped);
    if (index < 0)
    {
      NI_STOP(); // gates not connected
    }
    TestPacketPipe* pipe01 = (TestPacketPipe*)(nodes[index].nodes.s2d->GetPipe());
    TestPacketPipe* pipe10 = (TestPacketPipe*)(nodes[index].nodes.d2s->GetPipe());
    if (!isSwapped)
    {
      gate0.RemovePipe(nodes[index].nodes.s2d);
      gate1.RemovePipe(nodes[index].nodes.d2s);
    } else 
    {
      gate0.RemovePipe(nodes[index].nodes.d2s);
      gate1.RemovePipe(nodes[index].nodes.s2d);
    }

    StrongMT<TestChannel> channel = pipe01->channel;
    channels.remove(channel);

    pipes.remove(pipe01);
    pipes.remove(pipe10);

    nodes.eraseByIndex(index);
  }

  Gate2GateNodeInfo ConnectGates(rpc::Gate& gate0, rpc::Gate& gate1, int lag=0, const GUID* id=0, const char* name=0)
  {
    StrongMT<TestChannel> channel = new TestChannel(lag, isBlocked);
    channels.push_back(channel);
    nstl::string gate0Name = gates2names[nival::getaddressof( gate0 )];
    nstl::string gate1Name;
    if (name)
      gate1Name = name;
    else
      gate1Name = gates2names[nival::getaddressof( gate1 )];
    StrongMT<TestPacketPipe> pipe01 = new TestPacketPipe(channel, gate0Name.c_str(), gate1Name.c_str());        
    StrongMT<TestPacketPipe> pipe10 = new TestPacketPipe(channel, gate1Name.c_str(), gate0Name.c_str());        
    pipes.push_back(pipe01);
    pipes.push_back(pipe10);
    rpc::Node* node01 = gate0.AddPipe(pipe01, id);
    rpc::Node* node10 = gate1.AddPipe(pipe10);
    Gate2GateNodeInfo info = {node01, node10, pipe01, pipe10 };
    GateInfo key = { nival::getaddressof( gate0 ), nival::getaddressof( gate1 ), info };
    nodes.push_back(key);
    return info;
  }

  rpc::IPacketPipe * ConnectGates(const char* src, const char* dst, const GUID* id = 0)
  {
    rpc::Gate* srcGate = GetGate(src);
    rpc::Gate* dstGate = GetGate(dst);
    if (!dstGate && id)
    {
      dstGate = FindGateByID(*id);
    }
    if (!dstGate)
    {
      NI_STOP(); // no gate found
    }
    Gate2GateNodeInfo info = ConnectGates(*srcGate, *dstGate, 0, id, dst);
    return info.s2d->GetPipe();
  }

  rpc::Gate& GetGate(int index) { return *_gates[index]; }
  rpc::Gate* GetGate(const char* name) 
  { 
    nstl::map<nstl::string, nstl::vector<rpc::Gate*> >::iterator it = names2gates.find(name);
    if (it != names2gates.end())
    {
      if (it->second.size() > 0 )
      {
        return it->second[0];
      }
    }
    return 0; 
  }

  rpc::Node* GetNode(rpc::Gate* src, rpc::Gate* dst) 
  {
    return GetNode(*src, *dst);
  }

  rpc::Node* GetNode(rpc::Gate& src, rpc::Gate& dst) 
  {
    for (NodesContainer::iterator it=nodes.begin();it != nodes.end();++it)
    {
      if (it->gate0 == nival::getaddressof( src ) && it->gate1 == nival::getaddressof( dst ))
      {
        return it->nodes.s2d;
      }
      if (it->gate0 == nival::getaddressof( dst ) && it->gate1 == nival::getaddressof( src ))
      {
        return it->nodes.d2s;
      }
    }
    return 0;
  }

  rpc::Gate& AddGate(const char* name, rpc::IPipeProcessor* _processor=0)
  {
    return AddGate(name, 0, _processor);
  }
  void WaitForConnections()
  {
    while (!IsConnected()) Poll();
  }

  rpc::Gate& AddGate(const char* name, int threadsCount, rpc::IPipeProcessor* _processor=0)
  {
    StrongMT<rpc::IPipeProcessor> processor;
    if (!_processor)
    {
      processor = new EmptyPipeProcessor( name );
      processors.push_back(processor);
    } else
    {
      processor = _processor;
    }

    rpc::Gate* newGate = new rpc::Gate(processor, threadsCount);
    _gates.push_back(newGate);
    gates.push_back(*newGate);
    gates2names[newGate] = name;
    nstl::map<nstl::string, nstl::vector<rpc::Gate*> >::iterator it = names2gates.find(name);
    if (it == names2gates.end())
    {
      it = names2gates.insert(name);
    }
    it->second.push_back(newGate);
    return *newGate;
  }
protected:
  Gates gates;
  nstl::vector<StrongMT<rpc::IPipeProcessor> > processors;
  nstl::vector<StrongMT<TestChannel> > channels;
  nstl::vector<StrongMT<TestPacketPipe> > pipes;
  nstl::vector<StrongMT<rpc::Gate> > _gates;
  NodesContainer nodes; 
  nstl::map<rpc::Gate*, nstl::string> gates2names;
  nstl::map<nstl::string, nstl::vector<rpc::Gate*> > names2gates;
  bool isBlocked;

  struct EmptyPipeProcessor : public rpc::IPipeProcessor, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( EmptyPipeProcessor, IPipeProcessor, BaseObjectMT );

    nstl::string name;
    EmptyPipeProcessor( const char* _name = 0 ) : name(_name ) {}

    virtual ~EmptyPipeProcessor() {}
    virtual void OnCorruptData(rpc::IPacketPipe * ) {}
    virtual StrongMT<rpc::IPacketPipe> ConnectToPipe(const char*, const GUID& ) { return 0; }
    virtual const char* GetName() const { return name.c_str(); }
  };
};

struct OneToManyCase : ManyToManyCase
{

  OneToManyCase(const char* name, rpc::IPipeProcessor* _processor=0)
  {
    AddGate(name, _processor);
  }

  rpc::Gate& AddConnectedGate(const char* name, rpc::IPipeProcessor* _processor=0)
  {
    rpc::Gate&result = AddConnectedGate(name, 0, _processor);
    WaitForConnections();
    return result;
  }

  rpc::Gate& AddConnectedGate(const char* name, int threadsCount, rpc::IPipeProcessor* _processor=0)
  {
    rpc::Gate& newGate = AddGate(name, threadsCount, _processor);
    ConnectGates(GetRootGate(), newGate);
    return newGate;
  }

  rpc::Gate& GetRootGate() { return GetGate(0); }
};


struct TwoNodesCase : ManyToManyCase 
{
    StrongMT<rpc::Node> cnode0;
    StrongMT<rpc::Node> cnode1;

    TwoNodesCase(rpc::IPipeProcessor* p0=0, rpc::IPipeProcessor* p1=0)
    {
      rpc::Gate& node0 = AddGate("node0", 0, p0);
      rpc::Gate& node1 = AddGate("node1", 0, p1);
      ConnectGates(node0, node1);

      cnode0 = GetNode(node0, node1);
      cnode1 = GetNode(node1, node0);
      WaitForConnections();
    }

    void Disconnect(bool disconnectFirst=true, bool disconnectSecond=true)
    {
      rpc::Gate* gate0 = GetGate("node0");
      rpc::Gate* gate1 = GetGate("node1");
      if (disconnectFirst)
      {
        gate0->RemovePipe(GetNode(gate0, gate1));
      }
      if (disconnectSecond)
      {
        gate1->RemovePipe(GetNode(gate1, gate0));
      }
    }
};


template <typename T, typename RT>
struct Case : TwoNodesCase
{
    StrongMT<RT> ro;
    T* lo;

    Case():TwoNodesCase() 
    {
        ro = cnode0->Create<RT>();
        RPCMixin m;
        lo = m.waitForEntity<T>(cnode1, 0, *this);
    }
    template <typename P0>
    Case(const P0& value):TwoNodesCase() 
    {
      ro = cnode0->Create<RT>(value);
      RPCMixin m;
      lo = m.waitForEntity<T>(cnode1, 0, *this);
    }
};

#define TS_WAIT_FOR(condition, period)  \
for (int i=period;i>0&& !(condition);i-=2) { c.Poll(); threading::Sleep(1); } \
TS_ASSERT( condition )

#define TS_WAIT_FOR2(gate, condition, period)  \
  for (int i=period;i>0&& !(condition);i-=2) { gate.Poll(); threading::Sleep(1); } \
  TS_ASSERT( condition )

namespace test
{

struct SMatchmakingStatus : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  nstl::string  sessionId; 
  int     progress;
  int     requestsAccepted;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&sessionId); f.Add(3,&progress); f.Add(4,&requestsAccepted); return 0; }

  SMatchmakingStatus( int _progress, int _accepted, const nstl::string & _sessId ) :
  progress( _progress ), requestsAccepted( _accepted ), sessionId( _sessId ) {}

  SMatchmakingStatus() : progress( 0 ), requestsAccepted( 0 ) {}
};

  namespace TIOProtocol 
  { 
    typedef int   ObjectID;
    enum 
    { 
      invalidObjectId  = 0 
    };
    typedef float   Time;
  } 

  struct InitialSnapshot : rpc::Data
  {
    SERIALIZE_ID();

    struct DiffDesc
    {
      test::TIOProtocol::ObjectID id;
      bool isDead;
    };

    typedef list<DiffDesc> Diffs;

    struct SnapshotDesc
    {
      ZDATA
        test::TIOProtocol::ObjectID id;
      CVec3 target;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&target); return 0; }

      SnapshotDesc() : id(test::TIOProtocol::invalidObjectId), target(VNULL3) {}
    };

    typedef list<SnapshotDesc> Objects;

    ZDATA
      Objects dynamicObjects;
    Diffs difference;
    test::TIOProtocol::Time serverTime;
    ZEND int operator&( IBinSaver &f ) { f.Add(2, &dynamicObjects); f.Add(3, &difference); f.Add(4, &serverTime); return 0; }
    char buffer[1024*5];
  };

struct MockCorruptedPacketProcessor : public BaseObjectMT, public rpc::IPipeProcessor
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockCorruptedPacketProcessor, BaseObjectMT, rpc::IPipeProcessor );

public:
  MockCorruptedPacketProcessor(const char* name=0, ManyToManyCase* _env=0):
  corruptedPipe(0),
  env(_env)
  {
    if (name)
    {
      nodeName = name;
    }
  }

  virtual void OnCorruptData(rpc::IPacketPipe * _pipe)
  {
    corruptedPipe = _pipe;
  }

  virtual StrongMT<rpc::IPacketPipe> ConnectToPipe(const char* name, const GUID& id)
  {
    connections.push_back(name);
    if (env)
    {
      return env->ConnectGates(nodeName.c_str(), name, &id);
    }
    return 0;
  }
  virtual const char* GetName() const { return nodeName.c_str(); }

  rpc::IPacketPipe* corruptedPipe;
  nstl::string nodeName;
  ManyToManyCase* env;
  nstl::vector<nstl::string> connections;
};

struct UpdateCallback : rpc::IUpdateCallback
{
  UpdateCallback() 
  {
    Reset();
  }

  virtual void OnUpdated(const rpc::IRemoteEntity* _entity)
  {
    isUpdated = true;
    entity = _entity;
    entities.push_back(_entity);
  }
  bool isUpdated;
  const rpc::IRemoteEntity* entity;
  nstl::vector<const rpc::IRemoteEntity*> entities;

  void Reset()
  {
    isUpdated = false;
    entity = 0;
    entities.clear();
  }
};

} // test

