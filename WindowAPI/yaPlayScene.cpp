#pragma once
#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaCollider.h"
#include "yaCollisionManager.h"
#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaMonster.h"

namespace ya
{
	PlayScene::PlayScene()
	{
		//BgImageObject* bg = new BgImageObject();
		//bg->SetImage(L"Map", L"Map.bmp");
		//bg->Initialize();

		//AddGameObject(bg, eColliderLayer::BackGround);

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Map", L"..\\Resources\\Image\\Map.bmp");
		}

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		Monster* mons[2];
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		mons[0] = ya::object::Instantiate<Monster>(eColliderLayer::Monster);
		//mons[1] = ya::object::Instantiate<Monster>(Vector2{ 1600 / 2 + 130, 300 / 2 }, eColliderLayer::Monster);
	}

	void PlayScene::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		
		//Vector2 rect;
		//rect.x = mImage->GetWidth();  //*scale.x;
		//rect.y = mImage->GetHeight(); //*scale.y;

		//TransparentBlt(hdc, 0, 0, rect.x, rect.y
		//	, mImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		//TransparentBlt(hdc, 1280, 0, rect.x, rect.y
		//	, mImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		//TransparentBlt(hdc, 0, 720, rect.x, rect.y
		//	, mImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		//TransparentBlt(hdc, 1280, 720, rect.x, rect.y
		//	, mImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);

		//wchar_t szFloat[50] = {};
		//swprintf_s(szFloat, 50, L"CameraPos");
		//int strLen = wcsnlen_s(szFloat, 50);
		//TextOut(hdc, 10, 70, szFloat, strLen);
	}

	void PlayScene::Enter()
	{

	}

	void PlayScene::Exit()
	{

	}
}
