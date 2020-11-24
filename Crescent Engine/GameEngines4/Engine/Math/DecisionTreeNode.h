#ifndef DECISIONTREENODE_H 
#define DECISIONTREENODE_H 

class DecisionTreeNode {
public: 
	DecisionTreeNode() {}
	virtual ~DecisionTreeNode() {}
	virtual DecisionTreeNode makeDecision();
};

#endif; 