#include "yaGameObject.h"
#include "yaTime.h"
#include "yaApplication.h"
#include "yaCamera.h"

namespace ya
{
	GameObject::GameObject()
		: mPos{ 0.0f, 0.0f }
		, mScale{ 1.0f, 1.0f }
		, mDead(false)
		, mDeathTime(-100.0f)
		, mDeathTimeOn(false)
	{

	}

	GameObject::GameObject(Vector2 position)
		: mPos(position)
		, mScale{ 1.0f, 1.0f }
		, mDead(false)
		, mDeathTime(-100.0f)
		, mDeathTimeOn(false)
	{

	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{

	}

	void GameObject::Tick()
	{
		DeathLoop();

		// 모든 컴포넌트를 Tick 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		// 모든 컴포넌트를 Render 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}

		// Player Pos Debug Render
		//HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		//Brush brush(hdc, tr);
		//HPEN blackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		//HPEN oldPen = (HPEN)SelectObject(hdc, blackPen);
		//mPos = Camera::CalculatePos(mPos);
		//Rectangle(hdc, (mPos.x), (mPos.y), (mPos.x + 10.0f), (mPos.y + 10.0f));
		//SelectObject(hdc, oldPen);
		//DeleteObject(blackPen);
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}

	void GameObject::SetDeathTime(float time)
	{
		if (mDeathTime <= 0.0f)
		{
			mDeathTime = time;
			mDeathTimeOn = true;
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		if (component == nullptr)
			return;

		mComponents.push_back(component);
		component->mOwner = this;
	}

	void GameObject::DeathLoop()
	{
		if (mDeathTimeOn == true)
		{
			mDeathTime -= Time::DeltaTime();
			if (mDeathTime <= 0.0f)
				Death();
		}
	}
}