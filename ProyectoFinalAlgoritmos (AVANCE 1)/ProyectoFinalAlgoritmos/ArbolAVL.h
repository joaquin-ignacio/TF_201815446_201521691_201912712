#pragma once
#ifndef __ARBOLAVL_HPP__
#define __ARBOLAVL_HPP__
#include <iostream>
#include <functional>
#define max(a, b) (a > b? a : b)
using namespace std;

template<typename T, typename R>
class arbolAVL
{
	struct Node
	{
		T element;
		Node* left;
		Node* right;
		int height;

		Node(T element) :element(element), left(nullptr), right(nullptr), height(0) {}
	};
	T NONE = 0;
	Node* root;
	function<R(T)>key;
	int len;
public:
	arbolAVL(function<R(T)>key = [](T a) {return a; }) :key(key), root(nullptr), len(0) {}
	~arbolAVL() { clear(root); }
	void clear() { clear(root); len = 0; }
	void add(T elem) { add(root, elem); }
	int height() { return height(root); }
	int size() { return len; }
	void inOrder(function<void(T)>proc) { inOrder(root, proc); }
	T find(R val) { return find(root, val); }
private:
	void clear(Node*& node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}
	int height(Node* node)
	{
		return node == nullptr ? -1 : node->height;
	}
	void add(Node*& node, T elem)
	{
		if (node == nullptr)
		{
			node = new Node(elem);
			++len;
		}
		else
		{
			if (key(elem) < key(node->element))
			{
				add(node->left, elem);
			}
			else
			{
				add(node->right, elem);
			}
			balance(node);
		}
	}
	T find(Node* node, R val) {
		if (node == nullptr)
		{
			return NONE;
		}
		else if (val == key(node->element))
		{
			return node->element;
		}
		else if (val < key(node->element))
		{
			return find(node->left, val);
		}
		else
		{
			return find(node->right, val);
		}
	}
	void inOrder(Node* node, function<void(T)>proc)
	{
		if (node != nullptr)
		{
			inOrder(node->left, proc);
			proc(node->element);
			inOrder(node->right, proc);
		}
	}
	void updateHeight(Node* node)
	{
		if (node != nullptr)
		{
			int hl = height(node->left);
			int hr = height(node->right);

			node->height = max(hl, hr) + 1;
		}
	}
	void rotateLeft(Node*& node)
	{
		Node* aux = node->right;
		node->right = aux->left;
		updateHeight(node);
		aux->left = node;
		updateHeight(aux);
		node = aux;
	}
	void rotateRight(Node*& node)
	{
		Node* aux = node->left;
		node->left = aux->right;
		updateHeight(node);
		aux->right = node;
		updateHeight(aux);
		node = aux;
	}
	void balance(Node*& node)
	{
		int hl = height(node->left);
		int hr = height(node->right);
		if (hr - hl < -1)
		{
			hl = height(node->left->left);
			hr = height(node->left->right);
			if (hr > hl)
			{
				rotateLeft(node->left);
			}
			rotateRight(node);
		}
		else if (hr - hl > 1)
		{
			hl = height(node->right->left);
			hr = height(node->right->right);
			if (hl > hr)
			{
				rotateRight(node->right);
			}
			rotateLeft(node);
		}
		else
		{
			updateHeight(node);
		}
	}
};

#endif
