#ifndef KINEMATICSTEERINGOUTPUT_H 
#define KINEMATICSTEERINGOUTPUT_H

#include <glm/glm.hpp>

struct KinematicSteeringOutput {
	glm::vec3 velocity; 
	float rotation; 
};
#endif