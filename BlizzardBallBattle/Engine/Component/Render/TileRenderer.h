#pragma once

#include "Component.h"

struct SheetDescription {
    GLuint tileMapTextureID;
    float width;
    float height;
};

struct TileData {
    
}

class TileLayerGenerator {
public:
    virtual int[][] GenerateMap() = 0;
    virtual std::map<int, TileData>
}

class TileRenderer : public Component {
private:

public:
    TileRenderer(GameObject* gameObject, SheetDescription sheetDescription);
    GenerateWorld(onst initializer_list<int> &il);
}

