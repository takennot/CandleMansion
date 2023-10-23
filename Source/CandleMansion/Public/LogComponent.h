// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CANDLEMANSION_API ULogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString UniqueName;
	FString FilePath;

	int TotalDetectionTries = 0;
	int TotalExtinguishTries = 0;

	UFUNCTION(BlueprintCallable)
	void CreateNewLogFile();

	UFUNCTION(BlueprintCallable)
	void LogStartCollision(FString objectname);
	UFUNCTION(BlueprintCallable)
	void LogStopCollision(FString objectname);

	UFUNCTION(BlueprintCallable)
	void LogCandleSuccess();
	UFUNCTION(BlueprintCallable)
	void LogCandleTry();
	UFUNCTION(BlueprintCallable)
	void LogCandleTries(int candletries);

	UFUNCTION(BlueprintCallable)
	void LogObjectDetectedBoxTrace(FString objtype); // includes the type of the detected object: Candle, Ghost or GhostPatrol
	UFUNCTION(BlueprintCallable)
	void LogObjectDetectionTry();
	UFUNCTION(BlueprintCallable)
	void LogObjectDetectionTries(int detecttries);

	UFUNCTION(BlueprintCallable)
	void LogObjectDetectionLineTrace(FString objectname);

	UFUNCTION(BlueprintCallable)
	void LogGameTimeInSeconds();
	
	FString GetCurrentTime();
};
