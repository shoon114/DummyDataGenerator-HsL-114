#pragma once

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "../Schema/KeyType.h"

namespace ddg
{
    // Phase 3 출력: Phase 4(JSON 저장)에서 사용하는 순수 내부 표현 (외부 library 타입에 의존하지 않음)
    struct DummyValue
    {
        KeyType type;
        std::variant<int, double, std::string, bool> value;
    };

    struct DummyItem
    {
        std::vector<std::pair<std::string, DummyValue>> fields; // key name -> value
    };

    struct DummyDataSet
    {
        std::vector<DummyItem> items;
    };
}
