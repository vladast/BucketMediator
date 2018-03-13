#include <AudioInfoSerializer.h>
#include <sstream>

const std::string AudioInfoSerializer::Serialize(const FileInfo& fileInfo)
{
    std::stringstream jsonStream;
    jsonStream << "{"
               << "\"channel_count\":" << fileInfo.GetChannelCount() << ","
               << "\"sample_rate\":" << fileInfo.GetSampleRate() << ","
               << "\"execution_time\":" << fileInfo.GetExecutionTime()
               << "}";
    return jsonStream.str();
}
