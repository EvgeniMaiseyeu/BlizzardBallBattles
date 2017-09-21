#ifndef SHARED_CONSTS_H
#define SHARED_CONSTS_H

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
const int MAX_FPS = 60;


#ifdef __APPLE__
#define BASE_PATH "./BlizzardBallBattle/"
#elif defined _WIN32 || defined _WIN64
#define BASE_PATH = "./"
#endif 


#endif // ! SHARED_CONSTS

