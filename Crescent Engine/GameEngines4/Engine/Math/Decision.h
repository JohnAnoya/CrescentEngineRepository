#ifndef DECISION_H 
#define DECISION_H 

#include "DecisionTreeNode.h"
class Decision : public DecisionTreeNode
{
public: 
	Decision(); 
	virtual ~Decision(); 

	DecisionTreeNode makeDecision() override;
	virtual DecisionTreeNode getBranch();
	virtual float testValue(); 

	DecisionTreeNode trueNode; 
	DecisionTreeNode falseNode; 
};
#endif

