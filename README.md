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
│   ├── Model/
│   │   └── Item.h                      # id/name/quantity 최소 엔티티
│   ├── Serialization/
│   │   └── ItemSerialization.h/.cpp    # nlohmann/json ADL to_json/from_json
│   ├── Repository/
│   │   ├── IItemAppender.h             # FindAll + AppendAll만 있는 최소 인터페이스
│   │   └── JsonItemAppender.h/.cpp     # 기존 데이터 보존하며 append하는 writer
│   ├── Generator/
│   │   └── DummyItemGenerator.h/.cpp   # 시드 기반 랜덤 이름/수량 생성 (재현 가능)
│   ├── ThirdParty/nlohmann/json.hpp    # nlohmann/json single header
│   └── main.cpp                        # 생성 개수 입력 → 생성 → append → 요약 출력
├── test/                                # gmock 기반 단위 테스트 (Debug 빌드에 포함)
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

Release 앱은 생성할 개수를 입력받아, 실행 위치의 `items.json`에 있던 기존 데이터의 최대 id
다음 번호부터 새 항목을 이어서 붙이고(append), 생성 개수와 전체 개수를 요약 출력한다. 재실행해도
기존 데이터는 그대로 유지된 채 새 데이터만 추가된다.

## 테스트

- `JsonItemAppenderTest` (4개): 파일 없을 때 빈 목록, **파일 없을 때 append하면 새로 생성**,
  **기존 데이터를 보존하며 append**, 파일 손상 시 예외
- `DummyItemGeneratorTest` (5개): 요청 개수만큼 생성, 순차 id 부여, 양수 수량(도메인 제약),
  **같은 시드 → 같은 결과(재현성)**, 다른 시드 → 다른 결과

모든 클래스는 Red(실패하는 테스트 작성) → Green(최소 구현) 순서로 TDD 사이클을 거쳐 구현했다.
