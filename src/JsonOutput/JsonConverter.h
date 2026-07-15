#pragma once

#include <nlohmann/json.hpp>

#include "../DummyData/DummyValue.h"

namespace ddg
{
    // docs/design/phase4-json-file-output.md 참고
    // 외부 JSON library(nlohmann/json) 의존성을 이 모듈 내부로 한정한다.
    class JsonConverter
    {
    public:
        nlohmann::json toJson(const DummyDataSet& dataSet);

    private:
        nlohmann::json toJson(const DummyValue& value);
        nlohmann::json toJson(const DummyItem& item);
    };
}
