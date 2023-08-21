#pragma once
// Includes
#include "EnemyBehaviour.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class ZenChan final : public EnemyBehaviour
	{
	public:
		// Constructors and Destructor
		ZenChan(GameObject* pGameObject) :EnemyBehaviour(pGameObject) {};
		~ZenChan() = default;
		
		// Copy and Move semantics
		ZenChan(const ZenChan& other)					= delete;
		ZenChan& operator=(const ZenChan& other)		= delete;
		ZenChan(ZenChan&& other) noexcept				= delete;
		ZenChan& operator=(ZenChan&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;

		void SetTrapped() override;
		void FreeTrapped(glm::vec2 position) override;
		void SetDead(glm::vec2 position) override;
		
		
	private:
		// Member variables
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

