#include "Sound.h"
#include "Exception.h"

#include <vorbis/vorbisfile.h>

void Sound::onLoad(std::string path)
{
  ALenum format = 0;
  ALsizei freq = 0;
  std::vector<char> bufferData;

  alGenBuffers(1, &id.data());

  loadOgg(path + ".ogg", bufferData, format, freq);

  alBufferData(id, format, &bufferData.at(0),
    static_cast<ALsizei>(bufferData.size()), freq);
}

Sound::~Sound()
{
  alDeleteBuffers(1, &id.data());
}

void Sound::loadOgg(std::string fileName, std::vector<char> &buffer,
  ALenum &format, ALsizei &freq)
{
  int endian = 0;
  int bitStream = 0;
  long bytes = 0;
  char array[2048] = {0};
  vorbis_info *pInfo = NULL;
  OggVorbis_File oggFile = {0};

  // Use the inbuilt fopen to create a file descriptor
  if(ov_fopen(fileName.c_str(), &oggFile) != 0)
  {
    throw Exception("Failed to open file '" + fileName + "' for decoding");
  }

  // Extract information from the file header
  pInfo = ov_info(&oggFile, -1);

  // Record the format required by OpenAL
  if(pInfo->channels == 1)
  {
    format = AL_FORMAT_MONO16;
  }
  else
  {
    format = AL_FORMAT_STEREO16;
  }

  // Record the sample rate required by OpenAL
  freq = pInfo->rate;

  // Keep reading bytes from the file to populate the output buffer
  while(true)
  {
    // Read bytes into temporary array
    bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

    if(bytes < 0)
    {
      ov_clear(&oggFile);
      throw ("Failed to decode file '" + fileName + "'.");
    }
    else if(bytes == 0)
    {
      break;
    }

    // Copy from temporary array into output buffer
    buffer.insert(buffer.end(), array, array + bytes);
  }

  // Clean up and close the file
  ov_clear(&oggFile);
}
