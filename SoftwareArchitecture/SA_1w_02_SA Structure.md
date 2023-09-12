# SA_1w_02_SA Structure

## 리뷰

- 소프트웨어 아키텍처는 set of structures
- Structure is architectural if it supports __reasoning__ about the system and the system's __properties__.
- The Reasoning should be about an __attribute__ of the system that is important to some stakeholder



## Architecture is an Abstraction

- 아키텍처는 소프트웨어 elements와 그 관계로 구성됨
- how to deal with the __complexity__?
  - 아키텍처는 public side에 집중 (element's private는 not architectural)
- the __abstraction__ is essential to taming the __complexity__ of a system



## Architecture includes Behavior

- 각 element의 행동은 서로 상호작용하는 방법 반영함
- element의 행동은 다른 element나 시스템 전체에 영향끼침

> 이러한 행동은 소프트웨어 아키텍처의 일부로 고려되고 문서화돼야함



## Every Software System has a Software Architecture

- 모든 시스템은 시스템을 구성하는 elements들과 그 관계들로 이뤄짐
  - elements들과 그 관계들은 시스템의 reasoning에 도움됨
- 그러나, 아키텍처가 알려지지 않을 수 있음
  - 아키텍처는 description이나 specification과 독립적으로 존재 가능

> 아키텍처는 시스템의 본질적인 부분이지만 문서화되거나 명세화되지 않을 수 있음



# ※ Software Architecture Definition - 2

- 아키텍처는 시스템의 기본적인 구성 나타냄
  - 시스템의 components, 서로의 관계, 설계 및 진화의 원칙으로 구체화



## Goal of Software Architecture

![](https://velog.velcdn.com/images/vpdrnls/post/66c28075-52bf-4d9a-80a1-1ab168c4afcf/image.png)



- 최적화 optimization가 문제
- certain 파라미터가 결정돼야함
- 주어진 제약 조건에서 성능 최대화하기



## Common Aspects in Software Architecture Problem

- 문제에는 여러 해결책 존재. 가장 optimal solution 찾기
- N개의 목표와 그 측정법 존재
- Constraints의 종류
  - hard : 강제적으로 지켜야하는 제약
  - sotf : 최적화와 관련
- 영향 큰 주요 변수들
  - 이들 변경시 성능이나 constraints에 영향
  - 영향 변수 조정해 1. 성능최적화 + 2. constraints 만족하기



## 소프트웨어 개발

![](https://velog.velcdn.com/images/vpdrnls/post/d22c9124-7fa2-4771-9389-35212cf70c2e/image.png)



## SW 개발 패러다임 shift

![](https://velog.velcdn.com/images/vpdrnls/post/7307b1e1-f4df-4892-bc70-96b0e0fcdd1c/image.png)



## 소프트웨어 모델링 목적

![](https://velog.velcdn.com/images/vpdrnls/post/493bdc64-3c54-4b05-a64a-f04010780249/image.png)

