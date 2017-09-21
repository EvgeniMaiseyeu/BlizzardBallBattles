#include "HelperFunctions.h"

std::string BuildPath(char* fileName) {
#ifdef __APPLE__
  return std::string("./BlizzardBallBattle/") + fileName;
#elif defined _WIN32 || defined _WIN64
  return fileName;
#endif 
}