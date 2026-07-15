#pragma once

#include "../ConsoleInput/RawUserInput.h"
#include "DataSchema.h"

namespace ddg
{
    // docs/design/phase2-schema-construction.md 참고
    // RawUserInput(raw 문자열 기반 입력)을 해석하여 DataSchema를 구성한다.
    class SchemaBuilder
    {
    public:
        // 유효하지 않은 입력(중복 key 이름, 지원하지 않는 type 등)이면 std::invalid_argument를 던진다.
        DataSchema build(const RawUserInput& input);
    };
}
