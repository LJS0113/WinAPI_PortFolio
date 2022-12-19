#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Vector2 position);
		~Monster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		//void Dead();

	private:
		Image* mImage;
		float mTime;

		Image* mFlyImage;
		Image* mGaperHeadImage;
		Image* mGaperBodyImage;
		Image* mClottyImage;
		Image* mBossImage;

		Animator* mFlyAnimator;
		Animator* mGaperHeadAnimator;
		Animator* mGaperBodyAnimator;
		Animator* mClottyAnimator;
		Animator* mBossAnimator;

		GameObject* mGaperHead;
		GameObject* mGaperBody;

	};

}