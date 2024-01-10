# CG_7_중간이후__Programmable renderingPipeline

5/1

![image](https://user-images.githubusercontent.com/67236054/235416934-96ff6bd3-0c9d-402e-a32d-863de5f841af.png)

((래스퍼가 primitive를 픽셀, fragment로 바꾸고 보간, 이중보간하는, 프랙이 개수더많음 그걸 채우는 것들 보간하고 채우는))

## Fixed 랜더링 파이프라인

```markdown
구식 방법

인풋이 버텍스고 아웃풋이 픽셀이다
rasterizer가 버텍스를 프래그먼트/픽셀로 바꾸는 결정적인 역할함

버텍스 프로세서가 끝나면 vertex color가 결정되어 나감
컬러정보 없으면 이중보간하거나 해서 여기서 만들어서 내보냄

rasterizer에서 vertex color값을 interpolating 보간함
bilinear interpolating 이중보간을 해서 다 컬러값을 채운다.
	!!!초기에 있는 버텍스를 제외하고는 스스로 컬러를 결정할 수 없었음 이중보간해야 컬러 결정되는

빛이 있어서 어딘가를 하이라이팅할때 기존 방법은 하이라이팅이 안됨
per-vertex lighting > 초기에 주어진 버텍스 값을 기반으로 나머지 컬러 값들이 결정되기 때문에 문제생김

# 해결
버텍스 프로세서와 프랙프로세서를 수정함

1. 버텍스 프로세서에서 컬러 결정을 하지 말자
2. 프랙프로세서에서 컬러 결정하자

1. 버텍스 프로세서에서 컬러 결정하는 부분 프랙으로 보냄
2. 노말 정보를 interpolate 보간하는 걸 rasterizer가 하자

((클리핑을 해도 최종 픽셀에 반영안되는 프래그먼트들 좀 생길수밖에 없음))


///
컬러계산 vertex 프로세서에서 하고 클리핑하고 보간하고 그걸 보간한 컬러가 fragment 프로세서에서 정해짐
bilinerar보간해서 결정되는 컬러값

기존방법에서는 이중보간해서  13페이지같은 퍼포먼스가 불가했음 
vertex로 컬러값을 넘겨줘서
중간에 갑자기 색있는 이런게 안됨, 하이라이트 효과같은거

그래서 바뀐 방법이
최종컬러계산을 fragment 쉐이더에서 결정하는
vertex에서 안하고
```



17페이지

![image](https://user-images.githubusercontent.com/67236054/235417686-37337abf-06d0-4294-877b-d5fdaac7e89b.png)

input, output 잘보기



```markdown
# OpenGL GLSL
GLSL
첫번째줄 #으로 시작하는건 preprocessor, 코드 맥락이 어떤걸 기준으로 되어있는가
openGL버전 어떤걸 사용하는지

    uniform > 글로벌 변수, GPU 내부에서 전체적으로 정의되는 글로벌 변수
    attribute > vertex에 대한 attribut 담음
    varying > change 비슷, 버텍스가 최종에 픽셀로 바뀜, 


raserizer에서 fragment로 바꿔줌!!! 그래서 프랙프로세서에서 프랙받고 프랙 아웃으로 내보냄
이때 vertex로 시작해서 fragment로 바뀔수있는 변수가 필요함 그게 varying
보통 버텍프로세서에 하나, 프랙프로세서에 하나, 같은 변수이름으로 존재
버텍의 varying는 아웃풋(assign됨,좌변), 프랙의 varying는 인풋(등호기준 우변)임
결국 varying는 vertex에서 fragment로 변하는것

((
- 먼저 버전 선언 GLSL
- 쉐이더마다 메인 함수 존재
중요한거 독립적
vertex마다 독립적으로 로직이 돌아감
각 버텍스마다 작동함, 병렬적으로 작동함
중요 independent하게 돌아감

# uniform 중요
gpu내부에서 어떤 단계이든간에 유니폼 변수는 가져다 쓸수있음
일종의 전역변수같은 c에서
버텍스위치에 호모 좌표계로 바꾸고(a_pos, 1.0f)
매트릭스 곱해서 클리핑?인가전단계까지 완

# varying 변수
버텍스 쉐이더부터 fragment 쉐이더까지 값 전달, 일종의 아웃풋, vertex output이고 fragment input인
래스터화를 거쳐서 프래그먼트화된 컬러 v_color을 프래그먼트 쉐이더에서 처리

))
```



```
@@@varying은 버텍프로세서에서 나올때 버텍스 정보 가짐.
그리고 레스터 거쳐서 fragment 정보로 변한다.
그렇게 변한 fragment 정보가 프랙프로세서의 input으로 들어감@@@
```

17페이지의 main()은 버텍 쉐이더는 per-vertex, 각 버텍스마다 로직 돌아감. 1000개라고 하면 1000개 병렬처리

프랙쉐이더는 per-fragment, 각 프랙마다 돌아감 10000개라고 하면 만개 병렬처리

```
pre-definde 된? 녹색 부분은 선언하지 않았는데 사용함

```



## GLSL 컴파일

18페이지

![image](https://user-images.githubusercontent.com/67236054/235418193-7fd553d7-4237-4465-a257-490777e205f2.png)

```markdown
쉐이더도 결국 C/C++같은 코드라 컴파일해서 링킹해서 실행가능한 프로그램으로 만들어야함.
여기서는 GPU가 실행가능한 프로그램이 최종적으로 나옴
또 그걸 탑재, 로딩하는 과정까지 필요

각 쉐이더 오브젝트가 로딩으로 맞는 프로세서로 올라감
OpenGL에서는 컴파일러가 없고 함수로 컴파일, 링킹, 프로그램 업로드 등 다 가능함

((쉐이더마다 코드 올려서 컴파일
각 쉐이더마다 오브젝트 코드 만들어짐
링킹해서 실행가능한 쉐이더 프로그램(gpu 프로그램) 만들어짐
맞는 함수 잘 보기,,

glcreateshader > 박스, 쉐이더 오브젝트 코드 만드는
glshadersource > 텍스트 파일을 컴파일하기 전단계로해서 메모리에 올리겟다, 일종의 로딩
glcreateprogram > 쉐이더 프로그램 오브젝트, 그림상 박스 만드는
링킹전에 attach, glattachshader
그리고 링킹하고
))
```

## 쉐이더 변수에 assign하는 부분이 없다?

20페이지

![image](https://user-images.githubusercontent.com/67236054/235418489-67344f1c-2465-43bd-9ab8-c9a8b19e87e1.png)



```markdown
값에 assign 하는 과정이 없음 선언만 하고 17페이지
누가 gpu에 입력을 넣는가
입력이 gpu 밖에서 들어가는데 c코드가 인풋을 넣어준다
그 입력이 20페이지다(위에 이미지), 왼쪽에 glLinkProgram 아래 부분이 중요함

glgetuniformLocation, 포인터가 아니라 인덱스로 알려줌, a_pos의 위치 loc를 알려줌
glgetattriblocation, attribute 변수의 위치를 알려달라
이제 위치가 어디있는지 안다. 

# 랜더링할때
특정 변수의 위치 위 작업(이니셜,초기화)을 통해 알고있음
glUniformmat4로 첫번째인자가 gpu상의 위치, 
mat_pvm이 cpu에 있는 메모리임
mat_pvm값을 gpu에 쏜다, gpu 위치가 loc_u_pvm
그래서 assign하는 로직이 따로 없어도 된다

/

그래서 cpu상의 위치, gpu상의 위치가 정확해야 하고 또 보낼때도 제대로 가는지 봐야...
전송을, 정보를 안보내주면 안됨, 보내주는!작업 있어야
- 카메라는 uniform 변수로 넣어야(앞에 머라하셨는지 다 놓침)

```



## Programmable Rendering Pipeline

23페이지

```markdown
버텍스 쉐이더에 attribue 최소 8개 받을 수 있음 
attribute에는 좌표 x,y,z나 color r,g,b 아니면 노말 nx,ny,nz 등 가능
그리고 이 attribute들이 버텍 쉐이더 지나서 varying 아웃웃으로 나옴. 
Xclip = PV^-1MXobj
위 공식에서 x 클리핑한게 varying output 나온거고
vertex attribute가 Xobj임.

varying는  user-defined varying
gl_position, gl_frontFacing, gl_pointsize 는 pre-defined varying (3개 존재)

gl_position은 버텍스 쉐이더에 코드 있음
프로그래머가 계산해서 채워라. 나중에 프래그먼트에서 화면 그리는데 필요함
클리핑 스페이스의 좌표값 채워줘야함

```



25페이지

## Uniform - IO Storage Qualifiers

```markdown
유니폼은 전역변수, 화살표 방향중의
쉐이더에서 유니폼값 write, 수정 불가능 (assign 불가능)
쉐이더에서 유니폼값 read만 가능하다. 

그럼 유니폼값을 누가 set하는가?
	cpu, c/c++의 main.cpp에서 설정한다!!@@@
 	gpu의 쉐이더는 유니폼값 업데이트가 불가능하다.

/
built-in이 위의 3개, 이미 정의된 varying 인듯

/여기까지 강의1끝

```

