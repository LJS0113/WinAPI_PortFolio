#include "yaMap.h"
#include "yaResources.h"
#include "yaApplication.h"
#include "yaImage.h"
#include "yaGameObject.h"
#include "yaComponent.h"

namespace ya
{
	Map::Map()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Map", L"..\\Resources\\Image\\Map.bmp");
		}

	}

	Map::~Map()
	{

	}

	Map::Map(Vector2 pos)
		: mImage(nullptr)
	{
		SetPos(pos);
		SetScale(Vector2::One);
	}

	void Map::Tick()
	{
		GameObject::Tick();
	}

	void Map::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos = pos;

		Vector2 rect;
		rect.x = mImage->GetWidth();
		rect.y = mImage->GetHeight();

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Map::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}



	void Map::OnCollisionEnter(Collider* other)
	{
	}
	void Map::OnCollisionStay(Collider* other)
	{
	}
	void Map::OnCollisionExit(Collider* other)
	{
	}
}