#ifndef AUDIOHANDLER_H 
#define AUDIOHANDLER_H

#include <string> 
#include <map> 
#include <memory>
#include <fmod.hpp>
#include <glm/glm.hpp>
#include "../Core/Debugger.h"
#include "../../GAME/TesterClasses/AudioSource.h"

class AudioHandler
{
public:
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();
	bool InitializeAudio(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 velocity_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 forward_ = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f));
	void Update(float deltaTime_);
	void OnDestroy();

private:
	AudioHandler();
	~AudioHandler();

	FMOD::System* system;

	FMOD_VECTOR glmToFMOD(glm::vec3 vector_);

	void LoadSound(std::string soundName_, bool audioLooped_, bool audio3D_, bool streamType_);
	int PlaySound(std::string soundName_, glm::vec3 soundPosition_, glm::vec3 soundVelocity_ = glm::vec3(0.0f, 0.0f, 0.0f), float volume_ = 1.0f);
	FMOD::Sound* GetSound(std::string soundName_);

	void UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPosition_, glm::vec3 newVelocity_ = glm::vec3(1.0f, 1.0f, 1.0f));

	bool isPlayingResult;
	bool isPlaying(int channelID_);

	static std::map<std::string, FMOD::Sound*> fmodSounds;
	static std::map<int, FMOD::Channel*> fmodChannels;
	int ChannelID; //Total Channels 

	static std::unique_ptr<AudioHandler> audioInstance;
	friend std::default_delete<AudioHandler>;

	friend class AudioSource;
};
#endif 