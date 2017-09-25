#include "shared_constants.h"

void worldPositionToOpenGLPosition(float* x, float* y) {
    float glX = *x / GAME_WIDTH * 2.0;     //For worldX of -5/0/5, glX is -0.5/0/5. Adjust by scale.
    float glY = *y / getGameHeight() * 2.0 / ASPECT_RATIO; //For worldY of -3.5/0/5, glY is -0.5/0/5. Adjust by scale

    *x = glX;
    *y = glY;
}

void openGLPositionToWorldPosition(float* x, float* y) {

}

float getGameLeftX() {
    return - GAME_WIDTH / 2.0;
}

float getGameRightX() {
    return GAME_WIDTH / 2.0;
}
float getGameTopY() {
    return getGameHeight() / 2.0;
}
float getGameBottomY() {
    return -getGameHeight() / 2.0;
}

float getGameHeight() {
    return GAME_WIDTH / ASPECT_RATIO;
}

float getGameWidth() {
    return GAME_WIDTH;
}