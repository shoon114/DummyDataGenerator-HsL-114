#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace ddg
{
    // docs/design/phase4-json-file-output.md 참고
    // out 디렉토리 생성 및 JSON 파일 저장을 담당한다.
    class JsonFileWriter
    {
    public:
        explicit JsonFileWriter(std::string outDirectory = "out");

        // 저장된 파일의 전체 경로를 반환한다. 디렉토리 생성/파일 쓰기 실패 시 std::runtime_error를 던진다.
        std::string write(const nlohmann::json& json, const std::string& fileName);

    private:
        std::string outDirectory;
    };
}
