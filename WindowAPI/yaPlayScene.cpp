#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaGround.h"
#include "yaObject.h"
#include "yaCollider.h"
#include "yaCollisionManager.h"

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
		//AddGameObject(new Player(), eColliderLayer::Player);
		Player* player = ya::object::Instantiate<Player>(eColliderLayer::Player);
		//Ground* ground = ya::object::Instantiate<Ground>(eColliderLayer::Ground);
		//ground->SetPos(Vector2(700.0f, 700.0f));
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
