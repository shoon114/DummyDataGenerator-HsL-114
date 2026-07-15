#include "ConsoleInputReader.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace ddg
{
    namespace
    {
        // std::getline이 실패(EOF/스트림 오류)한 경우 무한 재입력 루프에 빠지지 않도록 즉시 예외를 던진다.
        void checkStreamAlive(const std::istream& in)
        {
            if (!in)
            {
                throw std::runtime_error("입력 스트림이 종료되어 더 이상 값을 읽을 수 없습니다.");
            }
        }
    }

    const std::vector<std::string>& ConsoleInputReader::supportedKeyTypes()
    {
        static const std::vector<std::string> types = { "int", "float", "string", "bool" };
        return types;
    }

    int ConsoleInputReader::readPositiveInt(const std::string& prompt)
    {
        while (true)
        {
            std::cout << prompt;

            std::string line;
            std::getline(std::cin, line);
            checkStreamAlive(std::cin);

            std::istringstream iss(line);
            int value = 0;
            char extra;

            if ((iss >> value) && !(iss >> extra) && value >= 1)
            {
                return value;
            }

            std::cout << "1 이상의 정수를 입력해 주세요.\n";
        }
    }

    std::string ConsoleInputReader::readNonEmptyString(const std::string& prompt)
    {
        while (true)
        {
            std::cout << prompt;

            std::string line;
            std::getline(std::cin, line);
            checkStreamAlive(std::cin);

            const bool hasWhitespace = std::any_of(line.begin(), line.end(),
                [](unsigned char ch) { return std::isspace(ch) != 0; });

            if (!line.empty() && !hasWhitespace)
            {
                return line;
            }

            std::cout << "공백 없는 문자열을 입력해 주세요.\n";
        }
    }

    std::string ConsoleInputReader::readKeyType(const std::string& prompt)
    {
        const auto& types = supportedKeyTypes();

        while (true)
        {
            std::cout << prompt;

            std::string line;
            std::getline(std::cin, line);
            checkStreamAlive(std::cin);

            std::string lowered = line;
            std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            if (std::find(types.begin(), types.end(), lowered) != types.end())
            {
                return lowered;
            }

            std::cout << "지원하지 않는 type 입니다. 다음 중 하나를 입력해 주세요: ";
            for (size_t i = 0; i < types.size(); ++i)
            {
                std::cout << types[i] << (i + 1 < types.size() ? ", " : "\n");
            }
        }
    }

    RawUserInput ConsoleInputReader::readUserInput()
    {
        RawUserInput input;

        const int keyCount = readPositiveInt("생성할 key 개수를 입력하세요: ");

        while (static_cast<int>(input.keys.size()) < keyCount)
        {
            const int index = static_cast<int>(input.keys.size()) + 1;

            KeyInputEntry entry;
            entry.name = readNonEmptyString("Key #" + std::to_string(index) + " 이름을 입력하세요: ");

            const bool isDuplicate = std::any_of(input.keys.begin(), input.keys.end(),
                [&entry](const KeyInputEntry& existing) { return existing.name == entry.name; });

            if (isDuplicate)
            {
                std::cout << "이미 존재하는 key 이름입니다. 다시 입력해 주세요.\n";
                continue;
            }

            entry.typeName = readKeyType("Key #" + std::to_string(index) + " 타입을 입력하세요 (int/float/string/bool): ");

            input.keys.push_back(std::move(entry));
        }

        input.itemCount = readPositiveInt("생성할 총 item 개수를 입력하세요: ");

        return input;
    }
}
