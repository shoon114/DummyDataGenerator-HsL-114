#include "JsonConverter.h"

namespace ddg
{
    nlohmann::json JsonConverter::toJson(const DummyValue& value)
    {
        return std::visit([](const auto& v) -> nlohmann::json { return v; }, value.value);
    }

    nlohmann::json JsonConverter::toJson(const DummyItem& item)
    {
        nlohmann::json object = nlohmann::json::object();

        for (const auto& [name, value] : item.fields)
        {
            object[name] = toJson(value);
        }

        return object;
    }

    nlohmann::json JsonConverter::toJson(const DummyDataSet& dataSet)
    {
        nlohmann::json array = nlohmann::json::array();

        for (const auto& item : dataSet.items)
        {
            array.push_back(toJson(item));
        }

        return array;
    }
}
