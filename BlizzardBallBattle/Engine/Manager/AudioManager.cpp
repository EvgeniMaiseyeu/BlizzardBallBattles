#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

AudioManager* AudioManager::instance;

AudioManager* AudioManager::GetInstance()
{
	if (instance == NULL)
		instance = new AudioManager();
	return instance;
}

void AudioManager::Release() {
	delete instance;
	instance = NULL;
}

AudioManager::AudioManager() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;

}

AudioManager::~AudioManager() {
	//mGameObj = NULL;
	Mix_Quit();

}

void AudioManager::PlayMusic(std::string filename, int loops) {
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	
	
}

void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::StopMusic() {
	Mix_CloseAudio();
}


