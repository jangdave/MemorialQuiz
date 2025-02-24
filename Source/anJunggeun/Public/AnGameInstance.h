// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SDetection/DetectionService.h"
#include "AnGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANJUNGGEUN_API UAnGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 QuestionCount = 0;

	UPROPERTY()
	class AAnGameModeBase* GM;

	UPROPERTY()
	EGrpcServiceState DetectionServiceState;
	
	UPROPERTY()
	UDetectionService* DetectionService;

	UPROPERTY()
	UDetectionServiceClient* DetectionServiceClient;

	UFUNCTION()
	void ConnectGRPC();

	UFUNCTION()
	void MakeClientGRPC();
	
	UFUNCTION()
	void CallShutdownService();

	UFUNCTION()
	void CallHelloService();

	UFUNCTION()
	void CallOService();

	UFUNCTION()
	void CallXService();

	UFUNCTION()
	void CallOXService();
	
	UFUNCTION()
	void OnDetectionServiceStateChanged(EGrpcServiceState NewState);
	
	UFUNCTION()
	void OnHelloResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcDetectionHelloResponse& Response);

	UFUNCTION()
	void OnOXResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcDetectionOXResponse& Response);
	
	UFUNCTION()
	void RestartLevel();
};
