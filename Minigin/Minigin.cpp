#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include  "Timer.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version)
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version)
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Monke::Minigin::Minigin(const std::string &dataPath, const int width, const int heigth, const int desiredFPS)
:
m_WindowW{ static_cast<float>(width)},
m_WindowH{ static_cast<float>(heigth)},
m_DesiredFPS(desiredFPS)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		heigth,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::Get().Init(g_window);

	ResourceManager::Get().Init(dataPath);

}

Monke::Minigin::~Minigin()
{
	Renderer::Get().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void Monke::Minigin::Run(const std::function<void()>& initiliaze) const
{
	initiliaze();

	auto& renderer = Renderer::Get();
	const auto& sceneManager = SceneManager::Get();
	auto& input = InputManager::Get();
	auto& timer = Timer::Get();

	const auto desiredFPSTime{ std::chrono::milliseconds( 1'000 / m_DesiredFPS ) };

	bool canContinueLoop = true;

	while (canContinueLoop)
	{
		timer.Update();
		canContinueLoop = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();

		//sleep to let the cpu rest between frames
		const auto sleeptime =   timer.GetLastTime() + desiredFPSTime - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleeptime);
	}
	//save data
}
