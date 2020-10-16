#include "BlendedSteering.h"

BlendedSteering::BlendedSteering(glm::vec3 targetPosition_) {
	result = new SteeringOutput();

	velocityMatch = new VelocityMatching(targetPosition_);
	separation = new SeparationSteering(targetPosition_);
	cohesion = new CohesionSteering(targetPosition_); 

	maxAcceleration = 10.0f; 
	maxRotation = 0.0f; 
	weight = 2.0f; 
}

BlendedSteering::~BlendedSteering() {
	delete result; 
	result = nullptr; 

	delete velocityMatch; 
	velocityMatch = nullptr; 

	delete separation; 
	separation = nullptr; 

	delete cohesion; 
	cohesion = nullptr; 
}

SteeringOutput* BlendedSteering::getSteering(GameObject* gameObject_) {
	result->SetLinear((velocityMatch->getSteering(gameObject_)->GetLinear() * weight) + (separation->getSteering(gameObject_)->GetLinear() * weight) + (cohesion->getSteering(gameObject_)->GetLinear() * weight));
	result->SetLinear(result->GetLinear() / weight); 

	return result; 
}