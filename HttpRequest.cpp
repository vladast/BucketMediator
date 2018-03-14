#include <HttpRequest.h>

#include <vector>

HttpRequest::HttpRequest(std::stringstream& request)
{
    std::string requestLine;
    std::vector<std::string> tokens;
    bool firstLine = true;
    while(std::getline(request, requestLine))
    {
        if (firstLine) // HTTP method
        {
            std::stringstream ssMethod(requestLine);
            std::string requestItem;
            int cnt = 0;
            while(std::getline(ssMethod, requestItem, ' '))
            {
                switch(cnt++)
                {
                case 0:     // Method
                    method = requestItem;
                    break;
                case 1:     // Request URI
                    requestUri = requestItem;
                    break;
                case 2:     // HTTP version;
                    // not used.
                default:
                    break;
                }
            }
            firstLine = false;
        }
        else // HTTP headers
        {
            std::stringstream ssHeader(requestLine);
            std::string requestItem;
            int cnt = 0;
            while(std::getline(ssHeader, requestItem, ':'))
            {
                // Not used currently
                // Should fillout map with all http header key-value pairs
            }
        }
    }
}

std::string HttpRequest::GetHeaderValue(const std::string& header) const
{
    std::string result("");
    auto cIter = headers.find(header);
    if (cIter != headers.end())
    {
        result = cIter->second;
    }
    return result;
}
