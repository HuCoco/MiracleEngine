//
//  RedBlackTree.hpp
//  Container
//
//  Created by HuCoco on 2016/11/19.
//  Copyright © 2016年 HuKe. All rights reserved.
//

#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#define GET_PARENT(n) ((n)->pParent)
#define GET_COLOR(n) ((n)->color)
#define IS_RED(n) ((n)->color == NodeColor::Red)
#define IS_BLACK(n) ((n)->color == NodeColor::Black)
#define SET_RED(n) ((n)->color = NodeColor::Red)
#define SET_BLACK(n) ((n)->color = NodeColor::Black)
#define SET_PARENT(n,p) ((n)->pParent = (p))
#define SET_COLOR(n,c) ((n)->color = (c))

enum class NodeColor {
	Red,
	Black
};

enum class LoopMethod {
	Recursion,
	Iteration
};

template <typename T, typename V>
class MSetNode {
public:
	NodeColor color;
	T Key;
	V Value;
	MSetNode<T, V>* pLeft;
	MSetNode<T, V>* pRight;
	MSetNode<T, V>* pParent;

	MSetNode(T a_Key, V a_Value, NodeColor a_Color)
		: Key(a_Key)
		, Value(a_Value)
		, color(a_Color)
		, pLeft(nullptr)
		, pRight(nullptr)
		, pParent(nullptr)
	{
	};
};


#define MENGINE_SET_ITERATOR_BEGIN( Set )	for(auto SetNode = Set.Begin(); SetNode != Set.End(); ++SetNode)	 					
#define MENGINE_SET_ITERATOR_END( Set ) 
#define MENGINE_SET_FIND( Set, Key)			auto SetNode = Set.Find(Key)
#define MENGINE_SET_GET_KEY					SetNode.Key()
#define MENGINE_SET_GET_VALUE				SetNode.Value()



template <typename T, typename V>
class MSetIterator
{
public:
	MSetIterator(MSetNode<T, V>* a_Node);

	MSetIterator<T, V> operator ++();
	MSetIterator<T, V> operator --();
	bool operator != (const MSetIterator<T, V>& Other);

	T Key() const;
	V Value() const;

private:
	void Increment();
	void Decrement();
private:
	MSetNode<T, V>* m_Node;
};

template <typename T, typename V>
class MSet {
public:
	MSet();
	~MSet();

	bool Insert(const T& key, const V& value);

	const MSetNode<T, V>* Find(T key, LoopMethod m = LoopMethod::Iteration) const;

	void Remove(const T& key);

	void Destory();

	const MSetNode<T, V>* Maximum();
	const MSetNode<T, V>* Minimum();

	MSetIterator<T, V> Begin();
	MSetIterator<T, V> End();
private:

	void Destory(MSetNode<T, V>* &root);

	bool Insert(MSetNode<T, V>* &root, MSetNode<T, V>* node);
	void InsertFixUp(MSetNode<T, V>* &root, MSetNode<T, V>* node);

	void LeftRotate(MSetNode<T, V>* &root, MSetNode<T, V>* x);
	void RightRotate(MSetNode<T, V>* &root, MSetNode<T, V>* y);

	MSetNode<T, V>* FindIteration(MSetNode<T, V>* node, const T& key) const;
	MSetNode<T, V>* FindRecursion(MSetNode<T, V>* node, const T& key) const;

	MSetNode<T, V>* Maximum(MSetNode<T, V>* root);
	MSetNode<T, V>* Minimum(MSetNode<T, V>* root);

	void Remove(MSetNode<T, V>* &root, MSetNode<T, V>* node);
	void RemoveFixUp(MSetNode<T, V>* &root, MSetNode<T, V>* node, MSetNode<T, V>* parent);

private:
	MSetNode<T, V>* pRoot;
};


template <typename T, typename V>
MSet<T, V>::MSet() {
	pRoot = nullptr;
}

template <typename T, typename V>
MSet<T, V>::~MSet() {
	Destory();
}

template <typename T, typename V>
void MSet<T, V>::Destory() {
	Destory(pRoot);
}

template <typename T, typename V>
void MSet<T, V>::Destory(MSetNode<T, V> *&root) {
	if (root == nullptr) {
		return;
	}

	if (root->pLeft != nullptr) {
		Destory(root->pLeft);
	}

	if (root->pRight != nullptr) {
		Destory(root->pRight);
	}

	delete root;
	root = nullptr;
}

/* ----------------------------- LEFT - ROTATE(T, x)----------------------------- */
//  y ← right[x]
//  right[x] ← left[y]
//  p[left[y]] ← x
//  p[y] ← p[x]
//  if p[x] = nil[T]
//  then root[T] ← y
//  else if x = left[p[x]]
//  then left[p[x]] ← y
//  else right[p[x]] ← y
//  left[y] ← x
//  p[x] ← y
/* ----------------------------- LEFT - ROTATE(T, x)----------------------------- */
template <typename T, typename V>
void MSet<T, V>::LeftRotate(MSetNode<T, V> *&root, MSetNode<T, V> *x) {

	MSetNode<T, V> *y = x->pRight;

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


/* ----------------------------- RIGHT - ROTATE(T, y)----------------------------- */
//  x ← left[y]
//  left[y] ← right[x]
//  p[right[x]] ← y
//  p[x] ← p[y]
//  if p[y] = nil[T]
//  then root[T] ← x
//  else if y = right[p[y]]
//  then right[p[y]] ← x
//  else left[p[y]] ← x
//  right[x] ← y
//  p[y] ← x
/* ----------------------------- RIGHT - ROTATE(T, y)----------------------------- */
template <typename T, typename V>
void MSet<T, V>::RightRotate(MSetNode<T, V> *&root, MSetNode<T, V> *y) {

	MSetNode<T, V> *x = y->pLeft;

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

/* ----------------------------- RB - INSERT - FIXUP(T, z)----------------------------- */
//  while color[p[z]] = RED
//  do if p[z] = left[p[p[z]]]
//  then y ← right[p[p[z]]]
//  if color[y] = RED
//  then color[p[z]] ← BLACK                    ▹ Case 1
//  color[y] ← BLACK							▹ Case 1
//  color[p[p[z]]] ← RED						▹ Case 1
//  z ← p[p[z]]									▹ Case 1
//  else if z = right[p[z]]
//  then z ← p[z]								▹ Case 2
//  LEFT - ROTATE(T, z)							▹ Case 2
//  color[p[z]] ← BLACK							▹ Case 3
//  color[p[p[z]]] ← RED						▹ Case 3
//  RIGHT - ROTATE(T, p[p[z]])					▹ Case 3
//  else (same as then clause with "right" and "left" exchanged)
//  color[root[T]] ← BLACK
/* ----------------------------- RB - INSERT - FIXUP(T, z)----------------------------- */
template <typename T, typename V>
void MSet<T, V>::InsertFixUp(MSetNode<T, V> *&root, MSetNode<T, V> *node) {

	MSetNode<T, V>* parent;
	MSetNode<T, V>* gparnet;

	while ((parent = GET_PARENT(node)) && (IS_RED(parent))) {

		gparnet = GET_PARENT(parent);

		if (parent == gparnet->pLeft) {
			MSetNode<T, V>* uncle = gparnet->pRight;
			if (uncle && IS_RED(uncle)) {
				SET_BLACK(uncle);
				SET_BLACK(parent);
				SET_RED(gparnet);
				node = gparnet;
				continue;
			}
			if (parent->pRight == node) {
				MSetNode<T, V>* tmp;
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
			MSetNode<T, V>* uncle = gparnet->pLeft;
			if (uncle && IS_RED(uncle)) {
				SET_BLACK(uncle);
				SET_BLACK(parent);
				SET_RED(gparnet);
				node = gparnet;
				continue;
			}
			if (parent->pLeft == node) {
				MSetNode<T, V>* tmp;
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



template <typename T, typename V>
bool MSet<T, V>::Insert(MSetNode<T, V> *&root, MSetNode<T, V> *node) {

	MSetNode<T, V>* y = nullptr;
	MSetNode<T, V>* x = root;

	while (x != nullptr) {

		if (x->Key == node->Key) {
			return false;
		}

		y = x;
		if (node->Key < x->Key) {
			x = x->pLeft;
		}
		else {
			x = x->pRight;
		}

	}


	node->pParent = y;

	if (y != nullptr) {
		if (node->Key < y->Key) {
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

template <typename T, typename V>
bool MSet<T, V>::Insert(const T& key, const V& value) {

	MSetNode<T, V>* z = new (std::nothrow) MSetNode<T, V>(key, value, NodeColor::Black);
	if (!Insert(pRoot, z)) {
		delete z;
		z = nullptr;
		return false;
	}
	return true;
}


template <typename T, typename V>
MSetNode<T, V>* MSet<T, V>::FindIteration(MSetNode<T, V> *node, const T &key) const {
	while ((node != nullptr) && (node->Key != key)) {
		if (key < node->Key) {
			node = node->pLeft;
		}
		else {
			node = node->pRight;
		}
	}
	return node;
}

template <typename T, typename V>
MSetNode<T, V>* MSet<T, V>::FindRecursion(MSetNode<T, V> *node, const T &key) const {
	if (node == nullptr || node->Key == key) {
		return node;
	}

	if (key < node->Key) {
		return FindRecursion(node->pLeft, key);
	}
	else {
		return FindRecursion(node->pRight, key);
	}
}

template <typename T, typename V>
const MSetNode<T, V>* MSet<T, V>::Find(T key, LoopMethod m) const {
	if (m == LoopMethod::Iteration) {
		return FindIteration(pRoot, key);
	}
	else if (m == LoopMethod::Recursion) {
		return FindRecursion(pRoot, key);
	}
	return nullptr;
}

template <typename T, typename V>
MSetNode<T, V>* MSet<T, V>::Minimum(MSetNode<T, V> *root) {
	if (root == nullptr) {
		return nullptr;
	}

	while (root->pLeft != nullptr) {
		root = root->pLeft;
	}
	return root;
}

template <typename T, typename V>
MSetNode<T, V>* MSet<T, V>::Maximum(MSetNode<T, V> *root) {
	if (root == nullptr) {
		return nullptr;
	}

	while (root->pRight != nullptr) {
		root = root->pRight;
	}
	return root;
}

template <typename T, typename V>
const MSetNode<T, V>* MSet<T, V>::Minimum() {
	return Minimum(pRoot);
}

template <typename T, typename V>
const MSetNode<T, V>* MSet<T, V>::Maximum() {
	return Maximum(pRoot);
}
template <typename T, typename V>
MSetIterator<T, V> MSet<T, V>::Begin()
{
	return MSetIterator<T, V>(Minimum(pRoot));
}

template <typename T, typename V>
MSetIterator<T, V> MSet<T, V>::End()
{
	return MSetIterator<T, V>(nullptr);
}


template <typename T, typename V>
void MSet<T, V>::Remove(MSetNode<T, V> *&root, MSetNode<T, V> *node) {

	MSetNode<T, V>* child;
	MSetNode<T, V>* parent;
	NodeColor color;

	if ((node->pLeft != nullptr) && (node->pRight != nullptr)) {
		MSetNode<T, V>* replace = node;

		replace = replace->pRight;
		while (replace->pLeft != nullptr) {
			replace = replace->pLeft;
		}

		if (GET_PARENT(node)) {
			if (GET_PARENT(node)->pLeft == node) {
				GET_PARENT(node)->pLeft = replace;
			}
			else {
				GET_PARENT(node)->pRight = replace;
			}
		}
		else {
			root = replace;
		}

		child = replace->pRight;
		parent = GET_PARENT(replace);
		color = GET_COLOR(replace);

		if (parent == node) {
			parent = replace;
		}
		else {
			if (child) {
				SET_PARENT(child, parent);
			}
			parent->pLeft = child;

			replace->pRight = node->pRight;
			SET_PARENT(node->pRight, replace);
		}

		replace->pParent = node->pParent;
		replace->color = node->color;
		replace->pLeft = node->pLeft;
		node->pLeft->pParent = replace;

		if (color == NodeColor::Black) {
			RemoveFixUp(root, child, parent);
		}

		delete node;
		node = nullptr;
		return;
	}

	if (node->pLeft != nullptr) {
		child = node->pLeft;
	}
	else {
		child = node->pRight;
	}

	parent = node->pParent;
	color = node->color;

	if (child) {
		child->pParent = parent;
	}

	if (parent) {
		if (parent->pLeft == node) {
			parent->pLeft = child;
		}
		else {
			parent->pRight = child;
		}
	}
	else {
		root = child;
	}

	if (color == NodeColor::Black) {
		RemoveFixUp(root, child, parent);
	}

	delete node;
	node = nullptr;
}
/* ----------------------------- RB - REMOVE - FIXUP(T, z)----------------------------- */
//	while x ≠ root[T] and color[x] = BLACK
//	do if x = left[p[x]]
//	then w ← right[p[x]]
//	if color[w] = RED
//	then color[w] ← BLACK							▹  Case 1
//	color[p[x]] ← RED								▹  Case 1
//	LEFT - ROTATE(T, p[x])							▹  Case 1
//	w ← right[p[x]]									▹  Case 1
//	if color[left[w]] = BLACK and color[right[w]] = BLACK
//	then color[w] ← RED								▹  Case 2
//	x ← p[x]										▹  Case 2
//	else if color[right[w]] = BLACK
//	then color[left[w]] ← BLACK						▹  Case 3
//	color[w] ← RED									▹  Case 3
//	RIGHT - ROTATE(T, w)							▹  Case 3
//	w ← right[p[x]]									▹  Case 3
//	color[w] ← color[p[x]]							▹  Case 4
//	color[p[x]] ← BLACK								▹  Case 4
//	color[right[w]] ← BLACK							▹  Case 4
//	LEFT - ROTATE(T, p[x])							▹  Case 4
//	x ← root[T]										▹  Case 4
//	else (same as then clause with "right" and "left" exchanged)
//	color[x] ← BLACK
/* ----------------------------- RB - REMOVE - FIXUP(T, z)----------------------------- */
template <typename T, typename V>
void MSet<T, V>::RemoveFixUp(MSetNode<T, V> *&root, MSetNode<T, V> *node, MSetNode<T, V> *parent) {

	MSetNode<T, V>* brother;

	while ((!node || IS_BLACK(node)) && node != root) {

		if (parent->pLeft == node) {

			brother = parent->pRight;
			if (IS_RED(brother)) {

				SET_BLACK(brother);
				SET_RED(parent);
				LeftRotate(root, parent);
				brother = parent->pRight;
			}

			if ((!brother->pLeft || IS_BLACK(brother->pLeft)) &&
				(!brother->pRight || IS_BLACK(brother->pRight))) {

				SET_RED(brother);
				node = parent;
				parent = GET_PARENT(node);

			}
			else {

				if (!brother->pRight || IS_BLACK(brother->pRight)) {

					SET_BLACK(brother->pLeft);
					SET_RED(brother);
					RightRotate(root, brother);
					brother = parent->pRight;
				}

				SET_COLOR(brother, GET_COLOR(parent));
				SET_BLACK(parent);
				SET_BLACK(brother->pRight);
				LeftRotate(root, parent);
				node = root;
				break;
			}
		}
		else {

			brother = parent->pLeft;
			if (IS_RED(brother)) {

				SET_BLACK(brother);
				SET_RED(parent);
				RightRotate(root, parent);
				brother = parent->pLeft;
			}
			if ((!brother->pLeft || IS_BLACK(brother->pLeft)) &&
				(!brother->pRight || IS_BLACK(brother->pRight))) {

				SET_RED(brother);
				node = parent;
				parent = GET_PARENT(node);
			}
			else {

				if (!brother->pLeft || IS_BLACK(brother->pLeft)) {

					SET_BLACK(brother->pRight);
					SET_RED(brother);
					LeftRotate(root, brother);
					brother = parent->pLeft;
				}

				SET_COLOR(brother, GET_COLOR(parent));
				SET_BLACK(parent);
				SET_BLACK(brother->pLeft);
				RightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node) {
		SET_BLACK(node);
	}
}

template <typename T, typename V>
void MSet<T, V>::Remove(const T &key) {
	MSetNode<T, V>* node = FindIteration(pRoot, key);

	if (node != nullptr) {
		Remove(pRoot, node);
	}

}


/* ----------------------------- MTreeIterator ----------------------------- */
template <typename T, typename V>
MSetIterator<T, V>::MSetIterator(MSetNode<T, V>* a_Node)
	: m_Node(a_Node)
{

}

template <typename T, typename V>
void MSetIterator<T, V>::Increment()
{
	if (m_Node == nullptr)
	{
		return;
	}
	if (m_Node->pRight != nullptr)
	{
		m_Node = m_Node->pRight;
		while (m_Node->pLeft != nullptr)
		{
			m_Node = m_Node->pLeft;
		}
	}
	else
	{
		MSetNode<T, V>* Parent = m_Node->pParent;
		if (Parent == nullptr)
		{
			m_Node = nullptr;
			return;
		}
		while (m_Node == Parent->pRight)
		{
			m_Node = Parent;
			Parent = Parent->pParent;
			if (Parent == nullptr)
			{
				m_Node = nullptr;
				return;
			}
		}
		if (Parent != nullptr)
		{
			m_Node = Parent;
		}
	}
}

template <typename T, typename V>
void MSetIterator<T, V>::Decrement()
{
	if (m_Node == nullptr)
	{
		return;
	}
	if (m_Node->pLeft != nullptr)
	{
		m_Node = m_Node->pLeft;
		while (m_Node->pRight != nullptr)
		{
			m_Node = m_Node->pRight;
		}
	}
	else
	{
		MSetNode<T, V>* Parent = m_Node->pParent;
		while (m_Node == Parent->pLeft)
		{
			m_Node = Parent;
			Parent = Parent->pParent;
			if (Parent == nullptr)
			{
				m_Node = nullptr;
			}
		}
		if (Parent != nullptr)
		{
			m_Node = Parent;
		}
	}
}
template <typename T, typename V>
MSetIterator<T, V> MSetIterator<T, V>::operator ++()
{
	Increment();
	return *this;
}

template <typename T, typename V>
MSetIterator<T, V> MSetIterator<T, V>::operator --()
{
	Decrement();
	return *this;
}

template <typename T, typename V>
bool MSetIterator<T, V>::operator != (const MSetIterator<T, V>& a_Other)
{
	return !(m_Node == a_Other.m_Node);
}

template <typename T, typename V>
T MSetIterator<T, V>::Key() const
{
	return m_Node->Key;
}

template <typename T, typename V>
V MSetIterator<T, V>::Value() const
{
	return m_Node->Value;
}

#endif