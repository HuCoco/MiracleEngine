#pragma once
#include <Independent/Platform/PreCompileHeader.h>

class MemStack
{
public:
	MemStack();
	MemStack(size_t a_Size);
	~MemStack();

	void Push(void* ptr);
	void* Pop();
	void Initialize(size_t a_Size);
	void Expand(size_t a_Size);
	bool isEmpty();
private:
	void** m_Stack;
	size_t m_MaxSize;
	size_t m_Index;
};

