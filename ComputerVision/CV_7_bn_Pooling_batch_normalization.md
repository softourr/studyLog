# CV_7_bn_Pooling_batch_normalization

## 1x1 Convolution

![image](https://github.com/hhzzzk/studyLog/assets/67236054/9aa3ae56-d591-43e9-afd6-b105b0bab4bb)

64x56x56 입력에 32개의 1x1컨볼루션 필터를 적용하면 32x56x56 출력이 나옵니다.

1x1 컨볼루션을 사용하면

1. 차원 감소
   - 입력의 각 위치에서 픽셀 간의 가중치 조합을 계산, 실제로는 각 입력 픽셀을 선형적으로 결합하는 것과 동일하다.
   - 출력 픽셀의 각 채널을 계산하기 위해 입력 픽셀의 선형 조합을 수행 = 입력의 차원이 감소
     - 입력의 차원이 감소하면 계산 비용이 줄거나, 모델 파라미터의 수가 감소된다.
2. 비선형성 추가



## CNN의 여러 하이퍼파라미터와 설정

![image](https://github.com/hhzzzk/studyLog/assets/67236054/a3f921e9-656a-4bb7-b9b5-3e2558efd379)

하이퍼파라미터는 사람이 설정한다.

위에서 커널 사이즈, 즉 필터의 크기와 사용하는 필터의 개수, 패딩과 걸음 Stride를 사람이 설정한다.



가중치 행렬은 [ 필터의 개수 x 채널수 x 커널크기hw ]



오른쪽은 보통 자주 사용하는 세팅이다. 



## Components of a Convolutional Network

CNN의 구성하는 것에는 

1. 컨볼루션 레이어
2. 활성화 함수
3. 풀링 층
4. 완전 연결층 FC
5. 정규화 층
6. 드롭 아웃 층

등이 있다.



## Pooling Layers: Another way to downsample

다운 샘플링 방법에는 여러 가지가 있는데 걸음수를 키우거나 풀링을 할 수 있다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/6366d6d3-58a5-435d-8808-4c89eab7a244)

풀링 레이어를 설정할 때 사용하는 하이퍼파라미터에는

1. 커널 크기
2. 걸음 수
3. pooling function가 있다.

풀링 레이어 내에서도 stride를 조절할 수 있다. 걸음 조절은 컨볼루션 레이어에서도 조정 가능하다.



## Pooling function : Max Pooling

맥스 풀링은 입력 데이터의 작은 영역에서 최대값을 추출해 다운샘플링한다.

- 입력에서 맥스 풀링 윈도우를 이동시키면서 각 윈도우에서 최대값을 선택해 출력을 생성한다. 스트라이드를 조절해 다운샘플링 비율을 결정할 수 있다.
- 맥스 풀링은 각 윈도우에서 가장 강한 특성을 출력에 반영한다 == 해당 영역에서 가장 중요한 정보를 유지하면서 공간적인 차원을 줄인다.
- 맥스 풀링은 데이터의 작은 변화에 대해 *불변성을 유지*한다! 제일 큰 값만 가져다 쓰므로 == 작은 변화(이동)에 덜 민감하다.
- 채널별 독립적 적용 : 각 입력 채널에 대해 맥스 풀링이 독립적으로 적용. 각 채널에서 가장 강한 신호를 추출
  - 각 채널의 특징을 독립적으로 강조하고 보존하는데 도움된다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/b1b85181-0dd7-42b6-9e4e-03d0db6f3b45)



## Pooling summary

![image](https://github.com/hhzzzk/studyLog/assets/67236054/1556eef5-6cac-4f8e-a575-18d3ef23c329)



## Convolutional Networks

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8f8eeab9-6e49-459a-9510-132d1c084755)

Classic architecture: [Conv, ReLU,Pool] x N, flatten, [FC, ReLU] xN, FC



1. 컨볼루션, 렐루, 풀링 층
   - 합성곱 층에서 이미지의특징 감지, 커널 사용
   - ReLU, 활성화 함수를 적용해 비선형성을 도입
   - 풀링층에서 공간적인 차원을 줄이기 위해 맥스 풀링이나 평균 풀링, 걸음 수 조절 등이 가능
   - 이러한 구성을 N번 반복
2. Flattern
   - 2d 특징 맵을 1d 벡터로 펼치는 연산을 수행한다.
   - 이를 통해 완전 연결 층에 입력으로 제공이 가능해진다.
3. FC, ReLU
   - 완전 연결 층에서 이전 단계에서 추출된 특징에 대해 학습 가능한 가중치를 사용해 비선형 변환을 수행
   - 렐루에서 다시 비선형성 도입
   - 해당 구성을 N번 반복
4. FC
   - 최종 완결 연결 층으로 출력을 생성한다.
   - 분류 문제의 경우 소프트맥스 활성화 함수를 사용해 클래스 확률을 얻을 수 있다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/cb89bd6e-d63d-4a44-b5ab-e16198c34283)

컨볼루션 레이어의 연산

- Cin은 채널 수, Cout은 필터의 개수
- output은 N(이미지 개수, 보통 생략) x Cout x H' x W'
  - H' = W' = ( W - K + 2P ) / S + 1
- 컨볼루션 레이어의 가중치 크기는 Cout x Cin x Kh x Kw



풀링 레이어의 연산

- output은 Cin x H' x W' 
  - H' = W' = (H - K ) / S + 1



> 신경망을 통과할수록 공간적인 크기가 감소하고 채널 수가 증가한다!

1. 공간적인 크기 감소 : 풀링 레이어나 스트라이드의 조절로 공간적 크기 줄어든다. 더 적은 수의 파라미터로 중요한 특징 학습
2. 채널수 증가 : 컨볼루션 레이어에서 이미지의 다양한 특징 추출하는 여러 개의 필터=채널을 사용!
3. 전체 볼륨 유지!
   - ???아니던데



## Problem: Deep Networks very hard to train!

## Batch Normalization

배치 정규화는 학습을 안정화하고 속도를 향상시키기 위한 기술이다.

주로 CNN의 완전 연결 레이어에서 사용된다.

- 각 레이어의 입력을 정규화하여 평균이 0이고 분산이 1이 되도록 스케일링 및 쉬프트를 수행
- 각 미니배치의 활성화 값을 평균과 분산으로 정규화한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/74cfdec6-cf3f-47fa-8112-9f0f500ca795)

위의 식처럼 정규화한다.

그런데 해당 식은 미분 가능한 함수이므로 역전파가 가능하다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/6878bb87-bcdf-4513-a644-1d65ecded6f4)

![image](https://github.com/hhzzzk/studyLog/assets/67236054/84c479d9-bc58-436b-8f64-c8406d5a6239)

1. 평균 계산 : 1번 식은 각 채널 j에 대한 평균이다. N은 미니배치의 크기이고 Xij는 미니배치의 각 포인트의 값들이다. 이를 통해 각 채널별로 평균을 계산
2. 표준편차 제곱 계산 : 2번 식은 각 채널 j에 대한 표준편차의 제곱이다. 각 채널별 표준편차의 제곱을 계산한다.
3. 정규화 : x^은 각 데이터 포인트의 j번째 채널을 정규화한 값이다.
   - 각 데이터 포인트의 각 채널을 해당 채널의 평균과 표준편차로 정규화한다.
   - 결과적으로 각 채널은 평균이 0이고 분산이 1인 분포를 가진다.



> 채널별로 구한다.



## Batch Normalization for ConvNets

배치 정규화 : 완전 연결층

![image](https://github.com/hhzzzk/studyLog/assets/67236054/31a9f6b9-bb96-4eb9-a713-60ba1436cae5)

입력 N X D

μ (뮤)는 입력 데이터 X의 각 차원! 별 평균을 나타내는 1 x D 차원 행렬

σ 시그마는 입력 데이터 x의 각 차원에 대한 표준 편차를 나타내는 1 x D 행렬. 배치 내 각 차원 별로 계산

γ (감마)는 스케일 파라미터, β(베타)는 시프트 파라미터로 각각 학습 가능한 가중치이고 1 x D 차원이다.



최종적으로 y는 배치 정규화를 통과한 출력이고  N X D 행렬이다.

감마, 베타를 사용해 정규화된 값을 스케일링하고 시프트 한다. (정규화된 값에 스케일 나누고, 시프트)



*X에 평균을 빼면 각 차원의 평균을 빼 데이터를 중앙에 정렬시킨다.*

*이를 표준편차로 나눠서 정규화*



**CNN에서의 배치 정규화**

![image](https://github.com/hhzzzk/studyLog/assets/67236054/8a0c8524-2b23-4bcc-be2b-9ab8172d0281)

입력에서 N은 미니배치 크기, C는 채널수

평균이 뮤는 채널수만큼 생기므로 1 X C X 1 X 1

위랑 같다.



## Layer Normalization

배치 정규화와 달리 미니 배치가 아닌 각 샘플에 대해 정규화를 수행한다. 주로 RNN과 같이 배치 크기가 작거나 없는 경우에 유용하게 사용된다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/7b469267-d147-476e-b812-50ea35e13eef)



![image](https://github.com/hhzzzk/studyLog/assets/67236054/d4b479f4-a632-4063-8a31-817c94386021)

입력 N은 입력 배치의 개수고 D는 각 샘플의 채널 개수다.

그래서 레이어 정규화는 배치에 따라 하는게 아니라 각 샘플에 대해 수행하므로 거의 1개의 배치에 대해 수행된다. N X 1



비교!!!

배치정규화는 각 배치에 대해 수행되므로 배치가 1, 레이어 정규화는 샘플=채널에 대해 수행되므로 이게 1



## Instance Normalization

각 샘플에 대해 정규화를 수행. 배치 크기에 상관없이 각 샘플=인스턴스를 독립적으로 정규화한다. 레이어 정규화와 유사하나 더 간단하다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/e8289bc3-8398-4a41-87b3-a61c0bf354ae)

입력의 미니배치 크기, 채널수, 높이, 너비이다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/3926f578-c653-4042-90f6-ec7c22d4c050)



배치는 배치에 대해 수행되므로 배치 N=1

레이어는 채널=1

인스턴스는 한 줄

그룹은...그룹