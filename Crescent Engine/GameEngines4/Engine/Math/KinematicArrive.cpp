#include "KinematicArrive.h"



KinematicArrive::KinematicArrive() {
  result = new KinematicSteeringOutput();
  targetPosition = glm::vec3(0.0f, -1.0f, 0.0f);
  maxSpeed = 5.0f;
  radius = 3.0f;
  timeToTarget = 0.5f;
}

KinematicArrive::~KinematicArrive() {
	delete result; 
	result = nullptr; 
}

glm::vec3 KinematicArrive::getSteering(GameObject* gameObject_) {
	result->SetVelocity(targetPosition - gameObject_->GetPosition());
	if (result->GetVelocity().length() < radius) {
		return glm::vec3(0.0f); //return null 
	}

	result->SetVelocity(result->GetVelocity() / timeToTarget);
	
	if (result->GetVelocity().length() > maxSpeed) {
		result->SetVelocity(glm::normalize(result->GetVelocity()));
		result->SetVelocity(result->GetVelocity() * maxSpeed);
	}

	std::cout << "Updating GameObject Position:	" << gameObject_->GetPosition().x << ", " << gameObject_->GetPosition().y << ", " << gameObject_->GetPosition().z << std::endl;
	//std::cout << "KinematicArrive Velocity:	" << result.GetVelocity().x << ", " << result.GetVelocity().y << ", " << result.GetVelocity().z << std::endl;
	
	return result->GetVelocity();
}
