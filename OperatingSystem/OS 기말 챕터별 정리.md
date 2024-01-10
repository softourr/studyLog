# OS 기말 챕터별 정리

```
9W

26 Concurrency - Q
27 interlude : thread api -Q race condition
28 locks -Q 
thread trace - HW

10W

28 locks2 -Q Remove spin
28 locks : futex locks
futex waiting cases - Q
29 Lock based concurrent data structure - Q
(HW - futex locks)



11w

30 condition variables -Q
31 semaphores -Q
31 semaphores2
HW Convering condition


12w

32 common concurrency problems -Q deadlock
condition variable with semaphore
convarsem-문법설명 - Q convarsem
HW-RW - lock bad, good


13w
숏퀴즈
37 hard disk drives
37 hard disk drives - scheduling - Q


14w

39 interlude : files and directories - Q
40 file system implementation - Q VSFS


```



9W

26 Concurrency - Q

27 interlude : thread api -Q race condition

28 locks -Q 

thread trace - HW



10W

28 locks2 -Q Remove spin

```markdown
# yield
spin해서 cpu 낭비하지 말고 yield하자
- 대신 문맥교환하는 오버헤드는 존재함.!쓰레드가 많고 문맥교환이 자주 있다면 오버헤드 비례해서 커짐
- starvation 발생가능, 어떤 쓰레드는 계속 양보만함
	> prioirity inversion(우선순위 낮으면 무한대기)
		락을 만들때 스핀락 피해야하는 이유
		해결 : priority inheritance,
		우선순위 낮아도 락을 얻은 쓰레드의 우선순위 일시적으로 올림
		또는 모든 쓰레드 우선순위 같게 만들거나
# 큐를 써서 대기열을 만든다
다음 쓰레드 순서를 만들자

flag가 큰락, guard가 작은락임

락할때는 flag 테스트앤셋이 분리, 이걸 가드를 이용해서 해결,묶고

언락도 마찬가지
spin할때 가드인 작은 락에서 작게 스핀

```



28 locks : futex locks

futex waiting cases - Q

29 Lock based concurrent data structure - Q

(HW - futex locks)



11w

30 condition variables -Q

31 semaphores -Q

31 semaphores2

HW Convering condition



12w

32 common concurrency problems -Q deadlock

condition variable with semaphore

convarsem-문법설명 - Q convarsem

HW-RW - lock bad, good



13w

숏퀴즈

37 hard disk drives

37 hard disk drives - scheduling - Q



14w

39 interlude : files and directories - Q

40 file system implementation - Q VSFS

//

1페이지 26 Concurrency - Q

3페이지 28 locks -Q

10페이지 32 common concurrency problems -Q deadlock



