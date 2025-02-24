// Fill out your copyright notice in the Description page of Project Settings.


#include "AnGameModeBase.h"
#include "AnGameInstance.h"
#include "OXWidget.h"
#include "Blueprint/UserWidget.h"

AAnGameModeBase::AAnGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 레벨 시퀀스 에셋 불러오는 법
	//FString test1111 = TEXT("/Game/kimgu/audio_sequence/audioLevelSequence1.audioLevelSequence1");
	//test.Add(LoadObject<ULevelSequence>(nullptr, *test1111));
}

void AAnGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 시작 state 설정
	SetDH_GM_State(EDHGameModeState::GM_IDLE);
	
	GI = Cast<UAnGameInstance>(GetGameInstance());

	OX_wid = Cast<UOXWidget>(CreateWidget(GetWorld(), OX_Widget));

	if(GI != nullptr)
	{
		QC = GI->QuestionCount;

		// grpc 연결 시작
		GI->ConnectGRPC();
	}
	
	if(OX_wid != nullptr)
	{
		OX_wid->SetText();

		OX_wid->AddToViewport();
		
		UE_LOG(LogTemp, Warning, TEXT("ox wid success"));
	}
	
	// 시작 시 index 확인 및 동기화
	ReadIndex();
}

void AAnGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAnGameModeBase::SyncInt()
{
	UE_LOG(LogTemp, Warning, TEXT("b QC : %d"), QC);
	UE_LOG(LogTemp, Warning, TEXT("b QT num : %d"), OX_wid->QuestionText.Num());

	// 전체 문제 수 보다 적으면 +1
	if(QC < OX_wid->QuestionText.Num()-1)
	{
		QC += 1;
	}
	// 전체 문제 초과(로테이션 완료)시 초기화
	else
	{
		QC = 0;
	}

	// 게임 인스턴스에 변수 저장(레벨 리스타트 대비)
	GI->QuestionCount = QC;

	if(DH_GM_state == EDHGameModeState::GM_O)
	{
		// 문제 푼 횟 수 2회보다 적으면 +1
		if(QN < 2)
		{
			QN += 1;

			EndSyncQuiz();
		}
		// 2회 초과하면 초기화
		else
		{
			QN = 0;

			EndSyncFin();
		}
	}
	else
	{
		QN = 0;

		EndQuiz();
	}

	UE_LOG(LogTemp, Warning, TEXT("a QC : %d"), QC);
}


void AAnGameModeBase::AnswerCheck()
{
	// 인터렉션 결과가 정답이랑 같을때
	if(userAnswer == OX_wid->QuestionAnswer[QC])
	{
		SetDH_GM_State(EDHGameModeState::GM_O);

		checkCorrect = "correct";
	}
	// 인터렉션 결과가 정답이랑 다를때
	else
	{
		SetDH_GM_State(EDHGameModeState::GM_X);

		checkCorrect = "discorrect";
	}

	// 로그 저장 함수 실행
	SaveLog();
}

void AAnGameModeBase::DH_GM_CHANGE()
{
	switch (DH_GM_state)
	{
	case EDHGameModeState::GM_IDLE:
		Idle_Start();
		break;
	case EDHGameModeState::GM_HELLO:
		Hello_Start();
		// 사용자 시작 시간 저장 함수
		SaveEntryLogTime();
		break;
	case EDHGameModeState::GM_TUTO:
		Tuto_Start();
		break;
	case EDHGameModeState::GM_QUIZ:
		Quiz_Start();
		break;
	case EDHGameModeState::GM_O:
		Quiz_Answer_O();
		break;
	case EDHGameModeState::GM_X:
		Quiz_Answer_X();
		break;
	case EDHGameModeState::GM_RESULT:
		Quiz_Result();
		break;
	}
}

void AAnGameModeBase::SetDH_GM_State(EDHGameModeState next)
{
	DH_GM_state = next;

	DH_GM_CHANGE();
}

void AAnGameModeBase::Idle_Start()
{
	FTimerHandle idleTimer;
	GetWorld()->GetTimerManager().SetTimer(idleTimer, this, &AAnGameModeBase::IdleCircle, 30.0f, false);
}

void AAnGameModeBase::CallAppendText()
{
	OX_wid->AppendText();
}

void AAnGameModeBase::CallAppendTrue(const FString OX)
{
	OX_wid->AppendTrue(OX);
}

void AAnGameModeBase::CallImageOn()
{
	OX_wid->ImageOnStart();
}

void AAnGameModeBase::CallImageOff()
{
	OX_wid->ImageOffStart();
}

void AAnGameModeBase::CallWidgetOn()
{
	OX_wid->WidgetOnStart();
}

void AAnGameModeBase::CallWidgetOff()
{
	OX_wid->WidgetOffStart();
}

void AAnGameModeBase::CallStateOn(const FString state)
{
	OX_wid->StateCheckFun(state);
}

void AAnGameModeBase::CallQNSet()
{
	QN = 0;
}

void AAnGameModeBase::CallHello()
{
	GI->CallHelloService();
}

void AAnGameModeBase::CallO()
{
	GI->CallOService();
}

void AAnGameModeBase::CallX()
{
	GI->CallXService();
}

void AAnGameModeBase::CallOX()
{
	GI->CallOXService();
}

void AAnGameModeBase::CallShutdown()
{
	GI->CallShutdownService();
}

void AAnGameModeBase::CallMakeClient()
{
	GI->MakeClientGRPC();
}

bool AAnGameModeBase::AppendJsonToFile(const FString& FilePath, const FString& JsonString)
{
	FString ExistFileContent;
	if(FFileHelper::LoadFileToString(ExistFileContent, *FilePath))
	{
		// 다음 줄에 추가하기
		ExistFileContent.Append(TEXT("\n"));
		ExistFileContent.Append(JsonString);
	}
	else
	{
		ExistFileContent = JsonString;
	}

	return FFileHelper::SaveStringToFile(ExistFileContent, *FilePath);
}

void AAnGameModeBase::SaveLog()
{
	FDateTime time = FDateTime::Now();
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("index"), saveIndex);
	JsonObject->SetStringField(TEXT("entry_at"), entryTime.ToString());
	JsonObject->SetNumberField(TEXT("q_id"), GI->QuestionCount + 1);
	JsonObject->SetStringField(TEXT("question"), OX_wid->QuestionText[GI->QuestionCount]);
	JsonObject->SetStringField(TEXT("answer"), userAnswer);
	JsonObject->SetStringField(TEXT("correct"), checkCorrect);
	JsonObject->SetStringField(TEXT("answer_at"), time.ToString());

	// JSON 객체를 문자열로 변환
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	// 파일 경로 설정
	FString FilePath = FPaths::ProjectDir() + TEXT("log.txt");

	// 파일에 JSON 데이터 추가
	if(AppendJsonToFile(FilePath, OutputString) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("log json success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("log json fail"));
	}
}

bool AAnGameModeBase::ReadJsonFromFile(const FString& FilePath, TSharedPtr<FJsonObject>& OutJsonObject)
{
	FString JsonContent;
	if (!FFileHelper::LoadFileToString(JsonContent, *FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *FilePath);
		return false;
	}

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);
	if (FJsonSerializer::Deserialize(Reader, OutJsonObject) && OutJsonObject.IsValid())
	{
		return true;
	}
    
	UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON"));
	return false;
}

bool AAnGameModeBase::WriteJsonToFile(const FString& FilePath, const TSharedPtr<FJsonObject> JsonObject)
{
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		return FFileHelper::SaveStringToFile(OutputString, *FilePath);
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to serialize JSON"));
	return false;
}

void AAnGameModeBase::ReadIndex()
{
	// JSON 파일 경로
	FString FilePath = FPaths::ProjectDir() + TEXT("index.txt");

	// JSON 파일 읽기
	TSharedPtr<FJsonObject> JsonObject;
	if (ReadJsonFromFile(FilePath, JsonObject))
	{
		int32 index = JsonObject->GetNumberField("index");

		UE_LOG(LogTemp, Warning, TEXT("index : %d"), index);

		// 변수 동기화
		saveIndex = index;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read JSON file"));
	}
}

void AAnGameModeBase::WriteIndex()
{
	// JSON 파일 경로
	FString FilePath = FPaths::ProjectDir() + TEXT("index.txt");

	// JSON 파일 읽기
	TSharedPtr<FJsonObject> JsonObject;
	if (ReadJsonFromFile(FilePath, JsonObject))
	{
		saveIndex += 1;
		
		// 변수 수정
		JsonObject->SetNumberField("index", saveIndex);

		// 수정된 JSON 파일 쓰기
		if (WriteJsonToFile(FilePath, JsonObject))
		{
			UE_LOG(LogTemp, Warning, TEXT("JSON file updated successfully"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to update JSON file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read JSON file"));
	}
}

void AAnGameModeBase::SaveEntryLogTime()
{
	// 실시간 체크 함수
	entryTime = FDateTime::Now();
}

void AAnGameModeBase::BindOInput()
{
	if(DH_GM_state == EDHGameModeState::GM_TUTO)
	{
		Tuto_Check_O();
	}
	else
	{
		userAnswer = "O";

		AnswerCheck();				
	}
}

void AAnGameModeBase::BindXInput()
{
	if(DH_GM_state == EDHGameModeState::GM_TUTO)
	{
		Tuto_Check_X();
	}
	else
	{
		userAnswer = "X";

		AnswerCheck();		
	}
}
