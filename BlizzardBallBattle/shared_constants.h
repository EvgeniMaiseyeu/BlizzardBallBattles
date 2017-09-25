#ifndef SHARED_CONSTS_H
#define SHARED_CONSTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
const int MAX_FPS = 60;

const int GAME_WIDTH = 30;

/*
Evgeni, this is my thinking for the world coordinate system and mapping it to GL. Want your opinion

WorldPoints is the x/y system walking around the game world, GL points is the u/v coordinates for drawing in OpenGL

WorldPoints is built on a game width of GAME_WIDTH, height of GetGameHeight that's based on the aspect ratio.
The game width is constantly the same, how much you see vertically is what changes.

If SCREEN_WIDTH is 1280 and SCREEN_HEIGHT is 960, the aspect ratio is 1.333 (we see 1.33 x coordinates for every y coordinate on screen)
If the GAME_WIDTH is 10 and aspect ratio 1.333, the getGameHeight() is 7.50 (we see 7.5 y coordinates on screen)

Given the above, world coordinates:
 * World(-5, -7.5) is GL(-0.5, -0.5), top-left
 * World(-5,  7.5) is GL(-0.5,  0.5), bottom-left
 * World( 5, -7.5) is GL( 0.5, -0.5), top-right
 * World( 5,  7.5) is GL( 0.5,  0.5), or bottom-right

 * World(0, 0) is GL( 0.0, 0.0), center of the screen

is that logical to you? I'm thinking of mapping it this way because our game world is symmetrical both horizontally and vertically,
but the horizontal-state must always be the same width, whereas the vertical height doesent really matter

The alternatives would be:
    Having World(0, worldY) be mapped to GL(0.0, glY), centering it. This would be logical due to having the same benefits as above,
    except its symetric, so you can always think "a negativeX means left teams side, positiveX means right teams side"
*/
//Pass in the reference to x/y floats that contain the current world position, it will update the variables to their GL positions
void worldPositionToOpenGLPosition(float* x, float* y);

//Pass in the reference to x/y floats that contain the current GL position, it will update the variables to their World positions
void openGLPositionToWorldPosition(float* x, float* y);

float getGameHeight();
float getGameWidth();
float getGameLeftX();
float getGameRightX();
float getGameTopY();
float getGameBottomY();

//(0, -1) (1, -1) (2, -1)
//(0,  0) (1,  0) (2,  0)
//(0,  1) (1,  1) (2,  1)
#endif // ! SHARED_CONSTS

