#pragma once
// Includes
#include "Component.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	class Subject;
	
	// Class Declaration
	class Lives final : public Component
	{
	public:
		// Constructors and Destructor
		Lives(GameObject* pGameObject);
		~Lives() = default;
		
		// Copy and Move semantics
		Lives(const Lives& other)					= delete;
		Lives& operator=(const Lives& other)		= delete;
		Lives(Lives&& other) noexcept				= delete;
		Lives& operator=(Lives&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Kill();

		int GetLives() const { return m_NrLives; }
		Subject* GetSubject() const { return m_pSubject.get(); }
		
		
	private:
		// Member variables
		int m_NrLives{ 3 };
		const std::unique_ptr<Subject> m_pSubject{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

