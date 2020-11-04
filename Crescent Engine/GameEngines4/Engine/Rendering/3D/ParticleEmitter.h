#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <string>
#include "OpenGLParticle.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Graphics/ShaderHandler.h"
#include "../../Math/Randomizer.h"
#include "../../Core/Renderers/Renderer.h"

using namespace MATH;

class ParticleEmitter{
public: 
	ParticleEmitter(int amountParticles_, std::string textureName_, std::string shaderProgram_); 
	~ParticleEmitter(); 

	void CreateParticles();
	void Update(float deltaTime_); 
	void Render(Camera* camera_); 
private: 
	float Randomize(float min_, float max_);

	int amountParticles; 
	GLuint shaderID;
	GLuint textureID;

	std::vector<Particle*> particles; 

	RendererType rendererType;
};
#endif 

