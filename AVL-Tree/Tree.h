#pragma once

#include <vector>

class Node {
private:
	unsigned int occurrences = 1;
	double data;
protected:
	bool valid = true;
public:
	Node* leftNode = nullptr, * rightNode = nullptr, * parent = nullptr;
	Node(double d);
	unsigned int getOccurrences();
	double getData();
	void addOccurrence();		//Figure out how to make these private
	void removeOccurence();
	void setData(double d);
	bool isValid() { return valid; }
};

class Tree {
private:
	std::vector<double> GUIpot;
	std::vector<double> GUIiot;
	std::vector<double> GUIpoot;

	void preOrderTraversaler(Node* currentNode);
	void inOrderTraversaler(Node* currentNode);
	void postOrderTraversaler(Node* currentNode);
	//levelOrderTraversaler should go here

	virtual void adder(double d, Node* current);
	Node* finder(double d, Node* current);

	void deleteTree(Node* current);

protected:
	void leftRotate(Node* currentNode);
	void rightRotate(Node* currentNode);

public:
	Node* root = nullptr;
	
	virtual ~Tree();
	void add(double d) {
		adder(d, root);
	};
	Node* find(double d) {
		return finder(d, root);
	}

	//void traverseAndPrint

	std::vector<double> preOrderTraversal();
	std::vector<double> inOrderTraversal();
	std::vector<double> postOrderTraversal();

	//levelOrderTraversal

	virtual void remove(double d);
};