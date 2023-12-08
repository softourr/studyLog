# DS_07_Collaborative Filtering

```
별점 예측하기 : Collaborative Filtering
Hybrid Method
```

## 별점 예측 방법

1. Collaborative Filtering > 유사한 것에 평균?
   1. Item-Item CF
   2. User-User CF
2. Latent Factor Model



## Item-Item CF

>  내가 유사한 드라마에 몇 점 주었는가?
>
>  사용자 x가 아이템 i에 매길 평점 예측하기

### 🍏 방법1. 평균내기 🍏

![image](https://github.com/hhzzzk/studyLog/assets/67236054/cba0f2f1-27e2-45ef-bd97-dd52c3135fa3)

**내가 평가한 아이템 중 현재 아이템과 가장 유사한 k개의 아이템의 평균값**

---

### 🍏 방법2. 더 유사한 아이템에 가중치 줘서 평균내기 🍏

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fe837f5a-edf6-455e-991e-795154042e48)



내가 평가한 아이템 중 유사한 아이템 k개의 sum을 내 아이템과 해당 아이템과의 유사도로 나눈 값

- 위의 평균내기를 단순히 k개로 나누는 것이 아니라 아이템 간의 유사도로 나눈다.



8p같은거 시험나옴! 직접 계산

드라마 사이의 유사도 계산 코사인 유사도 복습

- 두 개의 벡터끼리의 유사도 계산법 = 벡터곱/각 제곱루트해서 곱함

![image](https://github.com/hhzzzk/studyLog/assets/67236054/061e50f1-b02f-45a2-abfa-b5633c38a16f)

여기서는 피어슨 상관계수를 사용한 코사인 유사도



## User-User CF

아이템과 축만 달라진다. 나와 유사한 사람들이 아이템에 매긴 평점을 이용한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/2e4eccdb-b784-4272-a128-fd2e027a50dd)

---

- 이론상 아이템과 유저는 동일한 정확도를 가져야 하나 실제로는 아이템이 더 좋은 성능을 보인다.
  - 사람의 변덕 등 불안정한 요소들 때문에 아이템이 더 견고한 값을 가진다.

## Collaborative Filtering의 장단점

장점

- 추천대상에 제한이 없다.

단점

- **Cold start :** 충분한 유저와 평가 정보가 확보되어야 한다.
- **Sparsity :** 평가 데이터에 빈 곳이 많다. 같은 드라마를 평가한 유저가 적다.
- **First rater :** 한번도 평가되지 않은 드라마는 추천되지 않는다.
- **Popularity Bias :** 대부분 인기있는 아이템들만 추천된다.



## Hybrid Methods

1. 내용 기반 추천 방법(Content-based method)과 collaborative filtering를 섞는다.
   - 새로운 아이템을 추천할 때는 내용을 기반으로 한 item profile을 활용해 추천
   - 새로운 사용자에게 추천할 때는 전반적으로 인기가 좋은 아이템을 추천


2. 둘 이상의 추천시스템을 구현하고 통합해 추천
   - gloabal baselise + collaborative filtering



## Global Baseline Estimate

> 가전제 : 이미 높은 평점을 받은 드라마에는 대부분 높은 평점을 준다.
>
> ​		해당 사용자의 성향(점수에 깐깐, 후함 등) 반영

해당 사용자가 새로운 아이템을 보고 매길 평점 예측하기

- 해당 사용자는 새로운 아이템과 유사한 아이템 데이터가 없다는 전제



Gloabal Baseline Estimate (평점 예측)

- Gloabal Baseline (기본 점수) 예측
  - 평균 전체 드라마 평점 3.7점 + 해당 드라마 평점 평균(평균 +0.5점) - 해당 사용자의 평점 평균 (평균 - 0.2점)
  - 3.7 + 0.5 - 0.2 = 4.0점

> bxi = μ + bx + bi
>
> 사용자의 x의 아이템 i에 대한 baseline을 구하는 공식
>
> μ는 전체 평균 평점

## GBE + CF

기본 평점 예측에 콜라보 필터링 적용

- 위에서 계산한 GBE는 4.0
- 콜라보 필터링 : 해당 아이템과 유사한 아이템의 정보 사용

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fe35cbc3-5f83-4df1-8e7f-36a0fcac466f)

Rxi 사용자가 아이템에 매길 평점은

기본 점수 예측 = 전체 별점 평균과 사용자의 편향, 아이템의 편향 더한 것

CF더하기. 그러나 분자에 유사도와 (평점-편향)한 값을 곱해서 유사도의 sum으로 나눈다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/90112c8f-0a1e-477b-b38a-412ec72070d8)

실제 문제로 연습하기!



앞에서 편향을 더해주고 CF 계산에서 각각에 편향을 빼서 곱하는 것으로

전체적인 경향보다 해당 사용자의 특성이나 해당 아이템의 특성에 더 초점을 맞추게 된다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/ece14191-d489-4049-a871-3f164b94f74b)



![image](https://github.com/hhzzzk/studyLog/assets/67236054/f1f4d749-3d84-4d55-a316-ab3682a92585)



>  코사인 유사도는 벡터 간의 내적을 각 벡터의 크기를 곱한 값으로 나눈 것이다.

X,Y의 유사도는 X는 [5,0,4] Y는 [4,3,0]이다.

내적하면 20이고 각 크기는 루트 41과 루트 25, 5이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8ad79efd-c8fd-416c-a10c-24e4dd23b093)



위에서 다시 CF 반복하면

사용자가 평가하지 않은 영화에 대한 예측 평점을 계산할 때 아이템 간의 유사도를 이용해 collaborative filtering를 수행한다.

아이템-아이템 협업 필터링으로 각 아이템 간의 유사도를 계산하고 이를 이용해 예측 평점을 계산한다.

N은 아이템과 유사한 아이템들의 집합이다.

그 집합들을 분자에서는 유사도 곱 평점 마이너스 베이스라인

분모는 유사도를 합하는 것이다.

