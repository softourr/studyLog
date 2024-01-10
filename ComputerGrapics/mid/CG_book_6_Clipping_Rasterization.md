# CG_book_6_Clipping_Rasterization



```markdown
# 6.1 기본 구현 전략
컴퓨터 그래픽스에서는 응용프로그램에서 시작해 이미지로 끝남

Application program > (vertices) >Graphics system> (pixels) > Frame buffer

## 블랙박스란 
정점, 기하학적 객체, 속성, 카메라 설정 값들을 입력 데이터로 갖고 
출력은 __프레임 버퍼에서의 색 픽셀의 배열__이다.

음 생략

# 6.2 네 가지 주요 작업
기하학적 개체가 사용자 출력장치에 디스플레이될 때까지 그것을 렌더링하기 위한 네 가지 주요 작업
1. 모델링
2. geometric processing
3. rasterization
4. fragment processing
?
```



```markdown
# 6.3 Clipping
클리핑은 클리핑된 정점의 w 성분이 1이 아닌 경우 필요한 투시 제산 전에 수행됨
```

