#pragma once

#include "DummyValue.h"

namespace ddg
{
    // KeyType별 임의값 생성기 interface. 확장 시 이 interface를 구현하는 타입만 추가하면 된다.
    class IValueGenerator
    {
    public:
        virtual ~IValueGenerator() = default;
        virtual DummyValue generate() = 0;
    };
}
