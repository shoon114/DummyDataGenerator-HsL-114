# Phase 3. 정의된 Data Schema에 맞게 Dummy Data를 생성해내는 부분

## 목적

Phase 2에서 구성된 `DataSchema`를 기반으로, 각 key의 `KeyType`에 맞는 임의의 값을 생성하여 `itemCount`개의 item으로 이루어진 in-memory dummy data 집합을 만든다.

## 입력

Phase 2의 출력:

```cpp
struct KeySchema {
    std::string name;
    KeyType type;
};

struct DataSchema {
    std::vector<KeySchema> keys;
    int itemCount;
};
```

## 처리 내용

1. **Type별 임의값 생성기(Value Generator) 정의**
   - `KeyType::Int` → 지정 범위 내 임의 정수 생성
   - `KeyType::Float` → 지정 범위 내 임의 실수 생성
   - `KeyType::String` → 임의 길이/문자로 구성된 문자열 생성 (또는 사전 정의된 단어 조합)
   - `KeyType::Bool` → true/false 임의 생성
   - 각 type에 대해 `IValueGenerator` interface + type별 구현체(`IntValueGenerator`, `FloatValueGenerator`, ...)로 설계하여 확장성 확보
2. **Item 생성 반복**
   - `itemCount`만큼 반복하며, 매 반복마다 `DataSchema.keys`를 순회하여 각 key에 대응하는 값을 생성
   - 하나의 item은 key-value 목록으로 구성 (`DummyItem`)
3. **전체 데이터 집합 구성**
   - 생성된 item들을 모아 `DummyDataSet`으로 보관

## 출력 (다음 Phase로 전달되는 데이터)

```cpp
struct DummyValue {
    KeyType type;
    // 실제 값은 std::variant<int, double, std::string, bool> 등으로 보관
    std::variant<int, double, std::string, bool> value;
};

struct DummyItem {
    std::vector<std::pair<std::string, DummyValue>> fields; // key name -> value
};

struct DummyDataSet {
    std::vector<DummyItem> items;
};
```

## 고려 사항

- 난수 생성은 `<random>`의 mt19937 등 균일한 난수 엔진을 사용하고, 매 실행마다 다른 시드를 사용할지(완전 랜덤) 또는 고정 시드를 지원할지(재현 가능한 테스트용)는 별도 옵션으로 열어둔다.
- Value Generator를 schema 해석 로직과 분리해두면, 추후 "범위 지정", "커스텀 값 목록" 등 생성 규칙 확장 시 Phase 2/3 구조 변경 없이 Generator만 추가하면 된다.
- `DummyDataSet`은 JSON 라이브러리 종속 타입을 포함하지 않는 순수 내부 표현으로 유지하여, Phase 4에서 JSON 변환 시에만 외부 library 타입으로 매핑한다.
