# OS_11w_30,31

# OS_30_Condition Variables

418페이지

```markdown
락 이외에도 병행 프로그램을 제작할 수 있는 방법 존재함!

쓰레드가 실행을 계속하기 전에
특정 조건의 만족 여부를 검사한다면?
예시 : 부모 쓰레드가 작업 시작 전에 자식 쓰레드 작업 끝났는지 확인 > join()

공유 변수를 사용하면 부모 쓰레드가 회전하며 cpu 시간 낭비 > 비효율적
부모 쓰레드가 특정 조건이 참이 될 때까지 sleep하면서 기다리기 > 굿

# 30.1 컨디션 변수의 개념과 관련 루틴
쓰레드 실행시 특정 조건이 만족될 때까지의 대기를 위해 __컨디션 변수__ 사용 가능

__컨디션 변수__란?

- 일종의 큐 자료구조
- 쓰레드 실행에서 어떤 상태나 조건이 원하는 것과 다를 때 __조건이 만족되기를 대기하는 큐__
- 다른 쓰레드가 실행되어 시스템의 상태를 변경시키고, 해당 조건이 만족되면 대기 중인 쓰레드(n개)를 깨워 실행하도록 함

__연산__
wait() - 쓰레드가 스스로를 잠재우기 위해 호출
signal() - 조건이 만족되기를 대기하며 잠자고 있던 쓰레드를 꺠울 때 호출

## wait()
- mutex를 인자로 받음
- 호출될 때 mutex는 잠겨있었다고 가정
뮤텍스를 해제하고 호출한 쓰레드 재움
다른 쓰레드가 시그널을 보내 대기 중인 쓰레드가 sleep에서 깨어나면
wait()에서 리턴하기 전에 __반드시 락을 재획득__해야 함

@@@슬립에서 깨어난 프로세스는 리턴하기전에 락을 재획득해야한다@@@

시그널을 받아 대기상태에서 깨어나더라도 락을 획득하지 못하면 다시 sleep 상태로 들어감

/
대기모드로 들어가기전에 락을 반납하지 않거나, 
대기모드에서 깨어난 프로세스가 자신이 반납했었던 락을 다시 획득하지 않고 
실행을 계속한다면 다양한 경쟁조건이 발생한다. 
이를 방지하기 위하여 __대기 전과 후에 각각 락의 반납과 획득을 강제__한다.

421페이지

# 상태 변수 없는 경우
​```
void thr_exit()
{
    Pthread_mutex_lock(&m);
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}
void thr_join()
{
    Pthread_mutex_lock(&m);
    Pthread_cond_wait(&c, &m);
    Pthread_mutex_unlock(&m);
}
​```
잘못됨, exit가 먼저 호출되는 경우 
락을 걸고 시그널 보냈으나 깨울 쓰레드가 없음
그리고 join 실행되면 wait에 메인이 등록됨
이후 메인을 깨울 방법이 없음
> done 변수 꼭 필요

# 락 없는 경우
​```
void thr_exit()
{
    done = 1;
    Pthread_cond_signal(&c);
}
void thr_join()
{
    if (done == 0) // 락 걸지 않아서 테스트앤셋에서 테스트와 셋이 분리됨
        Pthread_cond_wait(&c);
}
​```
잘못됨, 경쟁 조건 발생
join 호출 후 바로 문맥전환 된다면
exit에서 done을 1로 바꾸고 시그널 보냄, 대기 쓰레드 없고
다시 문맥 전환되어 wait하면 메인을 깨울 방법이 없음
```



## 30 Condition Variables(1/6)

자식쓰레드 기다리거나 하는게 cv

exit와 wait을 통해 다른 쓰레드 흐름을 기다림



전역변수 이용하기, 상태변수cv로 활용

비지 웨이팅이라 cpu 낭비



30.1

cv, 조건 관련된 거 아님. 그냥 queue

조건만족하기를 기다리는 큐다

wait, signal 사용



전역변수 초기화

큐에 쓰레드들이 줄 섬

레디큐는 스케줄러가 스케줄링에 사용함

wait은 줄세우는거

깨우는건 signal 보냄, 시그널 받으면 줄선거 주에 하나를 레디 큐에 옮김



wait는 임계영역 안에서의 호출을 전제함

wait == sleep

비지 웨이팅이 아니라 sleep 시킴



흐름,![image](https://github.com/hhzzzk/2023_graphics/assets/67236054/6cc9e6b7-8c2f-49a1-b6bb-072b64142bf2)

cpu 낭비 안하고 sleep하면서 기다리기 가능

wake up 하려면 시그널 보내면 시그널 받은 큐, c에서 하나 레디큐로 보내고 레디상태로 됨



시간의 흐름으로 다시보기

@@@슬립에서 깨어난 프로세스는 리턴하기전에 락을 재획득해야한다@@@

![image](https://github.com/hhzzzk/2023_graphics/assets/67236054/285d6c8f-0ad3-41dd-8bfb-611e1a651f55)



케이스 2는 쓰레드 생성하고 바로 문맥교환

메인이 레디가 되고  타임아웃된 것

레디큐에 메인 있음



exit

신호 보내는게 임계영역이라 들어가기 전에 락걸고 언락



메인을 레디상태에서 런 상태가 됨

done 확인도 임계영역

결론, 조인이 뒤에 있어도 정상 작동함

![image](https://github.com/hhzzzk/2023_graphics/assets/67236054/e2b419f9-692c-4715-a5ad-a146fcf104e3)



1. 조건을 만족여부에 따라 기다림, 다르게 가능?

   일단 이 방법 정상작동 할 때도 안할 때도 있음

   메인이 블락, sleep됨

   exit로 신호, 시그널 보냄

   메인을 레디큐로 옮김

   메인이 레디상태됨, 스케줄링 되면 런 됨

   정상 작동하는 경우인데

   조인이 나중에 실행되면 오류남

   ​

   ![image](https://github.com/hhzzzk/2023_graphics/assets/67236054/4c51a637-09f8-4922-8d5a-807896d7cff8)

   exit에서 시그널 보냈는데 아무것도 없음

   조인하면 wait호출, c에 메인 올라감, 그러나 나중에 메인을 깨울 방법이 없음

   done 변수가 필요하다

   ​

2. 꼭 락을 써야 하나, 락을 다 제거하면?

   경쟁조건 발생,

   조인이 일종의 테스트 앤셋인데

   중간에  테스트만 하고 끊기면 락을 안걸어서, exit에서 done을 1로 만들어버림

   경쟁조건 발생

/

__condition variable__는 줄서서 깨워주기를 기다리는 곳

condition check는 state variable로 if나 while로 체크하는

시그널 보낼 때도 락을 걸고 풀고, wait도 락을 걸고 락을 풀고

@wait은 반드시 락을 걸고 풀고 해야함@, 시그널은 케바케



## 30 CV: Producer Consumer - Broken Solution(2/6)

```markdown
교재 423페이지
# 30.2 생산자/소비자(유한 버퍼) 문제
producer/consumer 문제 == bounded 버퍼 문제(유한버퍼)

다수의 생산자와 소비자 쓰레드들이 있을 때
생산자는 데이터를 버퍼에 넣고
소비자는 버퍼에서 데이터를 꺼내서 슴

grep foo file.txt | wc -l


```

30.2

버퍼를 통해 경쟁 조건 발생 가능

29.9에서 queue 예시

큐가 비었는데 소비하려고 하면 대기해야 하는데...



grep와 wc 명령어

file.txt를 열어서 foo라는 패턴이 나오는 부분을 추출

wc, 워드 카운트



grep의 출력이 파이프로 감

wc에 입력으로 파이프가 들어감



/

코드

버퍼가 int 하나임

프로듀서는 put, 비어있으면 넣음



get은 읽어오기, 있어야만 읽어오기 가능

grep이 프로듀서, wc가 소비자



cnt 개수 확인할때 기다려야함, wait



> a broken sol

cond가 기다리는 곳

count 변수는 전역변수, 공통



버퍼는 1개고 소비자, 생산자

## 30 CV: Producer Consumer - Broken Solution, if statement (3/6)

잘못된 sol인 이유

hoare semantics

mesa semantics





## 30 CV: Producer Consumer - Covering Conditions (6/6)

30.3

제시한 사이즈보다 작으면 wait



# OS_31_Semaphores(1)

438페이지

## 31 Semaphores (1/8)

```markdown
세마포어는 락과 컨디션 변수로 모두 사용 가능함!

# 31.1 세마포어의 정의
세마포어는 정수 값을 갖는 객체로 두개의 루틴으로 조작할 수 있음
	sem_wait()과 sem_post()
세마포어는 초기값에 의해 동작이 결정되기 때문에
	사용하기 전 __!제일 먼저!__ 값을 초기화해야 함
​```
sem_init(&s, 0, 1); // 3번째 인자인 1로 세마포어의 값 초기화
// 두번째 인자는 모두 0임, 같은 프로세스 내의 쓰레드 간에 세마포어를 공유한다는 의미
​```

초기화 이후 두개의 루틴 이용해 세마포어 다룸
루틴들은 동시에 다수 쓰레드들에 의해 호출가능함
임계 영역이 보호될 필요 있음
임계 영역 보호를 위해 사용할 함수 내에서 임계 영역 보호 문제 존재 ???

?일단 보호된다고 가정함

## 세마포어의 성질
1. sem_wait() > P() > 락
세마포어의 값이 1 이상이면 즉시 리턴,
세마포어 값이 1이상이 될 때까지 호출자를 대기(spin/sleep)시킴
세마포어 --

2. sem_post() > V() > 언락
세마포어 ++
대기하지 않음, 세마포어 값을 증가시키고 대기 중인 쓰레드 중 하나를 깨움

3. 세마포어가 음수라면
음수값은 현재 대기 중인 쓰레드의 개수와 같음

> 일단 이 두 개의 루틴/함수는 원자적으로 실행된다 가정


# 31.2 이진 세마포어(락), binary semaphores
439페이지

​```
sem_t m;
sem_init (&m, 0, X); // X로 초기화하기, X가 가져야할 값은?
sem_wait(&m);

//임계 영역 부분 여기에 배치
sem_post(&m);
​```

#
@@@p랑 v의 초기값은 1 중요@@@
쓰레드가 2개인 경우 p호출해 세마포어--해서 0됨
쓰레드는 세마포어가 음수인 경우에만 대기
세마포어 0이라 리턴하고 진행 가능
쓰레드0은 이제 임계영역 진입 가능
쓰레드0이 임계에 있을 때 다른 쓰레드가 락을 획득하려고 하지 않으면
쓰레드0이 v호출하면 세마포어 1로 됨(대기 쓰레드 없어서 아무도 안 깨움)

# 다른 경우
쓰레드0 락 보유, p호출하고 v아직 호출 안함, 임계 영역 진입
다른 쓰레드가 p호출해 임계 진입 시도
세마-- = -1, 대기상태
쓰레드0이 v호출하면 세마++ = 0되고 깨움
쓰레드1 락 획득
쓰레드1 작업 끝나면 v호출, 세마++ = 1

> 세마포어 락으로 사용 가능, 락은 사용가능/사용중 2개의 상태 가지므로이진 세마포어
```



## 31 Semaphores-Ordering (2/8)

```markdown
# 31.3 순서 보장을 위한 세마포어
세마포어는 병행 프로그램에서 일어나는 사건들의 순서 정하기에도 유용
컨디션 변수 사용했던 것처럼 세마포어 사용 가능

@@@세마포어의 초기값을 0으로 세팅함@@@

```



## 31 Semaphores-Producer Consumer (3/8)

```markdown
# 31.4 생산자/소비자 유한 버퍼 문제, bounded buffer

full 세마포어의 초기값은 0
empty 세마포어의 초기값은 1


# 첫번째 시도
empty, full이라는 두 개의 세마포어 사용
쓰레드는 empty 사용 사용가능한 버퍼 공간 있는지 표시
full 사용해 읽을 내용이 있는지 여부 표시
생산자는 데이터를 저장하기 위해 버퍼에 공간 생기길 기다리고
소비자는 버퍼 데이터 사용전에 버퍼에 읽을 데이터가 채워지길 기다림

__버퍼의 크기가 1인 경우__

```



## 31 Semaphores-Adding Mutex (4/8)

솔루션, 상호배제추가

락, 언락을 추가





## 31 Semaphores-Avoiding Deadlock (5/8)



## 31 Semaphores-Dining Philosopher (6/8)

## 31 Semaphores-Zemaphore (8/8)

31.7

# OS_31_Semaphores(2)



# 퀴즈

```
Condition Variable과 관련된 코드다.

void *child(void *arg)
{
    printf("child\n");
    thr_exit();
}
return NULL;
int main(int argc, char *argv[])
{
    printf("parent: begin\n");
    pthread_t p;
    Pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}

// case 1
int done = 0;
void thr_exit()
{
    done = 1;
}
void thr_join()
{
    while (done == 0)
        ; // Spin
}

 프로그램을 실행할 때 맞는 설명은 몇 번인지 설명도 함께 해주세요.

1. thr_join()의 첫 라인이 실행된 후에 thr_exit()의 첫 라인이 실행되는 경우 제대로 동작한다.


2. thr_exit()의 첫 라인이 실행된 후에 thr_join()의 첫 라인이 실행되는 경우 제대로 동작한다.


3. CPU가 1개 일 때 비효율적이다.


4. 리눅스에서 실행할 때 done이 속한 영역을 찾아 0으로 바꾸는 별도의 커널 쓰레드가 있다면 이 때문에 제대로 동작하지 않을 수 있다.
```

```
주어진 코드를 살펴보면, 부모 쓰레드와 자식 쓰레드 간에 동기화를 위해 done이라는 플래그 변수를 사용하고 있습니다. 이 변수는 thr_exit() 함수에서 1로 설정되고, thr_join() 함수에서 이 값이 1이 될 때까지 대기하는 스핀 루프가 실행됩니다.

선택지 1과 2는 thr_exit()와 thr_join()의 실행 순서에 관한 설명입니다. 실제로 thr_exit()의 첫 라인이 실행된 후에 thr_join()의 첫 라인이 실행되거나 그 반대로 실행될 수 있습니다. 하지만 어떤 순서로 실행되더라도 동작에는 영향을 주지 않습니다. 쓰레드 간의 동기화를 위해 done 변수를 사용하고 있으므로, done이 1이 될 때까지 대기하는 동안 thr_exit() 함수가 실행되든 말든 상관없이 올바르게 동작합니다.

선택지 3은 CPU가 1개일 때 비효율적이라는 설명입니다. 이 코드는 스핀 루프를 사용하여 대기하므로, done 변수가 1이 될 때까지 지속적으로 확인하는 방식입니다. CPU가 1개인 경우에는 스핀 루프가 계속 실행되면서 다른 작업을 수행하지 못하므로 비효율적일 수 있습니다. 하지만 선택지 3은 주어진 코드와는 직접적으로 관련이 없는 설명이므로 해당하지 않습니다.

선택지 4는 리눅스에서 실행할 때 done 변수가 속한 영역을 찾아 0으로 바꾸는 별도의 커널 쓰레드가 있다면 제대로 동작하지 않을 수 있다는 설명입니다. 주어진 코드에는 커널 쓰레드가 없으며, done 변수를 변경하는 작업은 현재 실행 중인 쓰레드에 의해 수행됩니다. 따라서 선택지 4는 해당 코드와 관련이 없는 설명입니다.

따라서 올바른 선택지는 1번과 2번입니다.
```





## Condition Variable

```markdown
케이스1
- 함수가 둘 다 한줄이라 atomic하게 실행되서 굳이 lock을 안걸어도 경쟁조건이 발생하지 않음
- 스핀돌면서 기다리니까 적상작동함 원래는 exit하고 join하는게 맞는 순서고 
변수 통해서 join이 exit 끝날때까지 기다리니까 ㄱㅊ
- 3 : spin쓰니까 cpu 1개면 비효율적
- 4 : 상황판단안됨 어디서 누가멀어캐걸었는지

케이스2
- 함수 앞뒤로 락,언락
- done, 공통변수 안쓰고 락만 쓰는 경우 > 4번 상관없음
- spin도 안함 > 3번 아님
- 6-12가면 락은 이미 쓰고 있고 시그널해서 깨울게없고 wait해서 자면 아무도 안깨움

케이스3
- 공통변수 쓰고 exit에는 락이 없음 근데 조인은 락이 있음
- spin이 없어서 3번은 아님
- 공통변수는 사용해서 4번은 문제생김
- 첫라인이 아니라 걍 함수실행 이후로 봐야됨
- 1 : 조인에서 락걸고 if갓다가 exit갔다가 돌아오면 경쟁조건 발생함. exit이 락이 없어서 문제
- 2 : 일단 done=1로 세팅이라 조인에서 12,13줄이 무조건 실행안됨. 그래서 계속 깨움

케이스4
- 락도 걸고 변수도 쓰고 굿
- 스핀이 없어서 3은 아니다
- 제대로 동작하는건 꼭 wait,signal하는게 아니라 락 언락 잘걸리고 그런...
```



## Semaphores

```

void *child(void *arg) { 
    printf("child\n"); thr_exit();
    return NULL;
}
int main(int argc, char *argv[]) {
    sem_init(&m, 0, 1);
    sem_init(&s, 0, X);
    printf("parent: begin\n");
    pthread_t p;
    Pthread_create(&p, NULL, child, NULL) thr_join();
    printf("parent: end\n");
    return 0;
}
제대로 된 실행 결과
parent: begin
child
parent: end


//case1
int done = 0;
sem_t m,s;

void thr_exit(){
  	sem_post(&s);
}
void thr_join(){
  	sem_wait(&s);
}

//case2
int done = 0;
sem_t m,s;

void thr_exit(){
	done = 1;
  	sem_post(&s);
}
void thr_join(){
	if(done ==0)
  		sem_wait(&s);
}

//case3

sem_t m,s;

void thr_exit(){
	sem_wait(&m);
	sem_post(&s);
  	sem_post(ms);
}
void thr_join(){
	sem_wait(&m);
	sem_wait(&s);
  	sem_post(ms);
}

```



```markdown
m은 1초기값, m이 1이면 언락, m=0이면 락 거는거고 뮤텍스
s는 순서정함 초기값 0이면 순서 
# 케이스 1
그냥 함수만 있음

# 케이스 2
변수사용함

# 케이스 3
세마포어에 세마포어해서 이중락같은, 세마포어를 락으로 쓴다.

# 케이스 4
변수도쓰고 세마포어도 락으로 쓴다.
```





# RW lock

acquire_read > 쓰는게 액티브 중이면 wait에 추가 아니면 액티브 // bad



release_readlock > 읽고잇는게없고 쓰는게 기다리고 있으면 쓰는거 깨움

acquire_writelock > 쓰고있거나읽고있으면 wait

release_writelock > 쓰는게기다리면쓰는거깨움, 읽는게기다리면 한번에 다 깨움

