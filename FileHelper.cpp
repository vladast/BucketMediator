#include <FileHelper.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string FileHelper::Execute(const std::string& command)
{
    std::string commandToProcess(command), commandOutput;
    const int bufferSize = 256;
    std::array<char, bufferSize> buffer;

    commandToProcess.append(" 2>&1");

    std::shared_ptr<FILE> pipe(popen(commandToProcess.c_str(), "r"), pclose);
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), bufferSize, pipe.get()) != nullptr)
        {
            commandOutput += buffer.data();
        }
    }
    return commandOutput;
}
