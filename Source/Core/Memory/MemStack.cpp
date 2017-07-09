#include "MemStack.h"
#include <stdlib.h>

MemStack::MemStack()
{

}

MemStack::MemStack(size_t a_Size)
	: m_MaxSize(a_Size)
{
	m_Stack = (void**)malloc(sizeof(void*) * m_MaxSize);
}

void MemStack::Initialize(size_t a_Size)
{
	m_MaxSize = a_Size;
	m_Stack = (void**)malloc(sizeof(void*) * m_MaxSize);
}


MemStack::~MemStack()
{
}

void MemStack::Expand(size_t a_Size)
{
	m_MaxSize = a_Size;
	realloc(m_Stack, m_MaxSize);
}

bool MemStack::isEmpty()
{
	return m_Index == 0 ? true : false;
}

void MemStack::Push(void* ptr)
{
	if (m_Index >= m_MaxSize)
	{
		Expand(m_MaxSize);
	}
	m_Stack[m_Index] = ptr;
	++m_Index;
}

void* MemStack::Pop()
{
	if (m_Index <= 0)
	{
		return nullptr;
	}
	return m_Stack[--m_Index];
}

