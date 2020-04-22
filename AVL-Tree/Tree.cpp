#include "AVL-Tree.h"

AVLNode::AVLNode(double d) {
	if (DEBUG_TRACE) std::cout << "Created new Node: " << d << "\n";
	data = d;
	leftNode = nullptr;
	rightNode = nullptr;
}
double AVLNode::getData() {return data;}

unsigned int AVLNode::getOccurrences() { return occurrences; }

signed int AVLNode::getBalfactor() { return balfactor; }

void AVLNode::setData(double d) { data = d; }

void AVLNode::addOccurrence() { occurrences += 1; }

void AVLNode::removeOccurence() { occurrences -= 1; }

void AVLNode::count(signed int curheight, signed int *maxheight) {
	if (DEBUG_TRACE) std::cout << "AVLNode " << getData() << " count(curheight: " << curheight << " maxheight: " << *maxheight << ")\n";
	curheight += 1;
	if (curheight > *maxheight) *maxheight = curheight;
	if (leftNode != nullptr) leftNode->count(curheight, maxheight);
	if (rightNode != nullptr) rightNode->count(curheight, maxheight);
}

void AVLNode::findBalance() {
	if (DEBUG_TRACE) std::cout << "AVLNode " << getData() << " findBalance()\n";
	signed int mh = 0, *maxheight;
	maxheight = &mh;
	if (leftNode != nullptr) leftNode->count(0, maxheight);
	int leftheight = *maxheight;
	mh = 0;
	if (rightNode != nullptr) rightNode->count(0, maxheight);
	int rightheight = *maxheight;
	balfactor = rightheight - leftheight;
}

void AVL::findBalance(AVLNode* current) {
	if (DEBUG_TRACE) std::cout << "AVL findBalance(current: " << current->getData() << ")\n";
	current->findBalance();
	if (current->leftNode != nullptr) findBalance(current->leftNode);
	if (current->rightNode != nullptr) findBalance(current->rightNode);
	if (current->parent != nullptr) {
		if ((current->parent->getBalfactor() > 1) || (current->parent->getBalfactor() < -1)) addBalance(current);
		else if (current->parent->parent != nullptr) if ((current->parent->parent->getBalfactor() > 1) || (current->parent->parent->getBalfactor() < -1)) addBalance(current->parent);
	}
}

void AVL::preOrderTraversaler(AVLNode* currentNode) {
	GUIpot.push_back(currentNode->getData());
	if (currentNode->leftNode != nullptr) preOrderTraversaler(currentNode->leftNode);
	if (currentNode->rightNode != nullptr) preOrderTraversaler(currentNode->rightNode);
}

void AVL::inOrderTraversaler(AVLNode* currentNode) {
	if (currentNode->leftNode != nullptr) inOrderTraversaler(currentNode->leftNode);
	GUIiot.push_back(currentNode->getData());
	if (currentNode->rightNode != nullptr) inOrderTraversaler(currentNode->rightNode);
}

void AVL::postOrderTraversaler(AVLNode* currentNode) {
	if (currentNode->leftNode != nullptr) postOrderTraversaler(currentNode->leftNode);
	if (currentNode->rightNode != nullptr) postOrderTraversaler(currentNode->rightNode);
	GUIpoot.push_back(currentNode->getData());
}

//levelOrderTraversaler

AVL::AVL() {/*maybe add something later*/}

AVL::~AVL() {
	while (root != nullptr) remove(root->getData());	//very inefficient
}

void AVL::add(double d, AVLNode* current) {
	if (root == nullptr) {
		root = new AVLNode(d);
		if (DEBUG_TRACE) std::cout << "add(d: " << d << " current: nullptr)\n";
	}
	else {
		if (DEBUG_TRACE) std::cout << "add(d: " << d << " current: " << current->getData() << ")\n";
		if (d == current->getData()) current->addOccurrence();
		else if (d > current->getData()) {
			if (current->rightNode == nullptr) {
				current->rightNode = new AVLNode(d);
				current->rightNode->parent = current;
				findBalance(root);
			}
			else add(d, current -> rightNode);
		}
		else {
			if (current->leftNode == nullptr) {
				current->leftNode = new AVLNode(d);
				current->leftNode->parent = current;
				findBalance(root);
			}
			else add(d, current->leftNode);
		}
	}
	if (DEBUG_TRACE) prePrint();
}
void AVL::addBalance(AVLNode *star) {
	if (DEBUG_TRACE) std::cout << "addBalance(star: " << star->getData() << " )\n";
	if (star->parent->getBalfactor() == 2 && star->getBalfactor() == -1) {
		AVLNode* temp = star->leftNode->rightNode;
		star->leftNode->rightNode = star;
		star->parent->rightNode = star->leftNode;
		star->leftNode->parent = star->parent;
		star->parent = star->leftNode;
		star->leftNode = temp;
		if (star->leftNode != nullptr) star->leftNode->parent = star;
		findBalance(root);
	}
	else if (star->parent->getBalfactor() == -2 && star->getBalfactor() == 1) {
		AVLNode* temp = star->rightNode->leftNode;
		star->rightNode->leftNode = star;
		star->parent->leftNode = star->rightNode;
		star->rightNode->parent = star->parent;
		star->parent = star->rightNode;
		star->rightNode = temp;
		if (star->rightNode != nullptr) star->rightNode->parent = star;
		findBalance(root);
	}
	else if (star->parent->getBalfactor() == 2 && star->getBalfactor() >= 1) {
		signed int left = 0;
		if (star->parent->parent != nullptr) {
			left = -1;
			if (star->parent->parent->rightNode == star->parent) left = 1;
		}
		star->parent->rightNode = star->leftNode;
		if (star->leftNode != nullptr) star->leftNode->parent = star->parent;
		star->leftNode = star->parent;
		star->parent = star->parent->parent;
		star->leftNode->parent = star;
		switch (left) {
		case -1:
			star->parent->leftNode = star;
			break;
		case 0:
			root = star;
			break;
		case 1:
			star->parent->rightNode = star;
			break;
		}
		findBalance(root);
	}
	else if (star->parent->getBalfactor() == -2 && star->getBalfactor() <= -1) {
		signed int left = 0;
		if (star->parent->parent != nullptr) {
			left = -1;
			if (star->parent->parent->rightNode == star->parent) left = 1;
		}
		star->parent->leftNode = star->rightNode;
		if (star->rightNode != nullptr) star->rightNode->parent = star->parent;
		star->rightNode = star->parent;
		star->parent = star->parent->parent;
		star->rightNode->parent = star;
		switch (left) {
		case -1:
			star->parent->leftNode = star;
			break;
		case 0:
			root = star;
			break;
		case 1:
			star->parent->rightNode = star;
			break;
		}
		findBalance(root);
	}
}

AVLNode* AVL::find(double d, AVLNode* current) {
	if (current == nullptr) {
		if (DEBUG_TRACE) std::cout << "find(d: " << d << " current: nullptr)\n";
		return nullptr;
	}
	if (DEBUG_TRACE) std::cout << "find(d: " << d << " current: " << current->getData() << ")\n";
	if (d == root->getData()) {
		return root;
	}
	else if (d > current->getData()) {
		if (current->rightNode != nullptr) {
			if (current->rightNode->getData() == d) {
				return current->rightNode;
			}
			else {
				return find(d, current->rightNode);
			}
		}
		else return nullptr;
	}
	else {
		if (current->leftNode != nullptr) {
			if (current->leftNode->getData() == d) {
				return current->leftNode;
			}
			else {
				return find(d, current->leftNode);
			}
		}
		else return nullptr;
	}
}

std::vector<double> AVL::preOrderTraversal() {
	GUIpot.clear();
	if(root != nullptr) preOrderTraversaler(root);
	return GUIpot;
}

std::vector<double> AVL::inOrderTraversal() {
	GUIiot.clear();
	if(root != nullptr) inOrderTraversaler(root);
	return GUIiot;
}
	std::vector<double> AVL::postOrderTraversal() {
	GUIpoot.clear();
	if (root != nullptr) postOrderTraversaler(root);
	return GUIpoot;
}
//levelOrderTraversal
//balance

void AVL::remove(double d) {
	if (DEBUG_TRACE) std::cout << "remove(d: " << d << ")\n";
	if (root != nullptr) {
		AVLNode* foundNode = find(d, root);
		if (foundNode != nullptr) {
			if (DEBUG_TRACE & (root->getData() != d)) std::cout << "foundNode: " << foundNode->getData() << "\n";
			if (foundNode->getOccurrences() > 1) foundNode->removeOccurence();
			else {
				int leafs = 0;
				if (foundNode->leftNode != nullptr) ++leafs;
				if (foundNode->rightNode != nullptr) ++leafs;
				if (DEBUG_TRACE) std::cout << "#leafs: " << leafs << "\n";
				switch (leafs) {
				case 0:
					if (root->getData() != d) {
						if (foundNode->parent->leftNode != nullptr) {
							if (foundNode->parent->leftNode == foundNode) foundNode->parent->leftNode = nullptr;
							else {
								std::cout << "TEST1: " << foundNode->parent->getData() << "\n";
								std::cout << "TEST2: " << foundNode->parent->rightNode->getData() << "\n";
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
					AVLNode* foundNodeoriginal = foundNode;
					for (unsigned int index = 0; index < traversal.size(); ++index) {
						if (traversal[index] == d) {
							foundNode = find(traversal[index + 1], root);
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
				if (root != nullptr) findBalance(root);
			}
		}
	}
	if (DEBUG_TRACE) prePrint();
}