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


GameObject::GameObject() {
  AddComponent("Transform", (Component*)new Transform(this));
}

Component* GameObject::GetComponent(std::string type) {
    return components[type].front();
}

std::vector<Component*> GameObject::GetComponents(std::string type) {
    return components[type];
}

void GameObject::AddComponent(std::string componentKey, Component *component) {
    //std::string type = typeid(component).name(); NOTE: This returns "class Component *" for a SpriteRenderer type, not a valid way to get the string type of a object
    if (!HasComponent(componentKey)) {
        std::vector<Component*> typeList;
        typeList.push_back(component);
        components[componentKey] = typeList;
    } else {
        components[componentKey].push_back(component);
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