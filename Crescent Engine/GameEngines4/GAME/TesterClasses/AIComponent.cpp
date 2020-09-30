#include "AIComponent.h"

AIComponent::AIComponent() : Component()
{
	
}

AIComponent::~AIComponent()
{
	delete kinematicArrive; 
	kinematicArrive = nullptr; 
}

bool AIComponent::OnCreate(GameObject* parent_) {
	parent = parent_;
	kinematicArrive = new KinematicArrive();
	kinematicSeek = new KinematicSeek(); 

	return true;
}

void AIComponent::Update(float deltaTime_) {
	if (parent != nullptr) {
		//parent->SetPosition(parent->GetPosition() + kinematicSeek->getSteering(parent) * deltaTime_); //Kinematic Seek Test
		parent->SetPosition(parent->GetPosition() + kinematicArrive->getSteering(parent) * deltaTime_); //Kinematic Arrive Test
	}
}
