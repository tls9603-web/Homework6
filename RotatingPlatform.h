// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class HOMEWORK6_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	ARotatingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 플랫폼의 시각적 외형을 담당하는 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// 에디터에서 설정 가능한 플랫폼의 초당 회전 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeed = 50.0f;
};