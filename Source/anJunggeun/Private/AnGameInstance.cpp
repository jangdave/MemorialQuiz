// Fill out your copyright notice in the Description page of Project Settings.


#include "AnGameInstance.h"
#include "AnGameModeBase.h"
#include "TurboLinkGrpcManager.h"
#include "TurboLinkGrpcUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

void UAnGameInstance::Init()
{
	Super::Init();

}

void UAnGameInstance::ConnectGRPC()
{
	// grpc 연결 시작
	UTurboLinkGrpcManager* TurboLinkManager = UTurboLinkGrpcUtilities::GetTurboLinkGrpcManager(this);

	DetectionService = Cast<UDetectionService>(TurboLinkManager->MakeService("DetectionService"));

	if(DetectionService == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("detection service is null!!!!"));
		return;
	}
	
	DetectionService->OnServiceStateChanged.AddUniqueDynamic(this, &UAnGameInstance::OnDetectionServiceStateChanged);

	DetectionService->Connect();

	// 로그
	//UE_LOG(LogTemp, Warning, TEXT("detection service is connect!!!!"));
	//auto test = UEnum::GetValueAsString(DetectionService->GetServiceState());
	//UE_LOG(LogTemp, Warning, TEXT("service state : %s"), *test);

	// 다음 단계로
	MakeClientGRPC();
}

void UAnGameInstance::MakeClientGRPC()
{
	UE_LOG(LogTemp, Warning, TEXT("GRPC!!!!"));
	
	if(DetectionService != nullptr && DetectionService->GetServiceState() == EGrpcServiceState::Ready)
	{
		DetectionServiceClient = DetectionService->MakeClient();

		// 델리게이트 함수 바인드
		DetectionServiceClient->OnHelloDetectionResponse.AddUniqueDynamic(this, &UAnGameInstance::OnHelloResponse);
		DetectionServiceClient->OnOXDetectionResponse.AddUniqueDynamic(this, &UAnGameInstance::OnOXResponse);

		// 콜 함수 실행
		CallHelloService();
	}
	else
	{
		FTimerHandle grpcTimer;
		GetWorld()->GetTimerManager().SetTimer(grpcTimer, this, &UAnGameInstance::MakeClientGRPC, 3.0f, false);
	}
}

// client shut sown 함수
void UAnGameInstance::CallShutdownService()
{
	DetectionService->RemoveClient(DetectionServiceClient);
	
	DetectionServiceClient->Shutdown();
	
	DetectionServiceClient = nullptr;
}

// 사용자 인식 함수
void UAnGameInstance::CallHelloService()
{
	FGrpcContextHandle DetecHello = DetectionServiceClient->InitHelloDetection();

	FGrpcDetectionEmpty helloRequest;
	
	DetectionServiceClient->HelloDetection(DetecHello, helloRequest);
}

// 푯말 O 인식 함수
void UAnGameInstance::CallOService()
{
	FGrpcContextHandle DetecOX = DetectionServiceClient->InitOXDetection();

	FGrpcDetectionOXRequest oxRequest;

	oxRequest.Ox = "O";

	DetectionServiceClient->OXDetection(DetecOX, oxRequest);
}

// 푯말 x 인식 함수
void UAnGameInstance::CallXService()
{
	FGrpcContextHandle DetecOX = DetectionServiceClient->InitOXDetection();

	FGrpcDetectionOXRequest oxRequest;

	oxRequest.Ox = "X";

	DetectionServiceClient->OXDetection(DetecOX, oxRequest);
}

void UAnGameInstance::CallOXService()
{
	FGrpcContextHandle DetecOX = DetectionServiceClient->InitOXDetection();

	FGrpcDetectionOXRequest oxRequest;

	oxRequest.Ox = "OX";

	DetectionServiceClient->OXDetection(DetecOX, oxRequest);
}

void UAnGameInstance::OnDetectionServiceStateChanged(EGrpcServiceState NewState)
{
	DetectionServiceState = NewState;
}

void UAnGameInstance::OnHelloResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult,
	const FGrpcDetectionHelloResponse& Response)
{
	if(GrpcResult.Code == EGrpcResultCode::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("is hello is : %s"), Response.IsHello ? TEXT("true") : TEXT("false"));

		if(Response.IsHello == true)
		{
			GM = Cast<AAnGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(GM != nullptr)
			{
				// 사용자 인사 인식 시작
				GM->SetDH_GM_State(EDHGameModeState::GM_HELLO);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("hello result : %s"), *GrpcResult.GetCodeString());

		// 응답 오류 시 레벨 재시작을 통한 재연결 시도
		RestartLevel();
	}
}

void UAnGameInstance::OnOXResponse(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult,
	const FGrpcDetectionOXResponse& Response)
{
	if(GrpcResult.Code == EGrpcResultCode::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("ox is : %s"), *Response.Ox);

		if(Response.Ox == "O")
		{
			GM = Cast<AAnGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(GM != nullptr)
			{
				if(GM->DH_GM_state == EDHGameModeState::GM_TUTO)
				{
					GM->Tuto_Check_O();
				}
				else
				{
					GM->userAnswer = Response.Ox;

					GM->AnswerCheck();				
				}
			}
				
		}
		else
		{
			GM = Cast<AAnGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(GM != nullptr)
			{
				if(GM->DH_GM_state == EDHGameModeState::GM_TUTO)
				{
					GM->Tuto_Check_X();
				}
				else
				{
					GM->userAnswer = Response.Ox;

					GM->AnswerCheck();		
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ox result : %s"), *GrpcResult.GetCodeString());

		// 응답 오류 시 레벨 재시작을 통한 재연결 시도
		RestartLevel();
	}
}

void UAnGameInstance::RestartLevel()
{
	FString name = GetWorld()->GetName();

	FName levelName = UKismetStringLibrary::Conv_StringToName(name);

	UE_LOG(LogTemp, Warning, TEXT("name : %s"), *levelName.ToString());
				
	UGameplayStatics::OpenLevel(GetWorld(), levelName);

	UE_LOG(LogTemp, Warning, TEXT("Level Restart!!"));
}