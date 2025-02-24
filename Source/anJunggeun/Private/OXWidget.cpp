// Fill out your copyright notice in the Description page of Project Settings.


#include "OXWidget.h"
#include "AnGameModeBase.h"
#include "Components/MultiLineEditableTextBox.h"

void UOXWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UOXWidget::AppendText()
{
	FString text = QuestionText[KimguGM->QC];
	int32 Qnum = KimguGM->QN;
	
	MEditableTextBox_QT->SetText(FText::FromString(text));

	SetQuestImage(Qnum);
}

void UOXWidget::AppendTrue(const FString OX)
{
	FString text = QuestionTrue[KimguGM->QC];
	
	MEditableTextBox_QT->SetText(FText::FromString(text));

	if(OX == "O")
	{
		SetTrueImage("O");
	}
	else
	{
		SetTrueImage("X");
	}
}

void UOXWidget::SetText()
{
	KimguGM = Cast<AAnGameModeBase>(GetWorld()->GetAuthGameMode());
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 대한민국의 독립운동을 위해 중국뿐만 아니라 여러 나라와 협력했다."))); // 1번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 1번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 대한민국의 독립운동을 위해 중국뿐만 아니라 여러 나라와 협력했다."))); // 1번 사실

	QuestionText.Emplace(FString::Printf(TEXT("이봉창의 의거는 1934년에 일어났다."))); // 2번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 2번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("이봉창의 의거는 1932년에 일어났다."))); // 2번 사실

	QuestionText.Emplace(FString::Printf(TEXT("윤봉길 의사는 훙커우 공원에서 대포를 사용하여 일본군 장성과 고위 관료들을 공격했다."))); // 3번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 3번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("윤봉길 의사는 훙커우 공원에서 폭탄을 던져 일본군 장성과 고위 관료들을 공격했다."))); // 3번 사실 

	QuestionText.Emplace(FString::Printf(TEXT("한국광복군은 대한민국 임시정부의 군사 조직으로 활동했다."))); // 4번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 4번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("한국광복군은 대한민국 임시정부의 군사 조직으로 활동했다."))); // 4번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("이봉창은 일왕을 암살하는 데 성공하였다."))); // 5번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 5번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("이봉창은 일왕을 암살하는 데 실패하였다."))); // 5번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("대한민국 임시정부는 1919년에 설립되었다."))); // 6번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 6번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("대한민국 임시정부는 1919년에 설립되었다."))); // 6번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구와 이봉창은 모두 평화적인 방법만을 사용하여 독립운동을 전개했다."))); // 7번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 7번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구와 이봉창은 무력과 평화적인 방법 모두를 사용하여 독립운동을 전개했다."))); // 7번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("윤봉길 의사는 김구와 함께 대한민국 임시정부에서 활동했다."))); // 8번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 8번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("윤봉길 의사는 김구와 함께 대한민국 임시정부에서 활동했다"))); // 8번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("일제강점기에는 일본의 교육 정책에 따라 한국어 교육이 금지되었다."))); // 9번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 9번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("일제강점기에는 일본의 교육 정책에 따라 한국어 교육이 금지되었다."))); // 9번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("대한민국 임시정부는 상하이에 설립되었다."))); // 10번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 10번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("대한민국 임시정부는 상하이에 설립되었다."))); // 10번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 독립운동을 위해 한국에서만 활동했다."))); // 11번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 11번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 독립운동을 위해 한국 외 다른 나라에서도 활동했다."))); // 11번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부의 주석을 역임하였다."))); // 12번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 12번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부의 주석을 역임하였다."))); // 12번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구의 호는 흑범이다"))); // 13번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 13번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구의 호는 백범이다."))); // 13번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("1920년대에는 만주 지역에서 독립운동이 활발하게 일어났다."))); // 14번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 14번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("1920년대에는 만주 지역에서 독립운동이 활발하게 일어났다."))); // 14번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 젊은 시절 동학에 가담하였다."))); // 15번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 15번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 젊은 시절 동학에 가담하였다."))); // 15번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 한인애국단을 조직하여 독립운동을 지원했다."))); // 16번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 16번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 한인애국단을 조직하여 독립운동을 지원했다."))); // 16번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("청산리 대첩은 독립군이 일본군을 상대로 패배한 전투이다."))); // 17번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 17번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("청산리 대첩은 독립군이 일본군을 상대로 승리한 전투이다."))); // 17번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("김구는 한국광복군을 통해 무장투쟁을 강조하였다."))); // 18번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 18번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 한국광복군을 통해 무장투쟁을 강조하였다."))); // 18번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("일제강점기 동안 일본은 한국어 사용을 장려하였다."))); // 19번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 19번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("일제강점기 동안 한국어 사용은 금지되었다."))); // 19번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("독립운동가들은 대외적으로 신분을 숨기기 위해 가명을 사용하였다."))); // 20번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 20번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("독립운동가들은 대외적으로 신분을 숨기기 위해 가명을 사용하였다."))); // 20번 사실 
	
	QuestionText.Emplace(FString::Printf(TEXT("이봉창 의사는 일본에서 일왕 투탄 의거를 시도하였다."))); // 21번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 21번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("이봉창은 일본에서 일왕을 암살하려 시도하였다."))); // 21번 사실

	QuestionText.Emplace(FString::Printf(TEXT("이봉창 의사의 수류탄은 목표에 명중했다."))); // 22번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 22번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("이봉창 의사는 일왕투탄의거시 그의 수류탄은 목표에 명중하지 못했다."))); // 22번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 여러 차례 체포되어 감옥에 갇혔고, 탈출에 성공한 적은 없다."))); // 23번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 23번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 여러 차례 체포되어 감옥에 갇혔으나 탈출에 성공하였다."))); // 23번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구와 안창호는 대한민국 임시정부에서 함께 활동하였다."))); // 24번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 24번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구와 안창호는 대한민국 임시정부에서 함께 활동하였다."))); // 24번 사실

	QuestionText.Emplace(FString::Printf(TEXT("독립운동가들은 일본 경찰을 피하고자 외국 대사관에 숨어있기도 하였다."))); // 25번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 25번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("독립운동가들은 일본 경찰을 피하기 위해 외국 대사관에 숨어있기도 하였다."))); // 25번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 서울에서 한인애국단을 조직했다."))); // 26번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 26번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 상하이에서 한인애국단을 조직했다."))); // 26번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 훙커우 공원 의거를 계획하고 지원했다."))); // 27번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 27번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 훙커우 공원 의거를 계획하고 지원했다."))); // 27번 사실

	QuestionText.Emplace(FString::Printf(TEXT("독립운동가들은 자금을 모으기 위해 해외 동포들과 협력하였다."))); // 28번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 28번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("독립운동가들은 자금을 모으기 위해 해외 동포들과 협력하였다."))); // 28번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구의 본명은 김창수였다."))); // 29번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 29번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구의 본명은 김창수였다."))); // 29번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 독립운동 자금을 마련하기 위해 미국을 주로 방문하였다."))); // 30번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 30번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 독립운동 자금을 마련하기 위해 자주 중국을 방문하였다."))); // 30번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구와 이봉창 의사는 모두 한인애국단에 속해 있었다."))); // 31번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 31번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구와 이봉창 의사는 모두 한인애국단에 속해 있었다."))); // 31번 사실

	QuestionText.Emplace(FString::Printf(TEXT("3.1 운동은 1919년 3월 1일에 시작되었다."))); // 32번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 32번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("3.1 운동은 1919년 3월 1일에 시작되었다."))); // 32번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 훙커우 공원 의거 이후 임시정부를 해체하였다."))); // 33번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 33번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 훙커우 공원 의거 이후 임시정부를 재건하였다."))); // 33번 사실

	QuestionText.Emplace(FString::Printf(TEXT("독립운동가들은 비밀리에 연락을 주고받기 위해 암호를 사용했다."))); // 34번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 34번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("독립운동가들은 비밀리에 연락을 주고받기 위해 암호를 사용했다."))); // 34번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부의 활동을 일본에서 이끌었다."))); // 35번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 35번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부의 활동을 중국에서 이끌었다."))); // 35번 사실

	QuestionText.Emplace(FString::Printf(TEXT("안창호는 백범이라는 호를 사용하였다."))); // 36번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 36번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("안창호는 도산이라는 호를 사용하였다."))); // 36번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 평안도 평양에서 태어났다."))); // 37번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 37번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 1876년 황해도 해주에서 태어났다."))); // 37번 사실

	QuestionText.Emplace(FString::Printf(TEXT("봉오동 전투는 1920년에 발생하였다."))); // 38번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 38번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("봉오동 전투는 1920년에 발생하였다."))); // 38번 사실

	QuestionText.Emplace(FString::Printf(TEXT("일제강점기에는 모든 한국인이 일본으로 이주했다."))); // 39번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 39번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("일제강점기에는 일부 한국인이 일본으로 이주했다."))); // 39번 사실

	QuestionText.Emplace(FString::Printf(TEXT("한국광복군은 1940년에 충칭에서 창설되었다."))); // 40번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 40번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("한국광복군은 1940년에 충칭에서 창설되었다."))); // 40번 사실

	QuestionText.Emplace(FString::Printf(TEXT("일제강점기는 1910년부터 1965년까지 지속되었다."))); // 41번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 41번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("일제강점기는 1910년부터 1945년까지 지속되었다."))); // 41번 사실

	QuestionText.Emplace(FString::Printf(TEXT("봉오동 전투에서 대한독립군이 일본군을 상대로 승리하였다."))); // 42번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 42번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("봉오동 전투에서 대한독립군이 일본군을 상대로 승리하였다."))); // 42번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 의거 후 일본의 지원을 받았다."))); // 43번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 43번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사의 의거 후 중국 국민당의 지원을 받았다."))); // 43번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부를 중국의 여러 도시로 옮겨 다니며 유지하였다."))); // 44번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 44번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 대한민국 임시정부를 중국의 여러 도시로 옮겨 다니며 유지하였다."))); // 44번 사실

	QuestionText.Emplace(FString::Printf(TEXT("3.1 운동은 1910년에 일어났다."))); // 45번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 45번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("3.1 운동은 1919년에 일어났다."))); // 45번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사를 한인애국단에 가입시켜 독립운동을 함께 하였다."))); // 46번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 46번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 윤봉길 의사를 한인애국단에 가입시켜 독립운동을 함께 하였다."))); // 46번 사실

	QuestionText.Emplace(FString::Printf(TEXT("청산리 대첩은 1920년 김좌진 장군이 이끄는 북로군정서군의 패배였다."))); // 47번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 47번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("청산리 대첩은 1920년 김좌진 장군이 이끄는 북로군정서군의 승리였다."))); // 47번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 동학군의 선봉장으로 활동한 적 있다."))); // 48번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 48번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 19세에 팔봉접주가 되어 동학군의 선봉장으로 해주성을 공략했다."))); // 48번 사실

	QuestionText.Emplace(FString::Printf(TEXT("광복은 1942년 8월 15일에 이뤄졌다."))); // 49번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 49번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("광복은 1945년 8월 15일에 이루어졌다."))); // 49번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 어려운 형편에서도 독학으로 과거 시험에 합격했다."))); // 50번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 50번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 과거 시험을 독학하였으나 합격하진 못하였다."))); // 50번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 안중근의 아버지인 안태훈의 집에서 도움을 받아 피신한 적이 있다."))); // 51번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 51번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 안중근의 아버지인 안태훈의 집에서 도움을 받아 피신했다."))); // 51번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 안창호의 여동생 안신호와 결혼했다."))); // 52번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 52번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 안창호의 여동생 안신호와 결혼하지 않았다."))); // 52번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구는 1945년 8월 18일 서울 진공 작전을 미군과 합동으로 수행하였다."))); // 53번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 53번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구는 1945년 8월 18일 서울 진공 작전을 미군과 합동으로 수행하려했으나 이른 광복으로 인해 무산되었다."))); // 53번 사실

	QuestionText.Emplace(FString::Printf(TEXT("대한민국 임시정부에서 국호를 '대한민국'으로 정하였다."))); // 54번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 54번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("대한민국 임시정부에서 국호를 '대한민국'으로 정하였다."))); // 54번 사실

	QuestionText.Emplace(FString::Printf(TEXT("태극기는 대한민국의 국기이다."))); // 55번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 55번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("태극기는 대한민국의 국기이다."))); // 55번 사실

	QuestionText.Emplace(FString::Printf(TEXT("임시정부는 일본 식민 지배 아래에서 법적으로 인정받은 정부였다."))); // 56번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 56번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("임시정부는 일본 식민 지배 아래에서 법적으로 인정받은 정부가 아니었다."))); // 56번 사실

	QuestionText.Emplace(FString::Printf(TEXT("안악사건은 일제가 신민회 회원을 탄압하기 위해 일으킨 사건이다."))); // 57번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 57번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("안악사건이란 일제가 신민회 회원들을 탄압하기 위해, 사건을 조작해 많은 독립운동가들을 투옥한 사건이다."))); // 57번 사실
	
	QuestionText.Emplace(FString::Printf(TEXT("일본이 백범 김구에게 건 현상금은 60만 원이었다."))); // 58번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 58번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("일본이 백범 김구에게 건 현상금은 60만 원으로 현재 약 200억 원 상당의 많은 금액이었다."))); // 58번 사실

	QuestionText.Emplace(FString::Printf(TEXT("독립운동가들은 국외에서도 활동하여 일본의 식민 지배에 대항했다."))); // 59번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 59번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("독립운동가들은 국외에서도 활동하여 일본의 식민 지배에 대항했다."))); // 59번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구의 자서전 제목은 '김구일지'이다."))); // 60번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("X"))); // 60번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("김구의 자서전 제목은 '백범일지'이다."))); // 60번 사실

	QuestionText.Emplace(FString::Printf(TEXT("안악사건은 105인 사건이라고도 불린다."))); // 61번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 61번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("안악사건은 105인 사건이라고도 불린다."))); // 61번 사실

	QuestionText.Emplace(FString::Printf(TEXT("김구의 호인 백범의 뜻은 일반 백성인 백정과 범부를 뜻한다."))); // 62번 질문
	QuestionAnswer.Emplace(FString::Printf(TEXT("O"))); // 62번 답변
	QuestionTrue.Emplace(FString::Printf(TEXT("백정 범부들이라도 애국심을 가지면 나라가 독립할 수 있을것이라는 뜻으로 호를 지었다."))); // 62번 사실
}

void UOXWidget::StateCheckFun(const FString state)
{
	StateCheckStart(state);
}
