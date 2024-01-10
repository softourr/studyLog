[TOC]



# CG_6_Clipping_Rasterization

## Clipping

viewing volume 밖의 object들을 지움, eliminate

- 파이프라인의 여러 위치에서 수행
- ​





### Line segment clipping

input line에서 viem volume를 통과하는 부분을 잘라내는 방법

- view volume와 선분과의 교차점을 추가 점을 찍어서 선을 분할함

### Polygon clipping

폴리곤에서 view volume 내부의 부분만 남도록 잘라냄

---

## Bound boxes and volumse

복잡한 폴리곤에서 클리핑을 수행하는 대신 xis-aligned bounding box나 extent 사용가능 (주로 게임엔진)

- accept/reject 여부를 바운딩 박스만을 기준으로 결정, 

  - 바운딩박스에 걸쳐지는 부분은 추가적으로detailed clipping작업이 필요하다

  (((바운딩 박스는 어떤 Object를 둘러싼 가상의 박스)))

  ​

# Rasterization(scan conversion)

개중요@@@@@@@@@@@@@@@

픽셀로 바꾸자, scan conversion

fragment로 바꾸는데 색을 interpolation...보간@@@

```markdown
Scan conversion이라고도 함
__primitive를 픽셀 집합으로 변환하는 프로세스__
(((Primitive Assembly 과정에서 Primitive을 그리는데, 이 때 어떤 pixel이 Primitive에 속하는지 계산하는 것.(OpenGL 에서는 이 과정을 알아서 해준다)
그래서 pixel에 들어가는 Fragment의 list를 뽑아낼 수 있다.)))

## 계산하는 것
Fragment location
– vertices, 정점 집합으로 지정된 primitive 내부의 픽셀들

Per-fragment attributes
– 색상 및 텍스처 좌표(texture coordinates)와 같은 속성은 
	vertices정점의 값을 interpolationg 보간하여 결정

# Line Rasterization
__DDA 알고리즘__
주어진 선 방정식(예: y = mx + h)을 사용하여 x를 델타x씩 증가시켜 y를 계산

- 각 line의 slope 기울기를 고려해야 하는데 m이 1보다 큰 경우 y 값의 간격이 너무 커짐
- 그래서 m이 1보다 크면 y가 증가할 때마다 x를 1/m만큼 증가시킴

- 실제로는 Bresenham's line algorithm 많이 쓰임
```

```markdown
https://velog.io/@jaehyeoksong0/graphics-3

# __Scan Conversion__
Scan Conversion은 Viewport transform에 의해 screen space로 옮겨진 모든 primitive들의 내부를 채우는 프래그먼트를 생성하는 단계이다.
좁은 의미에서의 래스터화를 지칭하는 단계이기도 하다.

primitive 삼각형의 screen space에서의 픽셀 위치를 결정하고, 삼각형의 정점별 속성vertex attributes을 보간하여 이를 각 픽셀 위치에 할당한다.

정점별 속성은 어플리케이션마다 다르지만, 주로 노멀, 텍스처 좌표, 색상 등을 포함하며, 원칙적으로 모든 정점별 속성은 같은 방법으로 보간된다.

간단히 정리하자면, Scan Coversion 단계에서는 크게 다음의 두 작업을 수행한다.
1. 삼각형을 채울 screen space에서의 픽셀별 위치를 결정한다.
2. 삼각형의 픽셀별 color, depth 등의 attribute를 할당한다.

# __linear interpolation__
모든 삼각형 내의 픽셀에 프래그먼트에 할당할 정점별 속성 계산을 위한 정보를 일일히 저장하는 것은 비효율적이다.
따라서 삼각형의 vertex 정보를 이용해 linear interpolation을 수행하여 정점별 속성을 구하고 이를 각 프래그먼트에 할당한다.

이에 대한 예시인 겹선형 보간Bilinear interpolation을 통해 프래그먼트의 속성을 구하는 과정을 간단하게 알아본다.

- 각 변에 대한 선형 보간이 수행되었고, 스캔라인을 따른 각 점에 대한 선형 보간이 수행되었다.

따라서 이 과정을 bilinear interpolation이라 한다.
본 예시에서는 이 과정을 통해 프래그먼트별 색상을 얻을 수 있었다.

실제 Scan Conversion 과정에서는 색상 값뿐만 아니라 노멀, 텍스처 좌표, 깊이 등 모든 정점별 속성을 보간하여 각 픽셀별 프래그먼트를 생성하게 된다. 이제 래스터화 단계가 완료되고 프래그먼트 처리 단계로 넘어가게 된다.
```



# 4월17일 월요일

11페이지

추상적  개념을 실제 픽셀로 바꾸자

- 픽셀 여기서는 fragment라고 부르자

dda 알고리즘으로 라인채움

## Polygon Rasterization

중요

입력은 정점인데 최종 출력은 픽셀로 나옴

14페이지

6개의 c 정점이 그 안을 가득채우는 픽셀로 변하는 알고리즘 이해하자

---

기벡에서 배운 선형 보간, linear interpolation

t를 0-1 사이에서만 이야기 하겠다,

그 범위 밖은 extrapolation,

---

Billinear interpolation

선형보간을 두번함

스캔라인마다  반복

per 폴리곤마다 해당 작업 반복

컬러결정



> hidden surdave removal,
>
> 16페이지
>
> 모든픽셀에 대해 일단 컬러 계산함
>
> 근데 실제 화면에 안그려질수도잇음
>
> 입힌 컬러가 최종화면에 안그려질수도잇는데
>
> 그래서 용어구분함
>
> fragment는 색을 입힌 거고
>
> 최종화면에 나온건 픽셀



vertex에 부여된 어떤 것도 interpolated 가능

데이터는 vertex에만 부여 가능

```markdown
# Bilinear interpolation
– 먼저, 라인의 색상이 interpolated
– 둘째, 각 스캔 라인의 색상이 interpolated
• 여기서 여러 attribtes들은 삼각형의 fragments 위에 interpolated

>>> 라인의 색한번, 스캔라인의 색 한번해서 두번 보간한다


(((Interpolation(인터폴레이션, 보간)이란 알려진 지점의 값 사이(중간)에 위치한 값을 알려진 값으로부터 추정하는 것)))
https://velog.io/@jaehyeoksong0/graphics-3
```



## Hidden Surface Removal

17페이지

__z버퍼알고리즘__

제일 카메라에 가까운 fragment만 픽셀로 바꿈



fragment의 depth값을 depth 버퍼값과 비교해서

더가까운 min값을 버퍼에 남긴다

장점1 프로그래머는 씬에서 객체의 렌더링 순서에 대해 신경 쓸 필요가 없음

장점2, 22페이지

Z 버퍼 알고리즘은 스캔 라인 알고리즘을 통해 음영과 숨겨진 표면 제거를 결합할 수 있습니다

![image](https://user-images.githubusercontent.com/67236054/233868606-b714427a-6131-453b-8a27-04d181f11aa5.png)

- 카메라와의 거리가 더 가까우면 Color Buffer와 Depth Buffer 모두 갱신한다.





__Painter's 알고리즘__

배경부터 그린다 화가처럼!

sorting 함, 소프트웨어적 접근

앞에잇는 폴리곤을 나중에 그린다.

뒤에 있는 걸 먼저 그림

z버퍼 알고리즘있는데 왜쓰나?

> '맨뒤로보내기' 등 레이어 순서 결정할때 등
>
> 소프트웨어적으로 depth 설정해야 하는 경우들 다수 존재



@@@z버퍼는 물체의 불투명함을 가정하고 돌아가는 알고리즘임

투명한 물체에는 사용불가함



__Back-face Removal__

카메라관점..

빠른 결정, 반시계방향, 시계방향으로 앞인지뒤인지빨리판단가능

