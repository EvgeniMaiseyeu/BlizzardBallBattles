#pragma once

#include "GLHeaders.h"
#include <array>

class ISprite {
public:
    virtual void BindTextCoordinates(GLuint glCBO) = 0;
    virtual GLuint GetTextureBufferID() = 0;
};