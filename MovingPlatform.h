// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class HOMEWORK6_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime);

	// 플랫폼의 시각적 외형을 담당하는 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// 에디터에서 설정 가능한 플랫폼의 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed = 100.0f;

	// 시작 위치로부터 왕복 이동할 최대 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxRange = 500.0f;

private:
	// 왕복 운동의 기준점이 되는 시작 위치
	FVector StartLocation;
	// 현재 플랫폼이 이동하고 있는 방향 벡터
	FVector Direction = FVector(1.0f, 0.0f, 0.0f);
};