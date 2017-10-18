#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include <SDL_mixer.h>
#include "AudioManager.h"

class GameObject {
private:


    std::map<std::string, std::vector<Component*>> components;
	std::map<std::string, Mix_Music> mMusic;
	std::map<std::string, Mix_Chunk> mSoundEffect;

public:

    GameObject();
	static GameObject* Instance();
	static GameObject* sInstance();
    Component* GetComponent(std::string type);
    std::vector<Component*> GetComponents(std::string type);
    void AddComponent(std::string componentKey, Component *component);
    void RemoveComponent(std::string type);

    bool HasComponent(std::string type);

    //template <class T>
    //vector<Component*> GetComponentsByType();
	//Mix_Music* GetMusic(std::string filename);
	//Mix_Chunk* GetSoundEffect(std::string filename);

private:
	//GameObject();
};