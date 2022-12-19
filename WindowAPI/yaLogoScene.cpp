#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
#include "yaApplication.h"
#include "yaToolScene.h"
#include "yaGround.h"
#include "yaUIManager.h"
#include "yaHUD.h"
#include "yaButton.h"

namespace ya
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"LogoBG", L"Start.bmp");
		bg->Initialize();

		AddGameObject(bg, eColliderLayer::BackGround);



		////UIManager::Push(eUIType::HP);
		////UIManager::Push(eUIType::MP);
		//UIManager::Push(eUIType::INVENTORY);

		////HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::HP);
		//HUD* hud = UIManager::GetUiInstant<HUD>(eUIType::MP);
		//hud->SetTarget(player);

		//
		//mons[0] = ya::object::Instantiate<Monster>(eColliderLayer::Monster);
		//mons[1] = ya::object::Instantiate<Monster>(Vector2{ 1600 / 2 + 130, 300 / 2 },eColliderLayer::Monster);

		////ya::Scene* scene = ya::SceneManager::GetScene(eSceneType::Tool);
		////ya::ToolScene* toolScene = dynamic_cast<ya::ToolScene*>(scene);
		////toolScene->LoadTilePalette(L"..\\Resources\\TileSaveFiles\\Test");

	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
		//ya::object::Destroy(mons[0], 3.0f);
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Logo Scene.bmp");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void LogoScene::Enter()
	{

	}

	void LogoScene::Exit()
	{
	}
}