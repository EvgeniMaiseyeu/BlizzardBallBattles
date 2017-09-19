//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <iostream>
#include <SDL_image.h>
#include "sprite.h"
#include "shader.h"
#include "matrix_math.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* TITLE = "Blizzard Ball Battle";
const int MAX_FPS = 60;

//Rendering variables
SDL_Window* mainWindow = NULL;
SDL_GLContext glContext = NULL;

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void RunGame();
void Cleanup();
bool Init();
bool HandlePolledEvent(SDL_Event event);

bool Init()
{
  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to init SDL\n";
    return false;
  }

  // Create our window centered as an OpenGL window
  mainWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  // Check that everything worked out okay
  if (!mainWindow) {
    std::cout << "Unable to create window\n";
    CheckSDLError(__LINE__);
    return false;
  }

  // Create our opengl context and attach it to our window
  glContext = SDL_GL_CreateContext(mainWindow);

  if (!SetOpenGLAttributes()) {
    return false;
  }

  // This makes our buffer swap syncronized with the monitor's vertical refresh
  SDL_GL_SetSwapInterval(1);

  // Init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

bool SetOpenGLAttributes()
{
  //All SDL_Gl_SetAttribute returns negative on fail, 0 on success. If result is zero, all succeeded
  int result = 0;

  // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
  result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // 4.5 relased August 2014, with 4.6 in July of 2017. Going with 4.5 in hopes that modern GPUs
  result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  result += SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return result == 0;
}

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
  GLfloat quadVertices[] = {
    //Position            //Color             //Texture Coordinates
    0.5f, 0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  //Top Right
    0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  //Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  //Bottom Left
    -0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 1.0f,   0.0f, 1.0f   //Top Left
  };

  GLuint indices[] = {
    0, 1, 3, // First Triangle
    1, 2, 3  // Second Triangle
  };

  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //4 points cause quad, 8 points cause x/y/z/r/g/b/tx/ty
  //position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  //color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  //textture coordinate attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); //Unbind BAO

  ////
  //SDL_Surface* image = IMG_Load("Assets/Character.png");
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  //glGenerateMipmap(GL_TEXTURE_2D);
  //SDL_FreeSurface(image);
  //glBindTexture(GL_TEXTURE_2D, 0); ﻿
  ////

  //Texture
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  SDL_Surface *temp = IMG_Load("Assets/Character.png");
  if (temp == NULL) {
    //ERROR
    int hit = 1;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp->w, temp->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  SDL_FreeSurface(temp);
  glBindTexture(GL_TEXTURE_2D, 0);
  //EndTexture

  Sprite character(texture);
  Transform transform;
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

    //Render Triangle
    ourShader.Use();

    
    //fuck your rotations

    GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Render characters
    character.render();

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

void Cleanup()
{
  // Delete our OpengL context
  SDL_GL_DeleteContext(glContext);

  // Destroy our window
  SDL_DestroyWindow(mainWindow);

  // Shutdown SDL 2
  SDL_Quit();
}

void CheckSDLError(int line = -1)
{
  std::string error = SDL_GetError();

  if (error != "")
  {
    std::cout << "SLD Error : " << error << std::endl;

    if (line != -1)
      std::cout << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}

void PrintSDL_GL_Attributes()
{
  int value = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
  std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
  std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
