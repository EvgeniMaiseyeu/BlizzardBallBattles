#include "Game.h"
#include "NetworkingManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameScene_Alpha_Networked.h"
#include "SceneTemplate.h"
#include <iostream>

/*
This class is not intended to have a lot of code. This is intended to be the on entry call for
the game code, custom game manager update calls, and cleanup on exit.

The heirachy of Updates begin at main.cpp.
main.cpp initializes engine managers and starts the GameManager.cpp main loop.
GameManager.cpp updates engine managers, Game.cpp update, then the global game objects, and finally the current scene on SceneManager.cpp.
The Game.cpp update calls specific managers made to exist for the game.
The SceneManager.cpp calls its update on all game objects that exist for that scene.
Each GameObject cycles through and updates each one of their game components.

*/

void Game::OnStart() {
    SceneManager::GetInstance()->PushScene(new SceneTemplate());
}

void Game::OnUpdate(int ticks) {

    if (!NetworkingManager::GetInstance()->IsConnected() && InputManager::GetInstance()->onKeyPressed(SDLK_h)) {
        NetworkingManager::GetInstance()->CreateHost();
      }
      
      if (!NetworkingManager::GetInstance()->IsConnected() && InputManager::GetInstance()->onKeyPressed(SDLK_j)) {
        NetworkingManager::GetInstance()->CreateClient();
      }
}

void Game::OnEnd() {

}