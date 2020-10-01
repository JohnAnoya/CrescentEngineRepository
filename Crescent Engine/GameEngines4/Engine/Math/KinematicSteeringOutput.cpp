#include "KinematicSteeringOutput.h"

KinematicSteeringOutput::KinematicSteeringOutput() {

}

KinematicSteeringOutput::~KinematicSteeringOutput() {

}

glm::vec3 KinematicSteeringOutput::GetVelocity() {
	return velocity; 
}

float KinematicSteeringOutput::GetRotation() {
	return rotation;
}

void KinematicSteeringOutput::SetVelocity(glm::vec3 velocity_) {
	velocity = velocity_; 
}

void KinematicSteeringOutput::SetRotation(float rotation_) {
	rotation = rotation_; 
}