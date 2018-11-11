#include "Exception.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <sr1/noncopyable>
#include <sr1/zero_initialized>

#include <memory>
#include <vector>

class Platform;
class Sound;

class Audio : public std::sr1::noncopyable
{
  friend class Platform;

  static std::shared_ptr<Audio> initialize(std::shared_ptr<Platform>& platform);
  void tick();

  std::sr1::zero_initialized<ALCdevice *> device;
  std::sr1::zero_initialized<ALCcontext *> context;
  std::vector<ALuint> audioSources;

  std::weak_ptr<Platform> platform;

public:
  ~Audio();

  void playSound(std::shared_ptr<Sound> sound);

};
