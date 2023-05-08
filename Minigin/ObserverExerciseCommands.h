#pragma once
// Includes
#include "Command.h"
#include "GameObject.h"
#include "Lives.h"
#include "Score.h"

namespace dae
{
	// Class Forward Declarations

	// Class Declaration
	class DieCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit DieCommand(GameObject* pGameObject) :GameObjectCommand(pGameObject) {}
		~DieCommand() = default;

		// Copy and Move semantics
		DieCommand(const DieCommand& other)					= delete;
		DieCommand& operator=(const DieCommand& other)		= delete;
		DieCommand(DieCommand&& other) noexcept				= delete;
		DieCommand& operator=(DieCommand&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override
		{
			auto pLives = GetGameObject()->GetComponent<Lives>();
			if (pLives) pLives->Kill();
		}


	private:
		// Member variables

		//---------------------------
		// Private Member Functions
		//---------------------------

	};

	// Class Declaration
	class ScoreCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit ScoreCommand(GameObject* pGameObject, int amount)
			: GameObjectCommand(pGameObject)
			, m_Amount{ amount }
		{
		}
		~ScoreCommand() = default;

		// Copy and Move semantics
		ScoreCommand(const ScoreCommand& other)					= delete;
		ScoreCommand& operator=(const ScoreCommand& other)		= delete;
		ScoreCommand(ScoreCommand&& other) noexcept				= delete;
		ScoreCommand& operator=(ScoreCommand&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override
		{
			auto pLives = GetGameObject()->GetComponent<Score>();
			if (pLives) pLives->AddPoints(m_Amount);
		}


	private:
		// Member variables
		int m_Amount;

		//---------------------------
		// Private Member Functions
		//---------------------------

	};
}