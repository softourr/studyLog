# Spring-Starter_1-1_create_proj

# 프로젝트 환경설정

## 프로젝트 생성

## 프로젝트 생성 사전 준비물

- Java 11 설치
- IDE: IntelliJ 또는 Eclipse 설치



1. 프로젝트 생성 링크: [https://start.spring.io](https://start.spring.io/)
   - 스프링 부트 스타터 사이트로 이동해 프로젝트 생성
2. 프로젝트 선택:
   - Project: Gradle Project
   - Spring Boot: 2.3.x
   - Language: Java
   - Packaging: Jar
   - Java: 11
3. Project Metadata:
   - groupId: hello
   - artifactId: hello-spring
4. Dependencies:
   - Spring Web
   - Thymeleaf

## Gradle 전체 설정

```
groovyCopy code
plugins {
    id 'org.springframework.boot' version '2.3.1.RELEASE'
    id 'io.spring.dependency-management' version '1.0.9.RELEASE'
    id 'java'
}

```

