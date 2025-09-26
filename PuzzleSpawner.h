// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSpawner.generated.h"

class UBoxComponent;
class AMovingPlatform;
class ARotatingPlatform;

// 스폰할 플랫폼의 종류별 설정을 묶어서 관리하기 위한 구조체
USTRUCT(BlueprintType)
struct FSpawnablePlatformInfo
{
    GENERATED_BODY()

    // 스폰할 플랫폼의 C++ 또는 블루프린트 클래스
    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> PlatformClass;

    // 해당 종류의 플랫폼을 몇 개 스폰할지 결정하는 개수
    UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
    int32 SpawnCount = 5;

    // 스폰될 때 적용될 최소 크기
    UPROPERTY(EditAnywhere)
    FVector MinScale = FVector(1.0, 1.0, 0.1f);

    // 스폰될 때 적용될 최대 크기
    UPROPERTY(EditAnywhere)
    FVector MaxScale = FVector(3.0f, 3.0f, 0.3f);
};


UCLASS()
class HOMEWORK6_API APuzzleSpawner : public AActor
{
    GENERATED_BODY()

public:
    APuzzleSpawner();

protected:
    virtual void BeginPlay() override;

private:
    // 플랫폼이 스폰될 영역을 시각적으로 나타내는 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Spawner Settings")
    UBoxComponent* SpawnVolume;

    // 에디터에서 설정할 스폰 대상 플랫폼들의 정보 배열
    UPROPERTY(EditAnywhere, Category = "Spawner Settings")
    TArray<FSpawnablePlatformInfo> PlatformsToSpawn;

    // MovingPlatform의 이동 속도 랜덤 범위 (X: 최소, Y: 최대)
    UPROPERTY(EditAnywhere, Category = "Randomization | Moving Platform")
    FVector2D MoveSpeedRange = FVector2D(50.f, 250.f);

    // MovingPlatform의 이동 거리 랜덤 범위 (X: 최소, Y: 최대)
    UPROPERTY(EditAnywhere, Category = "Randomization | Moving Platform")
    FVector2D MaxRangeRange = FVector2D(300.f, 1000.f);

    // RotatingPlatform의 회전 속도 최소값
    UPROPERTY(EditAnywhere, Category = "Randomization | Rotating Platform")
    float MinRotationSpeed = 10.f;

    // RotatingPlatform의 회전 속도 최대값
    UPROPERTY(EditAnywhere, Category = "Randomization | Rotating Platform")
    float MaxRotationSpeed = 100.f;

    // TimedPlatform이 사라지기까지의 시간 랜덤 범위 (X: 최소, Y: 최대)
    UPROPERTY(EditAnywhere, Category = "Randomization | Timed Platform")
    FVector2D DisappearDelayRange = FVector2D(2.0f, 5.0f);

    // TimedPlatform이 다시 나타나기까지의 시간 랜덤 범위 (X: 최소, Y: 최대)
    UPROPERTY(EditAnywhere, Category = "Randomization | Timed Platform")
    FVector2D ReappearDelayRange = FVector2D(1.0f, 3.0f);

private:
    // 모든 플랫폼의 스폰을 처리하는 메인 함수
    void SpawnAllPlatforms();
};