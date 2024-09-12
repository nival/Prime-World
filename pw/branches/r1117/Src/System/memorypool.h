#pragma once

#define MAX_MEMORY_BLOCK_COUNT 16
#define MEMORY_BLOCK_SIZE (1024*1024*10)

class MemoryBlock
{
	MemoryBlock& operator=(const MemoryBlock&);
	MemoryBlock(const MemoryBlock&);
	///
	unsigned int payload;
	unsigned int size;
	unsigned char* pData;
	friend class MemoryPool;
public:
	MemoryBlock() : payload(0), pData(0), size(0)
	{
	}

	void Initialize( unsigned int memoryBlockSize);

	void Clear();

	void Release();

	unsigned int GetSize() const { return size; }

	unsigned int GetPayload() const { return payload; } 

	unsigned int GetLeftover() const { return size-payload; }

	void* Allocate(unsigned int size);

	void Normalize( unsigned int _alignmentSize = 512 );

	bool IsEmpty() const { return (pData && !payload); }
	
	~MemoryBlock()
	{
		Clear();
		Release();
	}

};

class MemoryPool
{
	unsigned int currentBlockCount;
	nstl::string poolName;

  typedef nstl::list<MemoryBlock> MemoryBlocks;
	MemoryBlocks memoryBlocks;
	
	void AllocateNewBlock( unsigned int blockSize );

	hash_map<nstl::string, unsigned int> stats;
	
public:
	MemoryPool() 
		: currentBlockCount(0)
	{
		AllocateNewBlock(MEMORY_BLOCK_SIZE*2);
	}

	void* AllocateMemory( unsigned int size, const nstl::string& fileName );

	unsigned int GetPayload() const;

	unsigned int GetAllocatedSize() const;

	void Initialize( const nstl::string& memoryPoolName )
	{
		poolName = memoryPoolName;
	}

	void Release();

	void Clear();

	void ReleaseEmptyBlocks();

	const nstl::string& GetPoolName() const
	{
		return poolName;
	}

	~MemoryPool()
	{
		Release();
	}

};
