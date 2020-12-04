#include "IntDecision.h"

IntDecision::IntDecision(std::string path_, std::string fileName_, int test_) : Decision() {
	path = path_;
	fileName = fileName_;
	test = test_;
}

IntDecision::~IntDecision() {

}

int IntDecision::testValue() {
	std::string fullPath = path + fileName;

	XMLDocument* decisionTreeXMLFile = new XMLDocument();
	decisionTreeXMLFile->LoadFile(fullPath.c_str());

	for (XMLElement* it = decisionTreeXMLFile->FirstChildElement("decisionTree")->FirstChildElement(); it != NULL; it = it->NextSiblingElement())
	{
		std::string iteratorElement = it->GetText(); 
		if (test >= std::stoi(iteratorElement)) {
			return 1; 
		}

		else {
			return 0; 
		}
	}
}

DecisionTreeNode IntDecision::getBranch() {
	if (testValue()) {	
		trueNode.IntValue = testValue(); 
		return trueNode;
	}
	
	else {
		falseNode.IntValue = testValue();
		return falseNode;
	}
}
