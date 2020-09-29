#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex 
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh {
	std::vector<Vertex> vertextList;
	std::vector<int> meshIndices; 
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4> instances_);
	
private:
	void GenerateBuffers();
	SubMesh subMesh;
	
	GLuint VAO, VBO;	
	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint diffuseMapLocation, shininessLocation, transparencyLocation, ambientLocation, diffuseLocation, specularLocation; 

	GLuint viewPositionLocation, lightPositionLocation, lightAmbientLocation, lightDiffuseLocation, lightColourLocation; 

};
#endif

