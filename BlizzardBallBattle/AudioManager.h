#pragma once

#include"GameManager.h"
#include "GameObject.h"
#include <string>

class AudioManager {
private:
	static AudioManager* sInstance;
	GameObject* mGameObj;

public:

	static AudioManager* Instance();
	static void Release();

	
	//Starts playing music
	void PlayMusic(std::string filename, int loop = -1);
	//Pauses the current music
	void PauseMusic();
	//Resume playing the music
	void ResumeMusic();
	//Stops playing the music
	void StopMusic();
	//Starts sound effect, plays til the end and stops
	void PlaySoundEffect(std::string filename, int loop = 0, int channel = 0);

	Mix_Music *bgm = Mix_LoadMUS("mario_.wav");
	Mix_Chunk *soundEffect = Mix_LoadWAV("mario_.wav");

private:
	AudioManager();
	~AudioManager();
}; 
