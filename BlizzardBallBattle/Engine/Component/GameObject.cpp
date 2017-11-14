#include "GameObject.h"
#include "Transform.h"
#include "GameManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SceneManager.h"
 
GameObject::GameObject(bool g) {
    id = rand() + rand();
    isGlobal = g;
    if (isGlobal)
        GameManager::GetInstance()->AddGameObject(id, this);
    if (SceneManager::GetInstance()->HasScene())
        SceneManager::GetInstance()->GetCurrentScene()->AddGameObject(id, this);
    AddComponent<Transform*>(new Transform(this));
}

void GameObject::OnUpdate(int ticks) {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            it->second[i]->OnUpdate(ticks);
        }
    }
}

GameObject::~GameObject() {
  GameManager::GetInstance()->RemoveGameObject(id);
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

Mix_Chunk* GameObject::GetSEF(std::string filename) {
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);

	if (mSEF[fullpath] == nullptr) {
		mSEF[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mSEF[fullpath] == NULL)
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
	}
	return mSEF[fullpath];*/
