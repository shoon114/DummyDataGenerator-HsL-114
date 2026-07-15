# Phase 4. 생성된 Dummy Data를 JSON 파일로 저장하는 부분

## 목적

Phase 3에서 생성된 `DummyDataSet`(순수 내부 표현)을 JSON 형식으로 변환하고, `out` 디렉토리에 파일로 저장한다.

## 전제 조건

- JSON 표현/직렬화(CRUD API)는 **외부 library**를 사용하는 것으로 가정한다. (예: `nlohmann/json` 등)
- 본 프로젝트는 JSON parser/writer를 직접 구현하지 않고, 외부 library의 API를 wrapping하여 사용한다.

## 입력

Phase 3의 출력:

```cpp
struct DummyDataSet {
    std::vector<DummyItem> items;
};
```

## 처리 내용

1. **내부 표현 → 외부 JSON 타입 변환**
   - `DummyValue`의 `std::variant` 내용을 순회하며 외부 library의 JSON value 타입으로 매핑
     - `Int`/`Float`/`String`/`Bool` → 각각 대응하는 JSON 타입
   - `DummyItem`의 field 목록 → JSON object
   - `DummyDataSet`의 item 목록 → JSON array
   - 이 변환 로직은 `JsonConverter` (가칭) 모듈에서 전담하여, 외부 library 의존성을 이 모듈 내부로 한정한다.
2. **출력 디렉토리 확인/생성**
   - `out` 디렉토리가 없으면 생성 (예: `std::filesystem::create_directories`)
3. **파일 저장**
   - 파일명 규칙 결정 (예: 고정 파일명 `dummy_data.json` 또는 타임스탬프 기반 파일명)
   - 외부 library의 파일 쓰기 API(또는 stream 기반 출력)를 사용하여 `out/<filename>.json`에 저장
4. **결과 로그 출력**
   - 저장 완료 후 콘솔에 결과 경로와 생성된 item 개수를 출력

## 고려 사항

- 외부 JSON library API는 `JsonConverter` 모듈 뒤로 캡슐화하여, 추후 library 교체 시 이 모듈만 수정하면 되도록 설계한다. (다른 Phase는 외부 library 타입을 직접 알지 못하도록 유지)
- 대용량 item 생성 시 메모리에 전체 JSON을 올리는 대신 streaming 방식 저장이 필요할 수 있으나, 초기 구현은 in-memory 구성 후 일괄 저장 방식으로 단순화한다.
- 파일 저장 실패(디렉토리 권한, 디스크 공간 등) 시 예외 처리 및 사용자에게 오류 메시지 출력.
