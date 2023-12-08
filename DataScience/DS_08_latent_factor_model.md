# DS_L08_latent_factor_model

별점 예측 방법에는

1. 콜라보 필터링(아이템/유저)
2. latent 팩터 모델(잠재 요소 모델) 2가지가 있다.



## Factor Model

사용자와 아이템을 요소(factor)들로 나타낼 수 있다고 보는 모델

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fc830520-791c-48d0-a515-f0de6836cb4c)

데이터에서 학습되는 요인. 예시로 사용자의 취향이나 영화나 드라마의 특성 등



## Latent Factor Model

- 사용자와 아이템을 잠재적인 요소들로 나타낼 수 있다고 보는 모델



## Matrix Factoriazation

- 사용자와 영화를 같은 차원의 공간에 매핑한다.
  - 각각의 사용자와 영화를 같은 차원의 벡터로 표현
    - 사용자와 영화의 벡터의 내적 값이 사용자가 해당 영화에 매긴 평점 값이 나오도록! 학습시킨다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/84ecdb39-4af6-43a2-b8a8-d8223b001e7c)



사용자와 영화가 학습이 되어 벡터로 표현됐다면! 평점 예측이 가능하다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c9963790-3e40-40d2-94f7-a76efed96b47)



- arg min은 함수에서 최소값을 갖게 하는 변수를 나타낸다. 함수를 최소화! 최적화 하는 변수의 값이다.
- 위의 수식은 일종의 MSE. R은 실제 별점이고 P,Q의 곱(내적)은 예상별점이다. 
  - 실제값에서 예상값을 뺀 값을 제곱해서 더한다. 그 값을 최소화! == MSE

## 선형회귀와의 차이?

아래는 잠재요소 모델이다. 

![image](https://github.com/hhzzzk/studyLog/assets/67236054/00f62348-b1fb-4dfe-99fe-65aeaf1a6478)

>  선형회귀의 가설함수는 H(x)=wx+b
>
>  입력 변수 x에 대한 선형 관계를 나타내는 가중치 w를 학습을 통해 구한다(최적화). b는 편향

이와 다르게 잠재요소모델은 p와 q를 학습을 통해 최적화 시킨다. 비용함수는 MSE와 거의 유사하다 (실제값-예측값의 제곱합) 업데이트는 경사하강도 방법을 사용

- 잠재요소모델에 bias를 추가하면(pq+b) 선형회귀 모델 가설함수와 유사해진다. 그러나 변수가 2개라는 차이 존재
- 선형회귀는 convex 함수, 즉 볼록함수 형태이다. 이는 선형회귀는 선형 결합으로 이루어졌기 때문이다.
  - 따라서 하나의 값으로 최적화가 가능하다. 
  - 그러나 잠재요소모델은 말그대로 잠재 요소를 고려하므로 최적화 과정에서 convex를 보장할 수 없다. 비선형성이 추가될 수 있다.
  - convex 최적화 문제는 간단한 형태이므로 경사 하강법 등을 사용 가능하다.
  - non-covex 최적화 문제라 ALS같은 복잡한 최적화 알고리즘을 사용한다. 더 복잡한 최적화 방법 필요
- 그래서 ALS 방법을 사용하기도 하는데 P,Q중 하나의 변수를 랜덤값으로 고정하고 최적화, 다시 반대쪽을 고정하고 최적하는 방법이다. MSE를 사용해 오차를 최소화한다. 이 과정을 내적해서 해당 평점(정답값)이 나올 때까지 반복한다.



# Training, Test

잘 학습되었는지 검증하려면 학습 데이터와 테스트 데이터를 분리한다.

## 오버피팅

실제로 학습해보면 학습이 진행될수록 트레이닝 데이터에 너무 학습하는 오버피팅이 어느 순간 발생해 테스트 데이터의 오류가 높아진다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/94200fe7-e5a8-435a-b4b9-e600b9a55675)

## 오버피팅 해결 sol) 규제

Regularization

- 트레이닝 데이터에 너무 빠지지 않도록 최적화 과정에서 벡터가 범위를 벗어나는 너무 큰 값을 가질 경우 패널티를 주는 것

![image](https://github.com/hhzzzk/studyLog/assets/67236054/14b7db26-2e3c-4b3d-a814-e163bee35ebb)



## Lp Norm

Ln Norm이라고 교수님은 설명

n은 norm의 차수를 나타낸다. L1과 L2를 주로 사용

N차원 벡터가 있을 때 각 벡터의 절대값을 n차원해서 더한 후 1/n승한다.

L2는 제곱합해서 벡터를 더하고 루트를 씌운다.



## re

![image](https://github.com/hhzzzk/studyLog/assets/67236054/1d7a0ec1-da8d-44f5-8335-2bcc0f4349c5)



## Latent Factor Model + Bias

Cost Function

규제까지 적용한 손실함수의 형태는 다음과 같다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b7b3598e-45e9-46b3-a4fb-6376a35efb52)

7장 마지막 다시 보기 복습