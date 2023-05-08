#pragma once
// Includes
#include "Component.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	class Subject;
	
	// Class Declaration
	class Score final : public Component
	{
	public:
		// Constructors and Destructor
		Score(GameObject* pGameObject);
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
		Subject* GetSubject() const { return m_pSubject.get(); }
		
		
	private:
		// Member variables
		int m_Score{ 0 };
		const std::unique_ptr<Subject> m_pSubject{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

