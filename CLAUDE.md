# CLAUDE.md

이 문서는 Claude(에이전트)가 이 저장소에서 작업할 때 따라야 할 규칙을 정리한다.

## 프로젝트 개요

테스트용 더미 데이터를 생성해 JSON 저장소에 **append**하는 CLI 도구 PoC다. Main 프로젝트인
[`SampleOrderSystem-MINGOO-21015010`](https://github.com/kangtop729/SampleOrderSystem-MINGOO-21015010)의
초기 데이터 시딩 아이디어로 참고되며, 반도체 시료 도메인 로직은 다루지 않는다. 이 저장소는
`DataPersistence-MINGOO-21015010`과 별도 Git 저장소이므로 코드를 공유하지 않고, 엔티티/JSON 스키마를
자체적으로 정의한다. 세부 계획은 [`PLAN.md`](PLAN.md) 참고.

## 기술 스택

- 언어: C++20
- 빌드: Visual Studio / MSBuild (`.vcxproj`)
- 플랫폼: x64 / Debug, Release
- 테스트: GoogleTest / GoogleMock (`gmock` 1.11.0, NuGet 패키지)
- JSON: nlohmann/json 3.11.3 (single header, `src/ThirdParty/nlohmann/json.hpp`에 vendoring)

## 프로젝트 구성

[`ConsoleMVC-MINGOO-21015010`](https://github.com/kangtop729/ConsoleMVC-MINGOO-21015010)과 동일하게,
별도 테스트 프로젝트/Configuration 없이 `DummyDataGenerator-MINGOO-21015010.vcxproj`의 기본
Debug/Release 2개 Configuration만 사용한다.

- `src/main.cpp`는 두 Configuration 모두에서 공통으로 빌드되는 유일한 진입점이다. `_DEBUG` 전처리기
  정의(Debug Configuration에서 기본 설정됨) 여부로 동작이 갈린다.
  - `Debug`: `main()`이 `::testing::InitGoogleTest` + `RUN_ALL_TESTS()`를 호출해 테스트를 실행한다.
  - `Release`: 더미 데이터 생성 CLI를 실행한다. `test/*.cpp`는 빌드에서 제외된다.
- Model/Repository/Generator의 `.cpp`는 두 Configuration 모두에서 공통으로 빌드된다.

## 빌드 및 테스트 명령

```
# 테스트 빌드 및 실행 (Debug 빌드 = 테스트 실행)
msbuild DummyDataGenerator-MINGOO-21015010.vcxproj /p:Configuration=Debug /p:Platform=x64
x64\Debug\DummyDataGenerator-MINGOO-21015010.exe

# CLI 앱 빌드/실행
msbuild DummyDataGenerator-MINGOO-21015010.vcxproj /p:Configuration=Release /p:Platform=x64
x64\Release\DummyDataGenerator-MINGOO-21015010.exe
```

## 작업 원칙

1. **append 전용**: 기존 JSON 데이터를 덮어쓰지 않고 항상 추가만 한다. ID는 마지막 값 이후로 이어서 부여한다.
2. **영속성 방식 고정**: 반드시 JSON 파일 기반으로 구현한다 (Main 프로젝트와 일치해야 하는 항목).
3. **가벼운 TDD**: 이 저장소는 PoC이므로 Main만큼 촘촘한 경계값 테스트를 요구하지 않는다. 핵심
   시나리오 1~2개(생성 개수만큼 정확히 추가되는지, 기존 데이터가 보존되는지)에 대해 실패하는 테스트를
   먼저 작성하고 확인한 뒤, 최소 구현으로 통과시키는 Red-Green 사이클을 따른다.
4. **작은 단위 커밋 + 자동 push**: Phase 단위 혹은 그보다 작은, 의미 있는 단위로 커밋한다. 커밋 후
   바로 push까지 수행하고, 사용자는 push된 결과를 보고 검토한다.
5. **커밋 메시지 규칙**: 제목은 반드시 아래 5개 prefix 중 하나로 시작한다.
   - `[feature]` 새 기능 추가
   - `[refactor]` 동작 변경 없는 구조 개선
   - `[fix]` 버그 수정
   - `[docs]` 문서 변경
   - `[test]` 테스트 추가/수정, 테스트 인프라 변경
6. **Clean Code**: 함수는 한 가지 일만 하도록 작게 유지하고, 매직 넘버 대신 의미 있는 이름의 상수를
   사용하며, 불필요한 주석 대신 좋은 이름으로 의도를 드러낸다. 다만 PoC 특성상 Main만큼 세세한
   리팩토링/리뷰까지는 요구하지 않는다.
7. **불필요한 추상화 금지**: 명세에 없는 기능(복잡한 데이터 분포 설정 등)을 미리 만들지 않는다.
