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
#include "Orbit.h"
#include "Texture2D.h"

using namespace Monke;

void initiliaze(const Minigin& engine)
{
	auto& scene = SceneManager::GetInstance().CreateScene("Assignment");
	
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 15) };
	const auto pTextureBackground{ ResourceManager::GetInstance().LoadTexture("Images/background.tga") };
	const auto pTextureLogo{ ResourceManager::GetInstance().LoadTexture("Images/logo.tga") };
	const auto pTextureImage1 {ResourceManager::GetInstance().LoadTexture("Images/Fries.png") };
	const auto pTextureImage2{ ResourceManager::GetInstance().LoadTexture("Images/WaterMelon.png") };

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
		(engine.GetWindowW() / 2),
		(engine.GetWindowH() / 2)
	};
	const glm::vec2 posLogo
	{
		middleScreenPos.x - (pTextureLogo->GetSize().x / 2),
		middleScreenPos.y - (pTextureLogo->GetSize().y / 2) - 50
	};
	//
	pLogo->AddComponent<Transform>()->SetPosition(posLogo.x, posLogo.y);

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

	const glm::vec3 posImage1
	{
		middleScreenPos.x - (pTextureImage1->GetSize().x / 2),
		middleScreenPos.y - (pTextureImage1->GetSize().y / 2) + 100,
		0
	};

	///orbiting images
	const auto pImage1{ scene.MakeGameObject() };
	pImage1->AddComponent<Texture>()->SetTexture(pTextureImage1);
	pImage1->AddComponent<Transform>();

	const auto pOrbit = pImage1->AddComponent<Orbit>();
	pOrbit->SetRadius(25.f);
	pOrbit->SetRotationSpeed(45.f);
	pOrbit->SetCenter(posImage1);

	scene.Add(pImage1);

	const auto pImage2{ scene.MakeGameObject() };
	pImage2->AddComponent<Texture>()->SetTexture(pTextureImage2);
	pImage2->AddComponent<Transform>();

	const auto pOrbit2 = pImage2->AddComponent<Orbit>();
	pOrbit2->SetRadius(65.f);
	pOrbit2->SetRotationSpeed(-60.f);
	pOrbit2->SetCenter(glm::vec3{-10, -10, 0});

	scene.Add(pImage2);

	//pImage1->AddChild(pImage2);
	pImage2->SetParent(pImage1, false);

	pImage1->RemoveChild(pImage2);

	pImage1->AddChild(pImage2);
	//pFPS->RemoveComponent<Transform>();
	//
	//pImage1->Destroy();
}

int main(int, char* [])
{
	//original size {640, 480}
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 640, 480, 60000);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}
