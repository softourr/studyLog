# AI_Assignment_1

1. torch.rand() : 0부터 1까지의 균일 분포(uniform distribution)에서 무작위 수로 채워진 텐서를 반환합니다.
2. torch.zeros() : 크기가 변수로 정의된 모양으로 스칼라 값 0으로 채워진 텐서를 반환합니다.
3. torch.tensor() : 데이터로 텐서를 구성합니다.
4. torch.from_numpy() : numpy.ndarray로부터 텐서를 생성합니다.
5. torch.as_tensor() : 데이터를 torch.Tensor로 변환합니다.
6. torch.cat() : 주어진 차원에서 시퀀스(sequence) 텐서를 연결(concatenate)합니다.
7. torch.stack() : 새로운 차원을 따라 텐서의 시퀀스를 연결(concatenate)합니다.
8. torch.eye() : 주 대각선은 1이고 나머지는 0인 2차원 텐서를 반환합니다.
9. torch.tensor(), torch.Variable(), 또는 텐서 생성 시 requires_grad=True 속성을 설정하여 텐서를 생성할 수 있습니다. 이로 인해 torch.autograd는 자동 미분을 위해 이들에 대한 작업을 기록합니다.
10. torch.autograd.backward() : 그래프의 잎들에 대한 주어진 텐서들의 기울기의 합을 계산합니다. 그래프는 연쇄 법칙(chain rule)을 사용하여 미분됩니다. 텐서 중 어떤 것이 스칼라가 아니면(즉, 데이터에 하나 이상의 요소가 있는 경우) 그라디언트가 필요한 경우, 야코비안-벡터 곱(Jacobian-vector product)이 계산됩니다. 이 경우 함수에는 추가적으로 grad_tensors를 지정해야 합니다. 이는 대응하는 텐서에 대한 미분 함수의 그라디언트로서 일반적으로 "벡터"를 포함하는 일치하는 길이의 시퀀스여야 합니다(None은 그라디언트 텐서가 필요하지 않은 모든 텐서에 대한 허용 가능한 값입니다). 이 함수는 그래디언트를 잎들에 누적합니다. 호출하기 전에 .grad 속성을 0으로 설정하거나 None으로 설정해야 할 수 있습니다. 메모리에 누적된 그라디언트 레이아웃에 대한 자세한 내용은 기본 그라디언트 레이아웃(Default gradient layouts)을 참조하세요.
11. torch.autograd.grad() : 출력에 대한 입력들의 그라디언트 합을 계산하고 반환합니다. grad_outputs는 일반적으로 각 출력에 대한 미리 계산된 그라디언트로서 출력과 일치하는 길이의 시퀀스여야 합니다. 만약 출력이 requires_grad를 필요로 하지 않는다면, 그라디언트는 None일 수 있습니다. only_inputs가 True인 경우, 함수는 지정된 입력에 대한 그라디언트 목록만 반환합니다. False인 경우, 나머지 잎들에 대한 그라디언트도 계산되고, 이들의 .grad 속성에 누적됩니다.
12. torch.norm() : 주어진 텐서의 행렬 노름(matrix norm) 또는 벡터 노름(vector norm)을 반환합니다.
13. torch.no_grad() : 그라디언트 계산을 비활성화하는 컨텍스트 매니저입니다. 그라디언트 계산을 비활성화하는 것은 Tensor.backward()를 호출하지 않을 것이 확실한 추론(inference) 시 유용합니다. 이는 requires_grad=True인 입력이 있더라도 모든 계산의 결과는 requires_grad=False를 갖게 됩니다. 이 모드는 enable_grad 컨텍스트 매니저를 사용할 때에는 효과가 없습니다. 이 컨텍스트 매니저는 스레드 로컬(thread local)로 작동하며, 다른 스레드에서의 계산에는 영향을 미치지 않습니다. 또한 데코레이터로도 작동합니다.
14. torch.detach() : 현재 그래프로부터 분리된 새로운 텐서를 반환합니다. 결과 텐서는 절대 그라디언트를 필요로하지 않을 것입니다.



## 2. [활성함수] 다음 코드를 무엇을 의미하는지 이해하고 실행하여 결과를 확인하세요. (3점)

주어진 코드는 다양한 활성화 함수와 그들의 기울기를 시각적으로 비교하는 예제이다. 

1. 화면 출력 확인:
   - 왼쪽 subplot(121)은 다양한 활성화 함수의 형태를 나타낸다.
   - 오른쪽 subplot(122)은 각 활성화 함수의 기울기를 나타낸다.
2. 각 활성화 함수의 특징:
   - `Step 함수`:
     - 계단함수이다. 주어진 값에 따라 -1 또는 1을 반환한다. 이산적인 값을 출력한다. 이 함수는 hard하게 변화하기 때문에 기울기가 거의 없다. 미분이 불가능하다. 공간을 딱딱하게 계단형식으로 분할한다.
   - `Sigmoid 함수`
     - 입력 값을 0과 1 사이의 값으로 압축한다. 연속적인 값을 출력한다. 계단함수와 다르게 공간을 부드럽게 분할한다. 미분이 가능하다.
     - S자 형태의 곡선을 가진다. 그래디언트 소멸 문제가 있다.
   - `Tanh 함수`
     - S자 형태의 곡선이며 시그모이드 함수와 유사하나 출력 범위가 -1,1 사이이다. 시그모이드 함수보다 강한 그래디언트를 가지고 있어 학습이 빠르게 이루어질 수 있다. 여전히 그래디언트 소멸 문제가 있다.
   - `ReLU 함수`: 입력이 양수인 경우에는 입력 값을 그대로 반환하고, 음수인 경우에는 0을 반환한다. 주로 은닉층에 사용되며 시그모이드와 tanh함수보다 학습 속도가 빠르고 그래디언트 소실 문제를 완화할 수 있다.








```
# 파이썬 2, 파이썬 3 지원
import torch
import torch.nn as nn
import torch.optim as optim
from torch import FloatTensor 
from torch.autograd import Variable
device = "cuda" if torch.cuda.is_available() else "cpu"
# ============== define variables ============== 
gt = torch.tensor([10])
x1 = Variable(FloatTensor([[-10.], [10.]])) 
### allocate tensor
w1 = ### YOUR CODE HERE 
w2 = ### YOUR CODE HERE 
### define parameter
w1 = ### YOUR CODE HERE
w2 = ### YOUR CODE HERE
# ============================================== 
# ============== define functions ==============
ReLU = ### YOUR CODE HERE 
sigomid = ### YOUR CODE HERE
# ============================================== 
# ============== define optimizer ==============
# Use SGD with learning rate = 0.5 
optimizer = ### YOUR CODE HERE
# ============================================== 
# ================ define model ================
z1 = ### YOUR CODE HERE 
a1 = ### YOUR CODE HERE 
z2 = ### YOUR CODE HERE 
yhat = ### YOUR CODE HERE
# ============================================== 
# ===== calculate loss and do backward, step =====
loss = ### YOUR CODE HERE 
loss.backward()
# ==============================================
print("----")
print(x1, z1, a1, z2, yhat, sep='\n')
print("====")
print(w1, w2, sep='\n') 
optimizer.step()
print("----")
print(x1, z1, a1, z2, yhat, sep='\n') 
print("====")
print(w1, w2, sep='\n')
```



## 4. [퍼셉트론] 다음 코드를 이해 및 완성하고, 실행한 결과를 확인하세요. (5점)



```
import numpy as np
import matplotlib.pyplot as plt
import torch
%matplotlib inline

# Preparing a toy dataset
data = np.genfromtxt('perceptron_toydata.txt', delimiter='\t')
X, y = data[:, :2], data[:, 2]
y = y.astype(np.int)
print('Class label counts:', np.bincount(y))
print('X.shape:', X.shape)
print('y.shape:', y.shape)

# Shuffling & train/test split
shuffle_idx = np.arange(y.shape[0])
shuffle_rng = np.random.RandomState(123)
shuffle_rng.shuffle(shuffle_idx)
X, y = X[shuffle_idx], y[shuffle_idx]
X_train, X_test = X[shuffle_idx[:70]], X[shuffle_idx[70:]]
y_train, y_test = y[shuffle_idx[:70]], y[shuffle_idx[70:]]

# Normalize (mean zero, unit variance)
mu, sigma = X_train.mean(axis=0), X_train.std(axis=0)
X_train = (X_train - mu) / sigma
X_test = (X_test - mu) / sigma

plt.scatter(X_train[y_train==0, 0], X_train[y_train==0, 1], label='class 0', marker='o')
plt.scatter(X_train[y_train==1, 0], X_train[y_train==1, 1], label='class 1', marker='s')
plt.title('Training set')
plt.xlabel('feature 1')
plt.ylabel('feature 2')
plt.xlim([-3, 3])
plt.ylim([-3, 3])
plt.legend()
plt.show()

plt.scatter(X_test[y_test==0, 0], X_test[y_test==0, 1], label='class 0', marker='o')
plt.scatter(X_test[y_test==1, 0], X_test[y_test==1, 1], label='class 1', marker='s')
plt.title('Test set')
plt.xlabel('feature 1')
plt.ylabel('feature 2')
plt.xlim([-3, 3])
plt.ylim([-3, 3])
plt.legend()
plt.show()

# Defining the Perceptron model
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
class Perceptron():
    def __init__(self, num_features):
        self.num_features = num_features
        self.weights = torch.zeros(num_features, 1, dtype=torch.float32, device=device)
        self.bias = torch.zeros(1, dtype=torch.float32, device=device)
        # placeholder vectors so they don't need to be recreated each time
        self.ones = torch.ones(1)
        self.zeros = torch.zeros(1)

    def forward(self, x):
        linear = torch.add(torch.mm(x, self.weights), self.bias)
        predictions = torch.where(linear > 0, self.ones, self.zeros)
        return predictions

    def backward(self, x, y):
        predictions = self.forward(x)
        errors = y - predictions
        return errors

    def train(self, x, y, epochs):
        for e in range(epochs):
            for i in range(y.shape[0]):
                # use view because backward expects a matrix (i.e., 2D tensor)
                errors = self.backward(x[i].reshape(1, self.num_features), y[i]).reshape(-1)
                self.weights += (errors * x[i]).reshape(self.num_features, 1)
                self.bias += errors

    def evaluate(self, x, y):
        predictions = self.forward(x).reshape(-1)
        accuracy = torch.sum(predictions == y).float() / y.shape[0]
        return accuracy

# Training the Perceptron
ppn = Perceptron(num_features=2)
X_train_tensor = torch.tensor(X_train, dtype=torch.float32, device=device)
y_train_tensor = torch.tensor(y_train, dtype=torch.float32, device=device)
ppn.train(X_train_tensor, y_train_tensor, epochs=5)
print('Model parameters:')
print('  Weights: %s' % ppn.weights)
print('  Bias: %s' % ppn.bias)

# Evaluating the model
X_test_tensor = torch.tensor(X_test, dtype=torch.float32, device=device)
y_test_tensor = torch.tensor(y_test, dtype=torch.float32, device=device)
test_acc = ppn.evaluate(X_test_tensor, y_test_tensor)
print('Test set accuracy: %.2f%%' % (test_acc*100))

w, b = ppn.weights, ppn.bias
# 2D Decision Boundary
x0_min = -2
x1_min = ( (-(w[0] * x0_min) - b[0]) / w[1] )
x0_max = 2
x1_max = ( (-(w[0] * x0_max) - b[0]) / w[1] )

fig, ax = plt.subplots(1, 2, sharex=True, figsize=(7, 3))
ax[0].plot([x0_min, x0_max], [x1_min, x1_max])
ax[1].plot([x0_min, x0_max], [x1_min, x1_max])
ax[0].scatter(X_train[y_train==0, 0], X_train[y_train==0, 1], label='class 0', marker='o')
ax[0].scatter(X_train[y_train==1, 0], X_train[y_train==1, 1], label='class 1', marker='s')
ax[1].scatter(X_test[y_test==0, 0], X_test[y_test==0, 1], label='class 0', marker='o')
ax[1].scatter(X_test[y_test==1, 0], X_test[y_test==1, 1], label='class 1', marker='s')
ax[1].legend(loc='upper left')
plt.show()

```

**torch.Variable() : 과거 사용된 autograd방식으로 최신 버전에서는 torch에서 모든 tensor에 autograd가 가능하도록 설정됨**







