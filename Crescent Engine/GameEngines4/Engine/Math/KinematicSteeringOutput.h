#ifndef KINEMATICSTEERINGOUTPUT_H 
#define KINEMATICSTEERINGOUTPUT_H

#include <glm/glm.hpp>

class KinematicSteeringOutput {
public: 
	KinematicSteeringOutput(); 
	~KinematicSteeringOutput(); 
	glm::vec3 GetVelocity(); 
	void SetVelocity(glm::vec3 velocity_);

private: 
	glm::vec3 velocity; 
};
#endif