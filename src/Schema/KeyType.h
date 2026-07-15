#pragma once

#include <optional>
#include <string>

namespace ddg
{
    enum class KeyType
    {
        Int,
        Float,
        String,
        Bool,
    };

    namespace KeyTypeUtils
    {
        // typeName 문자열을 KeyType으로 변환한다. 지원하지 않는 문자열이면 std::nullopt을 반환한다.
        std::optional<KeyType> fromString(const std::string& typeName);

        std::string toString(KeyType type);
    }
}
