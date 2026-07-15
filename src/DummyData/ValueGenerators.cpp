#include "ValueGenerators.h"

namespace ddg
{
    namespace
    {
        std::mt19937 makeSeededEngine()
        {
            std::random_device rd;
            return std::mt19937(rd());
        }

        const std::string& alphabet()
        {
            static const std::string chars =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            return chars;
        }
    }

    IntValueGenerator::IntValueGenerator(int minValue, int maxValue)
        : engine(makeSeededEngine())
        , distribution(minValue, maxValue)
    {
    }

    DummyValue IntValueGenerator::generate()
    {
        return DummyValue{ KeyType::Int, distribution(engine) };
    }

    FloatValueGenerator::FloatValueGenerator(double minValue, double maxValue)
        : engine(makeSeededEngine())
        , distribution(minValue, maxValue)
    {
    }

    DummyValue FloatValueGenerator::generate()
    {
        return DummyValue{ KeyType::Float, distribution(engine) };
    }

    StringValueGenerator::StringValueGenerator(size_t minLength, size_t maxLength)
        : engine(makeSeededEngine())
        , lengthDistribution(minLength, maxLength)
        , charDistribution(0, static_cast<int>(alphabet().size()) - 1)
    {
    }

    DummyValue StringValueGenerator::generate()
    {
        const size_t length = lengthDistribution(engine);

        std::string result;
        result.reserve(length);
        for (size_t i = 0; i < length; ++i)
        {
            result += alphabet()[charDistribution(engine)];
        }

        return DummyValue{ KeyType::String, result };
    }

    BoolValueGenerator::BoolValueGenerator()
        : engine(makeSeededEngine())
        , distribution(0.5)
    {
    }

    DummyValue BoolValueGenerator::generate()
    {
        return DummyValue{ KeyType::Bool, distribution(engine) };
    }
}
