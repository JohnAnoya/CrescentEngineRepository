#ifndef COHESIONSTEERING_H
#define COHESIONSTEERING_H 

#include <map>
#include "SteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"
class CohesionSteering
{
public:
	CohesionSteering(glm::vec3 targetPosition_);
	~CohesionSteering();
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

