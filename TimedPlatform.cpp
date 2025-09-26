// Fill out your copyright notice in the Description page of Project Settings.

#include "TimedPlatform.h"
#include "UObject/ConstructorHelpers.h"

ATimedPlatform::ATimedPlatform()
{
    // 타이머를 사용하므로 Tick을 비활성화하여 성능을 최적화
    PrimaryActorTick.bCanEverTick = false;

    // 스태틱 메시 컴포넌트를 생성
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    // 메시 컴포넌트를 이 액터의 루트로 설정
    RootComponent = MeshComponent;

    // 생성자에서만 사용 가능한 FObjectFinder를 통해 기본 메시 애셋을 탐색
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

    // 안전장치 : 애셋을 성공적으로 찾았는지 확인
    if (SphereMeshAsset.Succeeded())
    {
        // 찾은 구체 메시를 MeshComponent에 적용
        MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
        // 기본 스케일을 조절
        MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

// 게임이 시작될 때 첫 번째 타이머를 설정하여 로직을 시작
void ATimedPlatform::BeginPlay()
{
    Super::BeginPlay();

    // 월드의 타이머 관리자를 통해 타이머를 설정
    GetWorld()->GetTimerManager().SetTimer(
        DisappearTimerHandle,       // 제어할 타이머 핸들
        this,                       // 함수를 호출할 대상 객체
        &ATimedPlatform::Disappear, // 호출될 함수
        DisappearDelay,             // 지연 시간
        false                       // 반복 여부 (false: 한 번만 실행)
    );
}

// 플랫폼을 사라지게 하는 타이머를 설정, Delay 이후 Reappear 호출(순환구조)
void ATimedPlatform::Disappear()
{
    // 플랫폼을 보이지 않고 충돌하지 않는 상태로 변경
    SetPlatformState(false);

    // ReappearDelay초 후에 Reappear 함수를 호출하도록 타이머를 설정
    GetWorld()->GetTimerManager().SetTimer(
        ReappearTimerHandle,
        this,
        &ATimedPlatform::Reappear,
        ReappearDelay,
        false
    );
}

// 플랫폼을 나타나게 하는 타이머를 설정, Delay 이후 Disappear 호출(순환구조)
void ATimedPlatform::Reappear()
{
    // 플랫폼을 보이고 충돌 가능한 상태로 변경
    SetPlatformState(true);

    // DisappearDelay초 후에 Disappear 함수를 호출하도록 타이머를 설정
    GetWorld()->GetTimerManager().SetTimer(
        DisappearTimerHandle,
        this,
        &ATimedPlatform::Disappear,
        DisappearDelay,
        false
    );
}

// 플랫폼의 가시성과 충돌 설정
void ATimedPlatform::SetPlatformState(bool bIsVisible)
{
    // 액터를 게임 월드에서 시각적으로 숨기거나 보이게
    SetActorHiddenInGame(!bIsVisible);
    // 액터의 충돌 기능을 활성화 또는 비활성화
    SetActorEnableCollision(bIsVisible);
}