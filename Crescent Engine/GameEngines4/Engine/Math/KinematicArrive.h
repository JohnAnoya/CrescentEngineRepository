#ifndef KINEMATICARRIVE_H 
#define KINEMATICARRIVE_H 

#include "KinematicSteeringOutput.h"
#include "../../Engine/Rendering/3D/GameObject.h"

class KinematicArrive
{
public: 
	KinematicArrive(); 
	~KinematicArrive();
	glm::vec3 getSteering(GameObject* gameObject_);
private:
	KinematicSteeringOutput* result;

	glm::vec3 targetPosition;
	float maxSpeed;
	float radius; 
	float timeToTarget; 
};
#endif

