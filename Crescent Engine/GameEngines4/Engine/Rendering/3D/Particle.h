#ifndef PARTICLE_H 
#define PARTICLE_H 

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
	Particle(GLuint shaderProgram_, GLuint textureID_);
	~Particle();

	void Render(Camera* camera_);

	void SetLifeTime(float lifeTime_); 
	void SetParticleSize(float particleSize_); 
	void SetPosition(glm::vec3 position_); 
	void SetVelocity(glm::vec3 velocity_); 

	float GetLifeTime(); 
	float GetParticleSize(); 
	glm::vec3 GetPosition(); 
	glm::vec3 GetVelocity(); 

private: 
	void GenerateBuffers(); 
	std::vector<Vertex3D> vertexList;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint textureID; 
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint colourLocation; 
	GLuint textureLocation; 

	float lifeTime;
	float particleSize;
	float angle; 

	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 particleColour;
	glm::vec3 rotation; 

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	friend class ParticleEmitter;
};
#endif 

