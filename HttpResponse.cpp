#include <HttpResponse.h>
#include <sstream>

HttpResponse::HttpResponse() : httpVersion("HTTP/1.1"), statusCode(200), messageBody("")
{
}

HttpResponse::HttpResponse(int statusCode) : httpVersion("HTTP/1.1"), messageBody("")
{
    this->statusCode = statusCode;
}

HttpResponse::HttpResponse(int statusCode, const std::string& messageBody) : httpVersion("HTTP/1.1")
{
    this->statusCode = statusCode;
    this->messageBody = messageBody;
}

std::string HttpResponse::GetReasonPhrase()
{
    std::string reasonPhrase;
    switch(statusCode)
    {
    case 200:
        reasonPhrase = "OK";
        break;
    case 204:
        reasonPhrase = "No Content";
        break;
    case 400:
        reasonPhrase = "Bad Request";
        break;
    case 403:
        reasonPhrase = "Forbidden";
        break;
    case 406:
        reasonPhrase = "Not Acceptable";
        break;
    case 500:
        reasonPhrase = "Internal Server Error";
        break;
    case 501:
        reasonPhrase = "Not Implemented";
        break;
    case 503:
        reasonPhrase = "Service Unavailable";
        break;
    case 505:
        reasonPhrase = "HTTP Version not supported";
        break;
    default:
        reasonPhrase = "Undefined";
        break;
    }
    return reasonPhrase;
}

const std::string HttpResponse::ToString()
{
    std::stringstream sstream;
    sstream << httpVersion << " " << statusCode << " " << GetReasonPhrase() << std::endl
            << std::endl
            << messageBody;
    return sstream.str();
}
