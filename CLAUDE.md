# DummyDataGenerator

## 프로젝트 개요

다양한 형태의 JSON 기반 Dummy Data DB를 생성하는 C++ 프로그램.

"다양한 형태"의 의미:
- 각 item의 **key 목록**은 사용자가 콘솔 입력으로 직접 정의한다.
- 각 key에 대응하는 **value**는 program이 자동으로 임의의 값을 생성하여 채운다.

즉, 사용자가 데이터의 스키마(key 구조)를 정의하면, 프로그램은 그 스키마에 맞는 더미 데이터를 대량으로 생성해 JSON 형태의 DB로 출력하는 것이 핵심 동작이다.

구체적인 기능 요구사항은 [docs/requirement/top-requirement.md](docs/requirement/top-requirement.md)를 따른다.

## 현재 상태

Visual Studio C++ 프로젝트 스켈레톤만 존재하며, 실제 구현은 아직 시작 전 단계.

## Commit Message Rule

commit message 작성 규칙은 [docs/rule/commit-msg.md](docs/rule/commit-msg.md)를 따른다.

- `docs` 디렉토리 이하 변경이나 markdown 파일 수정은 독립적인 commit으로 분리하고 prefix `[DOCS]`를 사용한다.
- 기능 구현 commit은 prefix `[FEATURE]`를 사용한다.
