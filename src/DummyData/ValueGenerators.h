#pragma once

#include <random>
#include <string>

#include "IValueGenerator.h"

namespace ddg
{
    class IntValueGenerator : public IValueGenerator
    {
    public:
        IntValueGenerator(int minValue = 0, int maxValue = 1000);

        DummyValue generate() override;

    private:
        std::mt19937 engine;
        std::uniform_int_distribution<int> distribution;
    };

    class FloatValueGenerator : public IValueGenerator
    {
    public:
        FloatValueGenerator(double minValue = 0.0, double maxValue = 1000.0);

        DummyValue generate() override;

    private:
        std::mt19937 engine;
        std::uniform_real_distribution<double> distribution;
    };

    class StringValueGenerator : public IValueGenerator
    {
    public:
        StringValueGenerator(size_t minLength = 5, size_t maxLength = 10);

        DummyValue generate() override;

    private:
        std::mt19937 engine;
        std::uniform_int_distribution<size_t> lengthDistribution;
        std::uniform_int_distribution<int> charDistribution;
    };

    class BoolValueGenerator : public IValueGenerator
    {
    public:
        BoolValueGenerator();

        DummyValue generate() override;

    private:
        std::mt19937 engine;
        std::bernoulli_distribution distribution;
    };
}
