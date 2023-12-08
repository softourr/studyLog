# CV_3_Regularization

## overfitting

모델이 훈련 데이터에 너무 맞춰져서 일반화 성능이 낮아진 것이다. 과대적합을 해결하는 방법에는 여러가지가 있다.



## 규제

![image](https://github.com/hhzzzk/studyLog/assets/67236054/01c9892c-4106-406a-ba42-a47cff6c35d7)



정규화기, 레귤라이저는 모델이 훈련 데이터에 과적합되는 것을 방지하기 위해 *손실 함수에 추가*되는 기준이다.

이를 통해 모델의 가중치 W의 파라미터들을 유도해 일반화 성능을 향상시키고 과적합을 줄일 수 있다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/f12a0472-4ede-4f65-8192-7a7cdfaeeaf6)



---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/51a64418-8f4d-41bf-b9b7-0586b94ef7dc)



가중치를 작게 유지하거나 큰 가중치에 대한 패널티를 부여하는 주요 규제 기법으로는 L1 정규화와 L2 정규화가 잇다.

L1 정규화(Lasso)는 가중치의 절대값의 합을 손실함수에 추가한다.

- 일부 가중치를 0으로 만드는 특성 선택 feature selection의 효과를 가진다.
- sparse

L2 정규화(Ridge)는 가중치의 제곱합을 손실함수에 추가한다.

- 가중치를 작게 유지하며, 전체적으로 분산된 가중치를 유도한다. 전체적으로 가중치가 줄어드는 feature shrink 효과, 가중치 감소 weight decay 효과



## Effect of the decay coefficient 𝜆

가중치 감쇠 계수가 크다는 것은 규제가 강하다는 것이다.

규제가 크면 가중치 크기에 대한 패널티가 강해진다. 

결과적으로 모델은 가중치를 더 작게 유지하려고 한다. 

가중치의 크기가 작아지면 모델은 더 단순한 형태를 가지며 훈련 데이터에 과적합을 방지할 수 있다. == 일반화

![image](https://github.com/hhzzzk/studyLog/assets/67236054/568e85cd-d93c-412d-83f0-bbfc1fe4d430)

계수가 크자 분류기의 형태가 더 단순해진다. 



## Model-based machine learning

1. 모델을 선택
2. 최적화 기준 선택. 손실함수 선택
3. 학습 알고리즘. 옵티마이저 선택



##  Our optimization criterion

![image](https://github.com/hhzzzk/studyLog/assets/67236054/28181faa-2147-4a83-923a-a02f3f392368)

loss 함수와 레귤라이저, 규제를 추가한 우리의 손실함수

여기서는 L2놈을 적용했다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/749ce3ef-e422-4ca4-9f97-89b763d88c66)



우리의 손실함수를 wj에 대해 미분하면 다음과 같은 형태가 된다.



## 경사하강법

우리는 경사하강법 옵티마이저를 이용해 가중치를 갱신한다.

learning rate, 학습률에 따라 손실을 감소시키는 방향에서 얼마만큼의 크기로 이동할지 결정된다. 

즉 학습률 η은 각 단계에서 이동할 정도를 나타낸다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7e3117dc-9d80-4e41-95f3-be88e0880c9e)

미분의 음의 방향으로 이동해야 손실함수가 감소되므로 -이다. 

위에서 손실함수를 미분한 결과를 가중치 갱신에 대입한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/75872873-cf8d-4bd1-aa3a-191c01eec058)

## 규제

위에서 레귤라이저로 L2놈을 적용했다.

Wj가 양수인 경우

- 정규화 항 −ηλwj 에서 Wj가 양수이므로 해당 함을 음수가 된다. 즉 감소
- 즉 가중치가 양수이면 해당 항에서 가중치를 감소시킨다.

Wj가 음수인 경우

- 해당 항에서 양수값이므로 가중치가 증가한다.



결과적으로 절대값의 크기가 작아지는 방향으로 가중치가 업데이트된다. 

## L1놈

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9972afe6-e98b-4197-b93e-ac292a9a6d58)

L1놈을 적용하면 손실함수의 미분은 다음과 같다.

절대값 함수는 원래 미분이 안된다. (첨점) 0 지점에서만 미분이 안되므로 양수, 음수로 나눠서 미분해야 한다.

그래서 sign 함수를 사용해 0보다 크면 1, 작으면 -1이 되도록 한다.



L2놈처럼 결국 Wj의 절대값이 작아지는 방향으로 갱신된다.



## L1놈, L2놈 차이

−ηλwj

L2놈은 자신의 크기만큼 가중치가 줄어든다. L1놈은 1씩 줄어든다.

L2놈은 0에 가까워질수록 이동거리가 매우 작아진다. 자기자신만큼을 곱하고 그만큼 줄어들기 때문에.



L1놈은 초반에는 1씩 줄어들어 느리지만 실제로 0값이 가능하다. 

속도가 일정하게 줄어든다. 실제로 0이 되는 특성을 sparse coding이라 한다.

몇몇 가중치가 실제로 0이 되는 feature selection 효과



> L2놈은 다같이 줄어드는 스무스한 효과
>
> L1놈은 sparse, 피처셀렉션 발생





## Matrix Operation

![image](https://github.com/hhzzzk/studyLog/assets/67236054/50f5d350-3ee5-472a-8e65-40b9e9f2dfcf)



연산그림을 매트릭스로 표현할 수 있다!! 헷갈리지 말기



## 규제 : Dropout

과대적합을 줄이는 규제 기법 중 하나이다.

훈련 중에 랜덤으로 선택된 신경망을 비활성화시킨다. 즉 해당 행렬을 0으로 만든다.

- 훈련 중에 각 확률 p로 무작위 선택해 활성화하거나 비활성화시킨다. 이를 통해 네트워크는 각 뉴런이 독립적으로 학습되도록 하고 특정 뉴런에 과도하게 의존하지 않도록 한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7afbd551-79a0-464a-90f1-98614f56174e)



일종의 앙상블 효과를 낸다.

- 각 훈련 반복, 미니배치 동안 서로 다른 신경망 아키텍처를 훈련한다.
  - 랜덤하게 신경망이 0이 되어 지워지기 때문에 연결형태가 다양해진다
- 각 미니배치가 처리될 때마다 서로 다른 집합의 드롭아웃된 뉴런을 경험하므로 변동성이 생긴다. 특정 가중치 집합에 의존하지 않게 된다.



## 규제 : Early-stoping

훈련 중에 모델이 검증 세트에서의 성능을 모니터링하고 검증 세트에서의 성능이 더이상 향상되지 않거나 악화되면 훈련을 중지시킨다. 

검증 데이터 validation은 test가 아니라 트레이닝 데이터를 일부 쪼갠 것이다. 20프로는 검증으로 사용하고 80프로를 훈련으로 사용한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/ebc1aaad-bd2f-4340-b23c-b39b0d80992d)





## Activation Functions

활성함수를 이용해 신경망에 비선형성을 추가한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/1b5212de-e42e-4ffd-a76f-4333a55e915f)



- ReLU 함수는 그래디언트 소실 문제를 해결한다.