#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Memory/MemChunk.h>
#include <Core/Memory/MemTree.h>
NAMESPACE_MENGINE_BEGIN

class MemPool
{
public:

	enum MemChunkBitsType
	{
		BIT_4,
		BIT_8,
		BIT_16,
		BIT_32,
		BIT_64,
		BIT_128,
		BIT_256,
		NUM_CHUNK_BIT
	};

	MemPool();
	~MemPool();

	void Initialize();
	void* Alloc(size_t a_Size);
	void Dealloc(void* ptr);

private:
	_U32 GetBestChunkIndex(size_t a_Size);

private:
	MemChunk m_Chunks[NUM_CHUNK_BIT];
	MemTree m_Tree;
	static const _U32 MemChunkBits[NUM_CHUNK_BIT];
};

NAMESPACE_MENGINE_END