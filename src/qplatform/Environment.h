#include <sr1/zero_initialized>

#include <memory>

class Platform;

class Environment
{
  friend class Platform;

public:
  float getDeltaTime();

private:
  static std::shared_ptr<Environment> initialize();

  std::sr1::zero_initialized<double> lastTime;
  std::sr1::zero_initialized<float> deltaTime;

  void tick();

};
