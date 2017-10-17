#pragma once

#include "GLHeaders.h"

class ISprite {
public:
    virtual void BindTextCoordinates(GLuint glCBO) = 0;
    virtual GLuint GetTextureBufferID() = 0;
};