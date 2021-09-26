#pragma once
#include "Tree.h"

class RedBlackNode : public Node {
private:
	bool color = true;	//black = false, red = true
public:
	RedBlackNode(double d, bool n) : Node(d) {
		if (n) {
			valid = false;
			color = false;
		}
		else {
			leftNode = new RedBlackNode(0, true);
			rightNode = new RedBlackNode(0, true);
			parent = new RedBlackNode(0, true);
		}
	};
	RedBlackNode(double d) : Node(d) {
		leftNode = new RedBlackNode(0, true);
		rightNode = new RedBlackNode(0, true);
		parent = new RedBlackNode(0, true);
	}
	bool isNull() { return !valid; }
	void setColor(bool c) { color = c; }
	void reColor() { color = !color; }
	bool getColor() { return color; }
};

class RedBlack : public Tree
{
public:
	virtual void remove(double d) override {
		remover(d, true);
	}
private:
	void remover(double d, bool balance = true);
	virtual void adder(double d, Node* current) override;
	void C1(RedBlackNode* star, RedBlackNode* uncle);
	void C3Left(RedBlackNode* star);
	void C3Right(RedBlackNode* star);
	void rebalance(Node* star);
};