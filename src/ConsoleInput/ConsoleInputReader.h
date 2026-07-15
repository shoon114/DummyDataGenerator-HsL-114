#pragma once

#include <string>
#include <vector>

#include "RawUserInput.h"

namespace ddg
{
    // docs/design/phase1-console-input.md 참고
    // 사용자로부터 dummy data 생성에 필요한 원시 입력을 console을 통해 받아온다.
    class ConsoleInputReader
    {
    public:
        RawUserInput readUserInput();

    private:
        int readPositiveInt(const std::string& prompt);
        std::string readNonEmptyString(const std::string& prompt);
        std::string readKeyType(const std::string& prompt);

        static const std::vector<std::string>& supportedKeyTypes();
    };
}
