#ifndef __FILE_SIZE_INFO_SERIALIZER_H__
#define __FILE_SIZE_INFO_SERIALIZER_H__

#include <Serializer.h>
#include <FileInfo.h>

class FileSizeInfoSerializer : public Serializer
{
public:
    const std::string Serialize(const FileInfo& fileInfo);
};

#endif // __FILE_SIZE_INFO_SERIALIZER_H__
