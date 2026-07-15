#include "KeyType.h"

namespace ddg::KeyTypeUtils
{
    std::optional<KeyType> fromString(const std::string& typeName)
    {
        if (typeName == "int") return KeyType::Int;
        if (typeName == "float") return KeyType::Float;
        if (typeName == "string") return KeyType::String;
        if (typeName == "bool") return KeyType::Bool;

        return std::nullopt;
    }

    std::string toString(KeyType type)
    {
        switch (type)
        {
        case KeyType::Int: return "int";
        case KeyType::Float: return "float";
        case KeyType::String: return "string";
        case KeyType::Bool: return "bool";
        }

        return "unknown";
    }
}
