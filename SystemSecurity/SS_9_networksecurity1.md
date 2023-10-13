# SS_9_networksecurity1

```
ARP level
TCP/IP level
Firewall
High Availability
Intrusion Detection System
DDoS
Intrusion Prevention System
```

## ARP level

```
ARP spoofing
man in the middle attack
Smurf attack
Packet sniffing
MAC flooding
```

🌻

## High Availability

시스템이나 네트워크가 지속적으로 이용 가능한 상태를 유지하며 장애 발생 시에도 빠르게 복구할 수 있는 수준의 신뢰성을 의미한다.

시스템이 기능 중단, 데이터 손실 또는 서비스 중단 없이 계속 사용 가능하도록 하는 것을 목표로 한다.

예시로 무선공유기를 사용할 때 한 대가 망가져도 비사용?무선 공유기 하나를 더 구비해 하나가 망가져도 서비스가 유지될 수 있도록 하는 것.

🌻

🌻

🌻

## 링크 레이어

데이터 링크 레이어이다. 두 개의 연결된 노드 간에 직접적인 통신을 관리한다.

링크 레이어의 주요 목표는 같은 물리적 네트워크 미디어를 공유하는 장치 간의 데이터 전달을 효율적으로 관리하는 것이다.

- 물리적 주소(MAC 주소 등)을 사용해 장치를 식별한다.
- 프레임(frame)라는 작은 데이터 패킷을 생성하고 물리적 링크로 전송한다.
- 오류 검출 및 재전송과 같은 오류 처리를 수행해 데이터 전송 신뢰성을 유지한다.
- 네트워크 계층과 직접 통신해 상위 레이어(네트워크 레이어)로 데이터를 전달한다.

## 네트워크 레이어

데이터 패킷을 원격 노드로 라우팅하고, 여러 네트워크 간의 통신을 관리한다.

- 논리적 주소(IP주소 등)을 사용해 노드와 네트워크를 식별한다.
- 라우팅 알고리즘을 사용해 패킷을 목적지로 전달하며 중간 라우터를 통해 다양한 경로를 선택한다.
- 서비스 품질(Quility of Service, QoS) 관리와 서비스 제공을 위한 다양한 프로토콜을 지원한다.
- 주로 데이터 그램(Datagram)패킷을 처리하며 목적지 노드로의 패킷 전달을 담당한다.

🌻

🌻

🌻

## ARP spoofing

네트워크에서 사용되는 주소 해상도 프로토콜(Address Resolution Protocol, ARP)을 이용한 공격 기법이다.

**ARP?**

ARP는 IP주소와 실제 하드웨어 MAC 주소 간의 매핑을 관리하는 프로토콜이다. 이 정보를 이용해 데이터 프레임을 올바른 장치로 전달한다.

- ARP 스푸핑은 위의 과정에서 중간에서 정보를 가로채 데이터를 스니핑하거나 데이터를 수정하거나 중단시키는 것이다.


- 같은 말로 ARP poisoning, ARP flooding, ARP poison routing라고도 한다.

![image](https://github.com/hhzzzk/studyLog/assets/67236054/f8ad3739-1f7b-47a1-8910-da826b7fde04)

- SW : 스위치는 로컬 영역 네트워크(LAN)에서 데이터 흐름을 관리하고 네트워크 효율성을 향상시킨다.
  - 데이터 패킷 전달 : MAC 주소를 사용해 각 연결된 장치를 식별하고 패킷을 목적지 장치로 전달한다.





## ARP request/reply 

네트워크에서 장치들은 다른 장치의 MAC 주소를 알기 위해 ARP를 사용한다.

ARP request : 누구의 MAC인지 질의

ARP reply : 누구의 MAC인지 응답

![image](https://github.com/hhzzzk/studyLog/assets/67236054/177e1680-43b1-4780-bbab-bde3ffe267e6)

1. **ARP request** : A가 R(목적지 장치)의 MAC 주소를 알기 위해 ARP 요청을 생성한다. 

​			**요청은 브로드캐스트로 전파되며 네트워크 내 모든 장치에 도달한다.**

2. ARP request 수신 : 스위치는 ARP 요청 패킷을 받고 해당 패킷을 브로드캐스트해 스위치에 연결된 모든 장치에 전송한다.

3. ARP reply : 공격자 B는 ARP 요청을 받고 공격 목적으로 A에 대한 가짜 ARP reply를 생성한다.

   ​			해당 응답에는 공격자의 MAC 주소가 R의 MAC 주소처럼 나타난다.

   ​			공격자는 이 가짜 응답을 스위치를 통해 A로 보낸다.

4. ARP reply 수신 : A는 가짜 ARP 응답을 받고 앞으로의 통신에서 R의 MAC 주소로 데이터를 전송한다.

   - 프로세스에 따라 먼저 도착한 응답을 수용하거나 나중에 도착한 응답을 수용하거나 할 수 있다.

5. 이후 A가 R로 데이터를 전송하려고 할 때마다 해당 데이터는 실제로 B에게 전송된다.

   B는 중간에서 데이터를 스니핑하거나 수정할 수 있다. == 중간자 공격(MITM)



## Man-in-the-middle-attack (MITM)

중간자 공격은 통신 경로 상에 제3자가 존재하여, 양쪽의 통신 당사자와 중간에서 통신을 가로채거나 조작하는 공격 형태이다.

- 디피-헬만은 중간자 공격에 취약하다.
  - 디피헬만은 공개 키 암호화 및 키 교환 프로토콜 중 하나이다.
  - 두 통신 당사자가 비밀 키를 교환하는 방법을 제공한다.



![image](https://github.com/hhzzzk/studyLog/assets/67236054/30d9a46c-4b4c-495b-bd76-d9bf81ae9cfc)



## MITM Countermeasure

```
–  PKI
–  One-time pad
–  Strong mutual authentication 
–  Second channel verification
```

## PKI

공개 키 인프라 : 공개키와 개인키를 사용해 통신을 보호하는 시스템이다.

일회용 패드 : 통신 당사자 간에 무작위로 생성된 키 스트림(일회용 패드)를 공유하고 이 키를 사용해 메시지를 아뫃화한다. 키 스트림은 한 번만 사용되기 때문에 공격자가 키를 복구하기 어렵다 == MITM 공격에 대한 방어로 적절

강력한 상호 인증

이중 채널 확인 : 두 개 이상의 통신 채널을 사용해 상호 인증 및 보안을 확인하는 것이다.



+한시간에끝내는패킷 영상은 교수님 기준 최고의 동영상! 꼭봐라!매우좋다! 숙제

+담주에는 진도는 안나가고 기출리뷰랑 질의응답 정도