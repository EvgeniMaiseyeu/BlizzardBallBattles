#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "SpriteRendererManager.h"

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

void AudioManager::PlayMusic(std::string filename, int loops, float volumeFactor) {
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *bgm = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(1, bgm, 0);
	Mix_Volume(1, 10 * volumeFactor);
}
void AudioManager::PlaySEFshoot(std::string filename, int loops, float volumeFactor) {
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *SEF = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(2, SEF, 0);
	Mix_Volume(2, 128 * volumeFactor);
}

void AudioManager::PlaySEFhit(std::string filename, int loops, float volumeFactor) {
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *SEF = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(3, SEF, 0);
	Mix_Volume(3, 35 * volumeFactor);
}

void AudioManager::PlayMusicForWin(std::string filename, int loops, float volumeFactor) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *bgm = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(4, bgm, 0);
	Mix_Volume(4, 50 * volumeFactor);
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
