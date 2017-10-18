#include "GameObject.h"
#include "Transform.h"

#include <SDL.h>
#include <SDL_mixer.h>

//GameObject* GameObject::sInstance = NULL;

//GameObject* GameObject::Instance() {
//	if (sInstance == NULL)
//		sInstance = new GameObject();
//	return sInstance;
//}



#include "GameManager.h"
 

GameObject::GameObject() {
  id = rand() + rand();
  GameManager::GetInstance()->AddGameObject(id, this);
  AddComponent<Transform*>(new Transform(this));
}
 
void GameObject::Update(int ticks) {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            it->second[i]->Update(ticks);
        }
    }
}


void GameObject::RemoveComponent(std::string type) {
    components[type].clear();
}

bool GameObject::HasComponent(std::string type) {
    return components.count(type);
}

/*Mix_Music* GameObject::GetMusic(std::string filename) {
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);
	
	if (mMusic[fullpath] == nullptr) {
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == NULL)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	return mMusic[fullpath];

}

Mix_Chunk* GameObject::GetSoundEffect(std::string filename) {
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);

	if (mSoundEffect[fullpath] == nullptr) {
		mSoundEffect[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mSoundEffect[fullpath] == NULL)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	return mSoundEffect[fullpath];
}*/

 
GameObject::~GameObject() {
  GameManager::GetInstance()->RemoveGameObject(id);
}
