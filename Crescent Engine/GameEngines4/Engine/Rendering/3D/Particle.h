#ifndef PARTICLE_H 
#define PARTICLE_H 
#define GLM_SWIZZLE 

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

class ParticleEmitter; 

struct Vertex3D
{
	glm::vec3 position; 
	glm::vec2 texCoords; 
};

class Particle{
public: 
	Particle(){}
	virtual ~Particle() {}
	virtual void Render(Camera* camera_) = 0;

	float lifeTime;
	float particleSize;
	float angle;

	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec4 particleColour;
	glm::vec3 rotation;
};
#endif 

