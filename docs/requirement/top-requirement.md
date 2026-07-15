# Top Requirement

## 개요

사용자가 콘솔 입력을 통해 item의 key 구성(schema)을 정의하면, program은 해당 schema에 맞는 임의의 값을 채운 dummy data를 생성하여 JSON 파일로 출력한다.

## Program Input (Console)

사용자로부터 다음 정보를 콘솔 입력으로 받는다.

1. **Key 개수**: item 하나가 가지는 key의 총 개수
2. **Key 구성**: key 개수만큼 반복하여 아래 정보를 입력받음
   - **Key Name**: key의 이름 (문자열)
   - **Key Type**: key의 값 타입 (예: 정수, 실수, 문자열, boolean 등)
3. **총 item 개수**: 생성할 dummy data item의 총 개수

## Program Output

- 출력 위치: `out` 디렉토리
- 출력 형식: JSON 파일
- 파일 내용: 사용자가 정의한 key 구성에 따라, 각 key의 type에 맞는 임의의 값이 채워진 item이 사용자가 지정한 총 개수만큼 생성됨

## 처리 흐름

1. 콘솔에서 key 개수를 입력받는다.
2. key 개수만큼 반복하여 각 key의 이름과 타입을 입력받아 schema를 구성한다.
3. 생성할 총 item 개수를 입력받는다.
4. 구성된 schema를 기반으로, 각 key type에 맞는 임의의 값을 생성하여 item 개수만큼 반복 생성한다.
5. 생성된 전체 item 목록을 JSON 형식으로 `out` 디렉토리에 파일로 저장한다.
