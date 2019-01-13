#pragma once

template <typename T>
class Tree;

template <typename T>
class Node
{
	friend class Tree<T>;
public:
	Node(const T value);
private:
	Node* left = nullptr;
	Node* parent = nullptr;
	Node* right = nullptr;
	T value;
};

template <typename T>
Node<T>::Node(const T value) :
	value(value)
{
}