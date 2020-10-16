#include "SteeringOutput.h"

SteeringOutput::SteeringOutput() {

}

SteeringOutput::~SteeringOutput() {

}

glm::vec3 SteeringOutput::GetLinear() {
	return linear;
}

float SteeringOutput::GetAngular() {
	return angular; 
}

void SteeringOutput::SetLinear(glm::vec3 linear_) {
	linear = linear_; 
}

void SteeringOutput::SetAngular(float angular_) {
	angular = angular_;
}