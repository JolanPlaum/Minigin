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
		void CreatePlayer(std::shared_ptr<GameObject>& go)
		{
			go = std::make_shared<GameObject>();

			go->AddComponent<Lives>();
			go->AddComponent<Score>();
		}

		void CreateLivesDisplay(std::shared_ptr<GameObject>& go, std::shared_ptr<Font> font, const SDL_Color& color)
		{
			go = std::make_shared<GameObject>();

			go->AddComponent<CTextureRenderer>();
			go->AddComponent<LivesDisplay>();
			auto text = go->AddComponent<CTextTexture>();
			text->SetFont(font);
			text->SetColor(color);
		}

		void CreateScoreDisplay(std::shared_ptr<GameObject>& go, std::shared_ptr<Font> font, const SDL_Color& color)
		{
			go = std::make_shared<GameObject>();

			go->AddComponent<CTextureRenderer>();
			go->AddComponent<ScoreDisplay>();
			auto text = go->AddComponent<CTextTexture>();
			text->SetFont(font);
			text->SetColor(color);
		}
	}
}