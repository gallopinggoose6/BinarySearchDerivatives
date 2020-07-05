#pragma once

#include <vector>

class Node {
private:
	unsigned int occurrences = 1;
	double data;
public:
	Node* leftNode = nullptr, * rightNode = nullptr, * parent = nullptr;
	Node(double d);
	unsigned int getOccurrences();
	double getData();
	void addOccurrence();		//Figure out how to make these private
	void removeOccurence();
	void setData(double d);
};

class Tree {
private:
	std::vector<double> GUIpot;
	std::vector<double> GUIiot;
	std::vector<double> GUIpoot;

	//void findBalance(AVLNode* current);
	void preOrderTraversaler(Node* currentNode);
	void inOrderTraversaler(Node* currentNode);
	void postOrderTraversaler(Node* currentNode);
	//levelOrderTraversaler
	virtual void adder(double d, Node* current);

public:
	Node* root = nullptr;
	
	virtual ~Tree();
	void add(double d) {
		adder(d, root);
	};
	Node* find(double d, Node* current);

	//void traverseAndPrint

	std::vector<double> preOrderTraversal();
	std::vector<double> inOrderTraversal();
	std::vector<double> postOrderTraversal();

	//levelOrderTraversal

	void remove(double d);
};