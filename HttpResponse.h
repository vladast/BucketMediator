#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <string>

class HttpResponse
{
    std::string httpVersion;
    int statusCode;
    std::string messageBody;
public:
    HttpResponse();
    HttpResponse(int statusCode);
    HttpResponse(int statusCode, const std::string& messageBody);
    int GetStatusCode() const { return statusCode; }
    std::string GetStatusCodeStr() const { return std::to_string(statusCode); }
    void SetStatusCode(int statusCode) { this->statusCode = statusCode; }
    std::string GetReasonPhrase();
    const std::string& GetMessageBody() { return messageBody; }
    void SetMessageBody(std::string& messageBody) { this->messageBody = messageBody; }
    void SetMessageBody(const std::string& messageBody) { this->messageBody = messageBody; }
public:
    const std::string ToString();
};

#endif // __HTTP_RESPONSE_H__
