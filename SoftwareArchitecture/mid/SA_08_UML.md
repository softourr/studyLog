# SA_08_UML

## UML

- UML은 OMG(Object Management Group) 표준이다.


- 소프트웨어 엔지니어링 분야의 범용적인 개발용 모델링 언어이다.
- 소프트웨어 개발 주기 전체를 지원한다.
- 다양한 다이어그램을 포함한다.

이용영역

- 요구사항 분석 단계에서 유즈케이스 다이어그램이 많이 사용됨
- domain concept model이나 software design을 기술하는데 class diagram을 많이 사용됨



## UML의 역사

![image](https://github.com/hhzzzk/studyLog/assets/67236054/748b5fd8-13c2-4141-abbe-36e36a4505c2)



## UML Diagrams

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9de3f230-355f-4a1a-bc7a-2da594146e94)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b35a2752-19e2-409f-94b8-132d2eaa37bf)



## UML 구성요소

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a4596fef-0d48-4cd5-b184-d662e0424763)



## 객체지향 모델 및 자원들간 관계

![image](https://github.com/hhzzzk/studyLog/assets/67236054/e7d0c110-4365-435a-ab82-a9dc5c93ca93)



## Use Case

- UML은 Use Case Diagram 표기법 정의
- Use Case 용도
  - provide a higher-level view of the system
  - 시스템의 기능 요구사항 이해
  - Use Case는 시스템의 외부 뷰 표현
  - Diagram보다는 텍스트 서술에 집중
- Use Case와 요구사항 관리
  - 시스템의 기능적 요구사항(functional requirements) 획득
  - 사용자와 시스템간의 상호작용 서술
  - 시스템이 어떻게 사용되는가를 이야기체로 서술

---

**Use Case**

- Usecase의 핵심은 시스템을 사용하는 사용자의 입장
- 공통적인 사용자 목표에 의해 묶인 시나리오들의 집합
- 내용이 잘 전달되어야 함

**액터(Actor)**

- 사용자가 시스템에 대해서 수행하는 역할
- 여러 사람이 하나의 액터로, 하나의 사람이 여러 액터로 맵핑 가능
- 액터가 반드시 사람일 수 도 있고 시스템일 수도 있음

**Flow of Events**

- 사용자와 시스템 간의 상호작용을 서술하는 일련의 스텝들
- 발생 가능한 Sequence 



##  Actor

**액터의 종류**

- 주 액터(primary actor)
  - Usecase의 주 목적을 가지고 있는 액터
  - Usecase를 주도적으로 접근함.
- 이차 액터(secondary actor)
  - Usecase 실행시키기 위해 시스템이 필요로 하는 지원하는 액터

**Flow of Events**

- 시스템과 액터 간의 상호작용 요소

**Use Case  레벨**

- 시스템 Usecase
  - 소프트웨어 시스템과의 상호작용 표현


- 비즈니스 Usecase
  - 비즈니스와  고객 또는 이벤트와의 상호작용 표현



## Use Case Diagram

- *blueprints for your system*
- a good communication tool for stakeholders
- Use Case들의 목차의 그래픽적인 테이블 표현
- 액터, Use Case, 액터와 Use Case 간의 관계(include, extend)로 구성
- 시스템의 사용에 대한 시나리오의 집합
- 사용자의 관점에서 시스템을 모델링 하기 위함
  - 사용자가 시스템에 대하여 바라는 바를 표현
- 대개 의뢰인과 개발팀이 참조하는 설계 문서의 한 부분으로 사용

![image](https://github.com/hhzzzk/studyLog/assets/67236054/059955ba-204f-489c-a056-ccdcf76269be)

**구성**

- 행위자 (Actor) 
  - 시스템과 교류하는 사람이나 시스템 또는 장치.
  - Use Case 를 시작시키고, Use Case가 끝나면 그 결과를 받음
- Use Case 
  - 시스템에서의 행위
  - Use Case 를 시작시킨 행위자는 왼쪽, 결과를 받는 행위자는 오른쪽에 표현.
- 시스템
  - Use Case 를 둘러싸는 사각형으로 표현.
  - 행위자는 대개 시스템 외부에 있는 반면, Use Case 는 시스템의 내부에 있다.

## Example

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fc03933a-f1e6-4398-b382-76d3772d6f88)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/e1dbd009-8075-4732-9fac-27ebf2f5dfae)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c53dad8a-32ed-42fe-bfae-25507ea6c817)



## Use Case Description

**구성요소**

- 이름 (Name)
- Actor 기술 (Description of Actor)
  - 요약 (Summary, Brief Description)
  - 역할 (Role)
- Usecase 기술 (Description of Usecases)
  - 요약 (Summary, Brief Description)
  - 사전조건 (Pre-condition)
  - 사후조건 (Post-condition)
  - 주 사건 흐름 (Main flow of event)
  - 대안 흐름 (Alternative flow)
  - 예외 흐름 (Exception flow)
  - 시나리오 (Scenario)
  - 기타
    - 비기능적 요구사항(Non-Functional Requirements)
    - 비즈니스 룰 (Business Rule)
    - 사용자 화면 (User Interface)



## Class Diagram

Class Diagram은 설계 시 가장 많이 사용되며  그 모델링 개념의 폭이 넓음

![image](https://github.com/hhzzzk/studyLog/assets/67236054/49f9ae15-0b20-4113-b83b-c555e61552be)



- **Class Diagram의 정의**
  - 객체 타입인 Class를 표현하는 Diagram.
  - Class의 속성(Attribute), 오퍼레이션(Operation), 연관관계(Association),  Generalization(일반화), Package등의 다른 Class와 사이의 다양한 정적인 관계를 표현
  - 정적 관계에 대한 제약 등을 표현



- **Class의 4가지 표현법**

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8d7375b6-e232-4472-b2fb-a39f7ecae663)