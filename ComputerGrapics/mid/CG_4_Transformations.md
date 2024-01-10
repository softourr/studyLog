[TOC]



# CG_4_Transformations

## Affine Space & Homogeneous Coordinates

```markdown
openGL은 homogeneous coordinate system을 사용함
2차원(x,y)는 3차원(x,y,1)로 표기함

비례, 
```

## 3/27

- 그래픽 카드는 homogeneous coordinates를 지원함
- 한차원을 더 더해서 벡터를 표현함

## Affine Space

+ 방향(벡터),위치(포인트),세기(스칼라) 세 가지를 포함함

+ 벡터와 위치값을 구분하려고! 사용한다.

+ ```markdown
  # Vector 연산자
  Scalar * Vector = Vector
  Vector + Vector = Vector
  Dot_Product(Vector, Vector) = Scalar
  Cross_Product(Vector, Vector) = Vector

  # Point 연산자
  Point - Point = Vector
  Point + Vector = Point
  0 * Point = 0(Zero Vector)
  ```

+ ​

+ ```markdown
  위치값의 연산? 되나?

  	포인트+포인트는 연산구조 성립x

  	서울-부산은 정의o, 변위==위치의 변화량(벡터)로 표현,

  	포인트-포인트=변위(벡터)

  	포인트 = 포인트 + 벡터

  	__스칼라,벡터,포인트의 연산체계를 합치자 >>> affine space
  	
  __포인트와 벡터는 덧셈 가능, 변위의 개념__

  ```

+ ###스칼라

  + 덧셈, 곱셈 가능
  + 스칼라는 양의 개념, 방향성이 없음=형체가없음=no geometric propoerties, 기하가 없다

+ ### 벡터

  + 크기와 방향으로 이뤄짐

  + segment, 선분, 끊어진 선

  + #### 벡터 operations

    + projection,외부의 현상을 나에게 투사함
    + cross product - 회전

  + #### 벡터 문제

    + 양과 방향만 같으면 같은 벡터로 취급
    + 스타트 포인트가 중요하지 않음, 위치값 달라도 같다.

+ ###포인트

  + 위치, 위치+위치는 연산 불가함, 위치-위치는 벡터 값임! 연산 가능


  + Q스타트 포인트 + 변위, 벡터 = P위치 > 위치에서 벡터만큼 연산하면 위치값 나옴



## Homogeneous Coordinates

+ 벡터와 위치 개념 구분함
+ n차원은 n+1차원 벡터로 나타내기

__> 포인트는 마지막 컴포넌트 1, 벡터는 0__

+ affine space 연산 가능하게 함

  ## 왜 사용?

4곱4 매트릭스에 4곱1 벡터 곱하면 4곱1 벡터 결과 나옴



A(m*n) - (입력 n차원) > 출력 m 차원, a는 linear func

입출력이 4d로 나와야 하기에 a func 함수는 4*4로 행렬이 됨



---

---



# Linear Transformation

```markdown
행렬,매트릭스로 표현 가능
덧셈이 아니라 곱셈으로 설계

로테이션, 스케일링은 다 행렬 연산, translation만 덧셈 연산이라
이동도 행렬 연산으로 해서 하나의 연산 체계로 해서 하드웨어 설계 쉽게하기 위함

23p까지함
```



## 3/29 수요일

## Linear transformation

### Translation 이동

+ 매트릭스를 곱하자, 단위행렬에 4행만 변수적용

+ 덧셈으로 짜지 않고 곱셈으로 짜는게 하드웨어적으로 비용절감

  ### 해석

  + 16개의 숫자를 4개의 섹터로 분할
  + 위치의 이동과 벡터의 이동 해석
    + 벡터의 의미 유지됨, 이동에 영향x
    + ![image](https://user-images.githubusercontent.com/67236054/233866571-668bb765-33a7-4c45-8794-5bcfc0d4c95e.png)

    ​

---

### Rotation 회전

+ 1,0은 x축 1열, 0,1은 y축 2열

+ homoCoor 활용

  + 001 원점, 100 x축, 010 y축

  + 벡터가 어디있던지 돌리면 됨, 시작위치  의미없음 벡터는

  + ```
    복소수 개념
    +-는 진행방향을 180도로 바꾸는데 i는 진행방향을 90도 바꾼다, 반시계방향
    숫자가 직선상이 아니라 평면상에 놓여진다.
    i는 회전과 관련

    복소수끼리의 곱은 회전값의 덧셈임
    유튭 영상 참고 필요하면

    ```

  + __quaternion__, 실수부 1개 허수부 3개로 표현

    + 3차원의 회전은 unit 쿼터니언에 대응한다. 
    + 특정 회전축을 꽂아서 세타만큼 돌리고 싶다. 25페이지
      + 1열이 첫번째 축이 회전된 후 x축 - 100
      + 물체입장에서  y축 010이 우리가 볼 때의 방향
      + 결과를 해석하고 이해..해야함
      + 카메라 움직임 생각
        + 각 열의 길이는 1로 일정하게 나와야함!
        + 1,2열을 내적하면 0(90도)가 유지되어야 함!
        + 3개의 열이 서로서로 90도 유지되어야함. 내적값 0으로 유지되어야!

### Model Transformations

#### Composite Transformation 합성 변환

+ 좌표값은 물리적으로 의미없음
+ 좌표값과 __좌표계__가 있어야 물리적으로 의미있음
  + 누구의 좌표계인가
  + scale는 원점에서 원점의 2배해도 원점이라 32페이지


---

# 4/3 월요일

#Model Transformations.

## Composite Transformation(합성변환)

scale 보통 먼저함, 모델 좌표계와 월드 좌표계 구분

스케일하면 월드 좌표계 변함, 함수처럼 좌측으로 작용이 쌓임

Sx > RSx > TRSx

두 배 확장되는 func 짜고 싶다 = scaling, linear func > matrix로 짤 수 있다.

rotation : u와 세타 적용

translation,,s : 4*4행렬에서 2,1,0 적용

>  해당 func 행렬에  인자 넣기

각 func는 4*4행렬, 함수는 입력이 오른쪽 , 출력이 왼쪽 (x=2)

T,R,S는 다 Linear 성질 유지, 연산 후 모든 func 적용된 것을 그림

----

물체 원점으로 가져옴 > rotation은 원점 기준으로 돌아감 > 다시 보냄

원점이 아닌 지점을 회전시킬 때



마찬가지로 스케일도 원점을 중심으로 스케일함

물체 중심 원점으로 가져옴 > 스케일함 > 다시 돌려보냄

---

## Instancing

미니언 만들때 100마리 만들지 말고 s,t,r을 100개 만든다.

모델 matrix만 인스턴스 개수만큼 만든다.



# Transformations for hierarchical objects

## Hieracrcical Transformation

달 > Rx, 회전, 모델데이터는 움직이지 않는다. 각각의 점의 rotation 먹이자 회전한 것처럼 보임

달의 좌표계, 지구의 좌표계

결론은 좌변의 지구의 좌표계 나옴

즉 우변에 달의 좌표계의 어떤 지점이 지구의 좌표게에서는 어디인지 계산식

![image](https://user-images.githubusercontent.com/67236054/233866696-0b20bde9-8d8e-4d9f-865e-2515ff69e08f.png)



예시 달에서 1,0을 수식에 넣으면 지구 좌표계에서의 그 위치 좌표가 나옴

> 좌표계 변환

a좌표계의 좌표가 b좌표게에서는 얼마인지 계산하는 수식

> 수식의 의미 알기!  그 좌표계에서 읽은 좌표값, 수식은 좌표계 변환

Xmoon이 입력, 결과 Xearth 나옴

이를 활용해서 카메라 전환이나 시점 변환 가능

@ 좌표계와 좌표시스템을 이해하자



## 코딩 48페이지

Drawarrays는 자기 좌표게에서 그림

자전을 하고 싶다

​	rotate 함수, rotation 곱해서 적용함. draw_moon함

​	결과 자전한 달이 그려짐



추가 지구에서 이동

![image](https://user-images.githubusercontent.com/67236054/233866758-57b53737-b13e-4824-98a2-9b27538a74a3.png)

​	t함수 추가, draw하면 지구좌표계를 기준으로 달을 그린다.

​	지구는 지구 좌표계에서 바로 draw_earth하면 됨

​	지구가 원점이고 달이 지구를 원점으로 도는 달 그림



태양계

​	태양은 태양 좌표계에서

​	지구계를 rotation, translate 시킴

​	태양계가 원점인 지구계를 그림

![image](https://user-images.githubusercontent.com/67236054/233866805-f39331bd-d9de-40ee-a208-810df272cf92.png)





# View Transformations 53페이지

카메라 시점

월드를 기준으로 자신의 원점이 계속 바뀜

벡터는 원점의 으미가 없다..?

왜안끝나요 ㅠㅠ ㅋㅋㅋ..ㅋ.ㅋ.ㅋ.ㅋ...

0은 원점을 안썼다는 의미래..원점이 필요없다.



# 4/5 수요일

## View Transformations

53페이지

뷰어가 카메라

> Ortho means that the basis vectors are orthogonal to each other
>
> 오쏘는 basis 벡터가 서로 직교한다는 의미임
>
> 노멀은 basis 벡터의 길이가 다 1임
>
> 각 축의 unit 길이도 1임

스케일을 제외한 것 리지드바디모션

오쏘노멀

스케일이 없음. 직각으로 노말은 크기가 1이 됐다.

카메라는 오쏘노멀, 오른손 좌표계를 씀, 오른손의 엄지방향이 z임

opengl은 오른손 좌표계



## Inside of gluLookAt()

glulookat함수

카메라를 위치시킴, 인자 카메라 위치,cop + 

카메라 기본적으로 오른손 좌표계

오른손으로 감을 수만 있으면 오른손 좌표계임

카메라의 오른쪽으로 갈수록 x값 증가, 등 설계 되어있음



V=TR

월드관점에서 봤을때 카메라가 그런것



## 카메라 프레임

이제 58페이지의 주황색 좌표계 기준으로 좌표값이 다 업뎃됨

59페이지



근데 카메라는 보여주는 거라 카메라가 보여주는  세상을 보여줘야함. 물체랑 다름



그 작업이 61페이지

카메라도 물체긴 함. 이전까지 작업한거고



최종적으로 카메라가 바라보는 세상을 해야하니까 Inverse를 취한다.

![image](https://user-images.githubusercontent.com/67236054/233866906-a8b6e11d-f6aa-4fbc-956c-110c5fa898d9.png)



로테이션 매트릭스는 ortho라서 inverse가 쉬움, 

행열 바꾸는 전치하면 된다



알아야할건 물체의 변환, 그리고 카메라는 물체의 변환에 최종적으로 카메라 좌표계로 바꾸는 작업 또 필요하다.! 그래서 Inverse 취해야하는데 ortho라서 전치만 하면 된다.



##Revisiting Composite Transformation

### 합성 변환

65페이지

결과가 d만큼 이동하고 젤 오른쪽 열이 그걸 나타냄



카메라도 마찬가지, 결국 화면은 카메라 기준



V의 inverse를 계산해주는게 gluLookAt임

> 모든 스케일, 로테이션은 원점으로 갔다가 하는게 디폴트임

68페이지

V 최종은 좌측상단은 로테이션 나타내고, 오른쪽 열은 이동 나타냄

최종은 거기에 Inverse를 해서 어쩌구한 결과값



# LAB_User_Interactions

## 실습 코드 작성

실습  코드를  완성하는데  있어  핵심이  되는  사항은  다음  세  부분이다.
1)         콜백함수   선언   및   등록

​	사용자   입력을   처리할   콜백   함수를   선언하고   등록한다.   한번   등록해   두면,   GLFW는   이벤트가 
발생될  때마다  등록해  놓은  콜백함수를  자동으로  호출한다.
2)         콜백함수  구현

​	선언한  콜백  함수를  구현한다.  앞서,  우리가  정의한  변수는  콜백  함수를  구현한  코드  내에서  목적에  맞게 업데이트  한다.
3)         업데이트된  변수  적용

​	콜백함수에  의해  업데이트된  변수를  OpenGL  함수에  넘겨  화면이  업데이트  되도록  한다.



이제  main.cpp  코드를  수정하여  우리가  정의한  특정  키가  눌리면  사용자  입력에  반응할  변수들을  업데이트하도록  하자.  먼저 OpenGL  프로그램에서  사용자의  입력에  반응할  변수를  소스코드  main.cpp에  앞쪽에  다음과  같이  정의한다.

![image](https://user-images.githubusercontent.com/67236054/233857476-81e019aa-06ab-4a2d-af3c-16196a0f21e7.png)



## 3.1        키보드  이벤트  콜백함수  선언  및  등록

GLFW는  윈도우가  전달하는  각종  이벤트에  반응할  수  있도록  설계되어  있다. 

여기서  이벤트라  함은  키보드  입력,  마우스  움직임 및  버튼  클릭,  화면의  크기  변경  등을  말한다.

기본적으로 GLFW로 작성된 프로그램은 각 이벤트에 대해 아무런 반응을 보이지 않는다. 

만일 프로그래머가 특정 이벤트(예를 들어 키보드 누르기)에 대해 반응할 수 있도록 작성하려면 



GLFW가 정의한 방식대로 __콜백함수를 등록__하고, 

이벤트가 적절히 처 리되도록 해당 __콜백함수를 구현__해야 한다. 




여기서는 키보드 입력에 따라 반응하는 프로그램을 작성하기 때문에, 키보드 이벤트를 다룰 수 있는 콜백함수 key_callback() 를  선언하고  glfwSetKeyCallback()로  콜백함수를  GLFW에  등록한다.

콜백함수를  등록할  때  유의해야할  점은  두가지는  아래와  같다.
1) 콜백함수의 입출력은 반드시 GLFW에서 정해놓은 형식을 따라야 한다. 

glfwSetKeyCallback()에 등록할 키보드 콜 백함수는 GLFWkeyfun의 입출력 형식을 따라야 한다. 

우리가 작성한 콜백함수 key_callback()는 GLFWkeyfun의 입출력 형식을 따르고 있음에 주목하자.

2)         콜백함수는   반드시   __렌더링   루프   이전에   등록__해야   한다. 

우리가   작성한   콜백함수   key_callback()는   렌더링   루프에 들어가기  전에  glfwSetKeyCallback()를  이용해  GLFW에  등록하였음을  주목하자.

![image](https://user-images.githubusercontent.com/67236054/233857614-3cf140f5-7158-4539-af48-b2e03e640042.png)

## 3.2        키보드  이벤트  콜백함수  구현

키보드 이벤트 처리를 담당할 콜백함수 key_callback() 함수를 다음과 같이 main.cpp 파일에 구현하여 키에 따라 변수가 적절히 업데이트 되도록 한다. 

![image](https://user-images.githubusercontent.com/67236054/233857697-9cd05efc-dcc5-400b-9bf1-08e5c6716418.png)

## 3.3        업데이트된  변수  적용

이제  등록한  사용자  이벤트,  즉  키보드가  눌릴  때마다  키보드  콜백함수인  key_callback()가  호출된다.  또,  key_callback() 함수에서  우리가  설계한  로직에  따라  특정  키가  눌리게  되면  그에  알맞게  변수가  업데이트  되었을  것이다.



이제  남은  일은  업데이트된  변수를  OpenGL에  적용하여  __화면을  업데이트__하는  것이다.  다음은  main()  함수에  정의된  루프로 GLFW에서  매  프레임마다  어떻게  OpenGL  렌더링을  처리할  것인지  정의한  코드  조각을  보여주고  있다.

![image](https://user-images.githubusercontent.com/67236054/233857749-236a096a-181d-45a5-aaee-13ec82d3d066.png)

매  프레임마다  어떤  방식으로  OpenGL  렌더링을  할  것인지는  사용자가  직접  정의할  수  있다.  

위  코드  조각에서  사용자  정의 렌더링  코드는  크게  다음의  3가지  작업을  하고  있다.
1)         업데이트된  배경색  적용:  glClearColor()함수
2)         업데이트된  물체  변환  적용:  set_transform()  함수
3)         업데이트된  렌더링  방식  적용:  render_object()  함수



## 3.3.1       업데이트된  물체  변환  적용

OpenGL에서 배경색은 glClearColor()를 통해 설정할 수 있다. 

다만, 배경색을 이용해 실제로 배경을 지우는 함수는 glClear() 이므로,  

glClear()가  호출되기  전에  업데이트된  배경색을  glClearColor()를  통해  OpenGL에  전달해  주기만  하면  된다.

배경색은   매   프레임마다   렌더링   전에   이미지   전체에   적용해야   하므로,   위   코드조각처럼   렌더링   루프   안에서   정의된   사용자 렌더링  코드  중  첫번째로  불리는  코드가  되어야  한다.



---

아래 코드조각은 변환(transformation)을 설정하는 set_transform() 함수이다. 

여기서 mat_view와 mat_proj은 카메라의 외부/내부 파라메터와 관련된 행렬이고 

현재 예제에서는 항등행렬로 설정하였다. 

즉, 카메라에 대한 설정은 따로 설정하지 않은 것이다.

 본 예제에서는 카메라의 변환을 다루지 않을 예정이니, 아래 코드조각에서 설정한 값을 그대로 사용하자.



물체의 변환은 모델 행렬 mat_model에서 다룬다. 

이전 코드에서 키보드 입력에 따라 물체의 위치 이동을 

g_translate_x, g_translate_y, g_translate_z 변수에 설정해 두었으므로, 

여기서는 GLM 함수 glm::translate를 호출하여 이동 행렬 (translation matrix)를 반환받고 이를 모델 행렬 mat_model로 설정한다.
또한,  g_is_animation의  값이  true인  경우  애니메이션을  위해  물체의  x-축  이동  위치를  나타내는  값  g_translate_x를 업데이트  한다.

![image](https://user-images.githubusercontent.com/67236054/233857873-ae9b16ac-e1c5-44a0-844f-094254dee58e.png)



## 3.3.3       업데이트된  렌더링  방식  적용

아래 코드조각은 업데이트된 렌더링 방식을 적용하여 물체를 렌더링하는 render_object() 함수이다. 

앞서 키보드 입력을 처리하여 배경색과 와이어프레임 모드 여부에 관한 변수를 업데이트하였기 때문에 

여기서는 업데이트된 변수를 이용해 물체를 렌더링하면 된다.



OpenGL에서 와이어프레임을 그리기 위해서는 여러가지 방법이 있지만, 가장 흔하게 사용되는 방식은 폴리곤의 내부를 채우지 않고 폴리곤의 경계인 라인(line) 부분만 그리게 하는 것이다. 

glPolygonMode()는 폴리곤을 채워서 그릴지 (GL_FILL), 그렇지 않고 경계만 그릴지 (GL_LINE)를 설정할 수 있는 함수이다.

![image](https://user-images.githubusercontent.com/67236054/233858117-46cfe9c4-8bf7-499c-9e49-e2804bdadf71.png)

