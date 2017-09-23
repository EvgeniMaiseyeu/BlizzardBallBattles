//Using SDL and standard IO
#include "GLHeaders.h"
#define GL3_PROTOTYPES 1
#include <stdio.h>
#include <string>
#include <iostream>
#include "shared_constants.h"
#include "sprite.h"
#include "shader.h"
#include "transform.h"
#include "rendering_engine.h"
#include "HelperFunctions.h"

void RunGame();
bool HandlePolledEvent(SDL_Event event);

RenderingEngine* renderingEngine;

int main(int argc, char *argv[])
{
  renderingEngine = new RenderingEngine();
  if (!renderingEngine->Init()) {
    return -1;
  }

  RunGame();

  renderingEngine->Cleanup();
  delete(renderingEngine);

  return 0;
}

void RunGame()
{
  bool gameLoop = true;
  int lastTicks = SDL_GetTicks();

  //Sprites for testing
  
  Shader ourShader(BuildPath("Game/Assets/Shaders/vertex_shader.vs").c_str(), BuildPath("Game/Assets/Shaders/fragment_shader.fs").c_str());
  GLuint texture = renderingEngine->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
  Sprite sprite(texture);
  renderingEngine->addSpriteForRendering(&sprite);
  sprite.setActiveShader(&ourShader);
  sprite.getTransform()->setScale(0.25f);
  //Sprite End

  while (gameLoop) {
    //Handle events like key pressed
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (!HandlePolledEvent(event)) {
        gameLoop = false;
      }
    }

    renderingEngine->Render();

    if (sprite.getTransform()->getX() > 1.0f) {
      sprite.getTransform()->setX(-1.0f);
    }
    sprite.getTransform()->addX(0.02f);
    sprite.getTransform()->addRotation(0.1f);

    //Cap at MAX_FPS (60) FPS and delay the uneeded time
    int newTicks = SDL_GetTicks();
    int delay = 1000 / MAX_FPS - SDL_GetTicks() + lastTicks;
    if (delay > 0) {
      lastTicks = newTicks;
      SDL_Delay(delay);
    }
  }
}

bool HandlePolledEvent(SDL_Event event) {
  bool continueGameLoop = true;

  if (event.type == SDL_QUIT)
    continueGameLoop = false;

  //KeyDown is actually KeyHeld, with SDL_KEYUP being on release.
  //Need state machine to keeep track of proper Pressed/Held/Release states, this event could update them
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
      continueGameLoop = false;
      break;
    case SDLK_r:
      // Cover with red and update
      //ClearColor(1.0, 0.0, 0.0, 1.0);
      //Clear(GL_COLOR_BUFFER_BIT);
      //L_GL_SwapWindow(mainWindow);
      break;
    case SDLK_g:
      // Cover with green and update
      //ClearColor(0.0, 1.0, 0.0, 1.0);
      //Clear(GL_COLOR_BUFFER_BIT);
      //L_GL_SwapWindow(mainWindow);
      break;
    case SDLK_b:
      // Cover with blue and update
      //ClearColor(0.0, 0.0, 1.0, 1.0);
      //Clear(GL_COLOR_BUFFER_BIT);
      //L_GL_SwapWindow(mainWindow);
      break;
    default:
      break;
    }
  }

  return continueGameLoop;
}

