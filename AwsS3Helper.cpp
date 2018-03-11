#include <AwsS3Helper.h>

AwsS3Helper::AwsS3Helper()
{
    awsAccessKeyId = AWS_ACCESS_KEY_ID;
    awsSecretAccessKey = AWS_SECRET_ACCESS_KEY;
    awsS3BucketRegion = AWS_S3_BUCKET_REGION;
}

AwsS3Helper::AwsS3Helper(const std::string& bucket) : awsS3Bucket(bucket.c_str())
{
}


AwsS3Helper::AwsS3Helper(const std::string& awsAccessKeyId, const std::string& awsSecretAccessKey,
            const std::string& awsS3BucketRegion, const std::string& awsS3Bucket)
{
    this->awsAccessKeyId = awsAccessKeyId;
    this->awsSecretAccessKey = awsSecretAccessKey;
    this->awsS3BucketRegion = awsS3BucketRegion.c_str();
    this->awsS3Bucket = awsS3Bucket.c_str();
}

void AwsS3Helper::setAccessKey(const std::string& accessKeyId)
{
    awsAccessKeyId = accessKeyId.c_str();
}
void AwsS3Helper::setSecretAccessKey(const std::string& secretAccessKey)
{
    awsSecretAccessKey = secretAccessKey.c_str();
}

void AwsS3Helper::setBucketRegion(const std::string& bucketRegion)
{
    awsS3BucketRegion = bucketRegion.c_str();
}

void AwsS3Helper::setBucket(const std::string& bucket)
{
    awsS3Bucket = bucket.c_str();
}

std::string AwsS3Helper::download(const std::string& fileKey)
{
    std::cout << "Downloading: " << fileKey << std::endl;
    std::string fileName = fileKey;
    std::replace(fileName.begin(), fileName.end(), '/', '_');
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration config;
        config.region = awsS3BucketRegion;
        Aws::S3::S3Client client =
                Aws::S3::S3Client(Aws::Auth::AWSCredentials(
                                      awsAccessKeyId.c_str(),
                                      awsSecretAccessKey.c_str()),
                                  config);

        Aws::S3::Model::GetObjectRequest object_request;
        object_request.WithBucket(awsS3Bucket).WithKey(fileKey.c_str());

        auto getObjectOutcome = client.GetObject(object_request);

        if (getObjectOutcome.IsSuccess())
        {
            std::ofstream local_file;
            local_file.open(fileName, std::ios::out | std::ios::binary);
            local_file << getObjectOutcome.GetResult().GetBody().rdbuf();
            local_file.close();
        }
        else
        {
            std::cout << "GetObject failed! " << std::endl
                      << "\tException name: "
                      << getObjectOutcome.GetError().GetExceptionName() << std::endl
                      << "\tError message: "
                      << getObjectOutcome.GetError().GetMessage() << std::endl;
        }
    }
    Aws::ShutdownAPI(options);
    return fileName;
}

void AwsS3Helper::upload(const std::string& fileKey, const std::string& filePath)
{
    std::cout << "Uploading file " << filePath << " to " << fileKey << std::endl;
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration config;
        config.region = awsS3BucketRegion;
        Aws::S3::S3Client client =
                Aws::S3::S3Client(Aws::Auth::AWSCredentials(
                                      awsAccessKeyId.c_str(),
                                      awsSecretAccessKey.c_str()),
                                  config);

        Aws::S3::Model::PutObjectRequest object_request;
        object_request.WithBucket(awsS3Bucket).WithKey(fileKey.c_str());

        auto input_data = Aws::MakeShared<Aws::FStream>("PutObjectInputStream", filePath.c_str(),
                                                        std::ios_base::in | std::ios_base::binary);

        object_request.SetBody(input_data);

        auto pubObjectOutcome = client.PutObject(object_request);

        if (!pubObjectOutcome.IsSuccess())
        {
            std::cout << "PutObject failed! " << std::endl
                      << "\tException name: "
                      << pubObjectOutcome.GetError().GetExceptionName() << std::endl
                      << "\tError message: "
                      << pubObjectOutcome.GetError().GetMessage() << std::endl;
        }
    }
    Aws::ShutdownAPI(options);
}
