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

class RenderingEngine {
private:
  //Rendering variables
  SDL_Window* mainWindow = NULL;
  SDL_GLContext glContext = NULL;
  GLfloat* quadVertices = NULL;
  GLuint* indices = NULL;

  bool SetOpenGLAttributes();
  void PrintSDL_GL_Attributes();
  void CheckSDLError(int line);

public:
  RenderingEngine();
  bool Init();
  void Cleanup();
  void Render();
};