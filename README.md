<img src="https://github.com/hhzzzk/studyLog/assets/67236054/2800b1ac-11c9-4da4-86b2-5f80f96c03b5" width="600" height="300" alt="Your Image" />


# 👁️‍🗨️ studyLog
공부 정리



# 🐤 univ

[`인공지능`](https://github.com/hhzzzk/studyLog/tree/main/AI)

[`컴퓨터비전`](https://github.com/hhzzzk/studyLog/tree/main/ComputerVision)

[`소프트웨어아키텍처`](https://github.com/hhzzzk/studyLog/tree/main/SoftwareArchitecture)

[`정보보호와시스템보안`](https://github.com/hhzzzk/studyLog/tree/main/SystemSecurity)

[`데이터과학`](https://github.com/hhzzzk/studyLog/tree/main/DataScience)

# Book&Lec

# CodingTest

# 🌲Commit MSG Rule

1. 제목과 본문을 **빈 행으로 구분**한다.
2. 제목은 **50글자** 이내로 제한한다.
3. 제목의 **첫 글자는 대문자**로 작성한다.
4. 제목 끝에는 **마침표를 넣지 않는다**.
5. 제목은 **명령문**으로 사용하며 **과거형을 사용하지 않는다**.
6. 본문의 **각 행은 72글자 내**로 제한한다.
7. 어떻게 보다는 **무엇과 왜를 설명**한다.



## Commit MSG Structure

```
// Header, Body, Footer는 빈 행으로 구분한다.
타입(스코프): 주제(제목) // Header(헤더) > 필수, 스코프 생략 가능

본문 // Body(바디) > 상세 내용

바닥글 // Footer > 이슈 참조 정보 ex:Issues #999
```

**타입(scope) 종류**

| 타입 이름    | 내용                               |
| -------- | -------------------------------- |
| feat     | 새로운 기능(feature)에 대한 커밋           |
| fix      | 버그 수정에 대한 커밋                     |
| build    | 빌드 관련 파일 수정 / 모듈 설치 또는 삭제에 대한 커밋 |
| chore    | 그 외 자잘한 수정에 대한 커밋 ex) .gitignore |
| ci       | ci 관련 설정 수정에 대한 커밋               |
| docs     | 문서 수정에 대한 커밋                     |
| style    | 코드 스타일 혹은 포맷 등에 관한 커밋            |
| refactor | 코드 리팩토링에 대한 커밋 ex) 변수 이름 변경      |
| test     | 테스트 코드 추가/수정                     |
| perf     | 성능(performance) 개선에 대한 커밋        |

- Commit Message에 "#[Issue Number]"를 입력하게 될 경우 자동으로 이슈에 커밋 내용을 추가

  > \#999 - 기능 수정

이슈 Close 하는 Keyword

- close

- closes

- closed

- fix

- fixes

- fixed

- resolve

- resolves

- resolved

  > close #999 - 오류 해결, 이슈닫음

[참고](https://velog.io/@chojs28/Git-%EC%BB%A4%EB%B0%8B-%EB%A9%94%EC%8B%9C%EC%A7%80-%EA%B7%9C%EC%B9%99)