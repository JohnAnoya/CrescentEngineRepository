#ifndef BLENDEDSTEERING_H 
#define BLENDEDSTEERING_H 

#include "SteeringOutput.h"
#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "VelocityMatching.h"
#include "../../Engine/Rendering/3D/GameObject.h"
#include <algorithm>
class BlendedSteering
{
public: 
	BlendedSteering(glm::vec3 targetPosition_);
	~BlendedSteering(); 

	SteeringOutput* getSteering(GameObject* gameObject_);
private:
	SteeringOutput* result;

	float maxAcceleration;
	float maxRotation; 
	float velMatchWeight; 
	float separationWeight;
	float cohesionWeight; 

	VelocityMatching* velocityMatch; 
	SeparationSteering* separation;
	CohesionSteering* cohesion; 
};
#endif 

