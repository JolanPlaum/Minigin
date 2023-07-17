#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
#include "Minigin.h"
#include "GameSelector.h"

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(dae::LoadGame);

	return 0;
}