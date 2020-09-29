#include "ComponentA.h"

ComponentA::ComponentA() : Component() {

}

ComponentA::~ComponentA() {

}

bool ComponentA::OnCreate(GameObject* parent_) {
	parent = parent_; 
	return true;
}

void ComponentA::Update(float deltaTime_) {
	std::cout << "Updating Component A" << std::endl; 
}