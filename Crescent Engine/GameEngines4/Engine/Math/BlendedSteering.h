#ifndef BLENDEDSTEERING_H 
#define BLENDEDSTEERING_H 

#include "SteeringOutput.h"
#include "SeparationSteering.h"
#include "CohesionSteering.h"
#include "VelocityMatching.h"
#include "../../Engine/Rendering/3D/GameObject.h"
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
	float weight; 

	VelocityMatching* velocityMatch; 
	SeparationSteering* separation;
	CohesionSteering* cohesion; 
};
#endif 

