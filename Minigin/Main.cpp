#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "FPS.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Text.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"

using namespace Monke;

void initiliaze()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 18) };
	const auto pTextureBackground{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pTextureLogo{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	//background object
	const auto pBackground{ std::make_shared<GameObject>() };
	pBackground->AddComponent<Transform>()->SetPosition(0,0);
	pBackground->AddComponent<Texture>()->SetTexture(pTextureBackground);
	//
	scene.Add(pBackground);

	//logo object
	const auto pLogo{ std::make_shared<GameObject>() };
	pLogo->AddComponent<Transform>()->SetPosition( 216, 200 );
	pLogo->AddComponent<Texture>()->SetTexture(pTextureLogo);
	//
	scene.Add(pLogo);

	//header text object
	const auto pText{ std::make_shared<GameObject>() };
	pText->AddComponent<Transform>()->SetPosition(80, 80);
	//
	const auto pTextComp{ pText->AddComponent<Text>() };
	pTextComp->SetFont(pFont);
	pTextComp->SetText("Programming 4 Assignment");
	//
	scene.Add(pText);

	//FPS object
	const auto pFPS{ std::make_shared<GameObject>() };
	pFPS->AddComponent<Transform>()->SetPosition(10, 10);
	//
	const auto pTextFPS{ pFPS->AddComponent<Text>() };
	pTextFPS->SetFont(pFontFPS);
	pTextFPS->SetColor(255, 255, 0);
	//
	pFPS->AddComponent<FPS>();
	//
	scene.Add(pFPS);

}

int main(int, char* [])
{
	const Minigin engine("../Data/");
	engine.Run(initiliaze);
	return 0;
}
