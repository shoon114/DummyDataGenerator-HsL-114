#pragma once

#include <string>
#include <vector>

namespace ddg
{
    // Phase 1 출력: Phase 2(schema 구성)로 전달되는 raw 입력 데이터
    struct KeyInputEntry
    {
        std::string name;
        std::string typeName; // "int", "float", "string", "bool"
    };

    struct RawUserInput
    {
        std::vector<KeyInputEntry> keys;
        int itemCount = 0;
    };
}
