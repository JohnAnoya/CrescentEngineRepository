#ifndef SEPARATIONSTEERING_H 
#define SEPARATIONSTEERING_H

#include <map>
#include "SteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"
class SeparationSteering
{
public: 
	SeparationSteering(glm::vec3 targetPosition_);
	~SeparationSteering();
	SteeringOutput* getSteering(GameObject* gameObject_);
private:
	SteeringOutput* result;
	glm::vec3 targetPosition;
	float maxAcceleration;
	float Threshold;

	std::map<std::string, GameObject*> sceneGameObjects;
	std::map<std::string, GameObject*>::iterator it;
};
#endif 

