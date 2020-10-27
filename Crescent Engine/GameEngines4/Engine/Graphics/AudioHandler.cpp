#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::audioInstance = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::fmodSounds = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::fmodChannels = std::map<int, FMOD::Channel*>();

AudioHandler::AudioHandler() {
	ChannelID = -1;
	isPlayingResult = false;
}

AudioHandler::~AudioHandler() {
	OnDestroy(); 
}

AudioHandler* AudioHandler::GetInstance() {
	if (audioInstance.get() == nullptr) {
		audioInstance.reset(new AudioHandler);
	}

	return audioInstance.get();
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 vector_) {
	FMOD_VECTOR FMODVector;

	FMODVector.x = vector_.x;
	FMODVector.y = vector_.y;
	FMODVector.z = vector_.z;

	return FMODVector;
}

bool AudioHandler::InitializeAudio(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forward_, glm::vec3 up_) {
	if (FMOD::System_Create(&system) != FMOD_OK) {
		Debugger::FatalError("Failed to Create the FMOD System!", "AudioHandler.cpp", __LINE__);
		return false;
	}

	int numDrivers = 0;
	system->getNumDrivers(&numDrivers);
	if (numDrivers == 0) {
		Debugger::FatalError("FMOD failed to find a driver!", "AudioHandler.cpp", __LINE__);
		return false;
	}

	if (system->init(2, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr) != FMOD_OK) {
		Debugger::FatalError("Failed to initialize FMOD!", "AudioHandler.cpp", __LINE__);
		return false;
	}

	if (system->set3DListenerAttributes(0, &glmToFMOD(position_), &glmToFMOD(velocity_), &glmToFMOD(forward_), &glmToFMOD(up_)) != FMOD_OK) {
		Debugger::FatalError("Failed to set FMOD 3DListenerAttributes!", "AudioHandler.cpp", __LINE__);
		return false;
	}

	return true;
}

void AudioHandler::LoadSound(std::string soundName_, bool audioLooped_, bool audio3D_, bool streamType_) {
	if (GetSound(soundName_) != nullptr) {
		Debugger::Error("You are trying to load the same sound multiple times!", "AudioHandler.cpp", __LINE__);
		return;
	}

	FMOD_MODE mode;
	mode = FMOD_DEFAULT;

	if (audioLooped_) {
		mode |= FMOD_LOOP_NORMAL;
	}

	else {
		mode |= FMOD_LOOP_OFF;
	}

	if (audio3D_) {
		mode |= FMOD_3D;
	}

	else {
		mode |= FMOD_2D;
	}

	//if Audio file is long, use the stream flag 
	if (streamType_) {
		mode |= FMOD_CREATESTREAM;
	}

	//if the Audio file is short (sound effect), turn on the sample flag instead
	else {
		mode |= FMOD_CREATECOMPRESSEDSAMPLE;
	}

	FMOD::Sound* newSound;
	newSound = nullptr;

	std::string fullPath = "./Resources/Audio/" + soundName_;
	system->createSound(fullPath.c_str(), mode, nullptr, &newSound);

	fmodSounds.insert(std::pair<std::string, FMOD::Sound*>(soundName_, newSound));
}

int AudioHandler::PlaySound(std::string soundName_, glm::vec3 soundPosition_, glm::vec3 soundVelocity_, float volume_) {
	FMOD::Channel* channel;
	channel = nullptr;

	system->playSound(GetSound(soundName_), nullptr, true, &channel); //Play the sound, but pause it to set some attributes 
	channel->set3DAttributes(&glmToFMOD(soundPosition_), &glmToFMOD(soundVelocity_));
	channel->setVolume(volume_);
	channel->setPaused(false); //Once all the attributes are set, unpause the sound 

	ChannelID += 1; //Increment the channel ID variable 
	fmodChannels.insert(std::pair<int, FMOD::Channel*>(ChannelID, channel));

	return ChannelID; 
}

FMOD::Sound* AudioHandler::GetSound(std::string soundName_) {
	if (fmodSounds.find(soundName_) != fmodSounds.end()) {
		return fmodSounds[soundName_];
	}

	else {
		return nullptr;
	}
}

void AudioHandler::UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPosition_, glm::vec3 newVelocity_) {
	if (fmodChannels.find(channelID_) != fmodChannels.end()) {
		fmodChannels[channelID_]->set3DAttributes(&glmToFMOD(newPosition_), &glmToFMOD(newVelocity_));
	}
}

bool AudioHandler::isPlaying(int channelID_) {
	if (fmodChannels.find(channelID_) != fmodChannels.end()) {
		fmodChannels[channelID_]->isPlaying(&isPlayingResult);
		return isPlayingResult;
	}

	return isPlayingResult;
}

void AudioHandler::Update(float deltaTime_) {
	system->update();
}

void AudioHandler::OnDestroy() {
	if (fmodSounds.size() > 0) {
		for (auto sounds : fmodSounds) {
			FMOD_Sound_Release(reinterpret_cast<FMOD_SOUND*>(sounds.second));
			sounds.second = nullptr;
		}
		fmodSounds.clear();
	}

	if (fmodChannels.size() > 0) {
		for (auto channels : fmodChannels) {
			FMOD_Channel_Stop(reinterpret_cast<FMOD_CHANNEL*>(channels.second));
			channels.second = nullptr;
		}
		fmodChannels.clear();
	}

	system->release();
	system = nullptr;
} 