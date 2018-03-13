#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__

#include <iostream>
#include <Serializer.h>

class Serializer;

class Serializable
{
public:
    virtual std::string Serialize(Serializer& serializer) = 0;
};

#endif // __SERIALIZABLE_H__
