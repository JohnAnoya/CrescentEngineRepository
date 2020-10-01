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
		  /* Kinematic Seek Test */
		parent->SetPosition(parent->GetPosition() + kinematicSeek->getSteering(parent)->GetVelocity() * deltaTime_); 
		parent->SetAngle(kinematicSeek->getSteering(parent)->GetRotation());

		 /* Kinematic Arrive Test */
		//parent->SetPosition(parent->GetPosition() + kinematicArrive->getSteering(parent)->GetVelocity() * deltaTime_); 
		//parent->SetAngle(kinematicArrive->getSteering(parent)->GetRotation());
	}
}
