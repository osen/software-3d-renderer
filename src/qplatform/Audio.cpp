#include "Audio.h"
#include "Sound.h"

std::sr1::shared_ptr<Audio> Audio::initialize(
  std::shared_ptr<Platform>& platform)
{
  std::sr1::shared_ptr<Audio> rtn = std::sr1::make_shared<Audio>();
  rtn->platform = platform;

#ifndef _WIN32
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
#endif

  return rtn;
}

Audio::~Audio()
{
#ifndef _WIN32
  for(std::sr1::vector<ALuint>::iterator it = audioSources.begin();
    it != audioSources.end(); it++)
  {
    alSourceStop(*it);
    alDeleteSources(1, &(*it));
  }

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
#endif
}

void Audio::tick()
{
#ifndef _WIN32
  for(std::sr1::vector<ALuint>::iterator it = audioSources.begin();
    it != audioSources.end();)
  {
    ALint state = 0;

    alGetSourcei(*it, AL_SOURCE_STATE, &state);

    if(state == AL_STOPPED)
    {
      alDeleteSources(1, &(*it));
      it = audioSources.erase(it);
    }
    else
    {
      it++;
    }
  }
#endif
}

void Audio::playSound(std::shared_ptr<Sound> sound)
{
#ifndef _WIN32
  ALuint sid = 0;
  alGenSources(1, &sid);
  //alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
  //alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
  alSourcei(sid, AL_BUFFER, sound->id);
  alSourcePlay(sid);

  audioSources.push_back(sid);
#endif
}
