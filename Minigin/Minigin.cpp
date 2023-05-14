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
#include "TimeManager.h"
#include "GuiManager.h"

SDL_Window* g_pWindow{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
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

dae::Minigin::Minigin(const std::string &dataPath)
{
	TimeManager::GetInstance();

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	GuiManager::GetInstance().Init(g_pWindow);

	Renderer::GetInstance().Init(g_pWindow);

	ResourceManager::GetInstance().Init(dataPath);

	//SteamAchievements::GetInstance().Init({
	//	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	//	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	//	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	//	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter")
	//	});
}

dae::Minigin::~Minigin()
{
	GuiManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();
	
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = TimeManager::GetInstance();
	auto& gui = GuiManager::GetInstance();

	sceneManager.Init();

	bool isRunning = true;
	while (isRunning)
	{
		//Update Time
		time.Tick();

		//Steam Callback
		//SteamAPI_RunCallbacks();

		//Input Events
		isRunning = input.ProcessInput();

		//Handle GUI
		gui.UpdateGui();

		//Game Logic
		sceneManager.Update();

		//Render
		renderer.Render();

		//Let CPU rest
		time.Sleep();
	}
}
