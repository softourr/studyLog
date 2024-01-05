자바스크립트는 다음 링크에서 쉽게 테스팅할 수 있습니다.

• 플레이코드 링크: <https://playcode.io/new/>

자바는 다음 링크에서 쉽게 테스팅할 수 있습니다.

• 코딩그라운드 링크: <https://www.tutorialspoint.com/compile_java_online.php>



# CH1 : 디자인 패턴과 프로그래밍 패러다임

1. 디자인 패턴
2. 프로그래밍 패러다임



––– 라이브러리

공통으로 사용될 수 있는 특정한 기능들을 모듈화한 것을 의미한다. 

**폴더명, 파일명 등에 대한 규칙이 없고 프레임워크에 비해 자유롭다.** 예를 들어 무언가를 자를 때 ‘도구’인 ‘가위’를 사용해서 ‘내가’ 직접 컨트롤하여 자르는데, 라이브러리는 이와 비슷하다.

 

––– 프레임워크

공통으로 사용될 수 있는 특정한 기능들을 모듈화한 것을 의미한다. 

폴더명, 파일명 등에 대한 규칙이 있으며 라이브러리에 비해 좀 더 엄격하다. 다른 곳으로 이동할 때 ‘도구’인 비행기를 타고 이동하지만 ‘비행기’가 컨트롤하고 나는 가만히 앉아 있어야 한다. 프레임워크는 이와 비슷하다.



## 1.1 디자인 패턴

디자인 패턴이란 프로그램을 설계할 때 발생했던 문제점들을 객체 간의 상호 관계 등을 이용하여 해결할 수 있도록 하나의 ‘규약’ 형태로 만들어 놓은 것



## 1.1.1 싱글톤 패턴

하나의 클래스에 오직 하나의 인스턴스만 가지는 패턴

- 데이터베이스 연결 모듈에 많이 사용
- 하나의 인스턴스를 만들어 놓고 해당 인스턴스를 다른 모듈들이 공유하며 사용
  - 인스턴스 생성 비용 절감
  - 그러나 의존성 높아짐



### 1. 자바스크립트의 싱글톤 패턴

- 리터럴 {}, 또는 new object로 객체 생성하면 다른 객체와 다른 유일한 객체. 이 자체만으로 싱글톤 패턴

```javascript
const obj = {
    a: 27
}
const obj2 = {
    a: 27
}
console.log(obj === obj2)
// false
```

- obj1과 2는 서로 다른 인스턴스



```javascript
class Singleton {
    constructor() {
        if (!Singleton.instance) {
            Singleton.instance = this
        }
        return Singleton.instance
    }
    getInstance() {
        return this.instance
    }
}
const a = new Singleton()
const b = new Singleton() 
console.log(a === b) // true
```

- a와 b는 Singleton.instance라는 하나의 인스턴스 가짐.



### 2. 데이터베이스 연결 모듈

```javascript
// DB 연결을 하는 것이기 때문에 비용이 더 높은 작업 
const URL = 'mongodb://localhost:27017/kundolapp' 
const createConnection = url => ({"url" : url})    
class DB {
    constructor(url) {
        if (!DB.instance) { 
            DB.instance = createConnection(url)
        }
        return DB.instance
    }
    connect() {
        return this.instance
    }
}
const a = new DB(URL)
const b = new DB(URL) 
console.log(a === b) // true
```

- DB.instance라는 하나의 인스턴스로 a,b를 생성.



### 3. 자바에서의 싱글톤 패턴

```java
class Singleton {
    private static class singleInstanceHolder {
        private static final Singleton INSTANCE = new Singleton();
    }
    public static Singleton getInstance() {
        return singleInstanceHolder.INSTANCE;
    }
}

public class HelloWorld{ 
     public static void main(String []args){ 
        Singleton a = Singleton.getInstance(); 
        Singleton b = Singleton.getInstance(); 
        System.out.println(a.hashCode());
        System.out.println(b.hashCode());  
        if (a == b){
         System.out.println(true); 
        } 
     }
}
/*
705927765
705927765
true

1. 클래스안에 클래스(Holder), static이며 중첩된 클래스인 singleInstanceHolder를 
기반으로 객체를 선언했기 때문에 한 번만 로드되므로 싱글톤 클래스의 인스턴스는 애플리케이션 당 하나만 존재하며 
클래스가 두 번 로드되지 않기 때문에 두 스레드가 동일한 JVM에서 2개의 인스턴스를 생성할 수 없습니다. 
그렇기 때문에 동기화, 즉 synchronized를 신경쓰지 않아도 됩니다. 

2. final 키워드를 통해서 read only 즉, 다시 값이 할당되지 않도록 했습니다.

3. 중첩클래스 Holder로 만들었기 때문에 싱글톤 클래스가 로드될 때 클래스가 메모리에 로드되지 않고 
어떠한 모듈에서 getInstance()메서드가 호출할 때 싱글톤 객체를 최초로 생성 및 리턴하게 됩니다. 
*/
```

- Lazy Initialization 기법을 활용하여 객체를 생성

- 클래스 내부에 중첩 클래스인 `singleInstanceHolder`를 사용하여 싱글톤 객체를 보장

  - 중첩 클래스로 선언함으로써 클래스 로딩 시점에 인스턴스가 생성되지 않고, `getInstance()` 메서드가 호출될 때 초기화
  - 아하 **자바에서 클래스는 최초 사용할 때 로딩되므로 중첩 클래스를 따로 호출하지 않는 한 인스턴스가 생성되지 않음. 이런게 lazy initialzation, 객체가 필요한 순간에만 생성!!!**

- `INSTANCE` 필드에 `final` 키워드가 사용되어 있으므로 싱글톤 인스턴스는 한 번 생성되면 변경할 수 없음

- 동기화(Synchronization)  문제

  - 자바에서 클래스는 최초 사용시 로딩. 클래스 로딩의 3가지 과정

  1. loading : 클래스 로더에 의해 클래스 파일이 디스크로부터 메모리로 로드
     - 클래스 파일의 바이트 코드가 메모리에 올라옴, 해당 클래스의 정적 변수 및 메서드를 초기화하지 않는다.
  2. linking : 클래스의 바이트 코드가 검증, 준비 및 해석
     - 클래스의 정적 변수들에 할당된 메모리 공간이 초기화
     - 정적 블록은 클래스가 처음 로딩될 때 실행
  3. 초기화 : 클래스의 정적 변수 및 초기화 블록 초기화



> 자바에서는 클래스가 처음 사용되는 시점에 클래스 로딩 발생
>
> 이를 통해 불필요한 클래스들을 로드하거나 초기화하지 않아 리소스 절약

 **자바에서 클래스는 최초 사용할 때 로딩되므로 중첩 클래스를 따로 호출하지 않는 한 인스턴스가 생성되지 않음. 이런게 lazy initialzation, 객체가 필요한 순간에만 생성!!!**



### 4. mongoose의 싱글톤 패턴

실제로 싱글톤 패턴은 Node.js에서 MongoDB 데이터베이스를 연결할 때 쓰는 mongoose 모듈에서 볼 수 있다. mongoose의 데이터베이스를 연결할 때 쓰는 connect()라는 함수는 싱글톤 인스턴스를 반환한다.

```javascript
Mongoose.prototype.connect = function(uri, options, callback) {
    const _mongoose = this instanceof Mongoose ? this : mongoose;
    const conn = _mongoose.connection;

    return _mongoose._promiseOrCallback(callback, cb => {
        conn.openUri(uri, options, err => {
            if (err != null) {
                return cb(err);
            }
            return cb(null, _mongoose);
        });
    });
};
```



### 5. MySQL의 싱글톤 패턴

Node.js에서 MySQL 데이터베이스를 연결할 때도 싱글톤 패턴 사용

```javascript
// 메인 모듈
const mysql = require('mysql');
const pool = mysql.createPool({
    connectionLimit: 10,
    host: 'example.org',
    user: 'kundol',
    password: 'secret',
    database: '승철이디비'
});
pool.connect();

// 모듈 A
pool.query(query, function (error, results, fields) {
    if (error) throw error;
    console.log('The solution is: ', results[0].solution);
});

// 모듈 B
pool.query(query, function (error, results, fields) {
    if (error) throw error;
    console.log('The solution is: ', results[0].solution);
});
```

메인 모듈에서 연결 인스턴스를 정의하고 다른 모듈에서 해당 인스턴스를 기반으로 쿼리를 보냄



## 싱글톤 패턴의 단점

1. **TDD, test driven development를 할 때 걸림돌이 된다.**

- TDD를 할 때 단위테스트를 주로 하는데 단위 테스트는 테스트가 서로 독립적이어야 하며 테스트를 어떤 순서로든 실행할 수 있어야 한다.
- 하지만 싱글톤 패턴은 미리 생성된 하나의 인스턴스를 기반으로 구현하는 패턴이므로 각 테스트마다 '독립적인' 인스턴스를 만들기 어렵다

> 맛있는 칼로리 만들때 전체 코드를 시작해서 순차적으로 인스턴스를 생성해야 테스트 가능
>
> 로그인 기능 건너뛰고 다른 모듈 테스트 불가능!



2. **의존성 주입**

모듈 간의 결합을 강하게 만든다. 이 때 의존성 주입 DI, Dependency injection을 통해 모듈 간의 결합을 느슨하게 만들어 해결 가능



### Dependency injection - DI : 의존성 주입

- 참고로 의존성이란 종속성이라고도 하며 A가 B에 의존성이 있다는 것은 B의 변경 사항에 대해 A도 수정해야 한다는 것이다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/c6e78526-9611-4572-aa64-134ec0430768)



- 메인 모듈이 직접 하위 모듈에 의존성을 주기보다 중간에 의존성 주입자 dependency injector를 이용해 메인 모듈이 간접적으로 의존성을 주입하도록 한다.
- 이를 통해 메인 모듈은 하위 모듈에 대한 의존성이 떨어진다. 이를 디커플링 된다라고 한다.



장점

- 모듈을 쉽게 교체 가능, 테스트 쉬움
- 구현시 추상화 레이어를 넣고 이를 기반으로 구현체를 넣어 의존성 방향이 일관되고 쉽게 추론 가능, 모듈 간의 관계 명확해진다.

단점

- 모듈들이 더욱 분리되므로 클래스 수가 늘어나 복잡성 증가, 약간의 런타임 패널티 발생

의존성 주입 원칙

>  상위 모듈은 하위 모듈에서 어떠한 것도 가져오지 않아야 한다. 또한 둘 다 추상화에 의존해야 하며, 이 때 추상화는 세부 사항에 의존하지 말아야 한다.





## 1.1.2 팩토리 패턴

- 객체를 사용하는 코드에서 객체 생성 부분을 분리해 추상화한 패턴


- 상속 관계에 있는 두 클래스에서 상위 클래스가 중요한 뼈대를 결정하고, 하위 클래스에서 객체 생성에 관한 구체적인 내용을 결정하는 패턴



