#ifndef OPENGLPARTICLE_H 
#define OPENGLPARTICLE_H 

#include "Particle.h"
class OpenGLParticle : public Particle
{
public: 
	OpenGLParticle(GLuint shaderProgram_, GLuint textureID_);
	virtual ~OpenGLParticle();
	void Render(Camera* camera_) override;

private: 
	void GenerateBuffers();
	std::vector<Vertex3D> vertexList;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint colourLocation;
	GLuint textureLocation;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
};
#endif