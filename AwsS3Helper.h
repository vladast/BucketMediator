#ifndef __AWS_S3_HELPER_H__
#define __AWS_S3_HELPER_H__

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/memory/stl/AWSStreamFwd.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <iostream>
#include <fstream>

static const char* AWS_ACCESS_KEY_ID = "AWS_ACCESS_KEY_ID";
static const char* AWS_SECRET_ACCESS_KEY = "AWS_SECRET_ACCESS_KEY";
static const char* AWS_S3_BUCKET_REGION = Aws::Region::EU_WEST_1;

/**
 * @brief The AwsS3Helper class Used to wrap AWS SDK's download and upload functionality
 */
class AwsS3Helper
{
    std::string awsAccessKeyId;
    std::string awsSecretAccessKey;
    Aws::String awsS3BucketRegion;
    Aws::String awsS3Bucket;
public:
    AwsS3Helper();
    /**
     * @brief AwsS3Helper c-tor with bucket name initialization
     * @param bucket Name of the S3 bucket that is to be used
     */
    AwsS3Helper(const std::string& bucket);
    AwsS3Helper(const std::string& awsAccessKeyId, const std::string& awsSecretAccessKey,
                const std::string& awsS3BucketRegion, const std::string& awsS3Bucket);
    void setAccessKey(const std::string& accessKeyId);
    void setSecretAccessKey(const std::string& secretAccessKey);
    void setBucketRegion(const std::string& bucketRegion);
    void setBucket(const std::string& bucket);
    /**
     * @brief download Download file from S3 bucket
     * @param fileKey S3 object key for the file that is to be downloaded
     * @return File name of locally stored file from S3 bucket
     */
    std::string download(const std::string& fileKey);
    /**
     * @brief upload Upload file to S3 bucket
     * @param fileKey S3 object key for the file that is to be uploaded
     * @param filePath Path to file that is to be uploaded
     */
    void upload(const std::string& fileKey, const std::string& filePath);
};

#endif // __AWS_S3_HELPER_H__
