#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ConsoleInput/ConsoleInputReader.h"
#include "Schema/SchemaBuilder.h"

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
    }
    catch (const std::exception& e)
    {
        std::cerr << "오류: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
