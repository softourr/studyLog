# DS_04_logistic_regression

## 이진 분류 문제 binary classification

- 종속 변수가 y가 0 또는 1인 경우의 회귀 분석
- 입력들이 결국 0 아니면 1인지 판단



## 선형회귀는 classification 문제에 제대로 작동하지 않는다.

선형회귀를 사용해 함수 직선을 찾아냈다면

데이터가 이상치, 멀리 있거나 하는 경우 오류 발생이 가능하다.

다른 방법 필요!

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6c3bcd64-86f1-495b-b071-bef268a0b4e4)



## Sigmoid 함수 (로지스틱 함수)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/363b34e4-9470-422d-8295-e2e0b2c65614)

직선 대신에 시그모이드 함수를 가설함수로 사용한다. 분류 문제를 나타내는데 더 적절하다!

![image](https://github.com/hhzzzk/studyLog/assets/67236054/ac81b4e2-2cc2-4025-9629-637df212c2e5)

## 가설, 비용, sigmoid

`기존의 cost 함수로는 경사하강법 알고리즘이 제대로 동작하지 않는다.`

선형회귀 문제에서 사용했던 경사하강법은 cost가 낮아지도록 공을 굴려가며 찾는 것인데

분류 문제에서도 같은 방법을 사용할 경우 *공이 굴러가지 않는 평면*인 부분이 생겨 제대로 동작하지 않는다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6deed88c-19e1-4698-a5cc-9c067d17daf7)



따라서 이런 평면인 부분을 경사지게! 만들어서 공이 굴러가도록 함수를 변경할 필요가 있다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/3ce7ae99-c973-4d9a-bbfa-1f19232eda95)



새로운 cost 함수는 C로 기존 cost 함수인 MSE 방식은 h가 1로 갈 때 1이 최대값이라 h가 더 증가해도 1로 고정되어 평면이 생겼다. 

그러나 새로운 cost 함수인 C는 -log(1-x) 형태로 h가 1에 가까워질수록 무한에 수렴하는 형태가 된다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/094a8bc5-d3ec-4cb5-bc9d-ec7b443b803b)



그렇게 만들어진 새로운 비용함수는 공이 잘 굴러가도록 경사가 잘 만들어졌군.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a51ae45b-ad85-43d4-9afb-24f3e06ee2db)



비용함수는 미분 가능해야 하므로 y=0, y=1로 조건이 나뉜 부분을 적절히 합쳐져 하나의 함수로 정리한다.

이제 이전의 경사하강법처럼 비용을 최소화하는 w,b값을 미분하면서 찾아가면 된다. 

입력이 다차원일 경우에도 w가 벡터로 바뀌면 된다.