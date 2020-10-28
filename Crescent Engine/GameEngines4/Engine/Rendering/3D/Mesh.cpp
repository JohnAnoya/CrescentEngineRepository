#include "Mesh.h"


Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_)
{
	VAO = 0;
	VBO = 0;

	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;

	diffuseMapLocation = 0; 
	shininessLocation = 0; 
	transparencyLocation = 0; 
	ambientLocation = 0;
	diffuseLocation = 0; 
	specularLocation = 0;

	shaderProgram = shaderProgram_;
	subMesh = subMesh_;

	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertextList.size() > 0) {
		subMesh.vertextList.clear(); 
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{	
	glUniform1i(diffuseMapLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform3f(viewPositionLocation, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3f(lightColourLocation, camera_->GetLightSources()[0]->GetLightColour().x, camera_->GetLightSources()[0]->GetLightColour().y, camera_->GetLightSources()[0]->GetLightColour().z);
	glUniform3f(lightPositionLocation, camera_->GetLightSources()[0]->GetPosition().x, camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);

	glUniform1f(diffuseMapLocation, subMesh.material.diffuseMap);
	glUniform1f(shininessLocation, subMesh.material.shininess);
	glUniform1f(transparencyLocation, subMesh.material.transparency);

	glUniform3f(ambientLocation, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLocation, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specularLocation, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	glBindVertexArray(VAO);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertextList.size());
	} 

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertextList.size() * sizeof(Vertex), &subMesh.vertextList[0], GL_STATIC_DRAW);

	// Vertex Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	viewPositionLocation = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLocation = glGetUniformLocation(shaderProgram, "light.lightPosition");
	lightAmbientLocation = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColourLocation = glGetUniformLocation(shaderProgram, "light.lightColour");

	diffuseMapLocation = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLocation = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLocation = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLocation = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLocation = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLocation = glGetUniformLocation(shaderProgram, "material.specular");
}
