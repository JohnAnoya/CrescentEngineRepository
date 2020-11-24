#include "Decision.h"

Decision::Decision() : DecisionTreeNode(){
	
}

Decision::~Decision() {

}

DecisionTreeNode Decision::makeDecision() {
	DecisionTreeNode branch = getBranch();

	return branch.makeDecision();
}