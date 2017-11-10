#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

class FrameBufferObject {
private:
    GLuint frameBuffer;
    GLuint texture;
    GLuint depthBuffer;

protected:
    const int WIDTH = 1280;
    const int HEIGHT = 720;

public:
    FrameBufferObject();
    void cleanUp();
    void bindFrameBuffer();
    void unbindCurrentFrameBuffer();
    int getTexture();
    int getDepthTexture();
    void initialiseFrameBuffer();
    void bindFrameBuffer(int frameBuffer, int width, int height);
    int createFrameBuffer();
    int createTextureAttachment( int width, int height);
    int createDepthBufferAttachment(int width, int height);
};