#include "AVL-Tree.h"

AVLNode::AVLNode(double d) : Node(d){
	if (DEBUG_TRACE) std::cout << "Created new Node: " << d << "\n";
}

signed int AVLNode::getBalfactor() { return balfactor; }

void Node::removeOccurence() { occurrences -= 1; }

void AVLNode::count(signed int curheight, signed int *maxheight) {
	if (DEBUG_TRACE) std::cout << "AVLNode " << getData() << " count(curheight: " << curheight << " maxheight: " << *maxheight << ")\n";
	curheight += 1;
	if (curheight > *maxheight) *maxheight = curheight;
	if (leftNode != nullptr) static_cast<AVLNode*>(leftNode)->count(curheight, maxheight);
	if (rightNode != nullptr) static_cast<AVLNode*>(rightNode)->count(curheight, maxheight);
}

void AVLNode::findBalance() {
	if (DEBUG_TRACE) std::cout << "AVLNode " << getData() << " findBalance()\n";
	signed int mh = 0, *maxheight;
	maxheight = &mh;
	if (leftNode != nullptr) static_cast<AVLNode*>(leftNode)->count(0, maxheight);
	int leftheight = *maxheight;
	mh = 0;
	if (rightNode != nullptr) static_cast<AVLNode*>(rightNode)->count(0, maxheight);
	int rightheight = *maxheight;
	balfactor = rightheight - leftheight;
}

void AVL::findBalance(AVLNode* current) {
	if (DEBUG_TRACE) std::cout << "AVL findBalance(current: " << current->getData() << ")\n";
	current->findBalance();
	if (current->leftNode != nullptr) findBalance(static_cast<AVLNode*>(current->leftNode));
	if (current->rightNode != nullptr) findBalance(static_cast<AVLNode*>(current->rightNode));
	if (current->parent != nullptr) {
		if ((static_cast<AVLNode*>(current->parent)->getBalfactor() > 1) || (static_cast<AVLNode*>(current->parent)->getBalfactor() < -1)) addBalance(current);
		else if (current->parent->parent != nullptr) if ((static_cast<AVLNode*>(current->parent->parent)->getBalfactor() > 1) || (static_cast<AVLNode*>(current->parent->parent)->getBalfactor() < -1)) addBalance(static_cast<AVLNode*>(current->parent));
	}
}

//levelOrderTraversaler

void AVL::adder(double d, Node* current) {
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
				findBalance(static_cast<AVLNode*>(root));
			}
			else adder(d, static_cast<AVLNode*>(current->rightNode));
		}
		else {
			if (current->leftNode == nullptr) {
				current->leftNode = new AVLNode(d);
				current->leftNode->parent = current;
				findBalance(static_cast<AVLNode*>(root));
			}
			else adder(d, static_cast<AVLNode*>(current->leftNode));
		}
	}
}

void AVL::addBalance(AVLNode *star) {
	if (DEBUG_TRACE) std::cout << "addBalance(star: " << star->getData() << " )\n";
	if (static_cast<AVLNode*>(star->parent)->getBalfactor() == 2 && star->getBalfactor() == -1) {
		AVLNode* temp = static_cast<AVLNode*>(star->leftNode->rightNode);
		star->leftNode->rightNode = star;
		star->parent->rightNode = star->leftNode;
		star->leftNode->parent = star->parent;
		star->parent = star->leftNode;
		star->leftNode = temp;
		if (star->leftNode != nullptr) star->leftNode->parent = star;
		findBalance(static_cast<AVLNode*> (root));
	}
	else if (static_cast<AVLNode*>(star->parent)->getBalfactor() == -2 && star->getBalfactor() == 1) {
		AVLNode* temp = static_cast<AVLNode*>(star->rightNode->leftNode);
		star->rightNode->leftNode = star;
		star->parent->leftNode = star->rightNode;
		star->rightNode->parent = star->parent;
		star->parent = star->rightNode;
		star->rightNode = temp;
		if (star->rightNode != nullptr) star->rightNode->parent = star;
		findBalance(static_cast <AVLNode*> (root));
	}
	else if (static_cast<AVLNode*>(star->parent)->getBalfactor() == 2 && star->getBalfactor() >= 1) {
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
		findBalance(static_cast <AVLNode*> (root));
	}
	else if (static_cast<AVLNode*>(star->parent)->getBalfactor() == -2 && star->getBalfactor() <= -1) {
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
		findBalance(static_cast<AVLNode*>(root));
	}
}