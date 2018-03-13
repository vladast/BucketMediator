#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <iostream>
#include <FileInfo.h>

class FileInfo;

/**
 * @brief The Serializer class
 */
class Serializer
{
public:
    virtual const std::string Serialize(const FileInfo& fileInfo) = 0;
};

#endif // __SERIALIZER_H__
