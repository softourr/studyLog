// 10장
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
/*
Specifying Uniform / Vertex Attribute Data
쉐이더 프로그램 초기화, 그리기 작업 수행
*/
////////////////////////////////////////Vertex Shader//////////////
#version 120 // GLSL 1.20
// uniforms used by the vertex shader
uniform mat4 u_PVM;
// attributes input to the vertex shader
attribute vec3 a_position;
attribute vec3 a_color; // input vertex color
// varying variables - input to the fragment shader
varying vec3 v_color; // output vertex color
void main()
{
    gl_Position = u_PVM * vec4(a_position, 1.0f);
    v_color = a_color;
}
/////////////////////////////////////////////////////////////
///////////////////////////////////////// Fragment Shader
#version 120 // GLSL 1.20
varying vec3 v_color;
void main()
{
    gl_FragColor = vec4(v_color, 1.0f);
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
GLuint vertexShader, fragmentShader, programObject;
GLuint loc_a_position, loc_a_color, loc_u_PVM;
GLuint position_buffer, color_buffer;
void init()
{
    programObject = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // get uniform / vertex attribute locations
    loc_u_PVM = glGetUniformLocation(programObject, "u_PVM");
    loc_a_position = glGetAttribLocation(programObject, "a_position");
    loc_a_color = glGetAttribLocation(programObject, "a_color");
    // 프로그램 객체 내에서 해당 변수 위치 가져옴
    glLinkProgram(programObject);
}
void draw()
{

    std::vector<glm::vec3> tv_positions; // per triangle-vertex 3D position
    std::vector<glm::vec3> tv_colors;    // per triangle-vertex 3D color
    // 버텍스 데이터 설정
    glm::mat4 mat_PMV; // Proj * View * Model
    // You set tv_positions, tv_colors, mat_PVM, and then...

    glUniformMatrix4fv(loc_u_PVM, 1, GL_FLASE, glm::value_ptr(mat_PVM));
    /*
    유니폼 변수에 값을 전달!
    ptr은 포인터로 반환, mat_PVM 데이터를 포인터로 반환
     */
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, &tv_positions[0]);

    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, &tv_colors[0]);

    glDrawArrays(...);
    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);
}

/*
65페이지
*/
////////////////////////////Simple Rendering w/ Objects and a Camera
GLuint vertexShader, fragmentShader, programObject;
GLuint loc_a_position, loc_a_color, loc_u_PVM;
GLuint position_buffer, color_buffer;
void init()
{
    programObject = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // get uniform / vertex attribute locations
    loc_u_PVM = glGetUniformLocation(programObject, "u_PVM");
    loc_a_position = glGetAttribLocation(programObject, "a_position");
    loc_a_color = glGetAttribLocation(programObject, "a_color");
    // 프로그램 객체 내에서 해당 변수 위치 가져옴
    glLinkProgram(programObject);
}
void set_gl_buffers()
{
    std::vector<glm::vec3> tv_positions; // You set per triangle-vertex 3D position
    std::vector<glm::vec3> tv_colors;    // You set per triangle-vertex 3D color
    // 객체의 위치와 색상 데이터 설정
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * tv_positions.size(), &tv_positions[0], GL_STATIC_DRAW);

    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * tv_colors.size(), &tv_colors[0], GL_STATIC_DRAW);
    // 버퍼 생성, 버퍼 바인딩, 데이터 버퍼에 전송
}
void render()
{
    glm::mat4 mat_PMV; // You compute PVM matrix, for example, using glm
    glUniformMatrix4fv(loc_u_PVM, 1, GL_FLASE, glm::value_ptr(mat_PVM));
    // 유니폼 변수에 전달, 업뎃

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // attriute의 변수 위치와 형식 설정
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(loc_a_color);
    glVertexAttribPointer(loc_a_color, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(...);

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_color);
}
///////////////////////////////////////////////////////Per-Fragment (Pixel) Lighting
/*
74페이지
*/
// vertex shader
#version 120               // GLSL 1.20
attribute vec3 a_position; // per-vertex position
attribute vec3 a_normal;
uniform mat4 u_PVM;
// for phong shading
uniform mat4 u_model_matrix;  // 모델 행렬
uniform mat3 u_normal_matrix; // 법선 행렬
// world coordinate 월드 좌표계에서의 위치와 법선 값 전달용
varying vec3 v_position_wc;
varying vec3 v_normal_wc;

void main()
{
    gl_Position = u_PVM * vec4(a_position, 1.0f);
    // 버텍스의 위치를 행렬 곱해서 클립 좌표계로 변환
    v_position_wc = (u_model_matrix * vec4(a_position, 1.0f)).xyz;
    // 버텍스의 위치를 모델 행렬과 곱해 월드 좌표계로 변환  저장
    v_normal_wc = normalize(u_normal_matrix * a_normal);
    // 버텍스의 법선 값을 법선 행렬과 곱해 월드 좌표계로 변환하고 정규화해 저장
}

// fragment shader
#version 120                // GLSL 1.20
varying vec3 v_normal_wc;   // 월드 좌표계로 변환된 법선 벡터
varying vec3 v_position_wc; // 월드 좌표계로 변환된 위치 벡터
// 조명
uniform vec3 u_light_position;
uniform vec3 u_light_ambient;
uniform vec3 u_light_diffuse;
uniform vec3 u_light_specular;
// 물체
uniform vec3 u_obj_ambient;
uniform vec3 u_obj_diffuse;
uniform vec3 u_obj_specular;
uniform float u_obj_shininess;

uniform vec3 u_camera_position;
uniform mat4 u_view_matrix;
vec3 directional_light() // 조명 모델 구현
{
    vec3 color = vec3(0.0);
    vec3 normal_wc = normalize(v_normal_wc);
    vec3 light_dir = normalize(u_light_position);
    // ambient
    color += (u_light_ambient * u_obj_ambient);
    // diffuse
    float ndotl = max(dot(normal_wc, light_dir), 0.0); // 정면방향만, 내적
    color += (ndotl * u_light_diffuse * u_obj_diffuse);
    // specular
    vec3 view_dir = normalize(u_camera_position - v_position_wc); // 픽셀의 방향
    vec3 reflect_dir = reflect(-light_dir, normal_wc);
    // 픽셀에서 광원을 향하는 방향, 빛방향 벡터를 표면의 법선에 반사시캄
    float rdotv = max(dot(view_dir, reflect_dir), 0.0);
    // 내적값 0이상으로 제한
    color += (pow(rdotv, u_obj_shininess) * u_light_specular * u_obj_specular);

    return color;
}
void main()
{
    vec3 result = directional_light();
    gl_FragColor = vec4(result, 1.0f);
}
///////////////////////////////////////////////////Texture Mapping with Sampler
/*
89페이지
*/
// vertex shader
#version 120 // GLSL 1.20
uniform mat4 u_PVM;
attribute vec3 a_position; // per-vertex position (per-vertex input)
attribute vec2 a_texcoord; // 텍스처 좌표 벡터
varying vec2 v_texcoord;
void main()
{
    gl_Position = u_PVM * vec4(a_position, 1.0f); // 빌트인 변수, 버텍스 위치 정규화 좌표계 변환결과 저장
    v_texcoord = a_texcoord;                      // 텍스처 좌표 픽셀 쉐이더에 보간되어 전달
}
// fragment shader
#version 120 // GLSL 1.20
// texture mapping
uniform sampler2D s_texture;
varying vec2 v_texcoord;
void main()
{
    gl_FragColor = texture2D(s_texture, v_texcoord);
}
/////////////////////////////////////////main.cpp

// Texture object handle
GLuint tex_id;
GLuint loc_a_position, loc_a_texcoord, loc_s_texture;
void init()
{
    loc_a_position = glGetAttribLocation(program, "a_position");
    loc_a_texcoord = glGetAttribLocation(program, "a_texcoord");
    loc_s_texture = glGetUniformLocation(program, "s_texture");
}
// Compile sahders and Link them into the program loc_a_position= glGetAttriblocation(program, "a_position"); loc_a_texcoord = glGetAttribLocation (program, "a_texcoord"); loc_s_texture = gÏGetUniformLocation (program, "s_texture");
void set_texture2D() // 텍스처 로드하고 바인딩
{
    unsigned char *image;
    // Fill image contents
    image = stbi_load(img_filepath.c_str(), &width, &height, &channels, STBI_rgb);
    glGenTextures(1, &tex_id); // 텍스처 객체 생성
    glBindTexture(GL_TEXTURE_2D, tex_id);

    g1TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    g1TexParameter f(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    g1TexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    g1TexParameter f(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    g1TexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
void render()
{
    // Set the sampler to texture unit
    glUniform1i(loc_s_texture, 0); // 샘플러2d 유니폼 변수에 유닛 번호 할당
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    // texcoord
    glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer_);
    glEnableVertexAttribArray(program.loc_a_texcoord);
    glVertexAttribPointer(program.loc_a_texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
