#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "GameSelector.h"
#include <iostream>

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(dae::LoadGame);

    return 0;
}