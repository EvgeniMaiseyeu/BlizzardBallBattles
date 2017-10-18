#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

//using namespace AudioManager;

AudioManager* AudioManager::sInstance = NULL;

AudioManager* AudioManager::Instance() {
	if (sInstance == NULL)
		sInstance = new AudioManager();
	return sInstance;
}

void AudioManager::Release() {
	delete sInstance;
	sInstance = NULL;
}

AudioManager::AudioManager() {
	mGameObj = GameObject::Instance();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;

}

AudioManager::~AudioManager() {
	mGameObj = NULL;
	Mix_Quit();

}

void AudioManager::PlayMusic(std::string filename, int loops) {
	//Mix_PlayMusic(mGameObj->bgm(filename), loops);
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);
}

void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::StopMusic(){
	Mix_CloseAudio();
}

void AudioManager::PlaySoundEffect(std::string filename, int loops, int channel) {
	//Mix_PlayChannel(channel, mGameObj->GetSoundEffect(filename), loops);
	

}
