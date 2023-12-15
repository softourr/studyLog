# SS_8_2_WebSecurity

[TOC]



이부분 다시보기...졸앗음...

## CSRF - Cross-Site Request Forgery

원클릭 공격 또는 세션 라이딩이라고도 한다.

**CWE-352 Cross-Site Request Forgery (CSRF):** 불법 명령이 웹사이트가 신뢰하는 **사용자**로부터 전송되는 악의적인 공격 유형

- **XSS는 사용자의 특정 사이트에 대한 신뢰를 악용한다.**
- **CSRF는 웹사이트의 사용자 브라우저에 대한 신뢰를 악용한다.**


!!  웹사이트에 악의적인 스크립트를 숨겨놓는


예시1

1. 멜러리는 밥의 은행 웹사이트에서 스크립트를 참조하는 html 이미지를 작성했다.
   - 이미지의 src 속성에는 실제로 이미지가 아니라 은행의 출금 스크립트가 포함되어 있다. (악성 스크립트)
2. 밥의 은행은 그의 인증 정보를 쿠키에 저장하고 있으며 쿠키가 만료되지 않았다.
3. 그럼 밥이 웹페이지를 방문하면 사이트는 해당 이미지를 요청한다.
   -  그러나 사실 이미지는 출금 스크립트를 실행하낟. 즉 밥이 웹페이지 방문하면 출금된다.
   -  밥의 브라우저는 웹페이지를 방문하면서 웹사이트에 대한 인증정보를 담고 있는 쿠키도 전송한다.
4. 은행은 밥의 브라우저가 유효한 인증정보를 가진 쿠키를 가지고 있어 출금 요청을 승인한다.



예시2

1. 웹서버는 현재 비밀번호를 요구하지 않고도 관리자 계정의 새로운 비밀번호를 설정할 수 있는 기능을 제공한다.
2. 공격자는 관리자에게 XSS를 사용해 악성 스크립트가 포함된 요청을 보낸다.
3. 관리자가 공격자가 제공한 웹페이지를 방문하면 XSS 스크립트가 실행되어 서버로 비밀번호 재설정 요청을 보낸다.
4. 공격자는 현재 비밀번호를 모르고도 관리자 계정의 비밀번호를 임의로 설정한다.



## CSRF 공격이 성공하는 전제조건

1. "Referer"헤더를 확인하지 않는 사이트를 대상으로 한다.
   - 헤더를 확인하지 않으면 CSRF 공격이 더 쉬워진다.
2. 사이트에서 특정 양식 제출 또는 URL이 웹사이트에서 사이드 이펙트를 일으켜야 공격이 의미가 있음. 이런 링크를 찾는 것
3. CSRF 공격은 양식이나 URL의 입력값들을 알맞게 설정해야 한다. 
4. 피해자가 대상 사이트에 로그인한 상태에서 공격자의 웹페이지로 유도해야 한다.



## CSRF 대책

1. 세션을 안전하게 관리
2. GET 및 POST 매개변수에도 인증 필요하도록
3. HTTP Referer 헤더 확인
4. 인증 쿠키의 수명을 제한하기
5. POST 처리시 GET 매개변수 무시하기
6. 모든 양식 제출에 상요자별 비밀 토큰 필요하도록 하기





## SQL Injection💖💖💖

개중요제일중요

**CWE-89 : 데이터를 SQL 쿼리로 적절하게 세탁하지 않는 오류**

Failure to Sanitize Data into SQL Querie

주로 데이터베이스에서 발생

- **취약점이 발생하는 경우 :** 사용자 입력이 sql문에 포함된 문자열 리터럴 이스케이프 문자에 대해 올바르게 필터링되지 않거나, 사용자 입력이 예상치 못할 때 등

![image](https://github.com/hhzzzk/studyLog/assets/67236054/abb7c15a-2033-419e-b246-9f3f88d83378)

end

18p부터 다음시간에 함. 동영상 꼭 보고오기.



start

12/7 목 14w2



**SQL Injection**

sql 인젝션은 sql 쿼리를 조작해 db에 대한 공격을 시도한다.

```
$sql = "select * from members where id='$id' and password='$password';"
```

위와 같은 쿼리에서 $id와 \$password에는 사용자가 입력한 값이 들어간다.

그러나 해당 id 입력에 'or'1=1'--이 사용되면 문제가 발생한다.



sql에서 주석처리는 --를 사용하면 뒤에 내용은 주석처리된다.

```
$sql = "select * from users where id = '' or '1=1' -- and password = '123123' ";
```

위와 같이 공격하게 되면 id는 공백이고 or true가 들어가고 뒤의 and password 입력은 주석처리된다.



즉 항상 true값이 되므로 공격이 성공한다.

- 공격자는 db의 해당 테이블의 모든 사용자 정보를 얻을 수 있다.

```
$sql = "select * from users where id = ' ′  ;  DROP TABLE  members  -- and password = '123123' ";

```

단순히 정보를 얻는 것 뿐아니라 DROP TABLE 등의 시도를 할 경우 DB의 테이블을 삭제시킬 수도 있다.



## SQL Injection - countermeasure

대책으로는 

1. 사용자 입력을 신뢰하지 않는다.
2. 특별한 char, 특수문자를 입력하지 못하게 한다.
3. 에러메시지를 노출하지 않는다.
4. db 계정의 권한을 낮춘다.

sql인젝션 매우 중요!!!!



## Insecure Direct Object Reference (IDOR)

객체 참조를 하는데 안전하지 못하게 직접 참조하는 것이다.

```
http://onepiece-spoilers.blogspot.com/2009/08/one-piece-554-english.html
```

위와 같은 원피스 불법만화를 보는 사이트가 있을 때 다음화를 보려고 555를 입력하는 등의 시도를 말한다.

- 이런 직접적인 참조로 본래 사용자가 접근할 수 없어야 하는데 데이터에 엑세스할 수 있다.

```
https://example.com/user/profile?userID=123
```

해당 URL에서 어떤 권한 검사도 이루어지지 않고 사용자가 직접 ID를 변경하면 사용자는 다른 사용자의 프로필에도 접근할 수 있다. 



## IDOR : Access Control for Administration

관리자 권한에 대한 접근을 강화해야 한다. IDOR 공격(직접참조 시도)을 통해 숨겨진 admin page, 관리자 페이지에 접속할 수 있다.

```
http://www.site.com/adm
http://www.site.com/admin_login.cgi
http://www.site.com/admin
http://www.site.com/webadmin
http://www.site.com/rhksflwk
http://www.site.com/manager
http://admin.site.com
http://manager.site.com
http://adm.site.com 
```

이런 시도들로 관리자 페이지를 찾아내면 위험하다.

**countermeasure**

1. 개별 포트 번호 및 방화벽 접근 제어
2. 웹서버 접근 제어

```
<Directory /www/admin/>
	AllowOverride AuthConfig
	Order deny, allow
	Deny from all
	Allow from IP lists
</Directory>
```

위처럼 특정 ip에서만 접속을 허용하도록 접근제어할 수 있다.



## Vulnerability Scanner

취약점 스캐너는 sw에서 취약점을 탐지하는데 사용되는 도구나 소프트웨어다.

1. 알려진 SW : nmap, hping3, nessus, paros
2. 서비스 중지를 방지하기 위해 사용된다.
3. 일부 도구는 실제 공격을 수행하기도 한다.

