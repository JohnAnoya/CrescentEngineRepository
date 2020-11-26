#include "FloatDecision.h"

FloatDecision::FloatDecision() : Decision() {

}

FloatDecision::~FloatDecision() {

}

float FloatDecision::testValue() {

}

DecisionTreeNode FloatDecision::getBranch() {
	if (maxValue >= testValue() && testValue() >= minValue) {	
		
		return trueNode;
	}
	
	else {
		
		return falseNode;
	}
}