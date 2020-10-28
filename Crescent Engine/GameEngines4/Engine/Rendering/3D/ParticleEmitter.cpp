#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int amountParticles_, std::string textureName_, std::string shaderProgram_) {
	particles.reserve(amountParticles_);
	amountParticles = amountParticles_; 
	textureID = TextureHandler::GetInstance()->GetTexture(textureName_);
	shaderID = ShaderHandler::GetInstance()->GetShader(shaderProgram_);

	CreateParticles(); 
}

ParticleEmitter::~ParticleEmitter() {
	if (particles.size() > 0) {
		for (auto particle : particles) {
			delete particle; 
			particle = nullptr; 
		}
		
		particles.clear(); 
	}
}

float ParticleEmitter::Randomize(float min_, float max_) {
	MATH::Randomizer randomizer; 

	return randomizer.rand(min_, max_); 
}

void ParticleEmitter::CreateParticles() {
	if (textureID == 0) {
		Debugger::Error("Could not create particles, textureID is equal to 0", "ParticleEmitter.cpp", __LINE__);
		return; 
	}

	if (shaderID == 0) {
		Debugger::Error("Could not create particles, shaderID is equal to 0", "ParticleEmitter.cpp", __LINE__);
		return;
	}

	for (int i = 0; i < amountParticles; i++) {
		Particle* newParticle = new Particle(shaderID, textureID);
		newParticle->SetLifeTime(Randomize(1.0f, 1.5f));
		newParticle->SetParticleSize(Randomize(0.5f, 1.0f));
		newParticle->SetPosition(glm::vec3(0.0f)); 
		newParticle->SetVelocity(glm::vec3(Randomize(0.0f, 1.5f), Randomize(0.0f, 2.0f), Randomize(0.0f, 1.0f)));
		particles.push_back(newParticle);
	}
}

void ParticleEmitter::Update(float deltaTime_) {
	for (auto particle : particles)
	{
		particle->SetLifeTime(particle->GetLifeTime() - deltaTime_);
		if (particle->GetLifeTime() <= 0.0f) {
			particle->SetPosition(glm::vec3(0.0f)); //Reset position and randomize other attributes
			particle->SetVelocity(glm::vec3(Randomize(0.0f, 1.5f), Randomize(0.0f, 2.0f), Randomize(0.0f, 1.0f)));
			particle->SetParticleSize(Randomize(0.5f, 1.0f));
			particle->SetLifeTime(Randomize(1.0f, 1.5f));
		}

		particle->SetPosition(particle->GetVelocity() * deltaTime_);
	}
}

void ParticleEmitter::Render(Camera* camera_) {
	glUseProgram(shaderID);
	for (auto particle : particles)
	{
		particle->Render(camera_);
	}
}