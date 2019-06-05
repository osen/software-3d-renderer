#include <vector>

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
