# CV_5_vector_backprop

ing

10w2, 11/8

![image](https://github.com/hhzzzk/studyLog/assets/67236054/49fcd6f2-c0da-41c0-8307-a1449d264ef3)

벡터의 미분 3가지

일대일 : 스칼라대스칼라

다대일 : 벡터대스칼라 = 다변수함수 미분, 편미분

다대다 : 벡터대벡터 = 야코비안

## 야코비안 행렬

![image](https://github.com/hhzzzk/studyLog/assets/67236054/14a07a66-03c4-46bf-b079-3d96422af3eb)

야코비안은 첫번째 행은 첫번째 f 함수를 각 변수로 편미분한 것이다. > 야코비안은 1차편미분만 한다. 헤센은 2차까지 함

두번째 행은 두번째 f함수를 각 변수로 편미분한 것이다.

열은 같은 변수를 편미분한다. (보통 x,y 순서)

행은 같은 f 함수를 편미분한다.



@@@ 오류역전파를  할 때 다대다 벡터일 경우 그래디언트로 야코비안 행렬이 사용된다.

> loss는 항상 단일 스칼라 값이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/807babb6-f04e-4b7b-9799-09f8cba7b400)

Dz는 z의 차원이다.

벡터를 미분하면 몇차원이냐면 미분하기 전의 차원이랑 같다. 그렇겠지? 

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7dccb791-1924-456a-9a97-fcbb95e43168)





![image](https://github.com/hhzzzk/studyLog/assets/67236054/a0132ab9-7610-4b56-8607-b373dd07c095)

다운스트림 그래디언트는 업스트림 그래디언트에 로컬 그래디언트를 곱한다.

전체에서 흘러온 업스트림에서 로컬 그래디언트를 곱하면 위와 같은 4050 다운스트림이 나옴

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fe2fd83b-bded-4a0f-8abb-54462c864238)



![image](https://github.com/hhzzzk/studyLog/assets/67236054/3e3a776b-0bf2-4a1c-93f1-5295c2f65284)



![image](https://github.com/hhzzzk/studyLog/assets/67236054/316ecb2e-e4bc-470a-a364-2ced8501a72c)



---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6b852170-fac0-4098-912f-3f3e98e24611)

y = xw

y의 1,1위치를 구하려면 행렬곱을 수행하면

위와같은 식이나온다. 해당 식에서 x11에 대해 미분하면 w11만 남는다. 즉 x11을 사용한 부분이 그대로 들어간다.



결국 dy를 x11 슬라이스로 미분하면 

x11이 언제 곱해지는지를 보면 y의 첫번째 행에서 w의 첫번째 열들과 곱해질 때만 사용된다.

그러므로 3 2 1 -1하고 나머지는 0이 된다. 



![image](https://github.com/hhzzzk/studyLog/assets/67236054/008ec2d9-829b-44be-9044-eb580a972651)

일반화하면 다음과 같이 된다. x에 대해 미분하므로 로컬 그래디언트는 다른 파라미터인 w의 x의 열에 해당하는 행을 가져온다.

x의 행이 업스트림에서 가져올 행(y에서 뭘 가져올지)이 되고!



![image](https://github.com/hhzzzk/studyLog/assets/67236054/a684a848-40c6-4f3e-a0d2-03201b16e8c4)

결국 지금 구하는게 업스트림 행렬값이 주어졌을 때 다운스트림 행렬값을 구하자는 건데

y=xw이므로 

위치는 고정하고 x로 미분하면 x위치에 업스트림이 들어가고 w는 전치해서 곱한다 이런식으로 외우기

미분하는 파라미터 자리에 업스트림 들어간다! 다른 파라미터는 전치!

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8f11c90b-8c34-4bb0-947d-7593055d2dac)