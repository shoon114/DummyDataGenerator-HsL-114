#include "JsonFileWriter.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace ddg
{
    JsonFileWriter::JsonFileWriter(std::string outDirectory)
        : outDirectory(std::move(outDirectory))
    {
    }

    std::string JsonFileWriter::write(const nlohmann::json& json, const std::string& fileName)
    {
        std::error_code ec;
        std::filesystem::create_directories(outDirectory, ec);
        if (ec)
        {
            throw std::runtime_error("출력 디렉토리를 생성할 수 없습니다: " + outDirectory + " (" + ec.message() + ")");
        }

        const std::filesystem::path filePath = std::filesystem::path(outDirectory) / fileName;

        std::ofstream file(filePath);
        if (!file.is_open())
        {
            throw std::runtime_error("JSON 파일을 열 수 없습니다: " + filePath.string());
        }

        file << json.dump(2);
        if (!file)
        {
            throw std::runtime_error("JSON 파일 저장에 실패했습니다: " + filePath.string());
        }

        return filePath.string();
    }
}
