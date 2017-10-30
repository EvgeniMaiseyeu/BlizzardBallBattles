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
#include <unordered_set>
#include <thread>
#include <mutex>

struct RenderingObject {
    ISprite* sprite;
    Transform* transform;
    SpriteRenderer* spriteRenderer;
};

struct RenderingGroup {
    GLuint shaderProgram;
    std::vector<RenderingObject> children;
};

class SpriteRendererManager {
private:
    //Singleton variables
    static SpriteRendererManager *instance;
    std::vector<SpriteRenderer*> activeSprites;
    std::unordered_set<int> disabledLayers;
    std::thread renderingThread;
    std::mutex renderTalkingStick;
    std::mutex renderReadingStick;
    std::vector<RenderingGroup> renderingGroups;
    bool renderingThreadIsAlive;

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
    void PrepareRenderingThread();

public:
    static SpriteRendererManager* GetInstance();

    //void Subscribe(int id, SpriteRenderer* spriteRenderer);
    //void UnSubscribe(int id);
    void OnUpdate(int ticks);

    SpriteRendererManager();
    bool Init();
    void Cleanup();
    void Render();
    GLuint GenerateTexture(std::string textureFileName);
    void AddSpriteForRendering(SpriteRenderer* sprite);
    
    void DisableRenderingLayer(int layer);
    void EnableRenderingLayer(int layer);
    void EnableAllRenderingLayers();
    bool IsRenderingLayerEnabled(int layer);
	void RemoveSpriteFromRendering(SpriteRenderer* sprite);
	void Purge();
};