#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Map : public GameObject
	{
	public:
		Map();
		~Map();

		Map(Vector2 pos);

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);
		Image* GetImage() { return mImage; }

	private:
		Image* mImage;
	};
}