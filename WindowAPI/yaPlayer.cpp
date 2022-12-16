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
		, mState(State::IDLE)
	{
		SetName(L"Player");
		SetPos({ 500.0f, 500.0f });
		SetScale({ 2.5f, 2.5f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\isaacPlayer.bmp");
		}

		mHead = new GameObject();
		mBody = new GameObject();

		//Idle 상태
		mHeadAnimator = new Animator();
		mHeadAnimator->CreateAnimation(L"HeadIdle", mImage
			, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f)
			, Vector2(-40.0f, -90.0f), 1, 0.2f);
		mHead->AddComponent(mHeadAnimator);

		mBodyAnimator = new Animator();
		mBodyAnimator->CreateAnimation(L"BodyIdle", mImage
			, Vector2(0.0f, 38.0f), Vector2(32.0f, 26.0f)
			, Vector2(-32.0f, -55.0f), 1, 0.1f);
		mBody->AddComponent(mBodyAnimator);

		mHeadAnimator->Play(L"HeadIdle", true);
		mBodyAnimator->Play(L"BodyIdle", true);

		// 아래방향 애니메이션
		mHeadAnimator->CreateAnimation(L"HeadDown", mImage
			, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f)
			, Vector2(-40.0f, -90.0f), 1, 0.2f);
		mBodyAnimator->CreateAnimation(L"BodyDown", mImage
			, Vector2(0.0f, 38.0f), Vector2(32.0f, 26.0f)
			, Vector2(-32.0f, -55.0f), 10, 0.1f);

		// 오른쪽방향 애니메이션
		mHeadAnimator->CreateAnimation(L"HeadRight", mImage
			, Vector2(80.0f, 0.0f), Vector2(40.0f, 40.0f)
			, Vector2(-40.0f, -90.0f), 1, 0.2f);
		mBodyAnimator->CreateAnimation(L"BodyRight", mImage
			, Vector2(0.0f, 78.0f), Vector2(32.0f, 26.0f)
			, Vector2(-32.0f, -47.0f), 10, 0.1f);

		// 윗방향 애니메이션
		mHeadAnimator->CreateAnimation(L"HeadUp", mImage
			, Vector2(160.0f, 0.0f), Vector2(40.0f, 40.0f)
			, Vector2(-40.0f, -90.0f), 1, 0.2f);
		mBodyAnimator->CreateAnimation(L"BodyUp", mImage
			, Vector2(0.0f, 38.0f), Vector2(32.0f, 26.0f)
			, Vector2(-29.0f, -55.0f), 10, 0.1f);

		// 왼쪽방향 애니메이션
		mHeadAnimator->CreateAnimation(L"HeadLeft", mImage
			, Vector2(240.0f, 0.0f), Vector2(40.0f, 40.0f)
			, Vector2(-40.0f, -90.0f), 1, 0.2f);
		mBodyAnimator->CreateAnimation(L"BodyLeft", mImage
			, Vector2(0.0f, 116.0f), Vector2(32.0f, 26.0f)
			, Vector2(-30.0f, -35.0f), 10, 0.1f);

		////mAnimator->FindEvents(L"MoveRight")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		//mAnimator->GetCompleteEvent(L"MoveRight") = std::bind(&Player::WalkComplete, this);
		//mHeadAnimator->GetCompleteEvent(L"HeadMoveRight") = std::bind(&Player::WalkComplete, this);
		//mBodyAnimator->GetCompleteEvent(L"BodyMoveRight") = std::bind(&Player::WalkComplete, this);

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
		delete mHead;
		delete mBody;
	}

	void Player::Tick()
	{
		GameObject::Tick();
		Pos playerPos = GetPos();
		Vector2 playerScale = GetScale();
		mHead->SetPos(playerPos);
		mBody->SetPos(playerPos);
		mHead->SetScale(playerScale);
		mBody->SetScale(playerScale);

		mBody->Tick();
		mHead->Tick();

		switch (mState)
		{
		case ya::Player::State::IDLE:
		{
			Idle();
		}
		break;
		case ya::Player::State::MOVE:
		{
			Move();
		}
		break;
		case ya::Player::State::ATTACK:
		{
			Attack();
		}
		break;
		case ya::Player::State::DIE:
		{
			Die();
		}
		break;
		default:
			break;
		}
	}

	void Player::Render(HDC hdc)
	{
		mBody->Render(hdc);
		mHead->Render(hdc);

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

	void Player::Idle()
	{
		if (KEY_PREESE(eKeyCode::W)
			|| KEY_PREESE(eKeyCode::S)
			|| KEY_PREESE(eKeyCode::A)
			|| KEY_PREESE(eKeyCode::D))
		{
			mState = State::MOVE;
		}

		if (KEY_PREESE(eKeyCode::UP)
			|| KEY_PREESE(eKeyCode::DOWN)
			|| KEY_PREESE(eKeyCode::LEFT)
			|| KEY_PREESE(eKeyCode::RIGHT))
		{
			mState = State::ATTACK;
		}

		mHeadAnimator->Play(L"HeadIdle", true);
		mBodyAnimator->Play(L"BodyIdle", true);

	}
	void Player::Move()
	{
		
		if (KEY_DOWN(eKeyCode::W))
		{
			mHeadAnimator->Play(L"HeadUp", true);
			mBodyAnimator->Play(L"BodyUp", true);
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			mHeadAnimator->Play(L"HeadDown", true);
			mBodyAnimator->Play(L"BodyDown", true);
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			mHeadAnimator->Play(L"HeadLeft", true);
			mBodyAnimator->Play(L"BodyLeft", true);
			GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mHeadAnimator->Play(L"HeadRight", true);
			mBodyAnimator->Play(L"BodyRight", true);
			GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}

		if (KEY_PREESE(eKeyCode::W))
		{
			mHeadAnimator->Play(L"HeadUp", true);
			mBodyAnimator->Play(L"BodyUp", true);
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_PREESE(eKeyCode::S))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
			mHeadAnimator->Play(L"HeadDown", true);
			mBodyAnimator->Play(L"BodyDown", true);
		}
		if (KEY_PREESE(eKeyCode::A))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
			mHeadAnimator->Play(L"HeadLeft", true);
			mBodyAnimator->Play(L"BodyLeft", true);
		}
		if (KEY_PREESE(eKeyCode::D))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
			mHeadAnimator->Play(L"HeadRight", true);
			mBodyAnimator->Play(L"BodyRight", true);
		}

		if (KEY_UP(eKeyCode::W)
			|| KEY_UP(eKeyCode::S)
			|| KEY_UP(eKeyCode::A)
			|| KEY_UP(eKeyCode::D))
		{
			mState = State::IDLE;
		}

		if (KEY_PREESE(eKeyCode::W)
			|| KEY_PREESE(eKeyCode::S)
			|| KEY_PREESE(eKeyCode::A)
			|| KEY_PREESE(eKeyCode::D))
		{
			mState = State::MOVE;
		}

		if (KEY_DOWN(eKeyCode::UP)
			|| KEY_DOWN(eKeyCode::DOWN)
			|| KEY_DOWN(eKeyCode::LEFT)
			|| KEY_DOWN(eKeyCode::RIGHT))
		{
			mState = State::ATTACK;
		}
	}
	void Player::Attack()
	{
		if (KEY_DOWN(eKeyCode::UP))
		{
			mHeadAnimator->Play(L"HeadUp", true);
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
			mHeadAnimator->Play(L"HeadDown", true);
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
			mHeadAnimator->Play(L"HeadLeft", true);
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
			mHeadAnimator->Play(L"HeadRight", true);
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.0f;
			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));
			missile->mDir += Vector2(1.0f, 0.0f);
		}

		if (KEY_UP(eKeyCode::UP)
			|| KEY_UP(eKeyCode::DOWN)
			|| KEY_UP(eKeyCode::LEFT)
			|| KEY_UP(eKeyCode::RIGHT))
		{
			mState = State::IDLE;
		}

		if (KEY_PREESE(eKeyCode::W)
			|| KEY_PREESE(eKeyCode::S)
			|| KEY_PREESE(eKeyCode::A)
			|| KEY_PREESE(eKeyCode::D))
		{
			mState = State::MOVE;
		}

		if (KEY_PREESE(eKeyCode::UP)
			|| KEY_PREESE(eKeyCode::DOWN)
			|| KEY_PREESE(eKeyCode::LEFT)
			|| KEY_PREESE(eKeyCode::RIGHT))
		{
			mState = State::ATTACK;
		}

	}
	void Player::Die()
	{
	}

}
