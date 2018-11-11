#include "Audio.h"
#include "Sound.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

std::shared_ptr<Audio> Audio::initialize(std::shared_ptr<Platform>& platform)
{
  std::shared_ptr<Audio> rtn = std::make_shared<Audio>();
  rtn->platform = platform;

  rtn->device = alcOpenDevice(NULL);

  if(rtn->device == NULL)
  {
    throw Exception("Failed to open audio device");
  }

  rtn->context = alcCreateContext(rtn->device, NULL);

  if(rtn->context == NULL)
  {
    alcCloseDevice(rtn->device);
    throw Exception("Failed to create context");
  }

  if(!alcMakeContextCurrent(rtn->context))
  {
    alcDestroyContext(rtn->context);
    alcCloseDevice(rtn->device);
    throw Exception("Failed to make context current");
  }

  return rtn;
}

Audio::~Audio()
{
  for(size_t asi = 0; asi < audioSources.size(); asi++)
  {
    ALuint& as = audioSources.at(asi);

    while(true)
    {
      ALint state = 0;

      alGetSourcei(as, AL_SOURCE_STATE, &state);

      if(state == AL_STOPPED)
      {
        alDeleteSources(1, &as);
        break;
      }

#ifdef _WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
    }
  }

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

void Audio::tick()
{
  for(size_t asi = 0; asi < audioSources.size(); asi++)
  {
    ALuint& as = audioSources.at(asi);
    ALint state = 0;

    alGetSourcei(as, AL_SOURCE_STATE, &state);

    if(state == AL_STOPPED)
    {
      alDeleteSources(1, &as);
      audioSources.erase(audioSources.begin() + asi);
      asi--;
    }
  }
}

void Audio::playSound(std::shared_ptr<Sound> sound)
{
  ALuint sid = 0;
  alGenSources(1, &sid);
  alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSourcei(sid, AL_BUFFER, sound->id);
  alSourcePlay(sid);

  audioSources.push_back(sid);
}
