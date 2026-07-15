# Phase 1. 사용자 Console 입력 받는 부분

## 목적

사용자로부터 dummy data 생성에 필요한 원시 입력(raw input)을 console을 통해 받아온다. 이 단계에서는 입력값의 의미(schema 구성 등)를 해석하지 않고, 입력을 받아 검증하고 구조화된 형태로 다음 Phase에 전달하는 역할만 담당한다.

## 입력 시나리오

1. **Key 개수 입력**
   - 정수 1개 입력 (item이 가지는 key의 총 개수)
   - 1 이상의 정수인지 검증
2. **Key 정보 반복 입력** (Key 개수만큼 반복)
   - **Key Name**: 공백 없는 문자열, 동일 이름 중복 불가
   - **Key Type**: 지원하는 type 목록 중 하나 (예: `int`, `float`, `string`, `bool`)
     - 지원하지 않는 type 입력 시 재입력 요청
3. **총 item 개수 입력**
   - 정수 1개 입력 (생성할 dummy data item의 총 개수)
   - 1 이상의 정수인지 검증

## 처리 구조

- `ConsoleInputReader` (가칭) 클래스가 아래 책임을 담당한다.
  - 정수 입력 read + 검증 + 재입력 유도 (`readPositiveInt`)
  - 문자열 입력 read + 검증 (`readNonEmptyString`)
  - key type 입력 read + enum 변환 + 검증 (`readKeyType`)
- 입력 검증 실패 시 예외를 던지지 않고, 사용자에게 오류 메시지를 출력한 뒤 동일 항목을 재입력받는다. (프로그램 비정상 종료를 최소화)

## 출력 (다음 Phase로 전달되는 데이터)

Phase 2로 전달할 raw input 구조체:

```cpp
struct KeyInputEntry {
    std::string name;
    std::string typeName; // "int", "float", "string", "bool" 등 raw 문자열
};

struct RawUserInput {
    std::vector<KeyInputEntry> keys;
    int itemCount;
};
```

## 고려 사항

- 지원 type 목록은 Phase 2의 schema 구성 로직과 공유되어야 하므로, type 이름 상수는 공통 헤더에 정의하는 것을 고려한다.
- 콘솔 입력 방식은 향후 파일/설정 기반 입력으로 대체될 수 있으므로, 입력 소스를 추상화(interface)해두면 확장에 유리하다. (본 Phase에서는 console 구현체만 작성)
