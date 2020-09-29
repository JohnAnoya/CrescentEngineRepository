#include "ComponentB.h"

ComponentB::ComponentB() : Component() {

}

ComponentB::~ComponentB() {

}

bool ComponentB::OnCreate(GameObject* parent_) {
	parent = parent_;
	return true;
}

void ComponentB::Update(float deltaTime_) {
	std::cout << "Updating Component B" << std::endl;
}
