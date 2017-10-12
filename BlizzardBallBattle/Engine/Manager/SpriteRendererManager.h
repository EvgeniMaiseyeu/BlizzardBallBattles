#pragma once

#include <map> ////
#include "GLHeaders.h"
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <iostream>
#include "SharedConstants.h"
#include <vector>
#include <array>
#include "SpriteRenderer.h"
#include "Transform.h"

class SpriteRendererManager {
private:
    //Singleton variables
    static SpriteRendererManager *instance;
    std::vector<SpriteRenderer*> activeSprites;

    //Rendering variables
    SDL_Window* mainWindow = NULL;
    SDL_GLContext glContext = NULL;
    std::array<GLfloat, 12> quadVertices;
    std::array<GLfloat, 8> textCoordinates;
    std::array<GLuint, 6> indices;
    GLuint VBO, VAO, EBO, CBO; //VertexBufferObject, VertexArrayObject, ElementsBufferObject, CoordinateBufferObject

    //Rendering methods
    bool SetOpenGLAttributes();
    void PrintSDL_GL_Attributes();
    void CheckSDLError(int line);

public:
    static SpriteRendererManager* GetInstance();

    //void Subscribe(int id, SpriteRenderer* spriteRenderer);
    //void UnSubscribe(int id);
    void Update(int ticks);

    SpriteRendererManager();
    bool Init();
    void Cleanup();
    void Render();
    GLuint GenerateTexture(std::string textureFileName);
    void AddSpriteForRendering(SpriteRenderer* sprite);
};