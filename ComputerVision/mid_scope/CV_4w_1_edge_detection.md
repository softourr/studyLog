# CV_4w_1_edge_detection

```
1. 에지 검출의 기초
	디지털 영상의 미분
	에지 모델과 연산자
	에지 강도와 에지 방향
2. 영교차 이론
3. 캐니 에지
4. 컬러 에지
5. 선분 검출
```

[참고](https://singularis7.tistory.com/46)

## 에지의 유용성과 한계

- 디지털 영상으로부터 영상의 중요한 특징(Feature)을 어떻게 뽑을 것인가?
- 특징이 무엇이며 어떻게 뽑아낼 것인가를 공부해본다.
- 엣지는 가장 중요한 특징 중 하나이다.
- 영상에서 엣지는 물체의 경계를 표시해주는 것이며 물체에 대한 경계는 조명과 같이 다양한 환경에 강인하다.
- 따라서 내가 **원하는 물체를 검색하거나 매칭**할 때 용이한 **선분 혹은 곡선으로 변환**할 수 있다

---

- 엣지는 어떤 명암값 또는 컬러값들에 **변화가 큰 지역들**을 모아둔 특징들을 의미한다.

**실종된 엣지 :** 객체의 엣지를 정확하게 감지 못함. 

**거짓 엣지 :** 객체의 엣지가 아닌 부분을 엣지로 감지함.

해당 오류를 최소화해야 한다. 어떻게 할래

## 에지 검출의 기초

- 물체의 경계는 변화가 크다. 이 원리에 따라 에지 검출 알고리즘은 명암, 컬러, 또는 텍스처의 변화량을 측정하고 변화량이 큰 곳을 에지로 검출한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/52c4f216-b098-49a3-9334-6fa680cf259f)

- surface normal discontinuity : 엣지를 구함으로써 *물체와 배경을 구분할 수 있는 경계*가 제공된다.
- depth discontinuity : 깊이가 갑자기 변화하는 지점. 어디가 앞이고 어디가 뒤 부분인지 구분할 수 있다.
- surface color discontinuity : 색상의 변화 지점. 글자 구분 가능
- illumination discontinuity : 조명이 변하는 지점. 뽑은 엣지로 부터 *어디에 조명이 있는지* 알 수 있다. 



```
1.1 디지털 영상의 미분
1.2 에지 모델과 연산자
1.3 에지 강도와 에지 방향
```



## 디지털 영상의 미분

![image](https://github.com/hhzzzk/studyLog/assets/67236054/461d9ddc-dab8-48ac-a4c9-3f498e76d8c2)



- s'(x) : x축 방향으로 s를 미분
- 디지털 영상에서 델타 x가 가장 작은 경우는 1이다. (픽셀 하나 차이)
- f(x+1) - f(x) 즉, 이웃하는 픽셀에서의 명암값의 차이 == 디지털 영상에서의 미분이다.
  - [-1][1\]의 필터로 구현 가능

---

​	그림3-2

디지털 영상 f에서 " f(x+1) - f(x) " 를 계산한 것이 f의 도함수 f'이다. (f' = 이웃하는 픽셀 간의 명암값 차이)

결과적으로 idx 5가 경계이고 이를 기준으로 좌우로 나눌 수 있다.

​	

🍁

🍁

🍁

# 에지 모델과 연산자

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b562effc-4cca-4f77-830a-ed636e1c881e)

계산 엣지 : 명암값의 차이가 크게 변한다.

램프 엣지 : 명암값의 차이가 서서히 변한다.

- 그림은 idx 3에서 계단엣지가 있고 idx 7부터 10까지 램프 엣지가 있다.
- 램프 엣지에서는 한 번 더 미분해서 램프의 시작과 끝 점의 엣지를 구할 수 있다.

? 2차 도함수 맞음?

![image](https://github.com/hhzzzk/studyLog/assets/67236054/264400a5-777e-424b-a58b-85e38d34aea7)

ㅇㅎ 아니 이건 원본 영상 기준으로 계산한거고...머지

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/dea94f1c-6e67-4c4f-83a9-4946f28e7368)

- 램프 에지에서 한 번 미분하면 봉우리의 형태로 변환됨 - 1차 도함수
- 램프 에지를 두 번 미분하면 영점과 만나는 점, 영교차가 생긴다. - 2차 도함수

> 결론 : 1차 미분에서 봉우리를 찾거나 2차 미분에서 영교차를 찾으면 두꺼운 에지를 찾은 것이다.



## Characterizing edges

![image](https://github.com/hhzzzk/studyLog/assets/67236054/908629be-3f1a-4c58-8c3d-ea587a2b884d)

**Intensity Function(명암 함수):** 이미지의 명암값의 변화를 그래프로 나타낸 것이다.

**First Derivative(1차 도함수):** 명암 함수의 기울기, 명암값의 변화량이다. 

**Edges Correspond to Extrema of Derivative(엣지는 도함수의 극값에 해당):** 엣지는 명암값의 변화가 가장 강한 부분이다. 1차 도함수의 극대,극소 값이 에지이다.!

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b2a2c21d-218b-4103-9169-5424fda37738)

## With a little Gaussian noise

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a2bd26bc-1141-4bbf-883b-7cb2045ac91e)

가우시안 노이즈가 추가되자 1차 도함수의 그래프가 변해버렸다. 이러면 에지가 원본보다 훨씬 더 많이 검출된다. 에러 검출 오류가 발생하겠군

![image](https://github.com/hhzzzk/studyLog/assets/67236054/5385a5c1-6499-46c7-b930-6a1bfe9d9403)

- 필터는 노이즈에 매우 민감하다! 엣지 뽑기가 어려워진다.
- 어떻게 하지?

## 가우시안 필터 노이즈 해결

![image](https://github.com/hhzzzk/studyLog/assets/67236054/5853c97b-36d5-49f0-b917-f9f93380d55f)

- 주어진 영상에 노이즈가 많은 경우 엣지 검출을 위한 미분을 수행하기 전에 가우시안 필터를 씌운다.
- 명암값이 전보다 부드럽게 바뀌는 단점, 그러나 전체적으로 잡음을 줄일 수 있다.
- 이후 미분하면 엣지 도출이 가능해진다.

```
가우시안 함수를 기반으로 한 필터를 생성하여 이미지에 적용하는 과정을 컨볼루션 연산이라고 한다.
컨볼루션 연산은 주어진 이미지와 필터 간의 합성곱 연산으로, 필터의 크기에 따라 각 픽셀에 대해 주변 픽셀들과의 가중 평균을 계산한다.
```

## Derivative theorem of convolution

미분 정리에 따르면 미분은 컨볼루션이다. 컨볼루션은 결합 법칙, 순서를 바꿔도 성립한다.

- 컨볼루션은 선형적인 특성을 갖고 있기 대문에 연산 순서를 바꿔도 성립한다.
- 가우시안 필터에 대해 1차 미분을 계산하고 f와 컨볼루션 연산을 수행하면 이전보다 한 단계를 생략할 수 있다.
  - 이전보다 더 연산횟수를 줄일 수 있다.



## Derivative of Gaussian filter



![img](https://velog.velcdn.com/images/3eung_h10n/post/f1ac1422-3e4f-490d-9be3-82d75eab7eec/image.png)

- 가우시안 필터를 이용해 2차원 영상의 x축과 y축 방향의 필터링을 하면 영상을 smooth 부드럽게 만들어 잡음을 제거하고 영상의 엣지 성분 분석을 할 수 있다.



## 현실에서 적용

- 현실에서 스무딩이 필요할 때 델타 x가 2인 방향으로 계산할 수 있다.
  - 델타x가 커지면 주변 픽셀들의 영향이 더 확대된다. 

![img](https://velog.velcdn.com/images/3eung_h10n/post/3b4cbb36-2564-4a46-92ad-6112c472b6f2/image.png)

My : y축 방향의 엣지 구하는 필터 마스크.

가로방향의 그레디언트를 구하는 필터는 세로(수직) 방향의 엣지를 구함 그레디언트와 엣지는 수직관계일수 밖에 없음

![img](https://velog.velcdn.com/images/3eung_h10n/post/bd21dae9-d0de-4cd3-ad47-d0ee3dd55315/image.png)

로버츠 : 엣지 감지, 대각 방향의 픽셀 차이를 계산해 엣지를 감지한다. x,y축 두 가지 마스크를 사용해 수직 및 수평 방향에서의 엣지 감지한다.

프레윗 :엣지 강조, 가로와 세로 방향에서의 픽셀 차이를 계산해 엣지를 감지한다. 가로 및 세로 방향의 엣지를 감지해 각 방향의 그레디언트를 계산한다.

소벨 : 엣지 탐지, 가로 및 세로 방향에서의 픽셀 차이를 계산해 엣지를 감지한다. 위의 두 필터보다 머 매끄럽고 정확한 결과 나온다.

- My의 두번째 열은 세로 방향, y의 방향이다. 소벨 필터는 자기 축에 해당되는 픽셀의 명암값을 강조한다! 



🍁

🍁

🍁

## 에지 감도와 에지 방향

엣지가 얼마나 강하고 방향이 어딘지 이해하기...

아니분량머선일이고...

![img](https://velog.velcdn.com/images/3eung_h10n/post/ffa7e125-7aea-402e-b897-be20ddf36c89/image.png)

- 강도와 방향을 나타내기 위해서 그레디언트(Gradient) 개념을 사용한다.
- 그레디언트는 명암이 어두운 곳에서 밝은 곳으로 변할 대의 변화를 나타나는 개념이다. 명암값의 변화량과 방향을 나타낸다. > 그레디언트는 벡터다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/78b8f7ab-5b19-4e15-8517-d09c20df98d8)



- x축 그레디언트 : 명암이 어두운 곳에서 밝은 곳으로 변할 때, 즉 명암값의 변화량이다.
- y축 그레디언트 : 명암값의 변화 방향이다.
- 그레디언트는 명암값이 변하는 방향이다. 즉 엣지는 그레디언트와 직교한다.

![img](https://velog.velcdn.com/images/3eung_h10n/post/79a2640f-8acb-4b07-8f89-6b1f493f4445/image.png)

첫번째 이미지는 x축으로 밝아진다. 방향은 유지 0

두번째 이미지는 x축은 변화가 없고 0, 방향이...

세번째 이미지는 x,y둘 다 변화



## 소벨 마스크를 이용한 에지 검출

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a58ecffa-42db-42cc-b299-cc91d8a53cff)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/04f1ac52-59a5-4c93-9f6c-a00106ae72f6)

픽셀 중심으로 소벨필터 각 자리 9개씩 곱해서 더하면 됨

![img](https://velog.velcdn.com/images/3eung_h10n/post/92aa4f99-ef7e-4802-bb3c-fa78fa9d0103/image.png)

dy,dx로 그레디언트 방향을 알 수 있다.

🍁

🍁

🍁

## 영교차 이론

```
1. 가우시안과 다중 스케일 효과
2. 로그 필터
```

## 가우시안과 다중 스케일 효과

## 가우시안을 사용하는 이유

- 미분은 잡음을 증폭시키므로 스무딩 적용이 중요하다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/bd0b11dd-3d58-4a86-b41a-e6825b7bb9ee)

- 시그마값을 조절해 다중 스케일 효과
- 에지의 세밀함 조절 가능하다.

![img](https://velog.velcdn.com/images/3eung_h10n/post/a93080f5-b654-41cf-9782-2a3e9b2fc48d/image.png)

- 가우시안의 시그마 값의 변화에 따라 가우시안 함수의 미분값도 여러가지로 달라짐
  - 시그마 값이 크면 뾰족해짐, 작으면 완만해짐

![img](https://velog.velcdn.com/images/3eung_h10n/post/666f70d8-f6f5-41f6-addd-01551f9d8d2d/image.png)



- 2차원에서 가우시안 필터의 크기는 시그마의 크기와 비례함
- 가우시안 필터의 마스크가 작으면 오차가 생기고 크면 시간이 오래걸림. 적절히 조절해야 한다.

![img](https://velog.velcdn.com/images/3eung_h10n/post/f322e119-ebb7-4472-b39a-80666d976624/image.png)



## LOG 필터

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c13ccade-d44c-4479-a40c-24fa1796755f)

라플라시안 : x축 방향의 2차미분과 y축 방향에서의 2차 미분의 합이 라플라시안 함수이다.

- 라플라시안 필터를 사용해 영교차 지점을 찾으면 쉽게 엣지를 찾을 수 있다.

---

로그필터는 라플라시안 오브 가우시안이다.

- 가우시안 필터를 적용하고 라플라시안(2차미분) 필터를 적용해 에지를 검출한다.
- 두 단계로 진행하면 계산 시간이 오래 걸리고 오류가 많이 생긴다.
- LOG 필터를 이용해 한 단계로 처리한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/0b259d60-1f1c-4073-943d-68f2561cb33b)



### 예제

![image](https://github.com/hhzzzk/studyLog/assets/67236054/5fb57df0-aa69-457d-89e3-2b032de50e90)

- 필터를 돌렸을 때 0이 만나는 지점을 찾아서 모아두면 엣지를 쉽게 찾을 수 있다.



### 시그마 값에 따른 LOG 필터 적용

- 8x8 영상에서 sigma가 5일 때에 3x3 크기의 LOG 필터를 적용하여 얻은 영상이다.
- 0이 교차하는 (부호가 바뀌는) 지점을 모아둔 1 들이 엣지 성분임을 알 수 있다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/41a12dcf-ebf8-41aa-9e87-a00890120749)

- sigma 즉, 필터의 크기가 커지면 가우시안 필터의 크기가 커지기 때문에 영상이 더 스무스하게 변환되며 엣지가 단순해진다.





