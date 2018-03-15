#include <RestRequestProcessor.h>
#include <FileInfo.h>
#include <Mp3ToWavConverter.h>
#include <AudioInfoSerializer.h>
#include <FileSizeInfoSerializer.h>
#include <iostream>

HttpResponse RestRequestProcessor::operator() (RestRequestParams restRequestParams)
{
    HttpResponse httpResponse;
    if (restRequestParams.GetApi() == "/wav-info")
    {
        std::cout << "Processing wav-info request..." << std::endl;
        // expecting only 'wavkey' param
        if (restRequestParams.GetParamsCount() == 1)
        {
            std::string wavkey = restRequestParams.GetParamValue("wavkey");
            if (wavkey == "")
            {
                httpResponse.SetStatusCode(403);
                httpResponse.SetMessageBody("Invalid request!");
            }
            else
            {
                // Received 'valid' S3 file key
                std::string fileName = awsS3Helper.download(wavkey);
                std::cout << "File downloaded to: " << fileName << std::endl;

                FileInfo fileInfo(fileName);
                AudioInfoSerializer audioInfoSerializer;
                std::string messageBody = fileInfo.Serialize(audioInfoSerializer);

                std::cout << "Message Body: " << messageBody << std::endl;

                httpResponse.SetStatusCode(200);
                httpResponse.SetMessageBody(messageBody);
            }
        }
        else
        {
            httpResponse.SetStatusCode(403);
            httpResponse.SetMessageBody("Invalid request!");
        }
    }
    else if (restRequestParams.GetApi() == "/mp3-to-wav")
    {
        if (restRequestParams.GetParamsCount() == 2)
        {
            std::string wavkey = restRequestParams.GetParamValue("wavkey");
            std::string mp3key = restRequestParams.GetParamValue("mp3key");

            if (wavkey == "" || mp3key == "")
            {
                httpResponse.SetStatusCode(403);
                httpResponse.SetMessageBody("Invalid request!");
            }
            else
            {
                // Download MP3 file
                std::string mp3FileName = awsS3Helper.download(mp3key);
                std::cout << "MP3 File downloaded to: " << mp3FileName << std::endl;

                // Convert MP3 to WAV
                Mp3ToWavConverter converter;
                std::string wavFileName = converter(mp3FileName);

                // Upload WAV file
                awsS3Helper.upload(wavkey, wavFileName);

                FileInfo wavFileInfo(wavFileName);
                FileSizeInfoSerializer fileSizeInfoSerializer;
                std::string messageBody = wavFileInfo.Serialize(fileSizeInfoSerializer);

                std::cout << "Message Body: " << messageBody << std::endl;

                httpResponse.SetStatusCode(200);
                httpResponse.SetMessageBody(messageBody);
            }
        }
        else
        {
            httpResponse.SetStatusCode(403);
            httpResponse.SetMessageBody("Invalid request!");
        }
    }
    else
    {
        httpResponse.SetStatusCode(403);
    }
    return httpResponse;
}
