#pragma once
// Includes
#include "Component.h"
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	class BoxCollider2D;
	class Lives;
	
	// Class Declaration
	class GalagaPlayer final : public Component
	{
	public:
		// Constructors and Destructor
		GalagaPlayer(GameObject* pGameObject) :Component(pGameObject) {};
		~GalagaPlayer();
		
		// Copy and Move semantics
		GalagaPlayer(const GalagaPlayer& other)					= delete;
		GalagaPlayer& operator=(const GalagaPlayer& other)		= delete;
		GalagaPlayer(GalagaPlayer&& other) noexcept				= delete;
		GalagaPlayer& operator=(GalagaPlayer&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		
		
	private:
		// Member variables
		Lives* m_pLivesComp{};
		DelegateHandle m_CollisionHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnCollisionNotify(const GameObject* pOther) const;
		
	};
}

