#pragma once
#include "GameObject.h"
#include "Lives.h"
#include "Score.h"
#include "LivesDisplay.h"
#include "ScoreDisplay.h"
#include "CTextTexture.h"
#include "CTextureRenderer.h"

namespace dae
{
	namespace ExerciseObserver
	{
		void CreatePlayer(GameObject* go)
		{
			go->AddComponent<Lives>();
			go->AddComponent<Score>();
		}

		void CreateLivesDisplay(GameObject* go, std::shared_ptr<Font> font, const SDL_Color& color)
		{
			go->AddComponent<CTextureRenderer>();
			go->AddComponent<LivesDisplay>();
			auto text = go->AddComponent<CTextTexture>();
			text->SetFont(font);
			text->SetColor(color);
		}

		void CreateScoreDisplay(GameObject* go, std::shared_ptr<Font> font, const SDL_Color& color)
		{
			go->AddComponent<CTextureRenderer>();
			go->AddComponent<ScoreDisplay>();
			auto text = go->AddComponent<CTextTexture>();
			text->SetFont(font);
			text->SetColor(color);
		}
	}
}