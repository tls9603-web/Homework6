// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimedPlatform.generated.h"

UCLASS()
class HOMEWORK6_API ATimedPlatform : public AActor
{
    GENERATED_BODY()

public:
    ATimedPlatform();

protected:
    virtual void BeginPlay() override;

public:
    // 플랫폼의 시각적 외형을 담당하는 스태틱 메시 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    // 플랫폼이 나타나 있다가 사라지기까지 걸리는 시간(초)
    UPROPERTY(EditAnywhere, Category = "Platform Settings")
    float DisappearDelay = 3.0f;

    // 플랫폼이 사라져 있다가 다시 나타나기까지 걸리는 시간(초)
    UPROPERTY(EditAnywhere, Category = "Platform Settings")
    float ReappearDelay = 2.0f;

private:
    // 사라지는 타이머를 제어하기 위한 핸들
    FTimerHandle DisappearTimerHandle;
    // 다시 나타나는 타이머를 제어하기 위한 핸들
    FTimerHandle ReappearTimerHandle;

    // 플랫폼을 사라지게 하는 함수 (타이머에 의해 호출됨)
    UFUNCTION()
    void Disappear();

    // 플랫폼을 다시 나타나게 하는 함수 (타이머에 의해 호출됨)
    UFUNCTION()
    void Reappear();

    // 플랫폼의 가시성과 충돌 상태를 한 번에 제어하는 헬퍼 함수
    void SetPlatformState(bool bIsVisible);
};