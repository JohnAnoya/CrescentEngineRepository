#ifndef INTDECISION_H 
#define INTDECISION_H

#include "Decision.h"
#include "../Core/XMLParser/tinyxml2.h"


using namespace tinyxml2;
class IntDecision : public Decision 
{
public: 
	IntDecision(std::string path_, std::string fileName_, int test_);
	virtual ~IntDecision(); 
	DecisionTreeNode getBranch() override;
	int testValue() override;

private: 
	std::string path; 
	std::string fileName;
	int test; 
};

#endif
