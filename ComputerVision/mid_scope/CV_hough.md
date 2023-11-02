# CV_hough

```
3.5 선분검출
	1. 에지 연결과 선분 근사
	2. 허프 변환
	3. RANSAC
```

검출된 에지를 여러가지 분야에서 활용하자

에지 연결과 선분 근사 : 에지를 간단하게 표현할 수 있는 방법

허프 변환 : 에지를 통해 선분이나 원을 찾는 방법

[참고](https://singularis7.tistory.com/49)

## 에지 연결과 선분 근사

이미지는 16 * 8 크기다. 영상에서 엣지가 차지하는 영역이 적기 때문에 공간이 남는다. 메모리 사용 비효율적이다.

메모리를 적게 쓰면서 효율적으로 에지를 찾을 수 있는 방법은 없을까?

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7bcc5de6-95c0-4367-bd1e-593cefe3d559)



## 체인 코드 사용

![image](https://github.com/hhzzzk/studyLog/assets/67236054/01383c88-66f0-4fe5-858c-1978a48eebaa)

영상의 픽셀을 돌다가 처음 만나는 점을 기준으로 오른쪽 방향이 0이다. 8방향 살핀다. 8연결성

체인코드는 시작점하고 방향을 숫자로 표현한다.

체인코드는 위와 같은 8연결성에서 어떻게 연결되어 있는지 표현하는 것을 의미한다.

영상에서 에지 성분을 끝점, 분기점, 통과점으로 분리할 수 있다.

1. @ 끝점 : 에지가 끝나는 점. 에지 기준 8연결성을 봤을 때 한 개의 에지만 있다.
2. \+ 분기점 : 에지가 두 방향으로 연결되는 점. 에지를 기준으로 8연결성에서 최소 3개 이상 연결된다.
3. O 통과점 : 에지 성분의 8연결성에서 2개의 에지 정보만 있다.

이 세가지 기준으로 토막 지어 나눌 수 있다. 분기점 기준으로



## 선분 근사

A점과 B점을 이어주는 직선으로부터 가장 멀리 있는 점 h가 있을 때 

​	선분 분할을 재귀적으로 반복해 에지 성분을 구한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c910789c-8a7e-4e9e-86a3-5ae0dcb3ba57)

다음과 같은 곡선 모양의 에지 성분을 근사적으로 표현해보자. 양 끝이 A,B

- A,B점을 연결하는 직선의 방정식 : 에지 성분을 대표하기에는 차이가 있다.
- 곡선과 직선 사이에 가장 거리가 먼 지점을 A'로 선택해 재귀적으로 직선 구해나감
  - A ~ B
  - A ~ A' + A' ~ B
  - 계속 분할 반복, 수많은 짧은 직선을 연결하면 곡선 형태 가능한, 미분개념



## 허프 변환

에지를 통해 선분, 원을 검출하는 방법

Hough Transform : 차원, 좌표계의 변환

- 2차원 영상에서 에지를 표현할 때 너무 많은 메모리 낭비
- 그렇다면 x,y 좌표계를 변환시켜 효율을 높여보자

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7ec9a701-369f-4163-a202-afa9dd00bb22)

- 에지 연결 과정 없이 선분 검출
  - 에지를 구성하는 픽셀값을 가지고 *어떤 특성*을 가지는지 나타낸다.
- x,y좌표계로 좌표값 하나씩 보면 메모리 비효율적, b-a 좌표계로 변환한다.
  - 기본적으로 직선은 y=ax+b, (x,y)을 안다면 기울기 a와 y절편 b를 구하는데 연산 필요
  - 이 과정을 줄이자. b-a공간은 기울기와 y절편 공간
- 이 때 영상 공간 y-x를 기울기 절편 공간 b-a로 변환한다.

*정리하면 y-x 공간에서 세 점을 이어주는 직선의 방정식 계산*

​	기울기와 절편을 알고 있다면 그 위의 모든 좌표를 설명할 수 있다. 메모리 효율 굿!!



## 수직선은 기울기가 무한, a가 무한

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a01b37a1-b448-45af-b24b-42d242ae8317)

수직선은 y축과 평행한 직선이다. 이런 경우 a가 무한대이므로 b-a공간으로 변환하기 어렵다.

그래서 극좌표계를 활용한다. 

sinθ 그래프와 삼각형 대응하는 그거..

- 극좌표계는 직선을 (p, θ)로 표현한다. p는 원점으로부터 직선까지의 수직거리(원의 반지름), 세타는 직선과 직교하는 선분과 원점과의 각도이다. 세타는 -90도에서 90도
- 각 점마다 한 개의 원, (p, θ)쌍이 생기므로 그림처럼 3개의 그래프
- 특정 각도에서 세 개의 그래프 곡선이 하나의 점으로 만난다.

정리하면 y-x좌표계의 3개의 점을 극좌표계로 나타낼 수 있어 메모리 효율적으로 사용 가능하다.

역으로 극좌표계에서 y-x좌표계로의 직선의 방정식도 구할 수 있다.



## Voting Scheme

갑자기 투표?

영상은 이산적이기 때문에 직선의 방정식을 벗어날 수 있다. 

그나마 많이 지나가는 곳을 극좌표계의 중심으로 가정해야 한다. 직방을 근사라도 할라고

직선과 가까운 위치에 voting 되는 픽셀을 지나는 극좌표계에서의 직선의 방정식을 찾아보자

![image](https://github.com/hhzzzk/studyLog/assets/67236054/2f7e9c55-5d73-4641-9071-2228d3c79147)

- 큰삼각형 기준으로 2,3구하고 기울기하면 4가 나온다.
- 위의 작은 삼각형 기준으로 5가 나오고 이래저래 정리하면
- 8번으로 좌표계 변환 공식이 나온다. 이를 이용해 x-y좌표를 극좌표로 바꿀 수 있다.

![img](https://blog.kakaocdn.net/dn/MViAS/btrfO39ugcb/mQc6VTFVrnF1JztO9923Lk/img.png)

관계식에 따라 x,y를 알고 있다면 각 세타에 대응하는 p값을 계산할 수 있다.

- x,y좌표계를 극좌표계로 변환시켜 가장 많이 선택되는 좌표 (p,세타)를 선택한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8f7262bb-3003-4d10-9fe5-2ab08b22b964)



## 코드 설명



![image](https://github.com/hhzzzk/studyLog/assets/67236054/d535a986-68ef-45f3-a2e5-c2794e73191a)

- H를 0으로 초기화한다. H는 세타값에 따른 p의 누적값을 기록하는 허프만 공간이다.
- 각 에지 포인트에 대해 세타값을 0-180까지 변경해가면 다음을 계산한다.
  - p = x * cos세타 + y*sin세타, H(세타, p) += 1
- 가장 많이 voting된 좌표를 찾는다. 그게 세타가 된다.
- 극좌표에 대해 실제로 시각화한 것이 아래 그림이다.

---

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9d9a7090-a98a-4240-bc32-6a12959cafca)

- voting되는 점을 통해 직선의 방정식의 개수를 예측하거나 모양이 같은 것을 예측할 수 있다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/711468b7-2640-4828-8fb9-4b1b9e718551)

- 사각형은 가장 많이 voting되는 점이 4개 정도 보인다. 즉 점이 4개면 직선의 방정식이 4개인 것이다. 4개의 직선은 사각형일 것이라고 예측할 수 있다.
  - 같은 기울기가 2개씩 나타나는 걸 볼 수 있다.
- 원은 몇개의 점으로 보이지 않고 유기적으로 연결된 느낌이라 무수히 많은 점으로 찍힌다. 

![image](https://github.com/hhzzzk/studyLog/assets/67236054/150056ff-ebc8-4a25-824c-be43a3c6d25a)

- 에지는 찍힌 점의 p와 세타값을 구하게 되면 그림에서 어디 부분의 에지인지 찾아낼 수 있다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/39bf71fa-53be-4ac0-bd14-d40bd4b02549)

- 여러 개의 직선은 이렇게 표현되더라.



## 노이즈가 있을 경우

- 정확하게 직선의 방정식인 경우 극좌표로 변환하면 한 점으로 voting된다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/eb021107-72dc-43a5-b298-1026b0f46340)



- 하지만 노이즈가 껴있으면 하나의 점으로 모이지 않는다. 그럴 경우 어떻게 할지

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6e45fc31-cf09-4fa1-a165-f9e64225d514)

- 이처럼 직선의 방정식이 아니라 거의 랜덤같은 점들이 찍히는 경우 voting이 하나의 점으로 모이지 않고 지저분해진다. 거미줄 같당

![image](https://github.com/hhzzzk/studyLog/assets/67236054/4a837065-a815-4e04-991b-4d46b5167fd5)

too coarse : 너무 듬성듬성 보면 하나의 점으로 voting이 안된다.

too fine : 너무 자세하게 볼 경우 끊어서 봐서 직방으로 볼 수 없다..

둘다 문제 솔루션 RANSAC 알고리즘 먼저 원부터 찾자

## 허프 변환으로 원찾기

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8463e99b-717e-4a8d-962e-1cf1c7c6026c)

- 2차원 영상에서 원 모양의 에지 성분이 있을 때 원의 반지름 r값을 알고 있다. (직선의 세타 대신 r을 사용)

- 원 에지 위를 기준으로 양쪽으로 r만큼 뻗어나간 지점들에 voting

  ![image](https://github.com/hhzzzk/studyLog/assets/67236054/8febbe9b-9291-47d6-ad90-1db0e727ae5f)

  - 즉 원 안의 한 점과 원 밖의 한 점에 voting
  - 원 밖의 점들에 많이 voting 되는 지점들이 원의 에지가 될 것이다.
  - 원 안으 점들은 원의 중심이 되겠지...



## Generalized Hough transform

허프 변환을 일반화해서 사물을 찾고 검색하는 알고리즘으로 응용이 가능하다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6cd848a2-1774-4051-b46b-049f8dd2dda2)

해당 템플릿에서 삼각형, 네모, 원의 voting이 다음처럼 각 방향이라고 하자.

- 물체에서 각 특징이 voting 하는 점 중 가장 많이 voting되는 점이 물체의 중심일 것이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/4fb4db84-fd19-4a5a-adaf-238f64573d70)



## 실제 적용

![img](https://velog.velcdn.com/images/3eung_h10n/post/00fe77a7-844c-4e40-bb5e-82a3dd795664/image.png)

- 자동차의 각 바퀴에서 동일한 뱡향으로 voting할 때 만나는 점이 자동차의 중심이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b40a4b1a-baa7-4991-b310-d6bb54ecb159)

- 이런 식으로 해서 물체의 중심을 찾을 수 있다.



## Implicit Shape Models(ISM)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/dbcd216f-ec5b-473c-a973-5e564108e9cb)

- 주어진 영상에서 특징들을 찾는다.
- 특징을 중심으로 영역을 모아 어디에 중심이 있는지 voting한다.
- voting이 가장 많이 되는 점을 물체의 가상의 중심이라고 가정한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/20836144-3260-40ab-b5b2-dd20a9d96a6c)

- 오토바이, 사람, 소와 같이 특정 기준으로 voting하면 물체가 잘 검출된다.
- 그러나 부분적으로 가려진 이미지에서는 단점 존재

## 허프 변환의 장단점

장점 : 잡음이 있어도 잘 검출한다.

부분 가려질 경우 검출 못한다 그림4? 그래도 어느정도 찾기는 하는데 뭐임

단점 : 시간이 많이 걸리고 모델이 많이 변하는 경우 잘 검출하지 못한다. 

​	자동차나 오토바이처럼 모양이 한정되어 있는 경우에는 잘 찾지만 

​	모델을 보는 방향에 따라 잘 검출하지 못할 수 있다.



## RANSAC

주어진 영상에 노이즈가 있을 때에도 직선의 방정식을 잘 구해보자.

선형 회귀를 이용한다.

c처럼 검출된 직선 외의 점들을 아웃라이어(특이점,오차점), 노이즈로 처리한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/3550e84c-456d-4d06-a40e-0c0bac321433)

## 랜색 과정

![image](https://github.com/hhzzzk/studyLog/assets/67236054/dc2bfd4d-52ba-4e15-9a69-637d3dadff65)

1. 랜덤하게 2개의 점을 선택한다. 두 점을 연결하는 직방을 구한다. 빨간 점 2개

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c8f6224c-e61e-4efe-9422-194f6be52399)



2. 사용자가 정한 특정 범위(직선 기준으로 양 방향으로 그만큼) 거리 안에 데이터가 얼마나 들어있는지 센다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/743a84cd-426b-4551-8e5d-6e12ea5113c3)

3. ?

![image](https://github.com/hhzzzk/studyLog/assets/67236054/3b393c3c-61c0-4eee-816c-1759c1e00f52)

4. 전체에서 해당 범위 안의 데이터가 몇 프로인지 계산해서 사용자가 정한 예시로 80프로 라고 하면 80프로를 넘는 두 직선을 찾아낼 때까지 두 개의 점을 다시 뽑기를 반복한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7000ea98-babf-4c13-a455-7a423e79b6fe)

찾았당





- 이렇게 구하면 아웃라이어, 잡음이 있이더 빠르게 구할 수 있다.