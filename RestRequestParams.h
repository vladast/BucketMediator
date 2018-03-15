#ifndef __REST_REQUEST_PARAMS_H__
#define __REST_REQUEST_PARAMS_H__

#include <string>
#include <map>

class RestRequestParams
{
    std::string api;
    std::map<std::string, std::string> params;
    RestRequestParams() {}
public:
    RestRequestParams(std::string requestUri);
    const std::string& GetApi() const { return api; }
    const std::map<std::string, std::string>& GetParams() const { return params; }
    std::string GetParamValue(const std::string& param);
    int GetParamsCount();
};

#endif // __REST_REQUEST_PARAMS_H__
