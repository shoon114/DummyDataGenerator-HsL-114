#include "DummyDataGenerator.h"

#include <stdexcept>

#include "ValueGenerators.h"

namespace ddg
{
    DummyDataGenerator::DummyDataGenerator()
    {
        generators[KeyType::Int] = std::make_unique<IntValueGenerator>();
        generators[KeyType::Float] = std::make_unique<FloatValueGenerator>();
        generators[KeyType::String] = std::make_unique<StringValueGenerator>();
        generators[KeyType::Bool] = std::make_unique<BoolValueGenerator>();
    }

    IValueGenerator& DummyDataGenerator::generatorFor(KeyType type)
    {
        const auto it = generators.find(type);
        if (it == generators.end())
        {
            throw std::invalid_argument("지원하지 않는 KeyType에 대한 generator가 없습니다.");
        }

        return *it->second;
    }

    DummyDataSet DummyDataGenerator::generate(const DataSchema& schema)
    {
        DummyDataSet dataSet;
        dataSet.items.reserve(schema.itemCount);

        for (int i = 0; i < schema.itemCount; ++i)
        {
            DummyItem item;
            item.fields.reserve(schema.keys.size());

            for (const auto& key : schema.keys)
            {
                item.fields.emplace_back(key.name, generatorFor(key.type).generate());
            }

            dataSet.items.push_back(std::move(item));
        }

        return dataSet;
    }
}
