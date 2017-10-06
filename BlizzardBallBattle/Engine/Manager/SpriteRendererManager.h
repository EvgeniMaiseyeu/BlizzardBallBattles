#pragma once

#include <map> ////
#include "GLHeaders.h"
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <iostream>
#include "shared_constants.h"
#include <vector>
#include "sprite.h"
#include <array>
#include "SpriteRenderer.h"

class SpriteRendererManager {
private:
    //Singleton variables
    static SpriteRendererManager *instance;
    vector<Sprite*> activeSprites;

    //Rendering variables
    SDL_Window* mainWindow = NULL;
    SDL_GLContext glContext = NULL;
    array<GLfloat, 32> quadVertices;
    array<GLuint, 6> indices;
    GLuint VBO, VAO, EBO;

    //Rendering methods
    bool SetOpenGLAttributes();
    void PrintSDL_GL_Attributes();
    void CheckSDLError(int line);

public:
    typedef pair<int, SpriteRenderer*> spriteRenderers;

    static SpriteRendererManager* GetInstance();

    void Subscribe(int id, SpriteRenderer* spriteRenderer);
    void UnSubscribe(int id);
    void Update(int ticks);

    SpriteRendererManager();
    bool Init();
    void Cleanup();
    void Render();
    GLuint GenerateTexture(std::string textureFileName);
    void addSpriteForRendering(Sprite* sprite);
};