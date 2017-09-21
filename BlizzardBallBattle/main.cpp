//Using SDL and standard IO
#include <iostream>
#include <SDL.h>
#include "sprite.h"
#include "shader.h"
#include "transform.h"

void RunGame();
bool HandlePolledEvent(SDL_Event event);

int main(int argc, char *argv[])
{
  if (!Init()) {
    return -1;
  }


  RunGame();

  Cleanup();

  return 0;
}

void RunGame()
{
  bool gameLoop = true;
  int lastTicks = SDL_GetTicks();

  Shader ourShader("vertex_shader.vs", "fragment_shader.fs");
  //Triangle points

  

  Sprite sprite(texture);
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

    //Refresh Screen
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    ////Render code

    //Render Quad
    ourShader.Use();
    sprite.getTransform()->addRotation(0.01f);
    sprite.getTransform()->addTranslation(0.002f, 0.001f);

    if (sprite.getTransform() != sprite.getTransform()) {
      bool bullshit = true;
    }
    
    //fuck your rotations

    GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, *(sprite.getTransform()));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Render characters
    sprite.render();

    SDL_GL_SwapWindow(mainWindow);

    //Cap at MAX_FPS (60) FPS and delay the uneeded time
    int newTicks = SDL_GetTicks();
    int delay = 1000 / MAX_FPS - SDL_GetTicks() + lastTicks;
    if (delay > 0) {
      lastTicks = newTicks;
      SDL_Delay(delay);
    }
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
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
      glClearColor(1.0, 0.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(mainWindow);
      break;
    case SDLK_g:
      // Cover with green and update
      glClearColor(0.0, 1.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(mainWindow);
      break;
    case SDLK_b:
      // Cover with blue and update
      glClearColor(0.0, 0.0, 1.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(mainWindow);
      break;
    default:
      break;
    }
  }

  return continueGameLoop;
}

