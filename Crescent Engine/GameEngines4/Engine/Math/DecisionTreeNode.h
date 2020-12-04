#ifndef DECISIONTREENODE_H 
#define DECISIONTREENODE_H 

#include <iostream>
#include <string> 
class DecisionTreeNode {
public: 
	DecisionTreeNode() { }
	virtual ~DecisionTreeNode() {}
	virtual DecisionTreeNode makeDecision() { return *this; }
	int IntValue; 
};

#endif; 