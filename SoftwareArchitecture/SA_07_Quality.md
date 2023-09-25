# SA_07_Quality

## Product Quality Model 

### 품질모델

품질모델 구조

- Quility : 목표 시스템이 충족해야 할 품질
- Quility Factor : 사용자나 관리자 중심, 시스템이 외부에 보이는 품질
  - Characteristics(특징), Factors라고도 함
- Quility Subfactor
  - 구현자 중심
  - 시스템 내부에서 다루는 품질
  - Quility Factor를 측정할 수 있는 소프트웨어 속성으로 바꾼 것
  - Sub-characteristics(부 특성), Criteria라고도 함
- Metric
  - 평가자 중심
  - 품질을 측정하는 방법과 척도

![image](https://github.com/hhzzzk/studyLog/assets/67236054/2a116938-edfa-4e01-b822-0b197501a632)





## ISO/IEC 9126 품질모델

1998년도에 ISO와 IEC에 의해 제안된 품질 모델로서 소프트웨어 품질 인증을 위한 국제 표준

- 품질모델
  - 9126 품질 모델에서는 품질을 외부와 내부로 분리
  - 외부와 내부에 대해 각각 6개의 특징들을 명시
  - 각 특징들은 부 특성들로 나누어진다.
  - 각 특성들은 내부와 외부 Metrics에 의해서 측정

### ISO/IEC 9126 품질 모델 프레임워크

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a2d20d35-ed9f-4d5b-af48-68bee1bc29ec)

- Internal Metrics : 소프트웨어 개발 과정 중에 나오는 산출물을 측정하기 위해 이용
- External Mertrics : 개발이 완료된 소프트웨어 제품에 특성을 측정하기 위해서 이용

### ISO/IEC 9126

![image](https://github.com/hhzzzk/studyLog/assets/67236054/cdb2573e-4983-4e50-a94e-8f2ed7c2441b)



### Product’s View of Quality

![image](https://github.com/hhzzzk/studyLog/assets/67236054/aeb08ab4-e274-4545-9e7a-0ec3900860e2)



### ISO/IEC 9126

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c893c82d-91fb-4d4a-a605-f5e7464043b9)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/80a228dd-e77c-4e5a-a1ef-829c34073138)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/1d34ced7-5ecd-48f4-aa14-3ad5c5a13871)







## Quality Model

품질 모델은 소프트웨어 제품의 특성을 평가할 때 고려될 품질 특성을 결정합니다.

## Functional Suitability

- 제품, 시스템이 제시된 요구사항을 지정된 조건에서 사용할 때 어느 정도로 만족시키는 기능을 제공하는지를 나타냄
  - Functional Completeness(기능적 완성도)
    - 제시된 작업과 사용자의 요구사항을 처리하고 지원하는데 어느 정도로 완전한지
  - Functional Correctness(기능적 정확성)
    - 시스템이 정확하고 필요한 정밀도로 결과를 산출하는 데 어느정도로 정확한지
  - Functional Appropriateness(기능적 적절성)
    - 시스템의 기능이 명시된 작업과 목표를 효과적으로 수행하는지

## Performance efficiency

- 제시된 조건 하에서 사용된 자원 양에 대한 성능
  - Time Behavior(시간 동작)
    - 응답 및 처리 시간과 처리량 비율이 요구 사항을 얼마나 충족시키는지를 나타냄
  - Resource Utilization(자원 활용)
    - 기능을 수행하는 동안 사용되는 자원의 양과 유형이 요구 사항을 얼마나 충족시키는지
  - Capacity(용량)
    - 시스템이 가지는 최대 한계치(데이터 양, 연결 수등)을 얼마나 충족시키는지

## Compatibility

- 다른 제품, 시스템과 소프트웨어 환경을 공유하면서 정보를 교환하고 필요한 기능을 수행하는 능력
  - Co-existence(공존성)
    - 다른 제품들과 공통의 환경 및 자원을 공유하면서 필요한 기능을 수행할 수 있는 정도
  - Interoperability(상호 운용성)
    - 두 개 이상의 시스템이 정보를 교환하고 교환된 정보를 사용할 수 있는 정도

## Usability

- 사용자에게 만족도를 느끼게 하며 명시된 목표를 달성할 수 있는 정도
  - Appropriateness(적절성)
    - 사용자가 자신의 요구 사항을 시스템이 어느 정도로 만족 시켜주는지 인식할 수 있는 능력
  - Recognizability(인식성)
    - 사용자가 시스템을 보고 쉽게 알아볼 수 있는 능력
  - Learnability (학습성)
    - 사용자가 시스템을 사용하여 목표를 달성하고 학습하는 데 어느 정도로 효과적인지
  - Operability(운용성)
    - 제품 또는 시스템이 쉽게 작동하고 제어할 수 있는지
  - User Error Protection(사용자 오류 방지)
    - 사용자가 실수 하지 않도록 보호하는 정도
  - User Interface Aesthetics(사용자 인터페이스 미학성)
    - 인터페이스가 사용자에게 쾌적하고 만족스러운 상호 작용을 가능하게 하는 정도
  - Accessibility (접근성)
    - 다양한 사용자 그룹이 시스템을 사용할 수 있도록 하는 능력

## Reliability

- 시스템이 제시된 기간과 조건 하에서 제시된 기능을 어느 정도로 수행하는지
  - Maturity(성숙도)
    - 시스템이 정상적인 운영 상황에서 얼마나 안정되고 신뢰성 있게 작동하는지
  - Availability(가용성)
    - 시스템이 필요한 시점에 작동 가능하고 접근 가능한 정도
  - Fault Tolerance(고장 허용성)
    - 시스템이 하드웨어 또는 소프트웨어의 결함이 존재하는 상황에서도 의도대로 작동하는 정도, 시스템이 결함이 발생해도 중단 없이 작동하고 데이터 무결성을 보존하는 능력
  - Recoverability(복구성)
    - 시스템이 중단이나 장애 발생 시 영향을 받은 데이터를 복구하고 원하는 시스템 상태를 다시 설정할 수 있는 정도

## Security

- 정보와 데이터에 대한 엑세스 권한 유형 및 수준에 적절한 정도의 데이터 엑세스를 가지도록 하는 것
  - Confidentiality(기밀성)
    - 데이터에 대한 접근을 권한을 가진 사람들에게만 허용하고, 무단 엑세스로부터 데이터를 보호하는 정도
  - Integrity(무결성)
    - 데이터에 대한 무단 엑세스와 변경을 방지하는 정도
  - Non-repudiation(부인 방지)
    - 행동 또는 이벤트가 발생하였을때 나중에 반박할 수 없도록 증명할 수 있는 정도
  - Accountability(책임 추적성)
    - 엔티티의 행동이 고유하게 추적될 수 있는 정도, 특정 엔티티(사용자)의 행동을 추적하고 책임을 할당할 수 있는 능력
  - Authenticity(인증성)
    - 특정 주체나 자원이 자신이 주장한 정체성과 일치하는지를 확인할 수 있는 능력

## Maintainability

- 시스템이 주어진 환경이나 요구 사항의 변화에 얼마나 빠르게 적응할 수 있는지를 나타냄
  - Modularity (모듈성)
    - 시스템이 별개의 구성 요소로 구성되어 있어서 한 요소를 변경하더라도 다른 요소에 미치는 영향이 최소한으로 제한되는 정도
  - Reusability (재사용성)
    - 자산(Asset)이 하나 이상의 시스템에서 사용되거나 다른 자산을 구축하는데 어느 정도로 사용될 수 있는지
  - Analyzability (분석 가능성)
    - 의도된 변경이 시스템에 미치는 영향을 평가하는 데 효과적이고 효율적으로 판단할 수 있는지
  - Modifiability (수정 가능성)
    - 수정과정에서 새로운 결함을 도입하지 않고 기존 제품 품질을 저하시키지 않고 어느 정도로 가능한지를 평가
  - Testability (테스트 가능성)
    - 시스템에 대한 테스트 기준을 설정하고 이 기준이 충족되었는지를 확인하기 위한 테스트를 수행하는 데 어느 정도로 효과적이고 효율적인지

## Portability

- 시스템이 다른 사용 환경으로 전환될 때 얼마나 효과적이고 효율적으로 전환될 수 있는지를 나타내는 정도
  - Adaptability (적응성)
    - 다른 하드웨어, 소프트웨어등 사용 환경에 효과적으로 사용 가능하도록 수정하거나 적응 시킬 수 있는 능력
  - Installability (설치 가능성)
    - 시스템이 특정 환경에서 성공적으로 설치되거나 제거될 수 있는 효과적이고 효율적인 정도
  - Replaceability (대체 가능성)
    - 다른 소프트웨어를 대체하고 같은 환경에서 같은 목적으로 사용할 수 있는 능력



## 품질모델 (ISO/IEC 9126)

### User’s View of Quality

![img](https://velog.velcdn.com/images/3eung_h10n/post/2af48b15-d8ed-4902-9660-cc1e7d10322f/image.png)

### 사용상 품질(Quality In Use)

![img](https://velog.velcdn.com/images/3eung_h10n/post/bc1fcad7-62b6-43d3-abe5-5ddefea75bfa/image.png)

![img](https://velog.velcdn.com/images/3eung_h10n/post/b9e0771c-d65f-4634-af04-21bd9c6ed7ea/image.png)

