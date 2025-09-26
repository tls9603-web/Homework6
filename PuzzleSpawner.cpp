// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MovingPlatform.h"
#include "RotatingPlatform.h"
#include "TimedPlatform.h"

APuzzleSpawner::APuzzleSpawner()
{
    // 매 프레임 업데이트가 필요 없으므로 Tick을 비활성화
    PrimaryActorTick.bCanEverTick = false;
    // 스폰 영역을 담당할 박스 컴포넌트를 생성하고 루트로 설정
    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    RootComponent = SpawnVolume;
}

// 액터 생성시 모든 플랫폼을 스폰하는 함수를 호출
void APuzzleSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnAllPlatforms();
}

void APuzzleSpawner::SpawnAllPlatforms()
{
    FActorSpawnParameters SpawnParams;
    // 스폰 시 다른 액터와 충돌하더라도 위치를 조정해서 항상 스폰되도록 설정
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 에디터에 설정된 플랫폼 정보 배열을 하나씩 순회
    for (const FSpawnablePlatformInfo& PlatformInfo : PlatformsToSpawn)
    {
        // 안전장치 : 스폰할 클래스가 지정되지 않았거나 스폰 개수가 0 이하면 넘어감
        if (PlatformInfo.PlatformClass == nullptr || PlatformInfo.SpawnCount <= 0)
        {
            continue;
        }

        // 해당 종류의 플랫폼을 지정된 SpawnCount만큼 반복하여 생성
        for (int32 i = 0; i < PlatformInfo.SpawnCount; ++i)
        {
            // SpawnVolume 영역 내에서 랜덤한 위치를 계산합니다.
            FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
                SpawnVolume->GetComponentLocation(), // 박스의 중심 위치
                SpawnVolume->GetScaledBoxExtent()    // 박스의 절반 크기 (범위)
            );

            // 계산된 위치에 액터를 스폰
            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
                PlatformInfo.PlatformClass,
                SpawnLocation,
                FRotator::ZeroRotator,
                SpawnParams
            );

            // 안전장치 : 액터가 성공적으로 스폰되었는지 확인
            if (SpawnedActor)
            {
                // 설정된 최소/최대 범위 내에서 랜덤한 스케일(크기) 값을 계산
                float RandX = FMath::RandRange(PlatformInfo.MinScale.X, PlatformInfo.MaxScale.X);
                float RandY = FMath::RandRange(PlatformInfo.MinScale.Y, PlatformInfo.MaxScale.Y);
                float RandZ = FMath::RandRange(PlatformInfo.MinScale.Z, PlatformInfo.MaxScale.Z);
                // 계산된 랜덤 스케일을 스폰된 액터에 적용
                SpawnedActor->SetActorScale3D(FVector(RandX, RandY, RandZ));

                // MovingPlatform 클래스 액터에 속성 설정
                if (AMovingPlatform* MovingPlatform = Cast<AMovingPlatform>(SpawnedActor))
                {
                    MovingPlatform->MoveSpeed = FMath::RandRange(MoveSpeedRange.X, MoveSpeedRange.Y);
                    MovingPlatform->MaxRange = FMath::RandRange(MaxRangeRange.X, MaxRangeRange.Y);
                }
                // RotatingPlatform 클래스 액터에 속성 설정
                else if (ARotatingPlatform* RotatingPlatform = Cast<ARotatingPlatform>(SpawnedActor))
                {
                    RotatingPlatform->RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed);
                }
                // TimedPlatform 클래스 액터에 속성 설정
                else if (ATimedPlatform* TimedPlatform = Cast<ATimedPlatform>(SpawnedActor))
                {
                    TimedPlatform->DisappearDelay = FMath::RandRange(DisappearDelayRange.X, DisappearDelayRange.Y);
                    TimedPlatform->ReappearDelay = FMath::RandRange(ReappearDelayRange.X, ReappearDelayRange.Y);
                }
            }
        }
    }
}