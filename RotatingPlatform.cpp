// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"
#include "UObject/ConstructorHelpers.h"

ARotatingPlatform::ARotatingPlatform()
{
    // 매 프레임 회전을 처리하기 위해 Tick 함수를 활성화
    PrimaryActorTick.bCanEverTick = true;

    // 스태틱 메시 컴포넌트를 생성
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    // 메시 컴포넌트를 이 액터의 루트로 설정
    RootComponent = MeshComponent;

    // 생성자에서만 사용 가능한 FObjectFinder를 통해 기본 실린더 메시 애셋 탐색
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    // 안전장치 : 애셋을 성공적으로 찾았는지 확인
    if (CylinderMeshAsset.Succeeded())
    {
        // 찾은 실린더 메시를 MeshComponent에 적용
        MeshComponent->SetStaticMesh(CylinderMeshAsset.Object);
        // 원반처럼 보이도록 기본 스케일을 조절
        MeshComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 0.2f));
    }
}

void ARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingPlatform::Tick(float DeltaTime) // DeltaTime: 프레임 간 시간 간격
{
    Super::Tick(DeltaTime);

    // 현재 회전 값에 추가적인 회전을 더합니다. Z축(Yaw)을 중심으로 회전
    // DeltaTime을 곱하여 프레임 속도에 관계없이 일정한 속도로 회전하도록 보장
    AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f)); // (Pitch, Yaw, Roll)
}

