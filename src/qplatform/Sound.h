#include "Resource.h"

#include <qsoft/qsoft.h>

#ifndef _WIN32
  #include <AL/al.h>
#endif

#include <sr1/zero_initialized>
#include <sr1/noncopyable>

#include <memory>
#include <string>
#include <vector>

class Audio;

class Sound : public Resource, public std::sr1::noncopyable
{
  friend class Audio;

#ifndef _WIN32
  std::sr1::zero_initialized<ALuint> id;

  void loadOgg(std::string fileName, std::vector<char> &buffer,
    ALenum &format, ALsizei &freq);
#endif

  void onLoad(std::string path);

public:
  ~Sound();

};
