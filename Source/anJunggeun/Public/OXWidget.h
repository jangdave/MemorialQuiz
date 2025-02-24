// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OXWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANJUNGGEUN_API UOXWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UMultiLineEditableTextBox* MEditableTextBox_QT;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* State_Check;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UImage* OX_image;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> QuestionText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> QuestionTrue;
	
	UPROPERTY()
	TArray<FString> QuestionAnswer;

	UFUNCTION(BlueprintCallable)
	void AppendText();

	UFUNCTION(BlueprintImplementableEvent)
	void SetQuestImage(const int32 index);
	
	UFUNCTION(BlueprintCallable)
	void AppendTrue(const FString OX);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTrueImage(const FString& text);
	
	UFUNCTION(BlueprintCallable)
	void SetText();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WidgetOnStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WidgetOffStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ImageOnStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ImageOffStart();
	
	UPROPERTY()
	class AAnGameModeBase* KimguGM;

	UFUNCTION(BlueprintImplementableEvent)
	void StateCheckStart(const FString& state);

	UFUNCTION()
	void StateCheckFun(const FString state);
};
