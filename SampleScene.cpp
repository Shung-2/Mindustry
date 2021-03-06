#include "stdafx.h"
#include "SampleScene.h"
#include "TriggerTest.h"
#include "UIMouseEvent.h"
#include "CallbackTest.h"
#include "EditText.h"
HRESULT SampleScene::Init()
{
    Scene::Init();
	CLIPMANAGER->AddClip("bomb", "bomb.png", 240, 80, 3, 1, 0.3f);
	CLIPMANAGER->AddClip("trapobject", "trapObject.png", 64, 128);
	CLIPMANAGER->AddClip("background", "scene1_background.png", 1024, 560);
	CLIPMANAGER->AddClip("spark_particle", "sprites/effects/spark-particle.png", 4, 20);
	CLIPMANAGER->AddClip("spark_circle", "sprites/effects/spark-circle.png", 180, 36, 5, 1, 0.08f);
	_stayTime = 0;
	SetBackBufferSize(1024, 560);
	_time = 0;
	//애너미 매니저
	//vectr<enemy*> 이거는 웨이브에 생성될 애너미 목록
	//DeadEvent(enemy* deadEnemy)
	//for으로 찾아가지고
	//vector[i] == deadEnemy
	//vector[i]->SetActive(false);
	//for(vector)
	//if(vector[i]->isActive == true)
	//return
	//Clear();

	//파티클 시스템 예시
	testParticleSystem = new GameObject();
	testParticleSystem->AddComponent(new ParticleSystem());
	testParticleSystem->GetComponent<ParticleSystem>()->Init("spark_particle", 12);
	testParticleSystem->GetComponent<ParticleSystem>()->SetDuration(0.3f);
	//testParticleSystem->GetComponent<ParticleSystem>()->SetPivotDistance(10.f);
	testParticleSystem->GetComponent<ParticleSystem>()->SetEmissionTerm(0.5f);
	testParticleSystem->GetComponent<ParticleSystem>()->SetScaleY(0.1f, 1.f);
	testParticleSystem->GetComponent<ParticleSystem>()->SetSpeed(1.f, 2.f);

	//테스트 editableText 초기화
	testEditText = new Button();
	testEditText->Init();
	testEditText->uiRenderer->Init(100, 32);
	testEditText->AddComponent(new EditText());
	testEditText->GetComponent<EditText>()->Init();

	//클립없이 UIRenderer초기화 하는법
	testNoClipUI.Init();
	testNoClipUI.uiRenderer->Init(100.f, 100.f);
	testNoClipUI.SetActive(false);

	//클립없이 Renderer 초기화 하는법
	testNoClipObj.Init();
	testNoClipObj.renderer->Init(100.f, 100.f);

	//게임오브젝트 구성하는예시
	testAnimObj.Init();
	testAnimObj.renderer->Init("bomb");
	testAnimObj.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj.animator->SetClip("bomb");
	testAnimObj.transform->SetScale(2.f, 2.f);
	testAnimObj.transform->SetAngle(45.f);
	testAnimObj.AddComponent(new BoxCollider());
	testAnimObj.GetComponent<BoxCollider>()->Init();
	testAnimObj.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);
	testAnimObj.AddComponent(new TriggerTest());
	testAnimObj.GetComponent<TriggerTest>()->Init();
	testAnimObj.GetComponent<TriggerTest>()->testObject = &testUIObj;
	testAnimObj.AddComponent(new CallbackTest());
	testAnimObj.GetComponent<CallbackTest>()->testObject = &testUIObj;

	testAnimObj2.Init();
	testAnimObj2.transform->SetPosition(100, 100);
	testAnimObj2.renderer->Init("bomb");
	testAnimObj2.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj2.animator->SetClip("bomb");
	testAnimObj2.transform->SetScale(1.f, 1.f);
	testAnimObj2.transform->SetAngle(270.f);
	testAnimObj2.AddComponent(new BoxCollider());
	testAnimObj2.GetComponent<BoxCollider>()->Init();
	testAnimObj2.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);

	testUIObj.Init();
	testUIObj.uiRenderer->Init("trapobject");
	testUIObj.transform->SetPosition(100, 100);

	SetBackBufferSize(1125, 875);

	background.Init();
	background.renderer->Init("background");
	background.transform->SetPosition(MAPWIDTH / 2, MAPHEIGHT / 2);

	testAnimObj.Init();
	testAnimObj.renderer->Init("bomb");
	testAnimObj.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj.animator->SetClip("bomb");
	testAnimObj.transform->SetScale(2.f, 2.f);
	testAnimObj.transform->SetAngle(45.f);
	testAnimObj.AddComponent(new BoxCollider());
	testAnimObj.GetComponent<BoxCollider>()->Init();
	testAnimObj.GetComponent<BoxCollider>()->SetSize(30.f, 30.f);

	testAnimObj2.Init();
	testAnimObj2.transform->SetPosition(100, 100);
	testAnimObj2.renderer->Init("bomb");
	testAnimObj2.animator->AddClip(CLIPMANAGER->FindClip("bomb"));
	testAnimObj2.animator->SetClip("bomb");
	testAnimObj2.transform->SetScale(1.f, 1.f);
	testAnimObj2.transform->SetAngle(270.f);

	testUIObj.Init();
	testUIObj.uiRenderer->Init("trapobject");
	testUIObj.transform->SetPosition(100, 100);

	_sceneChangeTime = 0;

	testButton.Init();
	testButton.uiRenderer->Init("trapobject");
	testButton.transform->SetPosition(WINSIZEX - 150, 150);
	testButton.transform->SetAngle(45.f);
	testButton.GetComponent<UIMouseEvent>()->Init();

	float angle = GetAngle(testUIObj.transform->position, testButton.transform->position);
	float angle2 = GetAngle(testButton.transform->position, testUIObj.transform->position);

	testUIObj.transform->SetAngle(ConvertAngleD2D(angle));
	testButton.transform->SetAngle(ConvertAngleD2D(angle2));

	/**********************************************************
	* UIMouseEvent 콜백함수 등록방법
	* 첫번째 매개변수 : std::bind(&클래스명::함수명, 오브젝트변수명.GetComponent<컴포넌트명>())
	* 두번째 매개변수 : EVENT::이벤트종류
	***********************************************************/
	testButton.GetComponent<UIMouseEvent>()->
		RegistCallback(std::bind(&CallbackTest::TestCallback, testAnimObj.GetComponent<CallbackTest>()), EVENT::ENTER);
	testButton.GetComponent<UIMouseEvent>()->
		RegistCallback(std::bind(&CallbackTest::TestCallback, testAnimObj.GetComponent<CallbackTest>()), EVENT::EXIT);
	testButton.GetComponent<UIMouseEvent>()->
		RegistCallback(std::bind(&CallbackTest::TestCallback, testAnimObj.GetComponent<CallbackTest>()), EVENT::CLICK);
	
	_sceneChangeTime = 0;

    return S_OK;
}

void SampleScene::Update()
{
	MainCam->Update();
	EFFECTMANAGER->Update();
	_time += TIMEMANAGER->getElapsedTime();
	if (_time >= 0.5f)
	{
	}
	background.Update();
	testAnimObj.Update();
	testAnimObj2.Update();
	testUIObj.Update();
	testParticleSystem->Update();
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//MainCam->transform->MoveX(5.f);
		testAnimObj.transform->MoveX(5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//MainCam->transform->MoveX(-5.f);
		testAnimObj.transform->MoveX(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//MainCam->transform->MoveY(-5.f);
		testAnimObj.transform->MoveY(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//MainCam->transform->MoveY(5.f);
		testAnimObj.transform->MoveY(5.f);
	}
	_sceneChangeTime += TIMEMANAGER->getElapsedTime();
	if (_sceneChangeTime >= 5.f)
	{
		//SCENEMANAGER->LoadScene("sample2");
	}
	testInt++;
	testEditText->Update();
	testAnimObj.Update();
	testAnimObj2.Update();
	testUIObj.Update();
	testButton.Update();
	testNoClipUI.Update();
	testNoClipObj.Update();
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//MainCam->transform->MoveX(5.f);
		testAnimObj.transform->MoveX(5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//MainCam->transform->MoveX(-5.f);
		testAnimObj.transform->MoveX(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//MainCam->transform->MoveY(-5.f);
		testAnimObj.transform->MoveY(-5.f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//MainCam->transform->MoveY(5.f);
		testAnimObj.transform->MoveY(5.f);
	}
	_sceneChangeTime += TIMEMANAGER->getElapsedTime();
	if (_sceneChangeTime >= 5.f)
	{
		//SCENEMANAGER->LoadScene("sample2");
	}
}

void SampleScene::Render()
{
    {
		Rect rect;
		rect = RectMakePivot(Vector2(WINSIZEX + 500, WINSIZEY / 2),
			Vector2(50, 50), Pivot::Center);

		D2DRenderer::GetInstance()->DrawRectangle
		(
			rect,
			D2DRenderer::DefaultBrush::Red,
			1.f
		);
		testAnimObj.Render();
		testAnimObj2.Render();
		testNoClipObj.Render();
		background.Render();
		testParticleSystem->Render();
		EFFECTMANAGER->Render();
		MainCam->Render();
		testEditText->Render();
		//D2DRENDERER->RenderText(250, 400, L"다람쥐 헌 쳇바퀴에 타고파", 50);
		//D2DRENDERER->RenderText(700, 400, L"테스트 텍스트", 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_CENTER,
		//	L"BMHANNAPro");
		//D2DRENDERER->RenderTextField(400, 400, L"다람쥐 헌 쳇바퀴에 타고파", D2D1::ColorF::Black, 50, 500, 200, 
		//	1.f,
		//	DWRITE_TEXT_ALIGNMENT_LEADING, L"배달의민족 한나체 Pro");
		testUIObj.Render();
		testButton.Render();
		testNoClipUI.Render();
    }
}

void SampleScene::Release()
{
}
