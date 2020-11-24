#ifndef FLOATDECISION_H 
#define FLOATDECISION_H

#include "Decision.h"

class FloatDecision : public Decision 
{
public: 
	FloatDecision(); 
	virtual ~FloatDecision(); 

	DecisionTreeNode makeDecision() override;
	DecisionTreeNode getBranch() override;
	float testValue() override;

	float minValue; 
	float maxValue; 
};

#endif
