#include "KinematicSeek.h"

KinematicSeek::KinematicSeek() {
	result = new KinematicSteeringOutput();
	targetPosition = glm::vec3(0.0f, -1.0f, 0.0f);
	maxSpeed = 5.0f;
}

KinematicSeek::~KinematicSeek() {
	delete result; 
	result = nullptr; 
}

glm::vec3 KinematicSeek::getSteering(GameObject* gameObject_) {
	//std::cout << "Updating GameObject Position:	" << gameObject_->GetPosition().x << ", " << gameObject_->GetPosition().y << ", " << gameObject_->GetPosition().z << std::endl;
	result->SetVelocity(targetPosition - gameObject_->GetPosition());
	result->SetVelocity(glm::normalize(result->GetVelocity()));
	result->SetVelocity(result->GetVelocity() * maxSpeed);

	std::cout << "KinematicSeek Velocity:	" << result->GetVelocity().x << ", " << result->GetVelocity().y << ", " << result->GetVelocity().z << std::endl;

	return result->GetVelocity(); 
}
