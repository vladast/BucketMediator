#include <Mp3ToWavConverter.h>

#include <FileHelper.h>

std::string Mp3ToWavConverter::operator() (std::string mp3FilePath)
{
    std::string wavFilePath = mp3FilePath + ".wav";
    std::string soxCommand = std::string("sox") + " " + mp3FilePath + " " + wavFilePath;
    std::string soxOutput = FileHelper::Execute(soxCommand);
    std::cout << "SoX conversion output: '" << soxCommand << "'" << std::endl;
    return wavFilePath;
}
