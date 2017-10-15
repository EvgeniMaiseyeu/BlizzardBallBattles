#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(GLuint textureBufferID, int columnCount, int rowCount, int skipLastFrames) {
    this->textureBufferID = textureBufferID;
    this->columnCount = columnCount;
    this->rowCount = rowCount;
    this->currentIndex = 0;
    this->skipLastFrames = skipLastFrames;
    ReloadTextCoordinates();
}

SpriteSheet::~SpriteSheet() {

}

void SpriteSheet::BindTextCoordinates(GLuint glCBO) {
    glBindBuffer(GL_ARRAY_BUFFER, glCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordinates), textCoordinates.data(), GL_STATIC_DRAW);
}

GLuint SpriteSheet::GetTextureBufferID() {
    return textureBufferID;
}


//2*2=4
//0, 1, 2, 3

void SpriteSheet::NextIndex() {
    int maxIndex = columnCount * rowCount - 1;
    if (++currentIndex > maxIndex - skipLastFrames) {
        currentIndex = 0;
    }
    ReloadTextCoordinates();
}

void SpriteSheet::ResetIndex() {
    currentIndex = 0;
    ReloadTextCoordinates();
}

/*
    0 / 2 = 0
    1 / 2 = 0
    2 / 2 = 1
    3 / 2 = 1
    4 / 2 = 2
*/

void SpriteSheet::ReloadTextCoordinates() {
    int maxIndex = columnCount * rowCount - 1;
    float columnPercent = 1.0f / ((float)columnCount); //1/2 = .5%, so 0%/50% or 0/1 out of 2
    int columnIndex = currentIndex % columnCount; //if index == 3, 3%2=1, index 3 is 2nd column
    float startX = (float)columnIndex * (float)columnPercent; //1 * 0.5 = 0.5f is start
    float endX = startX + columnPercent; //0.5f + 0.5f = 1.0f
    float rowPercent = 1.0f / ((float)rowCount);
    int rowIndex = currentIndex / columnCount; //if index == 3, 3%2=1, index 3 is in 2nd row
    float startY = 1 - (float)rowIndex * (float)rowPercent; //1 - 0.5f
    float endY = startY - rowPercent;
    startY = 1 - startY;
    endY = 1 - endY;
    std::cout << "ColumnPercent: " << columnPercent << " RowPercent: " << rowPercent << std::endl;
    std::cout << currentIndex << " x{" << startX << " : " << endX << "} y{" << startY << " : " << endY << "}" << std::endl;
    textCoordinates = {
        endX, startY,  //Top Right
        endX, endY,    //Bottom Right
        startX, endY,  //Bottom Left
        startX, startY //Top Left
  };
}