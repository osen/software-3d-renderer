#include "Sound.h"
#include "Exception.h"

#include "stb_vorbis.h"

void Sound::onLoad(std::string path)
{
#ifndef _WIN32
  ALenum format = 0;
  ALsizei freq = 0;
  std::vector<char> bufferData;

  alGenBuffers(1, &id.data());

  loadOgg(path + ".ogg", bufferData, format, freq);

  alBufferData(id, format, &bufferData.at(0),
    static_cast<ALsizei>(bufferData.size()), freq);
#endif
}

Sound::~Sound()
{
#ifndef _WIN32
  alDeleteBuffers(1, &id.data());
#endif
}

#ifndef _WIN32
void Sound::loadOgg(std::string fileName, std::vector<char> &buffer,
  ALenum &format, ALsizei &freq)
{
  int channels = 0;
  int sampleRate = 0;
  short *output = NULL;

  size_t samples = stb_vorbis_decode_filename(
    fileName.c_str(), &channels, &sampleRate, &output);

  if(samples == -1)
  {
    throw Exception("Failed to open file '" + fileName + "' for decoding");
  }

  // Record the format required by OpenAL
  if(channels == 1)
  {
    format = AL_FORMAT_MONO16;
  }
  else
  {
    format = AL_FORMAT_STEREO16;
  }

  // Record the sample rate required by OpenAL
  freq = sampleRate;

  buffer.resize(samples * 2);
  memcpy(&buffer.at(0), output, buffer.size());

  // Clean up the read data
  free(output);
}
#endif
