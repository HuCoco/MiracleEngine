#include <Core/Memory/MemTree.h>


Miracle::MemNode::MemNode(intptr_t a_Key, _U32 a_MemPoolIndex, NodeColor a_Color)
	: key(a_Key)
	, MemPoolIndex(a_MemPoolIndex)
	, color(a_Color)
	, isAlloced(true)
{

}

Miracle::MemTree::MemTree()
{

}



Miracle::MemTree::~MemTree()
{
	Destroy(m_pRoot);
}

void Miracle::MemTree::Destroy()
{
	Destroy(m_pRoot);
}

void Miracle::MemTree::Destroy(MemNode*& root)
{
	if (root == nullptr)
	{
		return;
	}

	if (root->pLeft != nullptr) {
		Destroy(root->pLeft);
	}

	if (root->pRight != nullptr) {
		Destroy(root->pRight);
	}

	delete root;
	root = nullptr;
}


void Miracle::MemTree::LeftRotate(MemNode*& root, MemNode* x)
{
	MemNode* y = x->pRight;

	x->pRight = y->pLeft;
	if (y->pLeft != nullptr) {
		y->pLeft->pParent = x;
	}

	y->pParent = x->pParent;

	if (x->pParent == nullptr) {
		root = y;
	}
	else {
		if (x->pParent->pLeft == x) {
			x->pParent->pLeft = y;
		}
		else {
			x->pParent->pRight = y;
		}
	}
	y->pLeft = x;
	x->pParent = y;
}

void Miracle::MemTree::RightRotate(MemNode*& root, MemNode* y)
{
	MemNode* x = y->pLeft;

	y->pLeft = x->pRight;
	if (x->pRight != nullptr) {
		x->pRight->pParent = y;
	}

	x->pParent = y->pParent;

	if (y->pParent == nullptr) {
		root = x;
	}
	else {
		if (y->pParent->pRight == y) {
			y->pParent->pRight = x;
		}
		else {
			y->pParent->pLeft = x;
		}
	}

	x->pRight = y;
	y->pParent = x;
}

void Miracle::MemTree::Insert(intptr_t a_Key, _U32 a_MemPoolIndex)
{
	MemNode* z = new MemNode(a_Key, a_MemPoolIndex, NodeColor::Black);
	if (!Insert(m_pRoot, z))
	{
		delete z;
		z = nullptr;
	}
}

bool Miracle::MemTree::Insert(MemNode*& root, MemNode* node)
{
	MemNode* y = nullptr;
	MemNode* x = root;

	while (x != nullptr) {

		if (x->key == node->key) {
			return false;
		}

		y = x;
		if (node->key < x->key) {
			x = x->pLeft;
		}
		else {
			x = x->pRight;
		}

	}


	node->pParent = y;

	if (y != nullptr) {
		if (node->key < y->key) {
			y->pLeft = node;
		}
		else {
			y->pRight = node;
		}
	}
	else {
		root = node;
	}

	SET_RED(node);

	InsertFixUp(root, node);

	return true;
}

void Miracle::MemTree::InsertFixUp(MemNode*& root, MemNode* node)
{
	MemNode* parent;
	MemNode* gparnet;

	while ((parent = GET_PARENT(node)) && (IS_RED(parent))) {

		gparnet = GET_PARENT(parent);

		if (parent == gparnet->pLeft) {
			MemNode* uncle = gparnet->pRight;
			if (uncle && IS_RED(uncle)) {
				SET_BLACK(uncle);
				SET_BLACK(parent);
				SET_RED(gparnet);
				node = gparnet;
				continue;
			}
			if (parent->pRight == node) {
				MemNode* tmp;
				LeftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			SET_BLACK(parent);
			SET_RED(gparnet);
			RightRotate(root, gparnet);

		}
		else {
			MemNode* uncle = gparnet->pLeft;
			if (uncle && IS_RED(uncle)) {
				SET_BLACK(uncle);
				SET_BLACK(parent);
				SET_RED(gparnet);
				node = gparnet;
				continue;
			}
			if (parent->pLeft == node) {
				MemNode* tmp;
				RightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			SET_BLACK(parent);
			SET_RED(gparnet);
			LeftRotate(root, gparnet);
		}

	}
	SET_BLACK(root);
}

Miracle::MemNode* Miracle::MemTree::Find(intptr_t key)
{
	return FindIteration(m_pRoot, key);
}

Miracle::MemNode* Miracle::MemTree::FindIteration(MemNode* node, intptr_t key)
{
	while ((node != nullptr) && (node->key != key)) {
		if (key < node->key) {
			node = node->pLeft;
		}
		else {
			node = node->pRight;
		}
	}
	return node;
}

