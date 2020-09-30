#ifndef KINEMATICSEEK_H
#define KINEMATICSEEK_H

#include "KinematicSteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"

class KinematicSeek
{ 
public: 
	KinematicSeek(); 
	~KinematicSeek(); 
	static KinematicSteeringOutput* getSteering(GameObject* gameObject_);
	glm::vec3 newOrientation(glm::vec3 currentVelocity_); 
private: 
	static glm::vec3 targetPosition;
	static float maxSpeed; 
};
#endif 

