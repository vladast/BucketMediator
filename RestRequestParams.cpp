#include <RestRequestParams.h>
#include <sstream>
#include <iostream>

RestRequestParams::RestRequestParams(std::string requestUri)
{
    std::cout << "Processing '" << requestUri << "'" << std::endl;
    std::stringstream requestUriStream(requestUri);
    std::string part;
    bool firstPart = true;
    while(std::getline(requestUriStream, part, '\?'))
    {
        std::cout << "part = '" << part << "'" << std::endl;
        if (firstPart) // API
        {
            api = part;
            firstPart = false;
        }
        else // Params
        {
            std::stringstream ssHeader(part);
            std::string query;
            int cnt = 0;
            while(std::getline(ssHeader, query, '&'))
            {
                std::cout << "query = '" << query << "'" << std::endl;
                std::stringstream ssQuery(query);
                std::string item, first;
                bool firstItem = true;
                while(std::getline(ssQuery, item, '='))
                {
                    std::cout << "item = '" << item << "'" << std::endl;
                    if (firstItem)
                    {
                        first = item;
                        firstItem = false;
                    }
                    else
                    {
                        params.insert(std::make_pair(first, item));
                    }
                }
            }
        }
    }

    std::cout << "Params:" << std::endl;
    for (auto it = params.begin(); it != params.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
}

std::string RestRequestParams::GetParamValue(const std::string& param)
{
    std::string result("");
    auto cIter = params.find(param);
    if (cIter != params.end())
    {
        result = cIter->second;
    }
    return result;
}

int RestRequestParams::GetParamsCount()
{
    return params.size();
}
