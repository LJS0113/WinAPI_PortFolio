#include "yaMonster.h"
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
#include "yaRigidbody.h"

namespace ya
{
	Monster::Monster()
		: mTime(0.0f)
	{
		SetName(L"Monster");
		SetPos({ 800, 300 / 2 });
		SetScale({ 1.0f, 1.0f });

		if (mImage == nullptr)
		{
			
			mGaperHeadImage = Resources::Load<Image>(L"GaperHead", L"..\\Resources\\Image\\gaperHead.bmp");
			mGaperBodyImage = Resources::Load<Image>(L"GaperBody", L"..\\Resources\\Image\\gaperBody.bmp");
			//mClottyImage = Resources::Load<Image>(L"Clotty", L"..\\Resources\\Image\\clotty.bmp");
			//mBossImage = Resources::Load<Image>(L"Boss", L"..\\Resources\\Image\\Middleboss.bmp");
			//mFlyImage = Resources::Load<Image>(L"Fly", L"..\\Resources\\Image\\fly.bmp");
		}

		mGaperHead = new GameObject();
		mGaperBody = new GameObject();

		mGaperHeadAnimator = new Animator();
		mGaperHeadAnimator->CreateAnimation(L"GaperHeadIdle", mGaperHeadImage
			, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f)
			, Vector2(0.0f, 0.0f), 1, 0.2f);

		mGaperHead->AddComponent(mGaperHeadAnimator);

		mGaperBodyAnimator = new Animator();
		mGaperBodyAnimator->CreateAnimation(L"GaperBodyIdle", mGaperBodyImage
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f)
			, Vector2(0.0f, 50.0f), 6, 0.1f);
		mGaperBody->AddComponent(mGaperBodyAnimator);

		mGaperHeadAnimator->Play(L"GaperHeadIdle", true);
		mGaperBodyAnimator->Play(L"GaperBodyIdle", true);

		AddComponent(new Collider());
	}

	//Monster::Monster(Vector2 position)
	//	: mTime(0.0f)
	//{
	//	SetName(L"Monster");
	//	SetPos(position);
	//	SetScale({ 3.0f, 3.0f });

	//	if (mImage == nullptr)
	//	{
	//		mGaperHeadImage = Resources::Load<Image>(L"GaperHead", L"..\\Resources\\Image\\gaperHead.bmp");
	//		mGaperBodyImage = Resources::Load<Image>(L"GaperBody", L"..\\Resources\\Image\\gaperBody.bmp");
	//		//mClottyImage = Resources::Load<Image>(L"Clotty", L"..\\Resources\\Image\\clotty.bmp");
	//		//mBossImage = Resources::Load<Image>(L"Boss", L"..\\Resources\\Image\\Middleboss.bmp");
	//		//mFlyImage = Resources::Load<Image>(L"Fly", L"..\\Resources\\Image\\fly.bmp");
	//	}

	//	mGaperHead = new GameObject();
	//	mGaperBody = new GameObject();

	//	//Idle ป๓ลย
	//	mGaperHeadAnimator = new Animator();
	//	mGaperHeadAnimator->CreateAnimation(L"GaperHeadIdle", mGaperHeadImage
	//		, Vector2(32.0f, 32.0f), Vector2(32.0f, 32.0f)
	//		, Vector2(0.0f, 0.0f), 1, 0.2f);

	//	mGaperHead->AddComponent(mGaperHeadAnimator);

	//	mGaperBodyAnimator = new Animator();
	//	mGaperBodyAnimator->CreateAnimation(L"GaperBodyIdle", mGaperBodyImage
	//		, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f)
	//		, Vector2(0.0f, 0.0f), 1, 0.1f);
	//	mGaperBody->AddComponent(mGaperBodyAnimator);

	//	mGaperHeadAnimator->Play(L"GaperHeadIdle", true);
	//	mGaperBodyAnimator->Play(L"GaperBodyIdle", true);
	//	//AddComponent(new Animator());
	//	AddComponent(new Collider());

	//}

	Monster::~Monster()
	{
		delete mGaperHead;
		delete mGaperBody;
	}

	void Monster::Tick()
	{
		Pos monsterPos = GetPos();
		Vector2 monsterScale = GetScale();
		mGaperHead->SetPos(monsterPos);
		mGaperBody->SetPos(monsterPos);
		mGaperHead->SetScale(monsterScale);
		mGaperBody->SetScale(monsterScale);

		mGaperHead->Tick();
		mGaperBody->Tick();

		GameObject::Tick();

		if (KEY_DOWN(eKeyCode::U))
		{
			SetPos({ 900, 300});
		}
	}

	void Monster::Render(HDC hdc)
	{
		mGaperBody->Render(hdc);
		mGaperHead->Render(hdc);
		
		GameObject::Render(hdc);
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}

}
