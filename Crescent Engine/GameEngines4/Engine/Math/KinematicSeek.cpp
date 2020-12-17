#include "KinematicSeek.h"

KinematicSeek::KinematicSeek() {
	result = new KinematicSteeringOutput();
	targetPosition = glm::vec3(-6.0f, -1.0f, 0.0f);
	maxSpeed = 1.0f;
}

KinematicSeek::~KinematicSeek() {
	delete result; 
	result = nullptr; 
}

KinematicSteeringOutput* KinematicSeek::getSteering(GameObject* gameObject_) {
	result->SetVelocity(targetPosition - gameObject_->GetPosition()); //Calculate direction vector 
	result->SetVelocity(glm::normalize(result->GetVelocity())); //Normalize the vector  
	result->SetVelocity(result->GetVelocity() * maxSpeed); //Set it equal to multiply itself with maxSpeed (in our case it's 5) 

	//Apart of the rotation aspect, didn't bother making the separate function 
	if (result->GetVelocity().length() > 0) { //Make sure we have a velocity 
		result->SetRotation(atan2(-result->GetVelocity().x, result->GetVelocity().z));
	}

	else {
		result->SetRotation(0.0f);
	}

	//Debugging test below, allowing me to see where exactly the object is moving within the world 
	std::cout << "Updating GameObject Position:	" << gameObject_->GetPosition().x << ", " << gameObject_->GetPosition().y << ", " << gameObject_->GetPosition().z << std::endl;
	//std::cout << "KinematicSeek Velocity:	" << result->GetVelocity().x << ", " << result->GetVelocity().y << ", " << result->GetVelocity().z << std::endl;
	
	return result; 
}
