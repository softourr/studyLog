# CV_4_compGraph_backprop

10w1

11/16 목 

3마무리, 4는 약간만하고 수업끝남



## Backpropagation with Computational graph

문제는 그래디언트를 어떻게 계산할 것인가?

경사하강법과 같은 최적화 알고리즘에서 가중치 업데이트를 위해서는 그래디언트가 필요하다.

- 오버피팅 방지를 위해 규제, 레귤라이저를 손실함수에 추가했다. 
- 비선형성(max)을 추가해 스코어 함수를 만들었다. 

![image](https://github.com/hhzzzk/studyLog/assets/67236054/d40fb30d-1198-4a2f-896d-23f8f6b517ed)

손실함수에 대해 각 가중치로 미분이 가능하다면 == 그래디언트 계산이 가능하다면 가중치 학습이 가능하다.



모듈화를 통해 중간과정의 연산이 바뀌거나 loss가 바뀌어도 빠르게 업데이트 가능하도록 해야 함 > 오류역전파의 등장

연산그래프를 이용해 모듈화



> 힌지는 기계학습에서 주로 분류문제에 사용되는 손실함수 중 하나이다.
>
> SVM과 관련이 깊다. 주어진 데이터의 예측값과 실제값의 차이를 측정하고 MAX를 사용



![image](https://github.com/hhzzzk/studyLog/assets/67236054/c311551f-a894-46ef-9518-972eb73ab47b)



f = qz

​	q = x+y

즉, f = (x+y)z

f를 y에 대해 미분하려면

f를 q에 대해 미분하고 q를 y에 대해 미분해야 함

![image](https://github.com/hhzzzk/studyLog/assets/67236054/4571a2a6-5fa7-4b3b-a2d5-bbe69bdeed88)

로컬 그래디언트는 해당 식에서 보이는 변수들 편미분한 거임. 해당 식에서 다 해결(로컬 그래디언트는 그럼 매개변수 개수만큼 편미분하겠다)

업스트림은  위에서 흘러들어오는, 좀 더 큰 범위에서 x+y는 사실 q여가지고 f를 q로 미분해야 하는 부분

다운스트림은 흘러 내려가는 것 업스트림과 로컬 곱해서 남은

이게 다음 업스트림으로 흘러감



end



start

진도 11/8, 10w2



## 활성함수 종류

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b8e546d1-2731-4a8e-9020-b49ac13cf592)

시그모이드를 하면 입력의 절대값이 매우 클 경우 0 또는 1로 수렴한다. 그결과 미분값이 0에 수렴한다.

즉 기울기가 0이 되는 그래디언트 소실 문제가 발생한다. 이를 해결한 것이 ReLU이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/5e026fc2-4d9f-4745-8067-40c78ff7fd78)

>  이런거 나올듯 분수 미분하기. 시그모이드 함수 등 수식 기본적인거 외우기
>
> softmax의 미분 나중에 과제로 냄



## Patterns in Gradient Flow

add, mul, max

덧셈은 그대로 흘러감

곱셈은 다른 변수값이 내려감

맥스는 더 큰 쪽에 본인값 흘리고 나머지는 0



## Backprop Implementation: ”Flat” gradient code: 

시험나올듯 채우는거

![연산그래프](https://github.com/hhzzzk/studyLog/assets/67236054/89f7e710-a800-4192-9581-dc3a29a7479e)

---



![image](https://github.com/hhzzzk/studyLog/assets/67236054/3a386726-3b5f-4420-a718-42be4c47fbdd)



