# 세부 구현 계획 (Design)

[top-requirement.md](../requirement/top-requirement.md)에서 정의한 기능을 아래 4단계(Phase)로 나누어 구현한다.

| Phase | 내용 | 문서 |
| --- | --- | --- |
| Phase 1 | 사용자 console 입력 처리 | [phase1-console-input.md](phase1-console-input.md) |
| Phase 2 | 입력을 토대로 data schema 구성 | [phase2-schema-construction.md](phase2-schema-construction.md) |
| Phase 3 | schema에 맞는 dummy data 생성 | [phase3-dummy-data-generation.md](phase3-dummy-data-generation.md) |
| Phase 4 | dummy data를 JSON 파일로 저장 | [phase4-json-file-output.md](phase4-json-file-output.md) |

각 Phase는 이전 Phase의 결과물을 입력으로 받는 순차적인 pipeline 구조를 가진다.

```
Console Input --(Phase1)--> Raw Input
Raw Input     --(Phase2)--> Data Schema
Data Schema   --(Phase3)--> Dummy Data (in-memory)
Dummy Data    --(Phase4)--> JSON File (out/)
```
