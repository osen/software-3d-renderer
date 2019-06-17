#include "Exception.h"

#ifndef _WIN32
  #include <AL/al.h>
  #include <AL/alc.h>
#endif

#include <sr1/noncopyable>
#include <sr1/zero_initialized>
#include <sr1/vector>
#include <sr1/memory>

class Platform;
class Sound;

class Audio : public std::sr1::noncopyable
{
  friend class Platform;

  static std::sr1::shared_ptr<Audio> initialize(
    std::sr1::shared_ptr<Platform>& platform);

  void tick();

#ifndef _WIN32
  std::sr1::zero_initialized<ALCdevice *> device;
  std::sr1::zero_initialized<ALCcontext *> context;
  std::sr1::vector<ALuint> audioSources;
#endif

  std::sr1::weak_ptr<Platform> platform;

public:
  ~Audio();

  void playSound(std::sr1::shared_ptr<Sound> sound);

};
