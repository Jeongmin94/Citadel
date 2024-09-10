# Citadel

## 1. Getting Started(Windows Only)

서브모듈로 GLFW, spdlog를 사용하고 있기 때문에 클론을 하기 위해 다음과 같은 명령어를 사용한다.

```bash
git clone --recursive https://github.com/Jeongmin94/Citadel.git
```

그리고 나서 `SetUp.bat` 파일을 실행하여 비주얼 스튜디오 솔루션 파일(`.sln`)을 생성한다. 프로젝트 실행 목적에 따라 시작 프로젝트를 설정하고(Set as Startup Project) 빌드하여 실행한다.

- 유닛 테스트: 유닛 테스트가 목적이라면 **UnitTest** 프로젝트를 시작 프로젝트로 설정
- 엔진: Citadel 엔진의 실행이 목적이라면 **Citadel** 프로젝트를 시작 프로젝트로 설정