#pragma once

#include "resource.h"
#include "Tree.h"

#define DEBUG_TRACE false
#define TEST true

#ifdef DEBUG_TRACE
#include <iostream>
#endif

class AVLNode : public Node {
private:
	signed int balfactor = 0;
	void count(signed int height, signed int* maxheight);
public:
	//AVLNode* leftNode = nullptr, * rightNode = nullptr, * parent = nullptr;
	AVLNode(double d);
	signed int getBalfactor();
	void findBalance();
};

class AVL : public Tree {
private:
	void findBalance(AVLNode* current);
	void addBalance(AVLNode* star);
	virtual void adder(double d, Node* current) override;
};