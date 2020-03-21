#pragma once

#include "resource.h"
#include <vector>

#define TEST true
#define DEBUG_TRACE true

#ifdef DEBUG_TRACE
#include <iostream>
#endif

class AVLNode {
private:
	unsigned int occurrences = 1;
	double data;
	void count(signed int height, signed int *maxheight);
	signed int balfactor = 0;
public:
	AVLNode* leftNode = nullptr, *rightNode = nullptr, *parent = nullptr;
	AVLNode(double d);
	unsigned int getOccurrences();
	signed int getBalfactor();
	double getData();
	void addOccurrence();		//Figure out how to make these private
	void removeOccurence();
	void setData(double d);
	void findBalance();
};

class AVL {
private:
	AVLNode** foundNode = nullptr;
	std::vector<double> GUIpot;
	std::vector<double> GUIiot;
	std::vector<double> GUIpoot;

	void findBalance(AVLNode* current);
	void preOrderTraversaler(AVLNode* currentNode);
	void inOrderTraversaler(AVLNode* currentNode);
	void postOrderTraversaler(AVLNode* currentNode);
	void addBalance(AVLNode* star);
	//levelOrderTraversaler

public:
	AVLNode* root = nullptr;
	AVL();
	~AVL();
	void add(double d, AVLNode* current);
	bool find(double d, AVLNode* current);

	//void traverseAndPrint

	std::vector<double> preOrderTraversal();
	std::vector<double> inOrderTraversal();
	std::vector<double> postOrderTraversal();

	void prePrint() {
		std::vector<double> temp = preOrderTraversal();
		std::cout << "Preorder Traversal of current Tree: [";
		for (double d : temp) std::cout << d << " ";
		std::cout << "]\n";
	}
	//levelOrderTraversal

	void remove(double d);
};