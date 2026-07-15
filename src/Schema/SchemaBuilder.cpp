#include "SchemaBuilder.h"

#include <algorithm>
#include <stdexcept>
#include <unordered_set>

namespace ddg
{
    DataSchema SchemaBuilder::build(const RawUserInput& input)
    {
        if (input.itemCount < 1)
        {
            throw std::invalid_argument("총 item 개수는 1 이상이어야 합니다.");
        }

        DataSchema schema;
        schema.itemCount = input.itemCount;
        schema.keys.reserve(input.keys.size());

        std::unordered_set<std::string> seenNames;

        for (const auto& entry : input.keys)
        {
            if (!seenNames.insert(entry.name).second)
            {
                throw std::invalid_argument("중복된 key 이름입니다: " + entry.name);
            }

            const auto type = KeyTypeUtils::fromString(entry.typeName);
            if (!type.has_value())
            {
                throw std::invalid_argument("지원하지 않는 key type입니다: " + entry.typeName);
            }

            schema.keys.push_back(KeySchema{ entry.name, type.value() });
        }

        return schema;
    }
}
