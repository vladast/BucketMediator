#ifndef __FILE_INFO_H__
#define __FILE_INFO_H__

#include <iostream>
#include <Serializer.h>
#include <Serializable.h>

class FileInfo : public Serializable
{
    int channelCount;
    int sampleRate;
    float executionTime;
    long fileSize;
private:
    FileInfo() {}
public:
    FileInfo(const std::string& filePath);
    int GetChannelCount() const { return channelCount; }
    int GetSampleRate() const { return sampleRate; }
    float GetExecutionTime() const { return executionTime; }
    long GetFileSize() const { return fileSize; }
public:
    friend std::ostream& operator<<(std::ostream& stream, const FileInfo& fileInfo);
    std::string ToString();
    std::string Serialize(Serializer& serializer);
};

#endif // __FILE_INFO_H__
