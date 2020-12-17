#include "AIComponent.h"

AIComponent::AIComponent(glm::vec3 targetPosition_) : Component()
{
	targetPosition = targetPosition_;
}

AIComponent::~AIComponent()
{
	delete kinematicSeek; 
	kinematicSeek = nullptr; 

	delete kinematicArrive; 
	kinematicArrive = nullptr; 

	delete blendedSteering; 
	blendedSteering = nullptr; 
}

bool AIComponent::OnCreate(GameObject* parent_) {
	parent = parent_;
	kinematicArrive = new KinematicArrive();
	kinematicSeek = new KinematicSeek(); 
	blendedSteering = new BlendedSteering(targetPosition); 

	return true;
}

void AIComponent::Update(float deltaTime_) {
	if (parent != nullptr) {

		/* Kinematic Seek Test */
		//parent->SetPosition(parent->GetPosition() + kinematicSeek->getSteering(parent)->GetVelocity() * deltaTime_); 
		//parent->SetAngle(kinematicSeek->getSteering(parent)->GetRotation());
		 /* Kinematic Arrive Test */
		//parent->SetPosition(parent->GetPosition() + kinematicArrive->getSteering(parent)->GetVelocity() * deltaTime_); 
		//parent->SetAngle(kinematicArrive->getSteering(parent)->GetRotation());

		/*Blended Steering for Flocking*/
		parent->SetPosition(parent->GetPosition() + blendedSteering->getSteering(parent)->GetLinear() * deltaTime_);
	}
}
