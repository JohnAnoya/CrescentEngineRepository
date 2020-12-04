#ifndef DECISION_H 
#define DECISION_H 

#include "DecisionTreeNode.h"
class Decision : public DecisionTreeNode
{
public: 
	Decision(); 
	virtual ~Decision(); 

	DecisionTreeNode makeDecision() override;
	virtual DecisionTreeNode getBranch() = 0;
	virtual int testValue() = 0; 

	DecisionTreeNode trueNode; 
	DecisionTreeNode falseNode; 
};
#endif

