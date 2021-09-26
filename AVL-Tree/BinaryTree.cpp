#include "Tree.h"

void Node::setData(double d) { data = d; }

unsigned int Node::getOccurrences() { return occurrences; }

double Node::getData() { return data; }

void Node::addOccurrence() { occurrences += 1; }

Node::Node(double d) {
	data = d;
	leftNode = nullptr;
	rightNode = nullptr;
}

void Tree::preOrderTraversaler(Node* currentNode) {
	GUIpot.push_back(currentNode->getData());
	if (currentNode->leftNode != nullptr) preOrderTraversaler(currentNode->leftNode);
	if (currentNode->rightNode != nullptr) preOrderTraversaler(currentNode->rightNode);
}

void Tree::inOrderTraversaler(Node* currentNode) {
	if (currentNode->leftNode != nullptr) if (currentNode->leftNode->isValid()) inOrderTraversaler(currentNode->leftNode);
	GUIiot.push_back(currentNode->getData());
	if (currentNode->rightNode != nullptr) if (currentNode->rightNode->isValid()) inOrderTraversaler(currentNode->rightNode);
}

void Tree::postOrderTraversaler(Node* currentNode) {
	if (currentNode->leftNode != nullptr) postOrderTraversaler(currentNode->leftNode);
	if (currentNode->rightNode != nullptr) postOrderTraversaler(currentNode->rightNode);
	GUIpoot.push_back(currentNode->getData());
}

void Tree::adder(double d, Node* current) {
	if (root == nullptr) {
		root = new Node(d);
	}
	else {
		if (d == current->getData()) current->addOccurrence();
		else if (d > current->getData()) {
			if (current->rightNode == nullptr) {
				current->rightNode = new Node(d);
				current->rightNode->parent = current;
			}
			else adder(d, current->rightNode);
		}
		else {
			if (current->leftNode == nullptr) {
				current->leftNode = new Node(d);
				current->leftNode->parent = current;
			}
			else adder(d, current->leftNode);
		}
	}
}

void Tree::deleteTree(Node* current) {
	if (current) {
		if (current->rightNode) deleteTree(current->rightNode);
		if (current->leftNode) deleteTree(current->leftNode);
		delete current;
	}
}

Tree::~Tree() {
	deleteTree(root);
}

Node* Tree::finder(double d, Node* current) {
	if (current == nullptr) return nullptr;
	if (d == root->getData()) {
		return root;
	}
	else if (d > current->getData()) {
		if (current->rightNode != nullptr) {
			if (current->rightNode->isValid()) {
				if (current->rightNode->getData() == d) {
					return current->rightNode;
				}
				else {
					return finder(d, current->rightNode);
				}
			}
		}
	}
	else {
		if (current->leftNode != nullptr) {
			if (current->leftNode->isValid()) {
				if (current->leftNode->getData() == d) {
					return current->leftNode;
				}
				else {
					return finder(d, current->leftNode);
				}
			}
		}
	}
	return nullptr;
}

std::vector<double> Tree::preOrderTraversal() {
	GUIpot.clear();
	if (root != nullptr) preOrderTraversaler(root);
	return GUIpot;
}

std::vector<double> Tree::inOrderTraversal() {
	GUIiot.clear();
	if (root != nullptr) inOrderTraversaler(root);
	return GUIiot;
}

std::vector<double> Tree::postOrderTraversal() {
	GUIpoot.clear();
	if (root != nullptr) postOrderTraversaler(root);
	return GUIpoot;
}

void Tree::remove(double d) {
	if (root != nullptr) {
		Node* foundNode = find(d);
		if (foundNode != nullptr) {
			if (foundNode->getOccurrences() > 1) foundNode->removeOccurence();
			else {
				int leafs = 0;
				if (foundNode->leftNode != nullptr) ++leafs;
				if (foundNode->rightNode != nullptr) ++leafs;
				switch (leafs) {
				case 0:
					if (root->getData() != d) {
						if (foundNode->parent->leftNode != nullptr) {
							if (foundNode->parent->leftNode == foundNode) foundNode->parent->leftNode = nullptr;
							else {
								foundNode->parent->rightNode = nullptr;
							}
						}
						else {
							foundNode->parent->rightNode = nullptr;
						}
					}
					else {
						root = nullptr;
					}
					delete foundNode;
					foundNode = nullptr;
					break;
				case 1:
				{
					if (root->getData() == d) {
						if (root->leftNode != nullptr) {
							root = root->leftNode;
							root->parent = nullptr;
						}
						else {
							root = root->rightNode;
							root->parent = nullptr;
						}
					}
					else if (foundNode->leftNode != nullptr) {
						foundNode->leftNode->parent = foundNode->parent;
						if (foundNode->parent->leftNode->getData() == d) foundNode->parent->leftNode = foundNode->leftNode;
						else foundNode->parent->rightNode = foundNode->leftNode;
					}
					else {
						foundNode->rightNode->parent = foundNode->parent;
						if (foundNode->parent->leftNode->getData() == d) foundNode->parent->leftNode = foundNode->rightNode;
						else foundNode->parent->rightNode = foundNode->rightNode;
					}
					delete foundNode;
					foundNode = nullptr;
					break;
				}
				case 2:
					std::vector<double> traversal = inOrderTraversal();
					Node* foundNodeoriginal = foundNode;
					for (unsigned int index = 0; index < traversal.size(); ++index) {
						if (traversal[index] == d) {
							foundNode = find(traversal[index + 1]);
							break;
						}
					}
					for (unsigned int i = 1; i < foundNode->getOccurrences(); ++i) {
						foundNodeoriginal->addOccurrence();
						foundNode->removeOccurence();
					}
					double temp = foundNode->getData();
					remove(foundNode->getData());
					foundNodeoriginal->setData(temp);
					break;
				}
			}
		}
	}
}

void Tree::leftRotate(Node* star) {
	if (star == root) root = star->rightNode;
	Node* temp = star->rightNode->leftNode;
	star->rightNode->leftNode = star;
	if (star->parent->leftNode == star)	star->parent->leftNode = star->rightNode;
	else star->parent->rightNode = star->rightNode;
	star->rightNode->parent = star->parent;
	star->parent = star->rightNode;
	star->rightNode = temp;
	if (star->rightNode != nullptr) star->rightNode->parent = star;
}

void Tree::rightRotate(Node* star) {
	if (star == root) root = star->leftNode;
	Node* temp = star->leftNode->rightNode;
	star->leftNode->rightNode = star;
	if (star->parent->leftNode == star) star->parent->leftNode = star->leftNode;
	else star->parent->rightNode = star->leftNode;
	star->leftNode->parent = star->parent;
	star->parent = star->leftNode;
	star->leftNode = temp;
	if (star->leftNode != nullptr) star->leftNode->parent = star;
}