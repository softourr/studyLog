# SA_05_아키텍처 디자인 Guidelines

```
Overview
•   Software Architect's Tasks
•   Definition of Architecture Styles
•   Consider Quality Attributes > in the next lecture!
•   Software Architecture Design Guidelines
•   Models for Software Architecture
```

## Software Architect's Tasks

- 시스템을 정적 *분할* 및 sub시스템으로 decomposition. subsystem간 통신 수행
- 데이터 흐름, 제어 흐름 조정 또는 메시지 발송 측면에서 *서로 다른 서브시스템 사이에 동적 제어관계를 설정*
- 아키텍처 스타일을 선택하는 동안 품질 속성 및 기타 비기능 요구사항에 대한 tradeoff 분석

## Definition of Architecture Styles

유사한 디자인 그룹의 공통 속성 properties를 abstract, 추상화한다.

- 시스템을 elements와 connectors의 집합으로 structure하는 방법에 대한 규칙, 제약 조건 및 패턴을 포함한다.
- 구성 요소 유형의 전반적인 디자인 패턴 및 흐름 제어 및 데이터 전송의 런타임 상호작용을 제어한다.
  - 구성요소들이 런타임시 어떻게 상호작용하며 데이터 흐름과 제어흐름 조정을 포함한다.

### Key components of an architecture style 

- Elements : 시스템에 필요한 기능을 수행하는 요소
- Connectors : elements 사이의 의사소통, 조정, 협력을 가능하게 하는 커넥터
- Constraints : elements를 통합해 시스템을 구성하는 방법의 정의
- Attributes : 선택한 structure의 장단점을 설명하는 속성

## 🍒Software Architecture Design Guidelines 🍒

how to do 보다 what to do 고민하기. 무엇을 해야할지 먼저 고민하기

- 아키텍처 및 세부 디자인 작업 수행 전에 기능적 및 비기능적 요구사항 식별, 검증해야함

구체적인 디자인 생각하기 전에 추상적으로 고민

- 구성 요소의 인터페이스와 추상 데이터 유형을 지정하는 추상 디자인부터 시작하기.

디자인 프로세스 초기에 비기능적 요구사항 생각해보기

- 기능적 요구사항을 아키텍처 디자인에 매핑할 때는 비기능적 요구사항도 고려하기.

소프트웨어 재사용성과 확장성을 가능한 많이 생각하기

- 새로운 시스템의 신뢰성와 비용 효율성을 높이기 위해 기존 소프트웨어 구성 요소를 재사용하는 방법도 고려하자.

각 element 안에서 높은 응집력 cohesion과 element 사이의 결합을 높이기

? Tolerate refinement of design

- 잦은 수정을 견딜 수 있도록 디자인하기.

애매모호한 설계와 지나치게 상세한 설계는 피합니다.

- 모호한 설계는 제약 조건이 부족하고 과도한 세부 설계는 구현을 제한합니다.

## Models for Software Architecture

> 소프트웨어 아키텍처는 소프트웨어 시스템을 높은 수준으로 추상화한다.
>
> 즉 소프트웨어 시스템을 단순화된 개념으로 표현하고 이해하기 쉽도록 한다. 이런 추상화는 분해, 구성, 아키텍처 스타일 및 품질 속성을 사용해 이루어진다.

- 소프트웨어 시스템을 구성하는 요소들을 나누고, 그 요소들을 조합해 특정 아키텍처 스타일과 품질 속성을 고려해 소프트웨어 시스템을 디자인한다.

### 소프트웨어 아키텍처에서 기술하는 것

- 컴포넌트들의 집합 및 이들 컴포넌트 간의 연결
  - 어떤 구성 요소들로 시스템이 이뤄져 있고, 이들이 서로 어떻게 상호작용하는지 설명
- 모든 컴포넌트와 연결의 배치 구성
  - 이러한 컴포넌트와 연결이 실제로 어떻게 배치, 연결되어 있는지 정의
- 프로젝트의 기능적 및 비기능적 요구사항을 준수.
  - 프로젝트에서 정의된 기능적인 요구사항뿐만 아니라 성능, 보안, 확장성 등과 같은 비기능적 요구사항도 충족시키는 디자인 추구

## Ways to describe Software Architecture

- Box and Line 다이어그램
  - 박스로 비즈니스 개념 선으로 구성 요소 간의 관계를 표현
- UML
  - 소프트웨어 설계와 문서화를 위한 표준화된 모델링 언어
  - 정적, 동적 다이어그램으로 나뉨
- 아키텍처 뷰 모델(4+1뷰 모델)
  - 4+1뷰 모델
  - 논리, 프로세스, 개발, 구현, 사용사례 뷰로 구성
- ADL(Architecture Description Language, ADL)
  - ADL은 소프트웨어 아키텍처를 형식적이고 의미론적으로 설명하는데 사용
  - 정확하고 포괄적인 문서화 및 이해를 도움