# DummyDataGenerator-MINGOO-21015010

테스트용 더미 데이터를 생성해 JSON 저장소에 append하는 CLI 도구 PoC.

Main 프로젝트 [`SampleOrderSystem-MINGOO-21015010`](https://github.com/kangtop729/SampleOrderSystem-MINGOO-21015010)의
초기 데이터 시딩 아이디어로 참고되는 산출물이다.

## 목적

- 실행할 때마다 기존 데이터를 유지한 채 지정한 개수만큼 더미 데이터가 추가되는지 검증한다.
- 생성된 데이터가 상식적인 도메인 제약(수량은 양수 등)을 위반하지 않는 구조를 실험한다.

## 구조

```
DummyDataGenerator-MINGOO-21015010/
├── src/
│   ├── Model/                       # 최소 엔티티
│   ├── Repository/                  # JSON append writer
│   ├── Generator/                   # 랜덤 값 생성 로직
│   ├── ThirdParty/nlohmann/json.hpp # nlohmann/json single header
│   └── main.cpp                     # CLI 실행
├── test/                            # gmock 기반 단위 테스트 (Debug 빌드에 포함)
├── CLAUDE.md
├── PLAN.md
└── README.md
```

자세한 구현 계획은 [`PLAN.md`](PLAN.md) 참고.

## 빌드 및 실행

```
# 테스트 빌드 및 실행 (Debug 빌드 = 테스트 실행)
msbuild DummyDataGenerator-MINGOO-21015010.vcxproj /p:Configuration=Debug /p:Platform=x64
x64\Debug\DummyDataGenerator-MINGOO-21015010.exe

# CLI 앱 빌드/실행
msbuild DummyDataGenerator-MINGOO-21015010.vcxproj /p:Configuration=Release /p:Platform=x64
x64\Release\DummyDataGenerator-MINGOO-21015010.exe
```

(구현 진행에 따라 테스트 구성/실행 결과 절 추가 예정)
