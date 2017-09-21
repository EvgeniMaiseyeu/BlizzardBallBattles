//Using SDL and standard IO
#define GL3_PROTOTYPES 1
#ifdef __APPLE__
  #include <GL/glew.h>
  #include <SDL2/SDL.h>
  #include <GLUT/glut.h>
  #include <GLFW/glfw3.h>
#elif defined _WIN32 || defined _WIN64
  #include <GL/glew.h>
  #include <SDL.h>
  #include <GL/glut.h>
  #include <GL/GL.h>
#endif 
#include <stdio.h>
#include <string>
#include <iostream>
#include "sprite.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* TITLE = "Blizzard Ball Battle";
const int MAX_FPS = 60;
/*
const GLchar* vertexShaderSource = "#version 150 core\n"
"layout ( location = 0 ) in vec3 position; \n"
"void main( ) \n"
"{\n"
"gl_position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar* fragmentShaderSource = "#version 150 core\n"
"out vec4 color; \n"
"void main( ) \n"
"{\n"
"color = vec4(1.0f, 0.5f, 2.0f, 1.0f);\n"
"}";
*/

const GLchar* vertexShaderSource = "#version 410\n"
"in vec3 position; \n"
"void main( ) \n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar* fragmentShaderSource = "#version 410\n"
"out vec4 color; \n"
"void main( ) \n"
"{\n"
"color = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n"
"}";

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

  if (!SetOpenGLAttributes()) {
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

  // This makes our buffer swap syncronized with the monitor's vertical refresh
  SDL_GL_SetSwapInterval(1);

  // Init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


  printf("Version: %s\n\n", glGetString( GL_VERSION ));

  return true;
}

bool SetOpenGLAttributes()
{
  //All SDL_Gl_SetAttribute returns negative on fail, 0 on success. If result is zero, all succeeded
  int result = 0;
  
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // 4.5 relased August 2014, with 4.6 in July of 2017. Going with 4.5 in hopes that modern GPUs
  result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);  
  
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

  ////Shader Start
  GLint success;
  GLchar infoLog[512];

  //Compile Vertex
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR: ShaderVertex Compilation Failed: " << infoLog << std::endl;
  }

  //Compile Fragment
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR: ShaderFragment Compilation Failed: " << infoLog << std::endl;
  }

  //Link ShaderProgram
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR: ShaderProgram Attachments Failed: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  //Shader End

  //Quad points
  GLfloat triangleVertices[] = {
    -0.5f, 0.0f, 0.0f, //bottom left
    0.5f, 0.0f, 0.0f, //bottom right
    0.0f, 0.5f, 0.0f, //top center
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

  //4 points cause quad, 3 points cause x/y/z
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //Sprite Start
  SDL_Surface *temp = SDL_LoadBMP("Assets/Character.bmp");
  GLuint texture;
  
  if (temp != NULL) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //BGR for .bmp, RGB for .png
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, temp->w, temp->h, 0, GL_BGR, GL_UNSIGNED_BYTE, temp->pixels);
    glGetError();
  }

  if (temp) {
    SDL_FreeSurface(temp);
  }

  Sprite character(texture);
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

    //Render Triangle //It should be drawing a empty triangle, but the background should be pink. Changed to red to confirm
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
