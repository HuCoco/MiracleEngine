#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

enum class NodeColor {
	Red,
	Black
};

enum class LoopMethod {
	Recursion,
	Iteration
};


class MemNode
{
public:
	intptr_t key;
	_U32 MemPoolIndex;
	NodeColor color;
	bool isAlloced;
	MemNode* pLeft;
	MemNode* pRight;
	MemNode* pParent;

	MemNode(intptr_t a_Key, _U32 a_MemPoolIndex, NodeColor a_Color);
};

#define GET_PARENT(n) ((n)->pParent)
#define GET_COLOR(n) ((n)->color)
#define IS_RED(n) ((n)->color == NodeColor::Red)
#define IS_BLACK(n) ((n)->color == NodeColor::Black)
#define SET_RED(n) ((n)->color = NodeColor::Red)
#define SET_BLACK(n) ((n)->color = NodeColor::Black)
#define SET_PARENT(n,p) ((n)->pParent = (p))
#define SET_COLOR(n,c) ((n)->color = (c))

class MemTree
{
public:
	MemTree();
	~MemTree();

	void Destroy();
	void Insert(intptr_t a_Key, _U32 a_MemPoolIndex);
	
	MemNode* Find(intptr_t key);
	
private:
	void LeftRotate(MemNode*& root, MemNode* x);
	void RightRotate(MemNode*& root, MemNode* y);

	void Destroy(MemNode*& root);

	bool Insert(MemNode*& root, MemNode* node);
	void InsertFixUp(MemNode*& root, MemNode* node);

	MemNode* FindIteration(MemNode* node, intptr_t key);
private:
	MemNode* m_pRoot{ nullptr };
};

NAMESPACE_MENGINE_END