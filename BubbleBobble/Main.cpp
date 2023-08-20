#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
#include <time.h>
#include "Minigin.h"
#include "GameSelector.h"

int main(int, char* [])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	dae::Minigin engine("../Data/");
	engine.Run(dae::LoadGame);

	return 0;
}