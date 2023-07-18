#pragma once
// Includes
#include "Component.h"
#include "Event.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Score final : public Component
	{
	public:
		// Constructors and Destructor
		Score(GameObject* pGameObject) :Component(pGameObject) {};
		~Score() = default;
		
		// Copy and Move semantics
		Score(const Score& other)					= delete;
		Score& operator=(const Score& other)		= delete;
		Score(Score&& other) noexcept				= delete;
		Score& operator=(Score&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void AddPoints(int amount);

		int GetScore() const { return m_Score; }

		Event<int> ScoreChanged;
		
		
	private:
		// Member variables
		int m_Score{ 0 };
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

