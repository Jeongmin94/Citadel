# Citadel

## 0. 사용 라이브러리

- OpenGL, GLFW, Glad, glm
- ImGui, ImGui-Docking
- spdlog
- googletest
- build system(Windows: premake5, Mac: CMake)

## 1. 시작하기

서브모듈로 GLFW, spdlog를 사용하고 있기 때문에 클론을 하기 위해 다음과 같은 명령어를 사용한다.

```bash
git clone --recursive https://github.com/Jeongmin94/Citadel.git
```

### 1.1 Windows

> Windows, Visual Studio 2022 사용을 전제로 함

`SetUp.bat` 파일을 실행하여 비주얼 스튜디오 솔루션 파일(`.sln`)을 생성한다. 프로젝트 실행 목적에 따라 시작 프로젝트를 설정하고(Set as Startup Project) 빌드하여 실행한다.

- 유닛 테스트: 유닛 테스트가 목적이라면 **UnitTest** 프로젝트를 시작 프로젝트로 설정
- 엔진: Citadel 엔진의 실행이 목적이라면 **Citadel** 프로젝트를 시작 프로젝트로 설정

### 1.2 Mac

> Apple Silicon 기반이며 gcc, g++, CMake 설치를 전제로 함
