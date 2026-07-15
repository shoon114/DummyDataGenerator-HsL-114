# Phase 2. 사용자 입력을 토대로 Data Schema를 구성하는 부분

## 목적

Phase 1에서 전달받은 `RawUserInput`(raw 문자열 기반 입력)을 해석하여, 이후 dummy data 생성(Phase 3)에서 바로 사용할 수 있는 구조화된 `DataSchema`를 만든다.

## 입력

Phase 1의 출력:

```cpp
struct KeyInputEntry {
    std::string name;
    std::string typeName;
};

struct RawUserInput {
    std::vector<KeyInputEntry> keys;
    int itemCount;
};
```

## 처리 내용

1. **Type 문자열 → Type Enum 변환**
   - `typeName` 문자열(`"int"`, `"float"`, `"string"`, `"bool"` 등)을 내부 enum `KeyType`으로 변환한다.
   - 알 수 없는 type은 Phase 1에서 이미 걸러졌다고 가정하지만, 방어적으로 재검증한다.
2. **Key 목록 무결성 검증**
   - key name 중복 여부 재확인
   - key 개수와 실제 입력된 key 목록 개수 일치 여부 확인
3. **DataSchema 객체 구성**
   - key 이름 + type 정보를 보유하는 `KeySchema` 목록
   - 생성할 item 총 개수 (`itemCount`)를 함께 보관

## 출력 (다음 Phase로 전달되는 데이터)

```cpp
enum class KeyType {
    Int,
    Float,
    String,
    Bool,
};

struct KeySchema {
    std::string name;
    KeyType type;
};

struct DataSchema {
    std::vector<KeySchema> keys;
    int itemCount;
};
```

## 고려 사항

- Type 확장(예: `date`, `enum` 등 추가 type)을 고려하여 `KeyType`을 enum class로 관리하고, type ↔ 문자열 매핑 테이블을 별도 유틸(`KeyTypeUtils`)로 분리한다.
- Phase 3(dummy data 생성)은 `DataSchema`만 알면 되고, 사용자의 원본 입력 형식(raw string 등)에 의존하지 않도록 계층을 분리한다.
