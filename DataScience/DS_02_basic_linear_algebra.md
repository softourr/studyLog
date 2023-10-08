# DS_02_basic_linear_algebra

## 벡터

1. 방향과 크기의 의미 포함
   - 스칼라는 방향성 없이 하나의 크기 나타낸다.
   - 속도는 벡터, 속력은 스칼라
   - 무게는 벡터, 질량은 스칼라


2. 유한한 차원의 공간에 존재하는 점
   - 파이썬의 리스트나 튜플을 사용해 벡터 표현이 가능하다.



## 리스트는 벡터가 아니다

- 리스트를 벡터처럼 사용하기 위해서는 각 점들끼리의 합, 차, 곱 등의 연산을 따로 정의해야함!



## 벡터의 내적

- 두 벡터의 내적은 각 성분간 곱들의 합이다.

```python
import math

# 두 개의 벡터를 리스트로 표현합니다.
v1 = [3, 4]
v2 = [1, 2]

# 1. 각 성분의 제곱 값의 합 계산
squared_sum = sum([x ** 2 for x in v1])

# 2. 벡터의 크기 계산
vector_size = math.sqrt(squared_sum)

# 3. 두 벡터 사이의 거리 계산
# 두 벡터의 차이 벡터를 계산합니다.
difference_vector = [v1[i] - v2[i] for i in range(len(v1))]

# 차이 벡터의 각 성분의 제곱 값을 합하여 거리를 구합니다.
distance = math.sqrt(sum([x ** 2 for x in difference_vector]))

print("각 성분의 제곱 값의 합:", squared_sum)
print("벡터의 크기:", vector_size)
print("두 벡터 사이의 거리:", distance)

```



## 행렬

매트릭스. 행은 가로선 개수

행렬의 곱을 파이썬의 리스트로 표현하려면

먼저 A(n * m), B(m * s)라고 하면

m이 같아야 하고 결과 행렬 C(n * s)이다.

- A의 행(n)과 B의 열(s)을 내적한 값이 C의 [n]/[s] 좌표가 된다.



## NumPy

- 데이터, 수치 분석을 위한 파이썬 패키지
- 효율적인 선형대수 연산
  - 행렬과 벡터 사용이 가능하다.
- 사용하기 쉽다.



### 💖벡터 생성💖

```python
import numpy as np 

a = np.array([1,2,3]) 
b = np.array([2,3,4])

print(f"a+b = {a+b}") # 벡터 더하기
print(f"a-b = {a-b}") # 벡터 빼기
print(f"a*b = {a*b}") # 벡터 요소별 곱하기
print(f"a.dot(b) = {a.dot(b)}") # 벡터 내적
```

### 💖행렬 생성💖

```python
import numpy as np

A = np.array([[1,2,3], [2,3,4]]) 
B = np.array([[2,3,4], [3,4,5]])

print(f"A+B = {A+B}") # 행렬 더하기
print(f"A-B = {A-B}") # 행렬 빼기
print(f"A.T = {A.T}") # 전치행렬 (Transpose)
print(f"A*B = {A*B}") # 행렬 요소별 곱하기
print(f"A.dot(B.T) = {A.dot(B.T)}") # 행렬 곱하기
```

