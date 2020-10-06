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

KinematicSteeringOutput* KinematicArrive::getSteering(GameObject* gameObject_) {
	result->SetVelocity(targetPosition - gameObject_->GetPosition()); //direction to target 
	if (result->GetVelocity().length() < radius) {
		return NULL; //return null 
	}

	result->SetVelocity(result->GetVelocity() / timeToTarget);
	
	if (result->GetVelocity().length() > maxSpeed) {
		result->SetVelocity(glm::normalize(result->GetVelocity()));
		result->SetVelocity(result->GetVelocity() * maxSpeed);
	}

	//Apart of the rotation aspect, didn't bother making the separate function  
	if (result->GetVelocity().length() > 0) { //Make sure we have a velocity 
		result->SetRotation(atan2(-result->GetVelocity().x, result->GetVelocity().z));
	}

	else {  
		result->SetRotation(0.0f);
	}

	//Debugging test below, allowing me to see where exactly the object is moving within the world 
	//std::cout << "Updating GameObject Position:	" << gameObject_->GetPosition().x << ", " << gameObject_->GetPosition().y << ", " << gameObject_->GetPosition().z << std::endl;
	//std::cout << "KinematicArrive Velocity:	" << result.GetVelocity().x << ", " << result.GetVelocity().y << ", " << result.GetVelocity().z << std::endl;
	
	return result;
}
