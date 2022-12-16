#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		enum class State
		{
			IDLE,
			MOVE,
			ATTACK,
			DIE,
		};

	public:
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void WalkComplete();

		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }

		void Idle();
		void Move();
		void Attack();
		void Die();

	private:
		State mState;
		float mCoff;
		float mSpeed;
		Vector2 mMisiileDir;
		int mHp;

		Image* mImage;

		Animator* mHeadAnimator;
		Animator* mBodyAnimator;

		GameObject* mHead;
		GameObject* mBody;
	};

}