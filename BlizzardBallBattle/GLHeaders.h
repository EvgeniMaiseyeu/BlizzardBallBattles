#ifndef GL_HEADERS_H
#define GL_HEADERS_H

#ifdef __APPLE__
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#elif defined _WIN32 || defined _WIN64
#include <GL/glew.h>
#include <SDL.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <SDL_image.h>
#endif 

#endif