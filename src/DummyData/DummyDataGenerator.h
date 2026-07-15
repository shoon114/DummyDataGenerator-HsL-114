#pragma once

#include <memory>
#include <unordered_map>

#include "../Schema/DataSchema.h"
#include "DummyValue.h"
#include "IValueGenerator.h"

namespace ddg
{
    // docs/design/phase3-dummy-data-generation.md 참고
    // DataSchema를 기반으로 KeyType별 IValueGenerator를 사용해 DummyDataSet을 생성한다.
    class DummyDataGenerator
    {
    public:
        DummyDataGenerator();

        DummyDataSet generate(const DataSchema& schema);

    private:
        IValueGenerator& generatorFor(KeyType type);

        std::unordered_map<KeyType, std::unique_ptr<IValueGenerator>> generators;
    };
}
