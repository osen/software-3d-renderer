#include <SDL2/SDL.h>

#include <vector>

#define KEY_UP SDLK_UP
#define KEY_LEFT SDLK_LEFT
#define KEY_DOWN SDLK_DOWN
#define KEY_RIGHT SDLK_RIGHT
#define KEY_SPACE SDLK_SPACE
#define KEY_T SDLK_t
#define KEY_Y SDLK_y

class Platform;

class Keyboard
{
  friend class Platform;

  std::vector<double> keys;
  std::vector<double> pressedKeys;

public:
  bool isKeyDown(double key);
  bool isKeyPressed(double key);

};
