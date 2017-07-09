#include "MemChunk.h"
#include <stdlib.h>

MemChunk::MemChunk()
	: m_pHead(nullptr)
	, m_pCurrentNode(nullptr)
	, m_pLastNode(nullptr)
	, m_Recyle()
	, m_Cursor(0)
{

}

MemChunk::MemChunk(size_t a_ChunkSize, size_t a_BlockSize)
	: m_TotalChunkSize(a_ChunkSize)
	, m_BlockSize(a_BlockSize)
	, m_NumBlocks(m_TotalChunkSize / m_BlockSize)
	, m_pHead(nullptr)
	, m_pCurrentNode(nullptr)
	, m_pLastNode(nullptr)
	, m_Recyle()
	, m_Cursor(0)
{
	if (m_TotalChunkSize % m_BlockSize != 0)
	{
		m_TotalChunkSize = m_NumBlocks * m_BlockSize;
	}
	void* temp = malloc(m_TotalChunkSize);
	MemChunkNode* node = new MemChunkNode();
	node->Chunk = temp;
	node->ChunkSize = m_TotalChunkSize;
	node->NumBlock = m_NumBlocks;
	node->Next = nullptr;
	m_pHead = node;
	m_pCurrentNode = node;
	m_pLastNode = node;
	m_Recyle.Initialize(m_NumBlocks);
}

MemChunk::~MemChunk()
{
}

void MemChunk::Initialize(size_t a_ChunkSize, size_t a_BlockSize)
{
	m_TotalChunkSize = a_ChunkSize;
	m_BlockSize = a_BlockSize;
	m_NumBlocks = m_TotalChunkSize / m_BlockSize;

	if (m_TotalChunkSize % m_BlockSize != 0)
	{
		m_TotalChunkSize = m_NumBlocks * m_BlockSize;
	}
	void* temp = malloc(m_TotalChunkSize);
	MemChunkNode* node = new MemChunkNode();
	node->Chunk = temp;
	node->ChunkSize = m_TotalChunkSize;
	node->NumBlock = m_NumBlocks;
	node->Next = nullptr;
	m_pHead = node;
	m_pCurrentNode = node;
	m_pLastNode = node;
	m_Recyle.Initialize(m_NumBlocks);
}


void* MemChunk::Alloc()
{
	if (m_Cursor >= m_pCurrentNode->NumBlock)
	{
		if (!m_Recyle.isEmpty())
		{
			void* pRet = m_Recyle.Pop();
			if (pRet != nullptr)
			{
				return pRet;
			}
		}

		if (m_pCurrentNode == m_pLastNode)
		{
			Expand(m_TotalChunkSize);
			m_Cursor = 0;
			m_pCurrentNode = m_pCurrentNode->Next;
			void* pRet = (char*)m_pCurrentNode->Chunk + (m_Cursor * m_BlockSize);
			++m_Cursor;
			return pRet;
		}
		else
		{
			m_pCurrentNode = m_pCurrentNode->Next;
			m_Cursor = 0;
			m_pCurrentNode = m_pCurrentNode->Next;
			void* pRet = (char*)m_pCurrentNode->Chunk + (m_Cursor * m_BlockSize);
			++m_Cursor;
			return pRet;
		}
	}
	else
	{
		void* pRet = (char*)m_pCurrentNode->Chunk + (m_Cursor * m_BlockSize);
		++m_Cursor;
		return pRet;
	}
}

bool MemChunk::Dealloc(void* ptr)
{
	MemChunkNode* p = m_pHead;
	while (p != nullptr)
	{
		intptr_t begin = reinterpret_cast<intptr_t>(p->Chunk);
		intptr_t end = reinterpret_cast<intptr_t>(p->Chunk) + p->ChunkSize;
		intptr_t Pointer = reinterpret_cast<intptr_t>(ptr);
		if (Pointer >= begin && Pointer < end)
		{
			m_Recyle.Push(ptr);
			return true;
		}
		p = p->Next;
	}
	return false;
}


void MemChunk::Expand(size_t a_ChunkSize)
{
	size_t NumBlock = a_ChunkSize / m_BlockSize;
	if (a_ChunkSize % m_BlockSize != 0)
	{
		a_ChunkSize = NumBlock * m_BlockSize;
	}
	void* temp = malloc(a_ChunkSize);
	m_TotalChunkSize += a_ChunkSize;
	m_NumBlocks += NumBlock;
	MemChunkNode* node = new MemChunkNode();
	node->Chunk = temp;
	node->ChunkSize = a_ChunkSize;
	node->NumBlock = NumBlock;
	node->Next = nullptr;
	m_pLastNode->Next = node;
	m_pLastNode = node;
}
