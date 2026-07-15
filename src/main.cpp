#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ConsoleInput/ConsoleInputReader.h"

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

        std::cout << "\n--- 입력 결과 (Phase 1) ---\n";
        for (const auto& key : input.keys)
        {
            std::cout << "- " << key.name << " : " << key.typeName << "\n";
        }
        std::cout << "총 item 개수: " << input.itemCount << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "오류: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
