#include "yaPlayer.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBackPack.h"
#include "yaRigidbody.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
		, mHp(100)
	{
		SetName(L"Player");
		SetPos({ 500.0f, 500.0f });
		SetScale({ 1.0f, 1.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\link.bmp");
		}

		//if (mHeadImage == nullptr)
		//{
		//	mHeadImage = Resources::Load<Image>(L"PlayerHead", L"..\\Resources\\Image\\link.bmp");
		//}

		//if (mBodyImage == nullptr)
		//{
		//	mBodyImage = Resources::Load<Image>(L"PlayerBody", L"..\\Resources\\Image\\link.bmp");
		//}

		mAnimator = new Animator();
		//mHeadAnimator = new Animator();
		//mBodyAnimator = new Animator();
		//mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Idle"
		//	, L"PlaneIdle");

		//mHeadAnimator->CreateAnimation(L"HeadIdle", mHeadImage
		//	, Vector2(0.0f, 0.0f), Vector2(40.0f, 38.0f)
		//	, Vector2(5.0f, -20.0f), 1, 0.1f);

		//mBodyAnimator->CreateAnimation(L"BodyIdle", mBodyImage
		//	, Vector2(0.0f, 38.0f), Vector2(32.0f, 36.0f)
		//	, Vector2(5.0f, -20.0f), 1, 0.1f);

		//mAnimator->CreateAnimation(L"MoveDown", mHeadImage
		//	, Vector2(0.0f, 0.0f), Vector2(0.0f, 34.0f)
		//	, Vector2(5.0f, -20.0f), 1, 0.1f);

		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 3, 0.1f);
		mAnimator->CreateAnimation(L"MoveDown", mImage
			, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 10, 0.1f);
		mAnimator->CreateAnimation(L"MoveLeft", mImage
			, Vector2(0.0f, 650.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 10, 0.1f);
		mAnimator->CreateAnimation(L"MoveUp", mImage
			, Vector2(0.0f, 780.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 10, 0.1f);
		mAnimator->CreateAnimation(L"MoveRight", mImage
			, Vector2(0.0f, 910.0f), Vector2(120.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 10, 0.1f);

		//mHeadAnimator->CreateAnimation(L"HeadIdle", mHeadImage
		//	, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 3, 0.1f);
		//mHeadAnimator->CreateAnimation(L"HeadMoveDown", mHeadImage
		//	, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mHeadAnimator->CreateAnimation(L"HeadMoveLeft", mHeadImage
		//	, Vector2(0.0f, 650.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mHeadAnimator->CreateAnimation(L"HeadMoveUp", mHeadImage
		//	, Vector2(0.0f, 780.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mHeadAnimator->CreateAnimation(L"HeadMoveRight", mHeadImage
		//	, Vector2(0.0f, 910.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);

		//mBodyAnimator->CreateAnimation(L"BodyIdle", mImage
		//	, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 3, 0.1f);
		//mBodyAnimator->CreateAnimation(L"BodyMoveDown", mImage
		//	, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mBodyAnimator->CreateAnimation(L"BodyMoveLeft", mImage
		//	, Vector2(0.0f, 650.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mBodyAnimator->CreateAnimation(L"BodyMoveUp", mImage
		//	, Vector2(0.0f, 780.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);
		//mBodyAnimator->CreateAnimation(L"BodyMoveRight", mImage
		//	, Vector2(0.0f, 910.0f), Vector2(120.0f, 130.0f)
		//	, Vector2(5.0f, -20.0f), 10, 0.1f);

		mAnimator->Play(L"Idle", true);
		//mHeadAnimator->Play(L"HeadIdle", true);
		//mBodyAnimator->Play(L"BodyIdle", true);

		////mAnimator->FindEvents(L"MoveRight")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"MoveRight") = std::bind(&Player::WalkComplete, this);
		//mHeadAnimator->GetCompleteEvent(L"HeadMoveRight") = std::bind(&Player::WalkComplete, this);
		//mBodyAnimator->GetCompleteEvent(L"BodyMoveRight") = std::bind(&Player::WalkComplete, this);
		
		AddComponent(mAnimator);
		//AddComponent(mHeadAnimator);
		//AddComponent(mBodyAnimator);

		Collider* coliider = new Collider();
		AddComponent(coliider);

		coliider->SetOffset(Vector2(0.0f, 50.0f));
		coliider->SetScale(Vector2(10.0f, 10.0f));

		Collider* coliider2 = new Collider();
		AddComponent(coliider2);

		coliider2->SetOffset(Vector2(60.0f, 0.0f));
		coliider2->SetScale(Vector2(10.0f, 10.0f));

		AddComponent<Rigidbody>();

		mCoff = 0.1f;
		mMisiileDir = Vector2::One;
	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		GameObject::Tick();

		if (KEY_PREESE(eKeyCode::W))
		{
			//pos.y -= 120.0f * Time::DeltaTime();
			//missile->mDir.y = -1.0f;

			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_PREESE(eKeyCode::S))
		{
			//pos.y += 120.0f * Time::DeltaTime();
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (KEY_PREESE(eKeyCode::A))
		{
			//pos.x -= 120.0f * Time::DeltaTime();
			//missile->mDir.x = 1.0f;
			GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (KEY_PREESE(eKeyCode::D))
		{
			//pos.x += 120.0f * Time::DeltaTime();
			GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = -500.0f;
			rigidbody->SetVelocity(velocity);

			rigidbody->SetGround(false);

			UIManager::Pop(eUIType::OPTION);
		}

		if (KEY_DOWN(eKeyCode::UP))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
			missile->mDir += Vector2(0.0f, -1.0f);
		}

		if (KEY_DOWN(eKeyCode::DOWN))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
			missile->mDir += Vector2(0.0f, 1.0f);
		}

		if (KEY_DOWN(eKeyCode::LEFT))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
			missile->mDir += Vector2(-1.0f, 0.0f);
		}

		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
			missile->mDir += Vector2(1.0f, 0.0f);
		}

		if (KEY_DOWN(eKeyCode::W))
		{
			mAnimator->Play(L"MoveUp", true);
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			mAnimator->Play(L"MoveDown", true);
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator->Play(L"MoveLeft", true);
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"MoveRight", true);
		}

		if (KEY_UP(eKeyCode::W))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::S))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::A))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::D))
		{
			mAnimator->Play(L"Idle", true);
		}

		//if (KEY_UP(eKeyCode::W))
		//{
		//	mAnimator->Play(L"HeadIdle", true);
		//	mAnimator->Play(L"BodyIdle", true);
		//}
		//if (KEY_UP(eKeyCode::S))
		//{
		//	mAnimator->Play(L"HeadIdle", true);
		//	mAnimator->Play(L"BodyIdle", true);
		//}
		//if (KEY_UP(eKeyCode::A))
		//{
		//	mAnimator->Play(L"HeadIdle", true);
		//	mAnimator->Play(L"BodyIdle", true);
		//}
		//if (KEY_UP(eKeyCode::D))
		//{
		//	mAnimator->Play(L"HeadIdle", true);
		//	mAnimator->Play(L"BodyIdle", true);
		//}
	}

	void Player::Render(HDC hdc)
	{
		//Vector2 pos = GetPos();
		//Vector2 scale = GetScale();

		//Vector2 finalPos;
		//

		//pos = GetPos();
		//scale = GetScale();

		//finalPos.x = (pos.x - mHeadImage->GetWidth() * (scale.x / 2.0f));
		//finalPos.y = (pos.y - mHeadImage->GetHeight() * (scale.y / 2.0f));
		//Vector2 rect;
		//rect.x = 40;
		//rect.y = 34;

		//finalPos = Camera::CalculatePos(finalPos);

		//TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
		//	, mHeadImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		//pos = Vector2(100.0f, 100.0f);
		//finalPos.x = (pos.x - mBodyImage->GetWidth() * (scale.x / 2.0f));
		//finalPos.y = (pos.y - mBodyImage->GetHeight() * (scale.y / 2.0f));

		//rect.x = 40;
		//rect.y = 34;

		//finalPos = Camera::CalculatePos(finalPos);

		//TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
		//	, mBodyImage->GetDC(), 0, 0, rect.x, rect.y
		//	, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{

	}

	void Player::OnCollisionStay(Collider* other)
	{

	}

	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::WalkComplete()
	{
		Missile* missile = new Missile();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale() / 2.0f;
		Vector2 missileScale = missile->GetScale();

		missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
	}
}
