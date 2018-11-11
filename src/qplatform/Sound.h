#include "Resource.h"

#include <qsoft/qsoft.h>

#include <AL/al.h>

#include <sr1/zero_initialized>

#include <memory>
#include <string>
#include <vector>

class Audio;

class Sound : public Resource
{
  friend class Audio;

  std::sr1::zero_initialized<ALuint> id;

  void onLoad(std::string path);

  void loadOgg(std::string fileName, std::vector<char> &buffer,
    ALenum &format, ALsizei &freq);

public:
  ~Sound();

};
