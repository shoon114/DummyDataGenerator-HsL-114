#include <iostream>
#include <string>
#include <type_traits>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ConsoleInput/ConsoleInputReader.h"
#include "DummyData/DummyDataGenerator.h"
#include "JsonOutput/JsonConverter.h"
#include "JsonOutput/JsonFileWriter.h"
#include "Schema/SchemaBuilder.h"

namespace
{
    std::string toDisplayString(const ddg::DummyValue& value)
    {
        return std::visit(
            [](const auto& v) -> std::string
            {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, bool>)
                {
                    return v ? "true" : "false";
                }
                else if constexpr (std::is_same_v<T, std::string>)
                {
                    return v;
                }
                else
                {
                    return std::to_string(v);
                }
            },
            value.value);
    }
}

int main()
{
#ifdef _WIN32
    // 소스 파일이 UTF-8로 저장되어 있으므로, 콘솔 출력도 UTF-8 코드페이지로 맞춘다.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try
    {
        ddg::ConsoleInputReader reader;
        const ddg::RawUserInput input = reader.readUserInput();

        ddg::SchemaBuilder schemaBuilder;
        const ddg::DataSchema schema = schemaBuilder.build(input);

        std::cout << "\n--- 구성된 Data Schema (Phase 2) ---\n";
        for (const auto& key : schema.keys)
        {
            std::cout << "- " << key.name << " : " << ddg::KeyTypeUtils::toString(key.type) << "\n";
        }
        std::cout << "총 item 개수: " << schema.itemCount << "\n";

        ddg::DummyDataGenerator dummyDataGenerator;
        const ddg::DummyDataSet dataSet = dummyDataGenerator.generate(schema);

        constexpr size_t previewCount = 5;
        std::cout << "\n--- 생성된 Dummy Data 미리보기 (Phase 3, 최대 " << previewCount << "개) ---\n";
        for (size_t i = 0; i < dataSet.items.size() && i < previewCount; ++i)
        {
            std::cout << "[" << i << "] ";
            const auto& fields = dataSet.items[i].fields;
            for (size_t f = 0; f < fields.size(); ++f)
            {
                std::cout << fields[f].first << "=" << toDisplayString(fields[f].second);
                if (f + 1 < fields.size())
                {
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "총 생성된 item 개수: " << dataSet.items.size() << "\n";

        ddg::JsonConverter jsonConverter;
        const nlohmann::json json = jsonConverter.toJson(dataSet);

        ddg::JsonFileWriter jsonFileWriter;
        const std::string savedPath = jsonFileWriter.write(json, "dummy_data.json");

        std::cout << "\n--- JSON 파일 저장 (Phase 4) ---\n";
        std::cout << "저장 경로: " << savedPath << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "오류: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
