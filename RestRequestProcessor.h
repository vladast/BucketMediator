#ifndef __REST_REQUEST_PROCESSOR_H__
#define __REST_REQUEST_PROCESSOR_H__

#include <AwsS3Helper.h>
#include <HttpResponse.h>
#include <RestRequestParams.h>

class RestRequestProcessor
{
    AwsS3Helper awsS3Helper;
public:
    RestRequestProcessor() {}
    RestRequestProcessor(AwsS3Helper awsS3Helper) { this->awsS3Helper = awsS3Helper; }
    AwsS3Helper& GetAwsS3Helper() { return awsS3Helper; }
    void SetAwsS3Helper(AwsS3Helper awsS3Helper) { this->awsS3Helper = awsS3Helper; }
    HttpResponse operator() (RestRequestParams restRequestParams);
};

#endif // __REST_REQUEST_PROCESSOR_H__
