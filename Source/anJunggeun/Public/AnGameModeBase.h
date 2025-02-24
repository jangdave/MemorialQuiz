// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "AnGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EDHGameModeState : uint8
{
	// 상태 저장 enum
	GM_IDLE,
	GM_HELLO,
	GM_TUTO,
	GM_QUIZ,
	GM_O,
	GM_X,
	GM_RESULT
};

/**
 * 
 */
UCLASS()
class ANJUNGGEUN_API AAnGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	
	AAnGameModeBase();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	class UAnGameInstance* GI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UOXWidget> OX_Widget;

	UPROPERTY(EditAnywhere)
	class UOXWidget* OX_wid;
	
	UFUNCTION(BlueprintCallable)
	void SyncInt();

	UFUNCTION(BlueprintImplementableEvent)
	void EndSyncQuiz();

	UFUNCTION(BlueprintImplementableEvent)
	void EndSyncFin();
	
	UFUNCTION(BlueprintImplementableEvent)
	void EndQuiz();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 QN;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 QC;

	// 정답 추론 함수
	UFUNCTION()
	void AnswerCheck();
	
	// GM state machine
	// gm state 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EDHGameModeState DH_GM_state;
	
	// state 실행 함수
	UFUNCTION()
	void DH_GM_CHANGE();

	// state 변경 함수
	UFUNCTION(BlueprintCallable)
	void SetDH_GM_State(EDHGameModeState next);
	
	// 시퀀스 플레이어 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ULevelSequence*> audioSequences;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, ULevelSequence*> IdleSequences;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULevelSequencePlayer* Player;
	
	UFUNCTION()
	void Idle_Start();

	UFUNCTION(BlueprintImplementableEvent)
	void IdleCircle();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Hello_Start();

	UFUNCTION(BlueprintImplementableEvent)
	void Tuto_Start();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Tuto_Check_O();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Tuto_Check_X();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Quiz_Start();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Quiz_Answer_O();

	UFUNCTION(BlueprintImplementableEvent)
	void Quiz_Answer_X();

	UFUNCTION(BlueprintImplementableEvent)
	void Quiz_Result();

	// widget 관련 함수
	UFUNCTION(BlueprintCallable)
	void CallAppendText();

	UFUNCTION(BlueprintCallable)
	void CallAppendTrue(const FString OX);
	
	UFUNCTION(BlueprintCallable)
	void CallImageOn();
	
	UFUNCTION(BlueprintCallable)
	void CallImageOff();
	
	UFUNCTION(BlueprintCallable)
	void CallWidgetOn();

	UFUNCTION(BlueprintCallable)
	void CallWidgetOff();

	UFUNCTION(BlueprintCallable)
	void CallStateOn(const FString state);
	
	// QN 초기화 함수
	UFUNCTION(BlueprintCallable)
	void CallQNSet();
	
	// grpc 함수
	UFUNCTION(BlueprintCallable)
	void CallHello();

	UFUNCTION(BlueprintCallable)
	void CallO();

	UFUNCTION(BlueprintCallable)
	void CallX();

	UFUNCTION(BlueprintCallable)
	void CallOX();

	UFUNCTION(BlueprintCallable)
	void CallShutdown();

	UFUNCTION(BlueprintCallable)
	void CallMakeClient();
	
	// 로그 메모장 함수
	UFUNCTION()
	static bool AppendJsonToFile(const FString& FilePath, const FString& JsonString);

	UFUNCTION()
	void SaveLog();

	// index 저장 함수
	static bool ReadJsonFromFile(const FString& FilePath, TSharedPtr<FJsonObject>& OutJsonObject);
	
	static bool WriteJsonToFile(const FString& FilePath, const TSharedPtr<FJsonObject> JsonObject);

	UFUNCTION()
	void ReadIndex();

	UFUNCTION(BlueprintCallable)
	void WriteIndex();
	
	UFUNCTION()
	void SaveEntryLogTime();

	UPROPERTY()
	int32 saveIndex;

	UPROPERTY()
	FDateTime entryTime;

	UPROPERTY()
	FString userAnswer;

	UPROPERTY()
	FString checkCorrect;

	UFUNCTION(BlueprintCallable)
	void BindOInput();

	UFUNCTION(BlueprintCallable)
	void BindXInput();
};
