#include "MemPool.h"
#include <time.h>

const _U32 Miracle::MemPool::MemChunkBits[NUM_CHUNK_BIT] = {
	4,		//BIT_4,
	8,		//BIT_8,
	16,		//BIT_16,
	32,		//BIT_32,
	64,		//BIT_64,
	128,	//BIT_128,
	256,	//BIT_256
};

Miracle::MemPool::MemPool()
{

}


Miracle::MemPool::~MemPool()
{
}

void Miracle::MemPool::Initialize()
{
	for (int i = 0; i < NUM_CHUNK_BIT; ++i)
	{
		m_Chunks[i].Initialize(1024 * 1024, MemChunkBits[i]);
	}
}

void* Miracle::MemPool::Alloc(size_t a_Size)
{
	clock_t a = clock();
	_U32 BestChunkIndex = GetBestChunkIndex(a_Size);
	void* pRet = nullptr;
	if (BestChunkIndex == -1)
	{
		pRet = malloc(a_Size);
		return pRet;
	}
	pRet = m_Chunks[BestChunkIndex].Alloc();

	clock_t b = clock();
	clock_t c = b - a;
	return pRet;
}

void Miracle::MemPool::Dealloc(void* ptr)
{
	bool IsDealloc = false;
	for (int i = 0; i < NUM_CHUNK_BIT && IsDealloc == false; ++i)
	{
		IsDealloc = m_Chunks[i].Dealloc(ptr);
	}

	
}

_U32 Miracle::MemPool::GetBestChunkIndex(size_t a_Size)
{
	if (a_Size <= 0)
	{
		MENGINE_ASSERT_MSG(false, "Zero!");
		return 0;
	}
	else if (a_Size > 0 && a_Size <= 4)
	{
		return BIT_4;
	}
	else if (a_Size > 4 && a_Size <= 8)
	{
		return BIT_8;
	}
	else if (a_Size > 8 && a_Size <= 16)
	{
		return BIT_16;
	}
	else if (a_Size > 16 && a_Size <= 32)
	{
		return BIT_32;
	}
	else if (a_Size > 32 && a_Size <= 64)
	{
		return BIT_64;
	}
	else if (a_Size > 64 && a_Size <= 128)
	{
		return BIT_128;
	}
	else if (a_Size > 128 && a_Size <= 256)
	{
		return BIT_256;
	}
	else if(a_Size > 256)
	{
		return -1;
	}
	
	return -2;
}
