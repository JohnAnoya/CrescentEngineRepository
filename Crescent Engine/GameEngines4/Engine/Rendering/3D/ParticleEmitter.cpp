#include "ParticleEmitter.h"
#include "../../Core/CoreEngine.h"

ParticleEmitter::ParticleEmitter(int amountParticles_, std::string textureName_, std::string shaderProgram_) {
	rendererType = CoreEngine::GetInstance()->GetRendererType();
	
	particles.reserve(amountParticles_);
	amountParticles = amountParticles_; 

	TextureHandler::GetInstance()->CreateTexture(textureName_, "./Resources/Textures/" + textureName_); 
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
		if (rendererType == RendererType::OPENGL) {
			OpenGLParticle* newParticle = new OpenGLParticle(shaderID, textureID);
			newParticle->lifeTime = (randomizer.rand(0.0f, 2.0f));
			newParticle->particleSize = 0.05f;
			newParticle->position = glm::vec3(0.0f);
			newParticle->velocity = glm::vec3(randomizer.rand(0.0f, 3.0f), randomizer.rand(0.0f, 3.0f), randomizer.rand(0.0f, 3.0f));
			newParticle->particleColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			particles.push_back(newParticle);
		}
	}
}

void ParticleEmitter::Update(float deltaTime_) {
	if (particles.size() > 0) {
		for (auto particle : particles)
		{
			particle->lifeTime = (particle->lifeTime - deltaTime_);
			if (particle->lifeTime <= 0.0f) {
				particle->position = glm::vec3(0.0f); //Reset position and randomize other attributes
				particle->velocity = glm::vec3(randomizer.rand(0.0f, 3.0f), randomizer.rand(0.0f, 3.0f), randomizer.rand(0.0f, 3.0f));
				particle->particleSize = 0.05f;
				particle->lifeTime = randomizer.rand(0.0f, 2.0f);
			}

			particle->position = particle->position + (particle->velocity * deltaTime_);
		}
	}
}

void ParticleEmitter::Render(Camera* camera_) {
	if (particles.size() > 0) {
		if (rendererType == RendererType::OPENGL) {
			glUseProgram(shaderID);
		}

		for (auto particle : particles)
		{
			particle->Render(camera_);
		}
	}
}