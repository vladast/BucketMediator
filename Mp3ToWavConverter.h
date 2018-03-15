#ifndef __MP3_TO_WAV_CONVERTER_H__
#define __MP3_TO_WAV_CONVERTER_H__

#include <string>

class Mp3ToWavConverter
{
public:
    std::string operator() (std::string mp3FilePath);
};

#endif // __MP3_TO_WAV_CONVERTER_H__
