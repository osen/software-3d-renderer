#ifndef QPLATFORM_ENVIRONMENT_H
#define QPLATFORM_ENVIRONMENT_H

#include <sr1/zero_initialized>

#include <memory>
#include <string>

class Platform;

class Environment
{
  friend class Platform;

public:
  float getDeltaTime();
  std::string getDataPath();

private:
  static std::shared_ptr<Environment> initialize();

  std::sr1::zero_initialized<double> lastTime;
  std::sr1::zero_initialized<float> deltaTime;

  void tick();

};

#endif
