#pragma once

#include <iostream>

#include "Node.h"

template <typename T>
class Tree
{
public:
	Tree();
	Tree(const Tree& source);
	Tree(Tree&& source);
	~Tree();

	Tree& operator=(const Tree& right);
	Tree& operator=(Tree&& right);

	void Add(const T item);
	void Clear();
	Node<T>* GetRoot() const;
	unsigned int GetSize();
	Node<T>* Maximum(Node<T>* node) const;
	Node<T>* Minimum(Node<T>* node) const;
	Node<T>* Next(Node<T>* node) const;
	Node<T>* Previous(Node<T>* node) const;
	void Print(const Node<T>* const node) const;
	bool Remove(const T item);
	Node<T>* Search(const T item) const;

private:
	Node<T>* root = nullptr;

	void Copy(Node<T>* node);
	void Move(Node<T>* node);
	void Delete(Node<T>* node);
	unsigned int Count(Node<T>* node);
	Node<T>* MySearch(Node<T>* node, const T item) const;
	Node<T>* MyRemove(Node<T>* node);
};

template <typename T>
Tree<T>::Tree()
{
}

template <typename T>
Tree<T>::Tree(const Tree& source)
{
	Copy(source.root);
}

template <typename T>
void Tree<T>::Copy(Node<T>* node)
{
	if (node != nullptr)
	{
		Node<T>* newNode = new Node<T>(node->value);
		newNode->left = Copy(node->left);
		newNode->right = Copy(node->right);
	}
}

template <typename T>
Tree<T>::Tree(Tree&& source)
{
	Move(source.root);
}

template <typename T>
void Tree<T>::Move(Node<T>* node)
{
	if (node != nullptr)
	{
		Node<T>* newNode = new Node<T>(node->value);
		newNode->left = node->left;
		newNode->right = node->right;
		newNode->parent = node->parent;

		node = nullptr;
	}
}

template <typename T>
Tree<T>::~Tree()
{
	if (root != nullptr)
	{
		Clear();
	}
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree& right)
{
	Copy(right.root);

	return *this;
}

template <typename T>
Tree<T>& Tree<T>::operator=(Tree&& right)
{
	Move(right.root);

	return *this;
}

template <typename T>
void Tree<T>::Add(const T item)
{
	Node<T>* newNode = new Node<T>(item);

	if (root == nullptr)
	{
		root = newNode;
	}
	else
	{
		Node<T>* node = root;
		Node<T>* parent = nullptr;

		bool isLeftChild = false;

		while (node != nullptr)
		{
			parent = node;

			if (item < node->value)
			{
				node = node->left;
				isLeftChild = true;
			}
			else
			{
				node = node->right;
				isLeftChild = false;
			}
		}

		newNode->parent = parent;

		if (isLeftChild)
		{
			parent->left = newNode;
		}
		else
		{
			parent->right = newNode;
		}
	}
}

template <typename T>
void Tree<T>::Clear()
{
	Delete(root);
}

template <typename T>
void Tree<T>::Delete(Node<T>* node)
{
	if (node != nullptr)
	{
		Delete(node->left);
		Delete(node->right);
		delete node;
	}
}

template <typename T>
Node<T>* Tree<T>::GetRoot() const
{
	return root;
}

template <typename T>
unsigned int Tree<T>::GetSize()
{
	unsigned int size = Count(root);

	return size;
}

template <typename T>
unsigned int Tree<T>::Count(Node<T>* node)
{
	if (node->left == nullptr && node->right == nullptr)
	{
		return 1;
	}

	unsigned int left, right;

	if (node->left != nullptr)
	{
		left = Count(node->left);
	}
	else
	{
		left = 0;
	}

	if (node->right != nullptr)
	{
		right = Count(node->right);
	}
	else
	{
		right = 0;
	}

	return left + right + 1;
}

template <typename T>
Node<T>* Tree<T>::Maximum(Node<T>* node) const
{
	Node<T>* key = node;

	while (key->right != nullptr)
	{
		key = key->right;
	}

	return key;
}

template <typename T>
Node<T>* Tree<T>::Minimum(Node<T>* node) const
{
	Node<T>* key = node;

	while (key->left != nullptr)
	{
		key = key->left;
	}

	return key;
}

template <typename T>
Node<T>* Tree<T>::Next(Node<T>* node) const
{
	if (node->right != nullptr)
	{
		return Minimum(node->right);
	}

	Node<T>* key = node->parent;

	while (key != nullptr && node == key->right)
	{
		node = key;
		key = key->parent;
	}

	return key;
}

template <typename T>
Node<T>* Tree<T>::Previous(Node<T>* node) const
{
	if (node->left != nullptr)
	{
		return Maximum(node->left);
	}

	Node<T>* key = node->parent;

	while (key != nullptr && node == key->left)
	{
		node = key;
		key = key->parent;
	}

	return key;
}

template <typename T>
void Tree<T>::Print(const Node<T>* const node) const
{
	if (node != nullptr)
	{
		Print(node->left);
		std::cout << node->value << ' ';
		Print(node->right);
	}
}

template <typename T>
bool Tree<T>::Remove(const T item)
{
	bool removed = false;

	Node<T>* node = MyRemove(Search(item));

	if (node != nullptr)
	{
		delete node;
		removed = true;
	}

	return removed;
}

template <typename T>
Node<T>* Tree<T>::MyRemove(Node<T>* node)
{
	Node<T>* key1 = nullptr;
	Node<T>* key2 = nullptr;

	if (node->left == nullptr || node->right == nullptr)
	{
		key1 = node;
	}
	else
	{
		key1 = Previous(node);
	}
	/////////
	if (key1->left != nullptr)
	{
		key2 = key1->left;
	}
	else
	{
		key2 = key1->right;
	}
	////////
	if (key2 != nullptr)
	{
		key2->parent = key1->parent;
	}
	////////
	if (key1->parent == nullptr)
	{
		root = key2;
	}
	else if (key1 == key1->parent->left)
	{
		key1->parent->left = key2;
	}
	else
	{
		key1->parent->right = key2;
	}
	////////
	if (key1 != node)
	{
		node->value = key1->value;
		node->left = key1->left;
		node->parent = key1->parent;
		node->right = key1->right;
	}

	return key1;
}

template <typename T>
Node<T>* Tree<T>::Search(const T item) const
{
	return MySearch(root, item);
}

template <typename T>
Node<T>* Tree<T>::MySearch(Node<T>* node, const T item) const
{
	if (node == nullptr || item == node->value)
	{
		return node;
	}
	else if (item < node->value)
	{
		return MySearch(node->left, item);
	}
	else
	{
		return MySearch(node->right, item);
	}
}