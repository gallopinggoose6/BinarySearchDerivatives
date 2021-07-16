#include "RedBlack.h"

void RedBlack::adder(double d, Node* current)
{
	if (root == nullptr) {
		root = new RedBlackNode(d);
		static_cast<RedBlackNode*>(root)->reColor();
		return;
	}
	else {
		if (d == current->getData()) current->addOccurrence();
		else if (d > current->getData()) {
			if (static_cast<RedBlackNode*>(current->rightNode)->isNull()) {
				delete current->rightNode;
				current->rightNode = new RedBlackNode(d);
				delete current->rightNode->parent;
				current->rightNode->parent = current;
				current = current->rightNode;
			}
			else adder(d, current->rightNode);
		}
		else {
			if (static_cast<RedBlackNode*>(current->leftNode)->isNull()) {
				delete current->leftNode;
				current->leftNode = new RedBlackNode(d);
				delete current->leftNode->parent;
				current->leftNode->parent = current;
				current = current->leftNode;
			}
			else adder(d, current->leftNode);
		}
	}

	//Balance Adapted from CU's Visualizing Data Structures: Copyright © 2015 by Rhonda Hoenigman
	while ((current != root) and (static_cast<RedBlackNode*> (current->parent)->getColor())) {
		if (current->parent == current->parent->parent->leftNode) {
			RedBlackNode* uncle = static_cast<RedBlackNode*> (current->parent->parent->rightNode);
			if (uncle->getColor()) {
				C1(static_cast<RedBlackNode*> (current), uncle);
				current = current->parent->parent;
			}
			else {
				if (current == current->parent->rightNode) {	//Case 2
					current = current->parent;
					leftRotate(current);
				}
				//Case 3 - x is now left child
				C3Left(static_cast<RedBlackNode*>(current));
			}
		}
		else {
			RedBlackNode* uncle = static_cast<RedBlackNode*> (current->parent->parent->leftNode);
			if (uncle->getColor()) {
				C1(static_cast<RedBlackNode*>(current), uncle);
				current = current->parent->parent;
			}
			else {
				if (current == current->parent->leftNode) {	//Case 2
					current = current->parent;
					rightRotate(current);
				}
				//Case 3 - x is now left child
				C3Right(static_cast<RedBlackNode*>(current));
			}
		}
		static_cast<RedBlackNode*>(root)->setColor(false);
	}
}

void RedBlack::remove(double d)
{
	if (root != nullptr) {
		Node* foundNode = find(d);
		Node* balanceNode;
		if (foundNode != nullptr) {
			if (foundNode->getOccurrences() > 1) foundNode->removeOccurence();
			else {
				int leafs = 0;
				if (foundNode->leftNode != nullptr) {
					if (!static_cast<RedBlackNode*>(foundNode->leftNode)->isNull()) ++leafs;
				}
				if (foundNode->rightNode != nullptr) {
					if (!static_cast<RedBlackNode*>(foundNode->leftNode)->isNull()) ++leafs;
				}
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
					delete foundNode->leftNode;
					delete foundNode->rightNode;
					delete foundNode;
					foundNode = nullptr;
					break;
				case 1:
				{
					if (root->getData() == d) {
						if (!static_cast<RedBlackNode*>(root->leftNode)->isNull()) {
							delete root->rightNode;
							root = root->leftNode;
							root->parent = nullptr;
						}
						else {
							delete root->leftNode;
							root = root->rightNode;
							root->parent = nullptr;
						}
					}
					else if (!static_cast<RedBlackNode*>(foundNode->leftNode)->isNull()) {
						delete foundNode->rightNode;
						foundNode->leftNode->parent = foundNode->parent;
						if (foundNode->parent->leftNode->getData() == d) foundNode->parent->leftNode = foundNode->leftNode;
						else foundNode->parent->rightNode = foundNode->leftNode;
					}
					else {
						delete foundNode->leftNode;
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
							foundNode = find(traversal[index + 1]);	//not the most efficient, but works. Could be improved later
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
			//Rebalance tree

		}
	}
}

void RedBlack::C1(RedBlackNode* star, RedBlackNode* uncle)
{
	static_cast<RedBlackNode*> (star->parent)->reColor();
	uncle->reColor();
	static_cast<RedBlackNode*> (star->parent->parent)->reColor();
}

void RedBlack::C3Left(RedBlackNode* star)
{
	static_cast<RedBlackNode*> (star->parent)->reColor();
	static_cast<RedBlackNode*> (star->parent->parent)->reColor();
	rightRotate(star->parent->parent);
}

void RedBlack::C3Right(RedBlackNode* star)
{
	static_cast<RedBlackNode*> (star->parent)->reColor();
	static_cast<RedBlackNode*> (star->parent->parent)->reColor();
	leftRotate(star->parent->parent);
}
