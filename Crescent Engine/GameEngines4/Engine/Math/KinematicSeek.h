#ifndef KINEMATICSEEK_H
#define KINEMATICSEEK_H

#include "KinematicSteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"

class KinematicSeek
{ 
public: 
	KinematicSeek(); 
	~KinematicSeek(); 
	KinematicSteeringOutput* getSteering(GameObject* gameObject_);
private: 
	KinematicSteeringOutput* result;

	glm::vec3 targetPosition;
	float maxSpeed; 
};
#endif 

