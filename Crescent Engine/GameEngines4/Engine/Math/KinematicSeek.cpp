#include "KinematicSeek.h"

KinematicSeek::KinematicSeek() {
	targetPosition = glm::vec3(1.0f, 1.0f, 1.0f);
	maxSpeed = 10.0f; 
}

KinematicSeek::~KinematicSeek() {

}

KinematicSteeringOutput* KinematicSeek::getSteering(GameObject* gameObject_) {

	std::cout << "getSteering for Object: " << gameObject_->GetTag() << std::endl; 
	KinematicSteeringOutput* result = new KinematicSteeringOutput(); 
	result->velocity = targetPosition - gameObject_->GetPosition(); 
	result->velocity = glm::normalize(result->velocity); 
	result->velocity *= maxSpeed; 

	return result; 
}

glm::vec3 KinematicSeek::newOrientation(glm::vec3 currentVelocity_) {
	
}