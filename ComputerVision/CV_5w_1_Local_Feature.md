# CV_5w_1_Local_Feature

![image](https://github.com/hhzzzk/studyLog/assets/67236054/d4d9eaa2-89b2-4496-9f8a-ef7877cb557a)

파노라마처럼 이어진 이미지를 연결해야 할 때

두 개의 영상에서 서로 대응하는 부분을 찾아 연결해야 한다.

이러한 대응점, 매핑점을 어떻게 찾을 것인가.

주로 3단계 검출, 기출, 매칭의 단계로 대응점을 찾는다.

```
1. 지역 특징 검출의 기초
2. 이동과 회전에 불변한 특징점 검출
3. 위치 찾기 알고리즘
4. 스케일에 불변한 특징점 검출
```

## 지역 특징 검출의 기초

```
특징 검출의 역사 : 지역 특징의 대두
지역 특징의 성질
지역 특징 검출 원리
```

## 특징 검출의 역사 : 지역 특징의 대두

- 무엇을 특징점으로 쓸 것인가?
  - 이전에 배운 에지, 그레디언트는 크기와 방향 정보만 가지므로 매칭에 사용하기에는 부족하다.
- 코너의 등장
  - 에지 토막에서 곡률이 큰 지점을 코너로 검출한다.
- 지역 특징의 대두
  - 명암 영상에서 직접 검출한다.
  - 코너에서 발전된 개념. 코너의 물리적 의미는 반복성이라는 것에 착안

## 지역 특징의 성질

지역 특징은 <위치, 스케일, 방향, 특징 벡터>의 4가지로 표현한다.

지역특징은 반복성, 분별력, 지역성, 정확성, 적당량, 계산 효율이라는 특성을 만족해야 한다.

위의 특징들 중 상황에 따라 적절한 특징을 가진 지역 특징을 선택한다.

## 지역 특징 검출 원리

`여러 방향으로 밝기 변화가 나타나는 곳일수록 높은 점수를 준다.`

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a7b2448c-b090-4ab3-a087-47b63342c67b)

그림 a,b,c의 가운데를 기준으로 

​	a는 상하좌우 모두 밝기 변화 >>> 코너

​	b는 좌우 밝기 변화		>>> 에지

​	c는 모두 밝기 변화가 없다. 	>>> flat

> 주어진 지점으로부터 4,8연결성으로 주변 명암값의 차이가 큰 지점이 local feature다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/09f3e396-a5a7-4f34-ae07-dbb7f35c9ee5)

**flat** : 상하좌우 명암 차이 없다.

**edge** : 좌우 혹은 상하로만 명암 차이가 있다. (x축이나 y축)

**corner** :  상하좌우 모두 명암 차이가 있다.



## 이동과 회전에 불변한 특징점 검출

```
모라벡 알고리즘
해리스 코너 > 여기까지만
2차 미분을 사용한 방법
슈산
```

## 모라벡 알고리즘

![img](https://velog.velcdn.com/images/3eung_h10n/post/af7b27b2-0504-40eb-b69f-2a1e69b7ac6c/image.png)

- 제곱차의 합으로 밝기 변화 측정
- 제곱해서 음수를 방지한다. w는 가중치. 
- *기존 y,x자리에서 v,u만큼 이동한 지점의 명암값에서 기존 자리를 빼고 제곱한다.*

![image](https://github.com/hhzzzk/studyLog/assets/67236054/59fd6cc7-db0d-44f5-996f-961bbe7a689a)

S(0,1)은 x축으로 1 이동. 즉 기존 9개의 픽셀의 각 자리에서 오른쪽으로 한 칸 이동한 지점의 값에서 기존 지점 값을 빼서 제곱하고 모두 더한 값이다.

S(-1,-1)은 왼쪽 위칸, 대각선 왼쪽 위의 지점에서 기존 지점을 빼고 제곱해서 더하면 된다.

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9d581968-bd23-4969-9528-0020a1eaf3f3)

자기 자신인 가운데 값은 0이다.

모라벨 결과인 a,b,c 값을 보면 

​	a는 상하, 좌우 모두 명암 차이가 난다. corner

​	b는 좌우로만 차이가. edge

​	c는 차이가 없다. flat 

![image](https://github.com/hhzzzk/studyLog/assets/67236054/79bd1653-c9a1-40e8-9829-2b83a07453b8)

a가 코너, b가 엣지, c가 플랫

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c9bb2e8a-e56b-4669-bce1-6eb54998b5a3)

- 모라벡 함수는 코너에 높은 값, 플랫이 가장 작은 값을 부여하는 함수이다.
- 4.2 식을 보며 네 방향 중 min 값을 고른다.
  - 코너인 경우 0,1이외의 다른 값이 나온다.
  - 엣지나 플랫은 0,1이 나온다.

**한계**

- 잡음에 대한 대처 방안이 없다.
- 한 화소에 대해 4방향만 확인한다.



## 해리스 코너🐺🐺🐺

가우시안 필터로 잡음을 해결하겠다.!

![image](https://github.com/hhzzzk/studyLog/assets/67236054/2fac463c-0c56-4c25-84fc-3f57f14bfe04)

만약 (v,u)가 매우 작은 값이라면 테일러 확장을 통해 근사적으로 표현 가능하다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9b595c1a-22f6-4785-917d-321f6d6c19c0)

결론

dy^2은 y축 명암값의 차이에 대한 분산

dx^2은 x축 명암값의 차이에 대한 분산

dydx는 x축 y축의 공분산, 밝기 변화가 방향에 따라 어떻게 상호작용 하는가

- 4개의 값이 모두 크다면 corner이다. 모두 작다면 flat이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b1f3d7e7-fa2e-4492-8177-956cd7c3e1d0)

2차 모멘트 행렬을 통해 x,y의 그레디언트 정보만으로 코너, 엣지, 플랫을 식별할 수 있다.

- dy,dx의 제곱 2개가 모두 크다면 코너, 모두 작다면 플랫, 둘 중 하나만 크다면 엣지이다.

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/4bd26067-25d8-4d93-97b5-a42a58cc9600)



![image](https://github.com/hhzzzk/studyLog/assets/67236054/ff67afab-a11b-43b3-96fa-2b788ba8c733)



## 위치 찾기 알고리즘

이동과 회전에 불변이다.

![img](https://velog.velcdn.com/images/3eung_h10n/post/c6e6d82f-1f56-4aa4-bbd1-903dc845468d/image.png)

스케일 변하면 변한다.

![img](https://velog.velcdn.com/images/3eung_h10n/post/812758f4-e692-47c3-b8e4-930952acbd53/image.png)



