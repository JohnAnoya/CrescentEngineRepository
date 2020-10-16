#ifndef VELOCITYMATCHING_H 
#define VELOCITYMATCHING_H

#include <map>
#include "SteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"
class VelocityMatching
{
public : 
	VelocityMatching(glm::vec3 targetPosition_);
	~VelocityMatching(); 
	SteeringOutput* getSteering(GameObject* gameObject_); 
private: 
	SteeringOutput* result; 

	glm::vec3 targetPosition;
	float maxAcceleration; 
	float timeToTarget; 

	std::map<std::string, GameObject*> sceneGameObjects;
	std::map<std::string, GameObject*>::iterator it;
};
#endif 
