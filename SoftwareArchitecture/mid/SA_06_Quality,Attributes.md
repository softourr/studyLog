# SA_06_Quality,Attributes

# Quality(품질)🍪

제품 또는 서비스의 품질?

- 제품 또는 서비스가 사용자 또는 고객의 요구사항(명시적 또는 묵시적)을 얼마나 만족시키는지에 영향을 미치는 모든 특징과 특성들.



## 품질속성  (Quality Attribute)

품질속성이란 양이나 질로 관찰하여 수치로 측정할 수 있는 시스템의 특성이다.

- 품질속성은 이해관계자들이 관심사와 요구사항을 그대로 반영
- 아키텍처는 이해관계자들이 원하는 수준으로 품질속성을 달성해야 함.

```
품질속성은 제품 또는 서비스의 품질을 측정하고 평가하는데 사용되는 특정 특성 또는 속성을 나타낸다. 
이러한 속성은 제품 또는 서비스가 특정 목표나 기준을 어떻게 충족시키는지를 정량/정성 적으로 나타내며 
사용자의 요구사항과 기대치를 충족시키는데 중요한 역할을 한다.
```



## Quality Attributes🍪🍪

품질속성은 시스템의 비기능적 요구사항의 중요한 부분이다.

시스템의 *측정 가능하거나 테스트 가능한 특성*, 시스템이 이해관계자의 요구사항을 얼마나 잘 만족시키는지를 나타내는데 사용한다.

시스템 분석가는 상세한 디자인 프로세스가 시작되기 전에 품질 속성의 목록을 작성해야 한다. 



## Quality Attributes in Implementation

### Implementation attributes (not observable at runtime) 실행 중에는 관찰 불가능한 구현 특성

- Interoperability 상호 운용성
  - 시스템 내부 구성 요소 간에 데이터를 교환하고 서로 접근하는 능력. 시스템의 부분들이 서로 호환되고 데이터를 공유하도록 하는 특성
- Maintainability and extensibility 유지보수성과 확장성
  - 시스템을 수정하고 편리하게 확장하는 능력
  - 시스템을 변경하고 더 많은 기능 추가가 용이함. 새로운 요구 사항 대응에 효과적인 특성
- Testability 테스트 가능성
  - 시스템이 테스트 과정을 쉽게 수행할 수 있는 정도. 테스트 가능한 시스템은 결함을 식별하고 수정하는데 도움이 된다.
- Portability 이식성
  - 소프트웨어 및 하드웨어 플랫폼에 대한 시스템의 독립 수준
  - 시스템이 다양한 환경에서 실행될 수 잇는 능력. 여러 플랫폼에 이식 가능한 시스템.
- Scalability 확장성
  - 시스템이 사용자 요청의 증가할 때 확장하는 능력.
  - 시스템이 더 많은 트래픽을 처리하고 성능을 유지하는데 도움.
- Flexibility 유연성
  - 시스템을 쉽게 수정할 수 있어 여러 환경이나 새로운 문제(처음 설계된 목적 이외)에 대응하는 능력. 
  - 시스템의 적응성을 높이고 다양한 상황에 유용.

## Quality Attributes in Runtime

### Runtime attributes (observable at runtime) 실행 중 관찰 가능한 런타임 특성

- Availability 가용성 : 시스템을 24/7 사용 가능한 능력. 사용자가 언젠든지 시스템에 접근하고 이용 가능하다.
- Security 보안 : 시스템이 외부/내부의 악의적인 공격에 대처하는 능력. 시스템이 공격에 대응하고 데이터 및 기능을 보호한다.
- Performance 성능 : 응답시간, 처리량 및 자원 이용 측면에서 시스템의 효율성을 향상시키는 능력. 시스템이 효율적으로 동작한다.
- Usability 사용성 : 시스템 사용에 대한 인간의 만족도 수준. 사용자가 시스템을 이용해 편리하고 만족스러운 정도.
- Reliability 신뢰성 :  고장 빈도, 출력 결과의 정확성, 고장까지의 평균 시간 (Mean-Time-to-Failure (MTTF)), 고장 복구 능력 및 고장 예측성
- Maintainability (extensibility, adaptability, serviceability, testability, compatibility, and configurability)
  - 유지보수성 (확장성, 적응성, 서비스 가능성, 테스트 가능성, 호환성, 설정 가능성): 소프트웨어 시스템 변경의 용이성
  - 시스템 변경이 쉽고 유지 관리에 도움이 됨. 새로운 요구사항에 대응도 용이. 테스트, 호환성 등 다룸



## Quality Attributes in Business needs

### Business attributes

- TIme to market 출시까지 걸리는 시간 : 요구 사항 분석부터 제품 출시일까지 걸리는 시간
- Cost 비용 : 시스템을 구축, 유지 관리 및 운영하는데 필요한 지출
- Lifetime 수명 : 제품이 폐기되기 전까지 살아있는 기간



## Typical quality attribute tradeoff pairs

> Tradeoff between reliability and performance

신뢰성과 성능간의 균형 맞춤. 높은 신뢰성 얻기 위해 일부 성능 저하 발생가능함. 이 때 발생하는 개념

>Tradeoff between scalability and performance

확장성과 성능간의 균형 맞춤. 시스템을 더 확장하면 많은 사용자를 지원할 수 있지만 일부 성능 저하 가능. 이때 발생하는 개념