[TOC]

# CG_1,2_Overview,Camera

## Overview of Rendering Pipeline

(((전체적으로 한 번 훑어봄)))

coordinates == 좌표

![image](https://user-images.githubusercontent.com/67236054/233839335-4b361e5f-a832-4ed8-a5f2-ceb833113636.png)

vertices == 정점

```markdown
# Vertex processor
객체 표현을 한 좌표계에서 다른 좌표계로 변환
Converting object representations from one coordinate system to anothe
- __Object__ coordinates > __Camera__ coordinates > __Screen__ coordinates


# Clipper and primitive assembler
Primitive assembly: a set of vertices > a set of primitives (e.g., quads) 
- Clipping primitives, when some portions are out of the screen
- 스크린 밖에 있는 primitives를 클리핑함, 잘라냄

# Rasterization
Rasterizer produces a set of fragments for each primitive
> 각 primitive마다 franments(픽셀)들 생성하는게 ""Rasterizer""
- Fragments: “potential pixels”
– Vertex attributes are interpolated over primitives
	정점의 attributes, 속성들은 primitive 위에 interpolated됨 ???
```



# CG_2_Camera

## Synthetic Camera

```markdown
# Elements of Image Formation
Viewer(camera) -synthetic Camera
Objects -synthetic objects
Light source(s) -Synthetic lights
Attributes
- Material, surface normal for reflection model 
(i.e., light-material interaction)

```

![image](https://user-images.githubusercontent.com/67236054/233840091-4ca64032-a986-438c-8e44-c9a20c0b6a6a.png)

```markdown
# Seeing - 본다는것, 선형 투사 기법
본다는 것은 빛이 날아와 눈에 맺히는 작용이고
본다는 것을 이해한 것은 장면에 대한 묘사가 가능하다는 것이다.

# Camera Specification – Projection types
Projection types에는 2가지가 있다
–  Perspective projection 
–  Orthographic projection 오쏘

  ## Perspective projection
  (((원근법으로 멀리 있는 건 작게, 가까이 있는 건 크게 그리는 방법이다.)))
  Parallel lines -> Vanishing point
  평행선이 한점으로 보이면 그게 소실점임


  ## Orthographic projection
  Parallel lines -> Parallel lines

---

# Camera Specification – Clipping Planes
Clipping
–  Physically, a camera (or your eyes) cannot “see” the whole world
	Objects that are not within the view volume are said to be clipped out of the scene
	"view volume" 밖의 objects를 씬에서 clipped out, 잘라낸다
	4 clipping planes: left / right / top/ bottom
	
오픈지엘에는 두 가지 클리핑 구역이 추가됨, 앞뒤
In OpenGL, there are two additional clipping planes
•  6 clipping planes: left / right / top/ bottom + __<front / back>__
•  Computer cannot process infinitely many objects
```

![image](https://user-images.githubusercontent.com/67236054/233840171-07b622cc-dba1-4c1c-bbb3-50bf916c51d4.png)

![image](https://user-images.githubusercontent.com/67236054/233840569-f4146e15-44c0-4980-8cc6-72020f1e4a9f.png)

```markdown
# Camera Specification – Extrinsic parameters
  Extrinsic parameters: 6 degrees of freedom (DOF) 

  6자유도는 로봇공학, 비행기 등에서 사용되는 여섯 개 운동방향임
  1은 앞뒤 y수직
  2는 좌우 x수평
  3은 상하 z깊이,depth
  123 자유도는 pos, 위치임
  나머지 3개는 orientation, 회전기울기이다
  4는 앞뒤 기울기 피치 pitch
  5는 좌우기울기 롤 roll
  6은 좌우회전 yaw

  –  Position: 3DOF
      Center of projection (COP): position of center of lens (x, y, z)
      렌즈의 중심
  –  Orientation: 3 DOF
      pitch(끄덕) –– yaw(도리) –– roll(갸웃)
  –  In OpenGL, extrinsic parameters are handled by camera transformations
      OpenGL 2.x or higher: implement proper transformations by yourself

.

# Camera Specification – Intrinsic parameters
Intrinsic parameters 
__Focal length__
	In OpenGL, there is no physical meaning
__Field of view (FOV)__
•  In OpenGL, __zoom-in/-out__ is handled by changing the field of view

# Camera Specification – Viewport
Viewport
- Similar to the size of photo printing
	A film -> Photos of different sizes
- A rectangular area of the display window: x, y, w, h
	(x, y): the lower-left corner of the viewport
	w, h: the width and height of the viewport
```

![image](https://user-images.githubusercontent.com/67236054/233841011-75d8f0a6-b4ae-45c1-a4d4-5b47297da7e7.png)



```markdown
# Camera Specification – Aspect ratio
Aspect ratio, 화면비 디스플레이 가로와 세로 길이의 비율
__width / height__
	For aspect ratio, absolute sizes of width & height are meaningless
- 	Aspect ratio of __display window__ (e.g., device screen) is important
```

![image](https://user-images.githubusercontent.com/67236054/233841239-2b0040a1-e542-43c8-bd79-1eb7d02e495d.png)

