#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <sstream>
#include <map>

class HttpRequest
{
    std::string method;
    std::string requestUri;
    std::map<std::string, std::string> headers;
    HttpRequest();
public:
    HttpRequest(std::stringstream& request);
    const std::string& GetMethod() const { return method; }
    const std::string& GetRequestUri() const { return requestUri; }
    const std::map<std::string, std::string>& GetHeaders() const { return headers; }
    std::string GetHeaderValue(const std::string& header) const;
};

#endif // __HTTP_REQUEST_H__
