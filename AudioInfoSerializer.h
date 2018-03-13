#ifndef __AUDIO_INFO_SERIALIZER_H__
#define __AUDIO_INFO_SERIALIZER_H__

#include <Serializer.h>
#include <FileInfo.h>

class AudioInfoSerializer : public Serializer
{
public:
    const std::string Serialize(const FileInfo& fileInfo);
};

#endif // __AUDIO_INFO_SERIALIZER_H__
