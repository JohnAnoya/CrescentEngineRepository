#include "BlendedSteering.h"

BlendedSteering::BlendedSteering(glm::vec3 targetPosition_) {
	result = new SteeringOutput();

	velocityMatch = new VelocityMatching(targetPosition_);
	separation = new SeparationSteering(targetPosition_);
	cohesion = new CohesionSteering(targetPosition_); 

	maxAcceleration = 1.0f; 
	maxRotation = 0.0f; 
	velMatchWeight = 2.0f; 
	separationWeight = 2.0f; 
	cohesionWeight = 2.0f; 
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
	result->SetLinear((velocityMatch->getSteering(gameObject_)->GetLinear() * velMatchWeight) + (separation->getSteering(gameObject_)->GetLinear() * separationWeight) + (cohesion->getSteering(gameObject_)->GetLinear() * cohesionWeight));
	
	//Calculate the total weight between each behaviour and divide the Linear vector by it
	float totalWeight = velMatchWeight + separationWeight + cohesionWeight; 
	result->SetLinear(result->GetLinear() / totalWeight); 

	//Cropping the result 
	result->SetLinear(max(result->GetLinear(), maxAcceleration));

	return result; 
}