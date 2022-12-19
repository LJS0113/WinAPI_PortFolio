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
#include "yaMap.h"

namespace ya
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"MapBG", L"Map.bmp");
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGround);

		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);

		//Map* map = ya::object::Instantiate<Map>(eColliderLayer::Map);

		Monster* monster = ya::object::Instantiate<Monster>(eColliderLayer::Monster);
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
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{

	}

	void PlayScene::Exit()
	{

	}
}
