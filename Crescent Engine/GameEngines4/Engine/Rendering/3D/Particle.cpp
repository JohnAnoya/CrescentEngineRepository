#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) {
	VAO = 0;
	VBO = 0;

	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;

	colourLocation = 0; 
	textureLocation = 0; 

	shaderProgram = shaderProgram_; 
	textureID = textureID_; 
	
	GenerateBuffers();
}

Particle::~Particle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subParticle.vertextList.size() > 0) {
		subParticle.vertextList.clear();
	}

}


void Particle::SetLifeTime(float lifeTime_){
	lifeTime = lifeTime_;
}

void Particle::SetParticleSize(float particleSize_){
	particleSize = particleSize_;
}

void Particle::SetPosition(glm::vec3 position_){
	position = position_;
}

void Particle::SetVelocity(glm::vec3 velocity_){
	velocity = velocity_;
}

float Particle::GetLifeTime(){
	return lifeTime;
}

float Particle::GetParticleSize(){
	return particleSize;
}

glm::vec3 Particle::GetPosition(){
	return position;
}

glm::vec3 Particle::GetVelocity(){
	return velocity;
}

void Particle::Render(Camera* camera_) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);


	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform3f(colourLocation, colour.x, colour.y, colour.z);
	glUniform1ui(textureLocation, textureID); 

	glBindVertexArray(VAO);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Particle::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subParticle.vertextList.size() * sizeof(Vertex), &subParticle.vertextList[0], GL_STATIC_DRAW);

	// Particle LifeTime 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, lifeTime));

	// Particle Size
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, particleSize));

	// Particle Position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

	// Particle Velocity 
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, velocity));

	// Texture Coords
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	// Particle Colour
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	colourLocation = glGetUniformLocation(shaderProgram, "colour");
}