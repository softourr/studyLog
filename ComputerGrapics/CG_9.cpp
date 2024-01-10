// 9장
/*
텍스처 매핑을 위한 openGL 코드 예시
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
/*
11페이지 텍스처 매핑 - Initialization
*/
// variables for texture mapping 텍스처 매핑에 필요한 변수들
GLuint tex_id;
GLsizei width, height;
GLbyte *img_pixels; // 포인터임
// load an image from system
// img_pixels must locate the client-side memory of the image
// width/height should be update
// pixel format is important
// …
// Generate a texture
glGenTextures(1, &tex_id); // 텍스처 식별자 생성, 생성된 식별자 tex_id변수에 저장
// Bind a texture w/ the following OpenGL texture functions
glBindTexture(GL_TEXTURE_2D, tex_id); // 지정된 텍스처 바인딩, 2D 텍스처 나타내는 상수에
// Select active texture unit 0
glActiveTexture(GL_TEXTURE0); // 활성 텍스처 유닛 선배. 첫번째 텍스처 유닛 사용
// Set texture parameters (wrapping modes, sampling methods)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 텍스처 매개변수 설정
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Transfer an image data in the client side to the server side
glTexImage2D(tex_id, 0, GL_RGBA, width, height, 0,
             GL_RGBA, GL_UNSIGNED_BYTE, pixels);
// 클라이언트 측의 이미지 데이터를 서버 측으로 전송, 이미지>>>텍스처
// Specify texture sampler in shader
glUniform1i(glGetUniformLocation(program, "my_sampler"), 0);
// 셰이더 내에서 사용할 텍스처 샘플러 지정, my_sampler이라는 셰이더의 유니폼 변수에 틱스처 유닛0을 할당
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/*
14페이지, 텍스쳐 매핑 Rendering
*/
// Select active texture unit
glActiveTexture(GL_TEXTURE0); // 활성화 텍스처 유닛 지정, 0번째? 텍스처 유닛 활성화
// Bind a texture w/ the following OpenGL texture functions
glBindTexture(GL_TEXTURE_2D, tex_id); // 해당 텍스처를 현재 활성화된 텍스처 유닛에 연결함
// Rendering w/ texcoords
glBindBuffer(…);
glEnableVertexAttribArray(loc_a_texcoord);
glVertexAttribPointer(loc_a_texcoord, …);
// 텍스처 좌표를 사용해 렌더링을 위해 관련된 버퍼와 속성을 바인딩하고 설정
glDrawArrays(…);                      // 랜더핑 수행
glDisableClientState(loc_a_texcoord); // 텍스처 좌표에 대한 클라이언트 상태를 비활성화

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/*
17페이지, 텍스쳐 래핑모드, 주소모드설정
*/
// texture address mode as repeat
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 텍스처 주소 모드를 반복모드로 지정 > 텍스처 좌표가 벗어나면 반복해서 텍스처 적용

// texture address mode as clamp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 경계고정, clamp to edge모드로 지정 > 텍스처 좌표 벗어나면 가장 가까운 텍스처 좌표값 사용해 텍스처 고정.

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/*
30페이지, 텍스처 필터링, 텍셀에서 어떤 색을 픽셀값으로 결정할것인지
*/

// setting for nearest samplings
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
g1TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 픽셀 중심에서 가장 가까운 텍셀 색상이 픽셀색
// setting for linear samplings
g1TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 텍셀 주변 색 보간해 픽셀색

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/*
38페이지, 고급 텍스처 샘플링 기법, Mipmap
*/

// Bind texture
glBindTexture(GL_TEXTURE_2D, tex_id); // 텍스처 바인딩, 이후 텍스처 작업 해당 텍스처 적용
// Setting several texture parameters
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 확대 필터링 방법 설정, 선형 필터링(보간) 사용
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
// 축소 필터링 방법, mipmap과 가장 가까운 텍셀로 선형 필터링
/*이 옵션은 텍스처를 축소할 때 Mipmap 레벨 중 가장 가까운 텍셀 값을 선형 보간하여
픽셀 값을 결정합니다. 이를 통해 텍스처의 축소된 버전을 보다 부드럽게 표시
*/

// Specify texture image data
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
glGenerateMipmap(GL_TEXTURE_2D); // Generate a mipmap texture, Unavailable in OpenGL 2.1
                                 // mipmap 텍스처 생성, 텍스처의 mipmap 레벨 자동생성해 텍스처 축소시 세부 텍스처 사용 가능

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/*
57페이지, 멀티 텍스쳐링
*/
/// Multitexture Fragment Shader
#version 120 // GLSL 1.20
uniform sampler2D s_basemap;
uniform sampler2D s_lightmap; // 2D 텍스처! 나타내는 유니폼 변수 / 기본텍스처,조명텍스처
varying vec2 v_texcoord;      // 버텍스 쉐이더에서 전달된 텍스처 좌표
void main()
{
    vec4 base_color;
    vec4 light_color; // 텍스처 컬러값 저장 변수

    base_color = texture2D(s_basemap, v_texcoord);
    light_color = texture2D(s_lightmap, v_texcoord); // 텍스처에서 좌표에 해당하는 컬러값 가져옴

    glFragColor = base_color * (light_color + 0.25);
    // 최종 컬러값 계산
}

/////////////////////////////////////////// 모던 OpenGL코드, main.cpp나
GLuint basemap_id, lightmap_id;
GLuint loc_s_basemap, loc_s_lightmap; // 유니폼 변수 위치
// Bind the base map
glActiveTexture(GL_TEXTURE0);             // 해당 텍스처 유닛 활성화
glBindTexture(GL_TEXTURE_2D, basemap_id); // 텍스처 id와 텍스처 유닛 바인딩
// Set the base map sampler to texture unit 0
glUniform1i(loc_s_basemap, 0); // 유니폼 변수에 정수값을 할당, 기본텍스처 샘플러 텍스처유닛0
// Bind the light map
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, lightmap_id);
// Set the base map sampler to texture unit 1
glUniform1i(loc_s_lightmap, 1); // 조명 텍스처의 샘플러를 텍스처 유닛 1로 설정
