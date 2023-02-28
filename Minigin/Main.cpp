#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <memory>

#include "Minigin.h"
#include "FPS.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Text.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"
#include "Texture2D.h"

using namespace Monke;

void initiliaze(const Minigin& engine)
{
	auto& scene = SceneManager::GetInstance().CreateScene("Assignment");
	
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };
	const auto pTextureBackground{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pTextureLogo{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	//background object
	const auto pBackground{ scene.MakeGameObject() };
	pBackground->AddComponent<Transform>()->SetPosition(0,0);
	pBackground->AddComponent<Texture>()->SetTexture(pTextureBackground);

	//logo object
	const auto pLogo{ scene.MakeGameObject() };
	pLogo->AddComponent<Texture>()->SetTexture(pTextureLogo);
	//
	const glm::vec2 middleScreenPos
	{
		(engine.GetWindowW() / 2) - (pTextureLogo->GetSize().x / 2),
		(engine.GetWindowH() / 2) - (pTextureLogo->GetSize().y / 2)
	};
	//
	pLogo->AddComponent<Transform>()->SetPosition(middleScreenPos.x, middleScreenPos.y);

	//header text object
	const auto pText{ scene.MakeGameObject() };
	pText->AddComponent<Transform>()->SetPosition(80, 80);
	//
	const auto pTextComp{ pText->AddComponent<Text>() };
	pTextComp->SetFont(pFont);
	pTextComp->SetText("Programming 4 Assignment");

	//FPS object
	const auto pFPS{ scene.MakeGameObject() };
	pFPS->AddComponent<Transform>()->SetPosition(10, 10);
	pFPS->AddComponent<FPS>();
	//
	const auto pTextFPS{ pFPS->AddComponent<Text>() };
	pTextFPS->SetFont(pFontFPS);
	pTextFPS->SetColor(255, 255, 0, 200);

}

int main(int, char* [])
{
	//original size {640, 480}
	//const Minigin engine("../Data/", 640, 480);
	//const Minigin* engine = new Minigin("../Data/", 640, 480);
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 640, 480);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}
