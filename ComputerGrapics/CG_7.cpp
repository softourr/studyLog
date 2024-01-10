// Initialization of Vertex Shader, Fragment Shader,and Program Object
///////////////////////////////////////////////////7장 20페이지
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void init_shader_program()
{
    GLuint vertex_shader = create_shader_from_file("./shader/vertex.glsl", GL_VERTEX_SHADER);
    std::cout << "vertex_shader id: " << vertex_shader << std::endl;
    assert(vertex_shader != 0);

    GLuint fragment_shader = create_shader_from_file("./shader/fragment.glsl", GL_FRAGMENT_SHADER);
    std::cout << "fragment_shader id: " << fragment_shader << std::endl;
    assert(fragment_shader != 0);

    /*
    create_shader_from_file을 통해 각각 정점 쉐이더와 프래그먼트 쉐이더의 식별자를 가져옴.
    쉐이더 객체는 GLSL 소스 코드 파일을 로드하여 생성됩니다.
    */
    /*
    assert() 문을 사용해 프로그램의 실행 중간에 문제가 발생했는지 확인, 문제 생기면 프로그램 중단됨*/
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader); // 쉐이더 객체를 쉐이더 프로그램에 연결
    glLinkProgram(program);                   // 쉐이더 프로그램을 링크합니다. 링크 과정에서 쉐이더 객체들이 결합되고 최종적인 실행 가능한 프로그램이 생성
    std::cout << "program id: " << program << std::endl;
    assert(program != 0);

    GLint loc_u_PVM = glGetUniformLocation(program, "u_PVM");
    // 프로그램 내에서 유니폼 변수 u_PVM의 위치를 가져옵니다. 이 위치는 나중에 유니폼 값을 설정할 때 사용
    GLint loc_a_position = glGetAttribLocation(program, "a_position");
    GLint loc_a_color = glGetAttribLocation(program, "a_color"); // 정점 속성 변수 a_position과 a_color의 위치를 가져옵니다. 이 위치는 정점 데이터를 전달할 때 사용
}
/*
glCreateProgram()을 사용하여 쉐이더 프로그램을 생성합니다.
쉐이더 프로그램은 정점 쉐이더와 프래그먼트 쉐이더를 함께 처리하기 위한
실행 가능한 프로그램
*/

// Rendering with Programmable Rendering Pipeline
void render_object()
{
    // Use a program
    glUseProgram(program); // 쉐이더 프로그램을 사용하도록 설정합니다. 이를 통해 그래픽스 렌더링에 사용할 쉐이더 프로그램이 선택
    // Load uniforms (Here, for setting mat_PVM as Proj * View * Model)
    mat_PVM = mat_proj * mat_view * mat_model;
    glUniformMatrix4fv(loc_u_PVM, 1, GL_FALSE, mat_PVM); // mat_PVM 행렬을 loc_u_PVM 유니폼 변수에 전달하여 프로그램 내에서 사용될 값으로 설정
    // Load attributes as per-vertex data (Here, we use VBO)
    glBindBuffer(…);
    glEnableVertexAttribArray(…);
    glVertexAttribPointer(…); // 버텍스 버퍼 객체(VBO)를 바인딩하고, 버텍스 속성 배열을 활성화하고, 정점 데이터의 구조 및 속성을 지정합니다. 이를 통해 개체의 정점 데이터가 쉐이더 프로그램으로 전달
    // Draw with per-vertex data
    glDrawArrays(…); // 정점 데이터를 사용하여 개체를 그립니다.이 함수는 정점 데이터에 따라 도형을 그릴 때 사용
    // …
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////32페이지
////////////////////////////////////////////////////vertext shader
/*요약 : 입력으로 들어오는 버텍스의 위치(a_position)와 색상(a_color)을 받아서,
투영 변환(u_PVM)을 적용한 후 출력으로 전달*/

#version 120        // GLSL 1.20
uniform mat4 u_PVM; // Proj * View * Model // 프로젝션 행렬, 뷰 행렬, 모델 행렬의 곱셈 결과를 저장하는 역할

attribute vec3 a_position; // per-vertex position (per-vertex input)
attribute vec3 a_color;    // per-vertex color (per-vertex input)
// 입력으로 받은 버텍스의 위치와 색상 정보를 각각 저장
varying vec3 v_color; // per-vertex color (per-vertex output)
/*이 변수는 버텍스 쉐이더의 출력으로 사용되어 프래그먼트 쉐이더로 전달됩니다.
버텍스마다 해당 변수의 값이 보간되어 프래그먼트 쉐이더로 전달되며,
이를 통해 각 픽셀에 대한 색상 값을 계산*/
void main() // 각 버텍스마다 실행, per-vertex
{
    gl_Position = u_PVM * vec4(a_position, 1.0f);
    v_color = a_color;
    /*gl_Position에는 투영 변환(u_PVM)을 적용한 버텍스의 위치가 저장되고,
    v_color에는 해당 버텍스의 색상이 저장*/
}

///////////////////////////////////////////////////fragment shader
///////////////////////////////////////////////////fragment shader
///////////////////////////////////////////////////fragment shader
/*요약 : 입력으로 전달받은 버텍스에서 보간된 색상 정보(v_color)를 받아와,
해당 픽셀의 색상을 결정하는 역할*/
#version 120          // GLSL 1.20
varying vec3 v_color; // per-fragment color (per-fragment input)
/*
버텍스 쉐이더에서 전달된 값으로 초기화되며,
각 픽셀에 대한 보간된 색상 값을 저장합니다.
버텍스 쉐이더에서 출력된 v_color 변수의 값은
프래그먼트 쉐이더로 보간되어 전달
*/
void main() // 각 픽셀마다 실행
{
    gl_FragColor = vec4(v_color, 1.0f);
    // gl_FragColor에는 v_color 값을 이용하여 해당 픽셀의 색상이 설정
    /*v_color 값을 RGBA 형태의 vec4로 변환하여 gl_FragColor에 저장합니다.
    마지막 인자인 1.0f는 알파 채널을 나타내며, 투명도를 설정*/
}

/////////////////////////////////////////////////////////main.cpp
/////////////////////////////////////////////////////////main.cpp
/////////////////////////////////////////////////////////main.cpp
GLint loc_u_PVM, loc_a_position, loc_a_color;
void init_shader_program()
{
    // Create a shader program with a vertex shader and a fragment shader
    program = glCreateProgram(); // 쉐이더 프로그램 생성
    // …
    // Get uniform / vertex attribute locations
    loc_u_PVM = glGetUniformLocation(program, "u_PVM");
    loc_a_position = glGetAttribLocation(program, "a_position");
    loc_a_color = glGetAttribLocation(program, "a_color");
    /*프로그램 내에서 사용할 유니폼 변수와 버텍스 attribute 변수의 위치 저장하는
    GLint형 변수 3개*/
}
void render_object()
{
    // Use the progam
    glUseProgram(program); // 만든 쉐이더 프로그램 활성화
    // Setting Proj * View * Model
    mat_PVM = mat_proj * mat_view * mat_model;
    glUniformMatrix4fv(loc_u_PVM, 1, GL_FALSE, mat_PVM);
    // 유니폼 변수에 mat_PVM 값 전달
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    /*position과 color 변수 활성화하고 해당 변수에 대한 데이터 속성 설정
    버텍스 배열 객체에 저장된 데이터를 쉐이더의 attribute 변수와 연결*/
    // Draw triangles
    glDrawArrays(GL_TRIANGLES, 0, 3); // 랜더링할 객체 그림
    /*현재 활성화된 쉐이더 프로그램과 설정된 attribute 변수에 따라
    버텍스 데이터 사용해 도형 그림*/
    // …
}