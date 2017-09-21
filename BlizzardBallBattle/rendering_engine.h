#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <SDL_image.h>
#include <iostream>
#include "shared_constants.h"
#include <vector>
#include "sprite.h"
#include <array>

class RenderingEngine {
private:
  //Rendering variables
  SDL_Window* mainWindow = NULL;
  SDL_GLContext glContext = NULL;
  array<GLfloat, 32> quadVertices;
  array<GLuint, 6> indices;

  GLuint VBO, VAO, EBO;
  vector<Sprite*> activeSprites;

  bool SetOpenGLAttributes();
  void PrintSDL_GL_Attributes();
  void CheckSDLError(int line);

public:
  RenderingEngine();
  bool Init();
  void Cleanup();
  void Render();
  GLuint GenerateTexture(std::string textureFileName);
  void addSpriteForRendering(Sprite* sprite);
};