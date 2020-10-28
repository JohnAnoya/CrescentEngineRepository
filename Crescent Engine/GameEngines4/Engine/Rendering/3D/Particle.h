#ifndef PARTICLE_H 
#define PARTICLE_H 

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
};

struct SubParticle {
	std::vector<Vertex> vertextList;
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
	SubParticle subParticle;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint textureID; 
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint colourLocation; 
	GLuint textureLocation; 

	float lifeTime;
	float particleSize;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec2 texCoords;
	glm::vec3 colour;
};
#endif 

