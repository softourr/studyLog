[TOC]



# CG_3_Objects

## Polygon soup

## Vertex List & Polygons

```markdown
# Synthetic Objects
이미지포메이션의 요소에는 뷰어, 오브젝트 라이트소스, 속성이 있고 여기서 오브젝트를 봄

3d 모델은 정점, 버텍스들과 면, faces로 구성됨
## Polygon soup
- Duplication of __vertex information__
- 버텍스 데이터를 복제하는 방식으로 3d 모델 데이터 저장, 메모리 사용량 증가하나 참조를 하지 않아 빠름
- 정점은 반시계 방향 순서대로 저장함

__Polygon data transmission__
쿼드는 정점이 4개임

## Vertex List & Polygons
- Duplication of __vertex indices(인덱스고 버텍스정보있는배열 따로 존재하는)__
- 정점 데이터의 정보를 List로 관리하는 방식으로 3D 모델 데이터를 저장하는 모델이다.
- 각 정점들을 사용할 때 List를 참조해서 사용해 메모리 사용량이 감소하지만, 느리다.
- 각 모델의 정점은 반시계 방향 순으로 저장한다.


## Triangle Meshes
모든 Polygon Primitive를 삼각형으로만 저장
속도 향상

- OpenGL ES, DirectX support triangle meshes only
```

# Modern OpenGL Rendering Architectures

## Vertex Arrays

```markdown
# Modern OpenGL Rendering Architectures
1. Vertex Arrays
	__기존 CPU에 연결된 메모리에 Vertex 데이터를 저장하는 기법__
	매 프레임마다 GPU로 Vertex 데이터를 전송하기 때문에 느리지만, 관리가 편하다.
	
	버텍스 데이터가 클라이언트 공간에 저장됨(CPU에 연결된 메모리)
	서버 공간(GPU)로 버텍스 데이터를 보내야됨
	
	코드절차
	1. Enable Arrays
	2. Specify data
	3. Render with glDrawArrays() or glDrawElements()

```

```markdown
버텍스 배열 예시
__Triangle Soup  VS  Vertex List & Triangles__ 2가지 방법 다 가능
1. Enable Arrays
2. Specify Data (polygon soup) vs (vertex list & polygons)
3. Render with (glDrawArrays()) vs (glDrawElements())


/
색은 (red, green, blue)
정점 반시계 방향으로 
```

```c++
// buffers in client space, 메인메모리에 위치
GLfloat position[] = { 0,0,0,  1,0,0,  1,1,0, 1,0,0, 2,1,0, 1,1,0 }; 
GLfloat color[]  = { 1,0,0,  0,1,0,  0,0,1, 0,1,0, 0,0,0, 0,0,1 };
// @@@버텍스 리스트 앤 트라이앵글에는 추가에 필요한 
GLubyte indices[]  = { 0, 1, 2, 1, 3, 2 };


// attribute IDs in server space, GPU의 위치
GLint loc_a_position = glGetAttribLocation(program, "a_position"); 
GLint loc_a_color    = glGetAttribLocation(program, "a_color");

// 버텍스 쉐이더의 attribute 중 a_position 부분 활성화
__
glEnableVertexAttribArray (loc_a_position); // 1번!!! 보내겠다는 flag, 신호를 줌
// 현재 배열 버퍼에 있는 데이터를 버텍스 쉐이더 a_position에 해당하는 attribute와 연결
// 데이터 위치 명시
glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, position); 
// GPU의 해당 위치에 GL_FLOAT를 3개 단위로 묶어서 
__
// 버텍스 쉐이더의 attribute 중 a_color 부분 활성화
glEnableVertexAttribArray (loc_a_color);
// 현재 배열 버퍼에 있는 데이터를 버텍스 쉐이더 a_color에 해당하는 attribute와 연결
glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, color);
__
---------------------------------------------------------------------------------------
// @@@triangle soup으로 물체 그리기
glDrawArrays(GL_TRIANGLES, 0, 6);
//  6개의 vertices그림

// @@@Vertex List & Triangles  로 물체 그리기!
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
// 그리는모드 > 6개의 vertices그림 > 인덱스의 타입 > EBO의 Offset

---------------------------------------------------------------------------------------
// 정점 attribute 배열 비활성화
glDiableVertexAttribArray(loc_a_position);
glDiableVertexAttribArray(loc_a_color);
```

## Vertex Buffer Objects (VBOs)



```markdown
2. Vertex Buffer Objects (VBOs)
	처음 랜더링 시 Vertex 데이터를 모두 GPU로 전송하는 기법이다.
	Vertex 데이터를 GPU가 관리하기 때문에 빠르지만, 관리가 불편하다.
	

Buffer Objects (BOs) allow storing of arrays in server space
버퍼 오브젝트가 배열을 gpu에 저장할 수 있도록 함
	E.g.) Vertex Buffer Objects (VBOs), Index Buffer Object (IBO)
__Steps to use BOs__
1.     Generate __buffer object identifiers__
2.     __Bind__ a buffer object, specifying for <vertex data vs indices>
3.     Request storage, optionally initialize, 저장소 요청하고 선택적 초기화함
4.     Specify data including offsets into buffer object
--- 여기까지가 초기화
5.     Enable vertex attribute array
6.     Bind buffer object to be used in rendering
7. 	   Render with VBOs (+ IBO) (e.g., glDrawArrays() or glDrawElements())
--- 여기까지 랜더링
```

```c++
# 초기화

// buffers in client space
GLfloat position[] = { 0,0,0,  1,0,0, 1,1,0, 1,0,0, 2,1,0, 1,1,0 }; 
GLfloat color[]    = { 1,0,0,  0,1,0, 0,0,1, 0,1,0, 0,0,0, 0,0,1 };
// 리스트에만 있는거
GLubyte indices[]  = { 0, 1, 2, 1, 3, 2 };
// buffer IDs in server space
GLuint position_buffer; 
GLuint color_buffer;
// 리스트에만 있음
GLuint index_buffer;
// create a vertex buffer & trasfer vertices data from client space to server space 
glGenBuffers(1, &position_buffer);
__
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

// create an index buffer & trasfer vertices data from client space to server space 
glGenBuffers(1, &color_buffer);
__
glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

// 스프나 리스트나 위치,컬러까지는 같다
// 리스트
glGenBuffers(1, &index_buffer);
__
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
```



```c++
# 랜더링

// specifying vertex data
glEnableVertexAttribArray(GL_ARRAY_BUFFER, loc_a_position); 
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); 

// specifying color data
glEnableVertexAttribArray(GL_ARRAY_BUFFER, loc_a_color); 
glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
-------------------------------------------------------------------------------------------
_
glDrawArrays(GL_TRIANGLES, 0, 6);
// 리스트
// specifying triangle-vertex index data

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer); 
__
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*) 0);

-------------------------------------------------------------------------------------------
// 아래는 동일
// reset buffers
glDisableVertexAttribArray(GL_ARRAY_BUFFER, loc_a_position); 
glDisableVertexAttribArray(GL_ARRAY_BUFFER, loc_a_color);
```



```markdown
# glEnableVertexAttribArray()
파라미터 인덱스는 사용하거나 사용하지 않을 vertext attributes의 인덱스를 지정함
- 활성화된 경우 vertex attribute array의 값이 활성화되어 glDrawArrays(), or glDrawElements()와 같은 vertex array 명령을 호출할 때 렌더링됨

# glVertexAttribPointer()
vertex atttribute 데이터 배열을 정의함
파라미터 순서대로 idx, size, type, normalized, stride, pointer

인덱스 지정하고

size는 1,2,3,4 중 하나임, 일반 Vertex Attribute당 component 수

type : Array에 포함된 각 Component의 type

normalized : fixed point data 값을 정규화할지(GL_TRUE), 고정점 값(GL_FALSE)로 직접변환할지 여부 결정

stride : 연속적 vertex attribute 사이의 byte offset을 지정

pointer : GL_ARRAY_BUFFER 대상에 binding된 Buffer의 Data저장소에 있는 배열에 있는 첫 Generic vertex attribute의 offset 지정
```



실제로 구현가능해야 할듯? 코드로?

중요한거는

스프는 정점이 각 삼각형마다 필요하고

리스트는 일단 인덱스 리스트는 겹치는거빼고 정점개수만큼 정점 데이터 있고

idx리스트 있어서 거기를 참고함



## lab_Adv_헬로트라이앵글

- CPU와   GPU는   각자   자신이   볼   수   있는   메모리만   본다는   것이   중요한   점이다.   

- 따라서,   모던   OpenGL을   이용해   삼각형을 그리려면 

  삼각형의  정점  데이터가  메인  메모리와  GPU  메모리  두  곳에  모두  존재해야  한다.



## 정점  버퍼  객체( V B O )  이해하기

VBO를  이용해  삼각형을  그리기  위한  핵심코드는  아래  세  부분이다.
1)         메인  메모리에  __정점  데이터를  정의__하는  부분
2)         GPU  메모리에서  VBO를  만들고,  메인  메모리에  정의된  정점  데이터를  GPU  메모리의  VBO로  전송하는  부분
3)         GPU  메모리의  VBO에  정의된  정점  데이터로  물체를  그리는  부분



```markdown
# 정점 데이터 전송
__CPU 메모리에 있는 정점 데이터를 어떻게 GPU 메모리로 전송하는가__

먼저 정점 데이터 전송에 앞서 
__GPU 메모리에 정점 데이터가 보관된 장소를 마련__해야 한다.

모던 OpenGL에서는 정점 데이터가 보관될 GPU 메모리를 할당하는 특수한 방법을 제공하는데 
이를 정점 버퍼 객체(vertex buffer object, 이하 VBO)라고 한다.

다음은  GPU  메모리에  정점의  삼차원  __위치와  칼라__를  담을  VBO를  2개  설정하고,  
CPU  메모리의  정점  정보를  GPU  메모리  상의 VBO로  전송하는  코드  조각이다.
```



```c++
GLuint         position_buffer; 
GLuint         color_buffer;
void    init_buffer_objects() 
{
    glGenBuffers(1,    &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER,    position_buffer);
    glBufferData(GL_ARRAY_BUFFER,    sizeof(g_position),    g_position,    GL_STATIC_DRAW); 
  
  
    glGenBuffers(1,    &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER,    color_buffer);
    glBufferData(GL_ARRAY_BUFFER,    sizeof(g_color),    g_color,    GL_STATIC_DRAW); 
}
```



```markdown
# glGenBuffers()
GPU 메모리에 버퍼 객체를 만들어 달라고 요구하는 함수이다. 
만들어진 버퍼 객체에 접근할 수 있는 인덱스는 call-by-reference 방식으로 넘겨 준다. 
한번에 여러 개를 만들어 달라고 요청할 수 있지만, 이 코드 조각에서는 glGenBuffers이 호출될 때마다 1개씩 만들어 달라고 요청하였다.

# glBindBuffer()
GPU 메모리에 생성된 버퍼 객체를 바인드하는 함수이다. 
glBindBuffer의 함수인자로 GL_ARRAY_BUFFER를  지정함으로써,  
GPU  메모리의  버퍼  객체를  정점  속성(vertex  attributes)을  저장할  수  있는  배열로  활용하였다.

# glBufferData()
CPU  메모리에  있는  데이터를  GPU  메모리로  __전송시키는  함수__이다.  
현재  바인드  되어  있는  버퍼  객체로 데이터가  전송된다.
```



```markdown
# 정점 데이터로 삼각형 그리기(GPU 메모리)
정점  데이터가  모두  GPU  메모리에  전송된  상태이므로
GPU  메모리에  있는  VBO에  기록된  삼각형  정점  데이터를 참조하여  그림을  그릴  수  있다.
다음은  GPU의  VBO에  저장된  정점  속성을  이용해  triangle  soup  방식으로  물체를  그리는  코드이다.
```



```c++
//triangle  soup
void    render_object() 
{
    glClear(GL_COLOR_BUFFER_BIT    |    GL_DEPTH_BUFFER_BIT);
    //    특정    쉐이더    프로그램    사용
    glUseProgram(program);
    //    정점    attribute    배열    loc_a_position    활성화
  
    glEnableVertexAttribArray(loc_a_position);
    //    앞으로    언급하는    배열    버퍼(GL_ARRAY_BUFFER)를    position_buffer로    지정
    glBindBuffer(GL_ARRAY_BUFFER,    position_buffer);
    //    현재    배열    버퍼에    있는    데이터를    버텍스    쉐이더    loc_a_position    위치의    attribute와    연결 
    glVertexAttribPointer(loc_a_position,    3,    GL_FLOAT,    GL_FALSE,    0,    (void*)0);
    //    정점    attribute    배열    loc_a_color    활성화
    glEnableVertexAttribArray(loc_a_color);
    //    앞으로    언급하는    배열    버퍼(GL_ARRAY_BUFFER)를    color_buffer로    지정
    glBindBuffer(GL_ARRAY_BUFFER,    color_buffer);
    //    현재    배열    버퍼에    있는    데이터를    버텍스    쉐이더    loc_a_color    위치의    attribute와    연결 
    glVertexAttribPointer(loc_a_color,    3,    GL_FLOAT,    GL_FALSE,    0,    (void*)0);
    //    삼각형    그리기
    glDrawArrays(GL_TRIANGLES,    0,    6); 
    //    정점    attribute    배열    비활성화
    glDisableVertexAttribArray(loc_a_position); 
    glDisableVertexAttribArray(loc_a_color);
    //    쉐이더    프로그램    사용해제 
    glUseProgram(0);
}
```

```markdown
이  코드  조각에서는  정점의  삼차원  위치가  담긴  VBO와  칼라가  담긴  VBO를  각각  쉐이더(shader)의  특정  속성(attribute)에  결합시 키고  삼각형을  렌더링하고  있다.

여기서  눈여겨  봐야할  부분은  glVertexAttribPointer의  가장  마지막  함수인자로  (void*)0를  넘겨줬다는  점이다.  

__원래 이 부분은 정점 데이터가 있는 CPU 메모리의 주소를 알려주는 부분인데, 우리는 GPU 메모리에 복사된 정점 데이터를 활용하기로 했으므로 CPU 메모리는 활용하지 않겠다는 의미에서 (void*)0로 설정했다는 점을 주목하자.__

# 그렇다면, 정점의 속성 정보가 있는 GPU 메모리의 위치는 어떻게 알려준 걸까?

가장 최근에 glBindBuffer로 바인드된 VBO가 glVertexAttribPointer에서 활용하는 정점 속성을 담고 있는 GPU 메모리 위치로 활용된다.

__정리하자면,   glVertexAttribPointer에서   가장   마지막   함수인자가   (void*)0인   경우,   정점   속성   데이터를   얻기   위해 CPU  메모리를  참조하지  않고  가장  최근에  바인드된  VBO를  참조하는  방식으로  동작한다.__
```



## 인덱스  버퍼  객체( I B O )  이해하기

이제  물체를  vertex  list  &  triangles  방식으로  그릴  때,  

GPU  메모리를  활용하는  방식인  정점  버퍼  객체(vertex  buffer  object,  VBO) 와  

인덱스  버퍼  객체(index  buffer  object,  IBO)를  살펴보도록  한다.

VBO의 경우, 정점 속성을 메모리에 저정할 때 vertex list & triangles 방식으로 관리해야한다는 점을 제외하고는 앞서 설명한 방식과 동일하다. 

여기서는 CPU 메모리에 정의된 IBO를 어떻게 GPU 메모리에 올리고 활용하는지에 대한 핵심코드만 살펴보기로 
한다. 



IBO를 이용해 폴리곤 정점의 인덱스를 표현하는 핵심코드는 아래 세부분이다.
1)         메인  메모리에  폴리곤  정점  인덱스  데이터를  정의하는  부분
2)         GPU  메모리에서  IBO를  만들고,  메인  메모리에  정의된  폴리곤  정점  인덱스  데이터를  GPU  메모리의  IBO로  전송하는  부분
3)         GPU  메모리의  IBO에  정의된  폴리곤  정점  인덱스를  활용해  물체를  그리는  부분



### 3.1        인덱스  데이터  정의  (CPU  메모리)

삼각형을 이루는 정점 인덱스를 정의하는 코드 조각이다. 

삼각형 2개를 그리기 위해, 총 6개의 인덱스 정보를 CPU 메모리 상의 배열에 나타내었다. 

정점 데이터의 경우, vertex list & triangle 방식으로 그리기 위해 4개의 위치와 칼라 정보를 정의하도록 수정하였다.

```c++
//    triangle-vertex    indices
GLubyte    g_indices[]    =    { 0,    1,    2,    0,    3,    1,};
//    vertex    list    &    triangles    방식으로    그리기    위해    정점    데이터를    수정함. 
//    per-vertex    3D    positions    (x,    y,    z)
GLfloat    g_position[]    =    {
0.5f, 0.5f, 0.0f, // 0th vertex position 
-0.5f, -0.5f, 0.0f, // 1st vertex position
0.5f, -0.5f, 0.0f, // 2nd vertex position 
-0.5f, 0.5f, 0.0f, // 3rd vertex position
};
//    per-vertex    RGB    color    (r,    g,    b)
GLfloat    g_color[]    =    {
1.0f,    0.0f,    0.0f,                                 //    0th    vertex    color    (red)
0.0f,    1.0f,    0.0f,                                 //    1st    vertex    color    (green)
0.0f,    0.0f,    1.0f,                                 //    2nd    vertex    color    (blue)
1.0f,    1.0f,    0.0f,                                 //    3rd    vertex    color    (yellow) 
};
```



### 3.2        인덱스  데이터  전송  (CPU  메모리  →  GPU  메모리)

CPU 메모리에 있는 정점 데이터를 어떻게 GPU 메모리로 전송하는지 살펴보자. 

먼저 정점 데이터 전송에 앞서 __GPU 메모리에 정점 데이터가 보관된 장소를 마련__해야 한다. 

모던 OpenGL에서는 정점 데이터가 보관될 GPU 메모리를 할당하는 특수한 방법을 제공하는데 이를 정점 버퍼 객체(vertex buffer object, 이하 VBO)라고 한다.
다음은  GPU  메모리에  정점의  삼차원  위치와  칼라를  담을  VBO를  2개  설정하고,  CPU  메모리의  정점  정보를  GPU  메모리  상의 VBO로  전송하는  코드  조각이다.

![image](https://user-images.githubusercontent.com/67236054/233854030-62d1dc4a-fe40-42f3-a65a-3fd8d7a0b319.png)

위의 코드 조각에서 __glBindBuffer와 glBufferData의 함수인자__

로 GL_ELEMENT_ARRAY_BUFFER를 지정했다는 점에 주목하도록 하자. 

이렇게 지정함으로써 버퍼 객체가 인덱스 데이터를 담아두는 장소임을 명시할 수 있다. 나머지 부분은 이전 예제와 유사하다.





### 3.3        VBO와  IBO를  이용해  삼각형  그리기  (GPU  메모리)

정점  데이터와  인덱스  데이터가  각각  VBO와  IBO  형태로  GPU  메모리에  전송된  상태이므로,  모던  OpenGL에서는  다음의  코드 조각과  같이  VBO와  IBO를  이용해  vertex  list  &  triangles  방식으로  물체를  그릴  수  있다.

![image](https://user-images.githubusercontent.com/67236054/233854122-8c59babc-bf5d-4bce-91f0-254efaaa8b6b.png)

이  코드  조각에서는  정점의  삼차원  위치가  담긴  VBO와  칼라가  담긴  VBO를  각각  쉐이더(shader)의  특정  속성(attribute)에  결합시 키고  삼각형을  렌더링하고  있다.

여기서 눈여겨 봐야할 부분은 glDrawElements의 가장 마지막 함수인자로 (void*)0을 넘겨줬다는 점이다. 

원래 이 부분은 인덱스 데이터가 있는 CPU 메모리의 주소를 알려주는 부분인데, 우리는 GPU 메모리 상의 IBO 데이터를 활용하기로 했으므로 CPU 메모리는 활용하지 않겠다는 의미에서 (void*)0로 설정했다는 점을 주목하자. 



그렇다면, 인덱스 정보가 있는 GPU 메모리 의 위치는 어떻게 알려준 걸까? 가장 최근에 glBindBuffer로 바인드된 IBO가 glDrawElements에서 활용하는 인덱스 정보를 담고 있는 GPU 메모리 위치로 활용된다.
정리하자면,  glDrawElements에서  가장  마지막  함수인자가  (void*)0인  경우,  인덱스  데이터를  얻기  위해  CPU  메모리를 참조하지  않고  가장  최근에  바인드된  IBO를  참조하는  방식으로  동작한다.



### 4        정리

모던 OpenGL에서 버퍼 객체를 이용해 렌더링을 할 때, __메인 메모리의 데이터를 전혀 참조하지 않고__ GPU 메모리에 있는 데이터만 참조해서 그림을 그렸다는 사실이다. 모던 OpenGL이 이런 방식으로 동작하기 때문에 정점에 대한 데이터가 메인 메모리와 GPU 메모리 두 곳에 존재한다는 사실 또한 중요하다. 



따라서, 효과적인 모던 OpenGL 프로그램 작성을 위해서는 두 곳에 존재하는 데이터를 어떻게 효과적으로 동기화(synchronization)할 것인가를 항상 고민해야 한다.

```markdown
# 생각해볼 문제
모던  OpenGL의  클라이언트-서버  모델을  이해하고  다음  사항을  고민해  보자.

1) 정점의  삼차원  위치나  칼라  데이터를  업데이트하고  새로  그리려면  어떤  방식으로  해야  할까?

2) GPU가  메인  메모리를  접근하지  못하도록  설계되어  있는데  왜  그런  것일까?

참고:  glMapBuffer와  glUnmapBuffer를  활용하면  위  사항에  대한  고민을  해결할  수  있다.
```



```markdown
하나의 함수를 호출하여 전체 buffer를 채우는 것 대신 __glBufferSubData__ 함수를 사용하여 buffer의 특정 부분을 채우는 것 또한 가능합니다. 
이 함수는 buffer target, offset, 데이터의 크기, 실제 데이터를 파라미터로 받습니다. 
이 함수의 새로운 점은 이 buffer를 어디에서부터 채울지를 지정하는 offset를 정해줄 수 있다는 점입니다. 
이는 buffer 메모리의 특정 부분에만 삽입/수정할 수 있도록 해줍니다.
이 buffer는 충분한 메모리가 할당되어있어야하므로 glBufferSubData 함수를 호출하기 전에 glBufferData 함수를 꼭 호출해야 합니다.


Buffer에 데이터를 집어넣는 또다른 방법은 
pointer에게 buffer의 메모리를 요청하고 
__데이터를 buffer에 직접 복사__하는 방법입니다. 


__glMapBuffer 함수를 사용하면 OpenGL은 현재 바인딩된 buffer의 메모리를 가리키고 있는 포인터를 리턴합니다.__

glUnmapBuffer 함수를 통해 포인터 작업이 끝났다고 알려줌으로써 OpenGL은 수행이 완료되었다는 것을 알 수 있습니다. 
Unmapping하여 이 포인터는 무효화되고 이 함수는 OpenGL이 buffer에 데이터를 성공적으로 매핑할 수 있었다면 GL_TRUE를 리턴합니다.

  glMapBuffer 함수를 사용하는 것은 먼저 임시메모리에 저장하지 않고 직접적으로 데이터를 buffer에 매핑하기에 유용합니다. 파일에서 직접적으로 데이터를 읽고 buffer의 메모리에 복사하는 것을 생각해보세요.
```



