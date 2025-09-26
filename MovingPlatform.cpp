// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "UObject/ConstructorHelpers.h"

AMovingPlatform::AMovingPlatform()
{
	// 매 프레임 움직임을 처리하기 위해 Tick 함수를 활성화
	PrimaryActorTick.bCanEverTick = true;

	// 스태틱 메시 컴포넌트를 생성
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	// 메시 컴포넌트를 이 액터의 루트로 설정
	RootComponent = MeshComponent;

	// 생성자에서만 사용 가능한 FObjectFinder를 통해 기본 메시 애셋을 탐색
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	// 안전장치 : 애셋을 성공적으로 찾았는지 확인
	if (CubeMeshAsset.Succeeded())
	{
		// 찾은 큐브 메시를 MeshComponent에 적용
		MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
		// 발판처럼 보이도록 기본 스케일을 조절
		MeshComponent->SetRelativeScale3D(FVector(3.0f, 1.0f, 0.2f));
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// 현재 위치를 왕복 운동의 기준점인 StartLocation으로 저장
	StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime) // DeltaTime: 프레임 간 시간 간격
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	// '방향 * 속도 * 시간' 공식을 이용해 다음 위치를 계산
	CurrentLocation += Direction * MoveSpeed * DeltaTime;
	// 계산된 다음 위치로 액터를 실제로 이동
	SetActorLocation(CurrentLocation);

	// 시작점과 현재 위치 사이의 거리를 계산
	float Distance = FVector::Dist(StartLocation, CurrentLocation);

	// 이동 거리가 설정된 최대 범위를 벗어났다면, 이동 방향을 반대로 뒤집어 왕복 운동을 구현
	if (Distance >= MaxRange)
	{
		Direction *= -1.0f;
	}
}