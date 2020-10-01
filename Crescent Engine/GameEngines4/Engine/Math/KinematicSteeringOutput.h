#ifndef KINEMATICSTEERINGOUTPUT_H 
#define KINEMATICSTEERINGOUTPUT_H

#include <glm/glm.hpp>

class KinematicSteeringOutput {
public: 
	KinematicSteeringOutput(); 
	~KinematicSteeringOutput(); 

	glm::vec3 GetVelocity(); 
	float GetRotation(); 

	void SetVelocity(glm::vec3 velocity_);
	void SetRotation(float rotation_); 
private: 
	glm::vec3 velocity; 
	float rotation; 
};
#endif