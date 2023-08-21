#pragma once
// Includes
#include "Component.h"
#include <string>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Item final : public Component
	{
	public:
		// Constructors and Destructor
		Item(GameObject* pGameObject) :Component(pGameObject) {};
		~Item() = default;
		
		// Copy and Move semantics
		Item(const Item& other)					= default;
		Item& operator=(const Item& other)		= default;
		Item(Item&& other) noexcept				= default;
		Item& operator=(Item&& other) noexcept	= default;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void SetName(const std::string& name);
		std::string GetName() const { return m_Name; }
		
		
	private:
		// Member variables
		std::string m_Name{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

