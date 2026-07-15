# Commit Message Rule

## 기본 원칙

- `docs` 디렉토리 이하 변경 사항이나 markdown 파일 수정 사항은 **독립적인 commit**으로 분리하여 생성한다.
  - 코드 변경과 문서 변경을 같은 commit에 섞지 않는다.
- 기능 구현과 관련된 commit은 별도의 prefix로 구분한다.

## Prefix 규칙

| Prefix | 대상 |
| --- | --- |
| `[DOCS]` | `docs` 디렉토리 이하 변경, markdown 파일 변경 |
| `[FEATURE]` | 기능 구현 commit |

## 예시

```
[DOCS] requirement: top requirement 작성
[FEATURE] JSON schema 파서 구현
```
