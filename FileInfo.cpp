#include <FileInfo.h>
#include <FileHelper.h>
#include <Serializer.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

std::ostream& operator<<(std::ostream& stream, const FileInfo& fileInfo)
{
    stream << "Channels: " << fileInfo.GetChannelCount() << std::endl
           << "Sample rate: " << fileInfo.GetSampleRate() << std::endl
           << "Execution time: " << fileInfo.GetExecutionTime() << std::endl
           << "File size: " << fileInfo.GetFileSize() << std::endl;
}

FileInfo::FileInfo(const std::string& filePath)
{
    std::cout << "Checking " << filePath << std::endl;

    std::string::size_type size;

    std::string soxiCommand = std::string("soxi") + " -c " + filePath;
    std::string soxiOutput = FileHelper::Execute(soxiCommand);
    channelCount = std::stoi(soxiOutput, &size);

    soxiCommand = std::string("soxi") + " -r " + filePath;
    soxiOutput = FileHelper::Execute(soxiCommand);
    sampleRate = std::stoi(soxiOutput, &size);

    soxiCommand = std::string("soxi") + " -D " + filePath;
    soxiOutput = FileHelper::Execute(soxiCommand);
    executionTime = std::stof(soxiOutput, &size);

    soxiCommand = std::string("wc") + " -c < " + filePath;
    soxiOutput = FileHelper::Execute(soxiCommand);
    fileSize = std::stol(soxiOutput, &size);

    std::cout << "channelCount = " << channelCount << std::endl;
    std::cout << "sampleRate = " << sampleRate << std::endl;
    std::cout << "executionTime = " << executionTime << std::endl;
    std::cout << "fileSize = " << fileSize << std::endl;
}

std::string FileInfo::ToString()
{
    std::stringstream stringStream;
    stringStream << "Channels: " << channelCount << std::endl
                 << "Sample rate: " << sampleRate << std::endl
                 << "Execution time: " << executionTime << std::endl
                 << "File size: " << fileSize << std::endl;
    return stringStream.str();
}

std::string FileInfo::Serialize(Serializer& serializer)
{
    return serializer.Serialize(*this);
}
