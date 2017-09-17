//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* TITLE = "Blizzard Ball Battle";


int main(int argc, char* args[])
{
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  ////The surface contained by the window
  //SDL_Surface* screenSurface = NULL;

  SDL_GLContext glContext = NULL;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize.\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  //Create our window
  window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  
  //Disable deprecated calls, instead of letting them 'function'. Force us to use newer safer calls
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0) {
    printf("SDL could not set ContextProfileMask attribute.\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  //Using OpenGL 3.x. OpenGL is up to version 4.x, but 3.x is compatible with all modern hardware/drivers for sure
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0) {
    printf("SDL could not set ContextMajorVersion attribute.\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  //Using OpenGL 3.2, as 3.3
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0) {
    printf("SDL could not set ContextMinorVersion attribute.\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  //Enable DoubleBuffer so we draw on back-buffer, which is brought to front, instead of front-buffer. Makes visuals smoother
  if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) {
    printf("SDL could not set DoubleBuffer attribute.\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  glContext = SDL_GL_CreateContext(window);
  if (glContext == NULL) {
    printf("SDL could not create a OpenGL Context\n SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  glewExperimental = GL_TRUE;

  glewInit();

  SDL_Delay(2000);


  //else
  //{
  //  //Create window
  //  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  //  if (window == NULL)
  //  {
  //    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  //  }
  //  else
  //  {
  //    //Get window surface
  //    screenSurface = SDL_GetWindowSurface(window);
  //
  //    //Fill the surface white
  //    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
  //   
  //    //Update the surface
  //    SDL_UpdateWindowSurface(window);
  //
  //    //Wait two seconds
  //    SDL_Delay(2000);
  //  }
  //}
  //

  //Destroy window
  SDL_DestroyWindow(window);
  
  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}