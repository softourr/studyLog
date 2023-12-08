# DS_06_Similarity

# 비슷한 문서 찾기

## Bag_Of_Words

문서를 정형화된 데이터로 표현할 수 있다면 

​	비슷한 정도, 유사도를 측정할 수 있다.

BOW는 문서를 단어들의 가방(중복집합)으로 표현한다.

- 가정 : 비슷한 문서는 단어들이 많이 겹칠 것이다.

## Cosine Similarity

단어 가방을 벡터로 표현해 유사도를 측정한다.

단어 등장 횟수를 cnt한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/fdf58da3-1c00-44c2-b0cc-fa9ccbd44bfd)

벡터에서 같은 방향을 가리키면 유사도가 높다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/842eccb9-91eb-492e-a542-a8645222ea28)

단어가 많이 겹치면 코사인 유사도가 높다. 분자는 내적, 분모는 원점에서의 거리 구함

위의 a,b,c를 계산하면

a,b = 0.95

a,c = 0.32

b,c = 0.22



## Jaccard Similarity

집합간 유사도를 측정한다.

BOW를 집합으로 보고 자카드 유사도를 활용한다.

단어집합이 존재하면 1 없으면 0이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/72376f95-a0bd-4a80-ab04-af022ef56cda)

분자는 교집합이고

분모는 합집합인 이유는 만약 모든 단어가 있는 문서라면 교집합이 무조건 100프로가 나오기 때문이다.



## BOW의 한계

> 의미가 반대인 두 문장도 비슷한 단어를 가지고 있다면 높은 유사도가 나온다.

1. 단어의 순서를 고려하지 않는다.
2. 자주 등장하는 단어가 유사도에 큰 영향을 미친다. (a, the, of, you...)
3. Sparisity(희소성) : 문서에 등장하지 않는 단어가 훨씬 많다. 메모리 낭비.
4. 새로운 단어는 BOW에서 의미가 없다.



## n-gram

연달아 등장하는 단어 n개를 하나의 묶음으로

1 극복 : 단어 순서를 고려한다.

2 극복 : 자주 등장하는 단어의 힘이 약해진다. 연달아 등장하는 단어들은 희귀해질 것이다.

3 악화 : sparsity 악화

4 여전 : 새로운 단어는 여전히 해결이 안됐다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/64b91bd1-5578-4a1f-a5c6-10b34513ac23)



## Similarities with n-gram

n-gram을 벡터 혹은 집합으로 표현, 유사도를 적용

![image](https://github.com/hhzzzk/studyLog/assets/67236054/75f41d8b-63ce-4dc7-b78c-4dd7728a6afd)



## TF-IDF

문서의 어떤 단어가 중요단어일까?

- 이 문서에는 자주 등장하는 단어, 다른 문서에는 잘 등장하지 않는 단어

주어진 문서에서 단어마다 중요도 매기기

- TF, Term Frequency : 이 단어가 문서에서 얼마나 자주 등장했는가?

![image](https://github.com/hhzzzk/studyLog/assets/67236054/faa34c94-c8f6-4c79-97e7-a2b6a6236a86)

f ij = 문서 j에서 단어 i가 등장한 빈도수 
n i = 단어 i가 등장한 문서 수
N = 전체 문서 수



- DF, Document Frequency : 이 단어가 모든 문서에서 얼마나 자주 등장했는가?
- IDF(Inverse DF) : DF의 역수

![image](https://github.com/hhzzzk/studyLog/assets/67236054/5d122f0e-9bab-413d-a197-5786572557eb)



# 비슷한 드라마 찾기

## 추천시스템

내가 재밌게 본 드라마와 비슷한 드라마는?

## 유사도

두 드라마의 유사도를 어떻게 측정할 수 있을까?

1. 장르나 키워드가 비슷하면 비슷하다.
2. 사람들의 평가가 비슷하면 비슷하다.



## 자카드 유사도

두 집합이 얼마나 비슷한지를 츩정한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/91c9660a-5477-4bc0-ae08-937dc3d1baf6)

## 평가 유사도

## 코사인 유사도

벡터로 봤을 때 같은 방향을 가리키면 유사도가 높다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/061e50f1-b02f-45a2-abfa-b5633c38a16f)

왜 u,c의 유사도가 a,b보다 높을까?

- *평가 안한 것을 0으로 생각하기 때문!!!*
  - 안 봤는데 보고 안좋게 평가하는 것보다 더 안좋게 계산된다!



## Centered Cosine Similarity

CCS = Pearson Correlation Coefficient, 가장 대표적인 상관계수

- sol ) 평가하지 않은 경우, 평균 점수를 부여한다.
- 각 벡터별로 평가한 점수의 평균

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7f6fdadd-5cd3-430e-a78f-01ace5c973c4)



왜 a,c와 b,c가 양수일까?

- *모든 평점이 긍정적이라서!!!!!*
  - sol ) 모든 평점을 평균 점수만큼 빼주기
  - 각 벡터의 평균을 각 벡터의 평점마다 빼 준다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/3fc54326-b6f7-4f04-9b0f-469b12c1aece)



## 추천하기

- 내가 재밌게 본 드라마 a와 유사도가 가장 높은 드라마 n개 추천하기
- 장르, 키워드 유사도 J(a,x)와 평가 유사도 U(a,x)를 모두 활용

![image](https://github.com/hhzzzk/studyLog/assets/67236054/05c053b3-a391-40f8-80ff-810e66b4a0b7)