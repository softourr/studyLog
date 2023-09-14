# SA_04_Architecture Design

```
Overview
•   Architecture Design: What
•   Architecture Design: Who
•   Architecture Design: Why
•   Architecture Design: When
•   Architecture Design: Output
•   IEEE standard for software life cycle
```

## Architecture Design: What

🍷소프트웨어 디자인의 목표는 모든 고객의 요구사항을 충족하는 모델을 구축하는 것이다.🍷

- 아키텍처 디자인이란?
  - 소프트웨어의 major structural elements 간의 관계를 정의한다.
  - 시스템에 정의된 요구사항을 달성하기 위해 사용할 수 있는 아키텍처 스타일과 설계 패턴
  - 아키텍처 구현 방식에 영향을 미치는 제약조건, constraints
  - 아키텍처 디자인 representation은 시스템 요구 specification과 분석 모델에서 도출됨
    - 아키텍처를 그림, 다이어그램 등의 시각적 문서로 표현해 팀원 간 이해 도움

## Architecture Design: Who

> 누구에게 아키텍처 디자인의 책임이 있는가?

- 소프트웨어 아키텍처를 만드는 설계자와 디자이너는 소프트웨어 시스템 요구사항을 아키텍처 디자인으로 translate(map)한다.
- 그 과정에서 앱 도메인의 복잡성을 분할하고 정복해 소프트웨어 아키텍처를 해결하기 위한 다양한 디자인 전략을 적용한다.

## Architecture Design: Why

> 소프트웨어 아키텍처 디자인이 왜 그렇게 중요한가?

- 디자인이 제대로 안되면
  - 시스템 요구사항을 충족하지 못한다.
  - 이후 요구 사항 변경에 대응 못함
  - 재사용못함
  - 예측하지 못한 동작이나 오류 발생 가능
  - 성능 하락 등
- 아키테거 디자인 단계에서 위의 경우들에 대한 적절한 계획과 고민이 필요함. 그렇지 않으면 시간과 비용 소모가 비효율적
- 소프트웨어 아키텍처 디자인이 잘 되면
  - 소프트웨어 제작하면 생기는 위험을 방지
  - 구현 및 테스트에 용이
  - 높은 품질 소프트웨어 가능

## Architecture Design: When

> 소프트웨어 설계는 언제 이루어지는가?

### Software Development Lift Cycle (SDLC) 🍷

![img](https://velog.velcdn.com/images/3eung_h10n/post/f4bcadaf-85fa-4276-84ac-3480d655a954/image.png)



소프트웨어 개발 수명 주기

- software requirements analysis stage
- software design (architecture and detailed) stage (early phase)
- software development and implementation stage
- testing and quality assurance, maintenance, and evolution stage

## Architecture Design: Output

구축할 소프트웨어에 대한 전체적인 representation



## IEEE standard for software

![img](https://velog.velcdn.com/images/3eung_h10n/post/164d4201-dc0a-4581-af2c-a2ed5d9dcaca/image.png)



## Software Requirement Specification (SRS)

##### *디자인에 필요한 요구사항을 분석하는 방법*

- Requirement Modeling
  -  information domain modeling, data modeling 
  - function modeling, behavioral modeling
  - user interface modeling
- Requirement Description
  -  UML use-case specifications 
  - Data Flow Diagrams (DFD)
  - State Transition Diagrams (STD)
- 두 가지 측면
  - 기능 요구사항 : 소프트웨어 시스템의 기능성
  - 비기능 요구사항 : 시스템 품질, 제약 조건 및 동작









