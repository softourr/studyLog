# CG_7_ShaderProgramming_Patr1

## 4/19

```markdown
https://velog.io/@jodmsoluth/OpenGL-Graphics-pipeline

# graphics pipeline의 두가지 역할
1. 스크린은 사실상 2D 픽셀이므로 개발자가 input으로 넣은 3D 좌표를 2D 픽셀로 변환하는 작업
2. 변환한 2D 좌표에 rgb(255,255,255) 색을 넣는 작업

결과적으로 그래픽파이프라인은 3D좌표를 2D픽셀로 만드는 작업을 말합니다.
그래픽 파이프라인의 각 단계에서 GPU 위에 작은 프로그램들을 실행시킴으로써 데이터를 빠르게 처리하기 위해 수천개의 작은 프로세싱 코어를 가지고 있습니다. 이 작은 프로그램들이라는 것은 shaders라고 합니다.

기본 쉐이더도 있지만 Vertex shader, Geometry shader, Fragment shader 다음에는 개발자가 GLSL로 작성한 쉐이더를 직접 주입할 수 있습니다.
```



## Programmable Rendering Pipeline

계산기와 컴퓨터의 차이?

내가 원하는 프로그래밍 스타일로 컴퓨터의 하드웨어 성격을 바꾸는게 가능하다. 컴퓨터는. 

계산기는 정해진 계산이라는 하드웨어적 작업을 바꿀 수 없음



결국 내가 하려는 작업 정리해서 렌더의 파이프 이해하고 내가 하고싶은걸 파이프라인 로직에 맞게 작업하면 됨



입력으로부터 출력으로 가는 이 흐름이 랜더링 파이프다.



쉐이더도 맞음.

쉐이더를 짜서 GPU에 올리면 해당 로직대로 돌아감



## Understanding Fixed Rendering pipeline

재질, 카메라 방향과 각도에 따라 화면 밝기나 color가 계산됨



### Fixed Rendering Pipeline

프래그먼트 하나의 컬러변경 불가능한 단점

- 각각의 정점마다 컬러를 준게 아니라 어떤 면으로 구별함







### Per-vertex Lighting v.s. Per-pixel Lighting

Fixed(고정) rendering pipeline은 per-vertex lighting 만 지원함

- 빛의 계산은 vertex processor에서만!! 가능
- We may ignore specular effects from highlights, with coarse triangles



Programmable rendering pipeline은 per-fragment lighting 지원함

- 빛의 계산을 fragment processor 에서 수행되는 방식 가능
- We can __represent__ specular effects from highlights, with coarse triangles



__Per-vertex lighting__

> 빛의 계산이  vertex processor에서만 가능

__Per-fragment lighting__

> fragment processor에서도 빛의 계산 가능함







- 왜 vertex에서 컬러 계산하고 픽셀에서 계산하지 않았을까 과거에
  - 통상적으로 vertex 개수가 픽셀 개수보다 훨씬 적음, 