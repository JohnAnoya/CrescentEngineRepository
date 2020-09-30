#include "AIComponent.h"

AIComponent::AIComponent() : Component()
{

}

AIComponent::~AIComponent()
{

}

bool AIComponent::OnCreate(GameObject* parent_) {
	parent = parent_;
	KinematicSeek::getSteering(parent);
	return true;
}

void AIComponent::Update(float deltaTime_) {
	if (parent != nullptr) {
		std::cout << "Updating GameObject:	" << parent->GetTag() << std::endl; 
		
	}
}
