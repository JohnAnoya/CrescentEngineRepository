#include "KinematicSteeringOutput.h"

KinematicSteeringOutput::KinematicSteeringOutput() {

}

KinematicSteeringOutput::~KinematicSteeringOutput() {

}

glm::vec3 KinematicSteeringOutput::GetVelocity() {
	return velocity; 
}

void KinematicSteeringOutput::SetVelocity(glm::vec3 velocity_) {
	velocity = velocity_; 
}