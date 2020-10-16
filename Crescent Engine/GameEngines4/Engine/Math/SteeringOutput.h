#ifndef STEERINGOUTPUT_H 
#define STEERINGOUTPUT_H 

#include <glm/glm.hpp>

class SteeringOutput
{
public: 
	SteeringOutput();
	~SteeringOutput(); 

	glm::vec3 GetLinear();
	float GetAngular();

	void SetLinear(glm::vec3 linear_);
	void SetAngular(float angular_);
private: 
	glm::vec3 linear; 
	float angular; 
};
#endif 
