#include <FileSizeInfoSerializer.h>
#include <sstream>

const std::string FileSizeInfoSerializer::Serialize(const FileInfo& fileInfo)
{
    std::stringstream jsonStream;
    jsonStream << "{"
               << "\"file_size\":" << fileInfo.GetFileSize() << ","
               << "\"execution_time\":" << fileInfo.GetExecutionTime()
               << "}";
    return jsonStream.str();
}
