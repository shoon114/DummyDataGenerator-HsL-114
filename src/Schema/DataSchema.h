#pragma once

#include <string>
#include <vector>

#include "KeyType.h"

namespace ddg
{
    // Phase 2 출력: Phase 3(dummy data 생성)에서 바로 사용하는 구조화된 schema
    struct KeySchema
    {
        std::string name;
        KeyType type;
    };

    struct DataSchema
    {
        std::vector<KeySchema> keys;
        int itemCount = 0;
    };
}
