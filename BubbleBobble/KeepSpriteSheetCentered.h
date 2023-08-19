#pragma once
// Includes
#include "Component.h"
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	class CSpriteRenderer;
	class EntityCollision;
	
	// Class Declaration
	class KeepSpriteSheetCentered final : public Component
	{
	public:
		// Constructors and Destructor
		KeepSpriteSheetCentered(GameObject* pGameObject) :Component(pGameObject) {};
		~KeepSpriteSheetCentered() = default;
		
		// Copy and Move semantics
		KeepSpriteSheetCentered(const KeepSpriteSheetCentered& other)					= delete;
		KeepSpriteSheetCentered& operator=(const KeepSpriteSheetCentered& other)		= delete;
		KeepSpriteSheetCentered(KeepSpriteSheetCentered&& other) noexcept				= delete;
		KeepSpriteSheetCentered& operator=(KeepSpriteSheetCentered&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;
		void Update() override;
		
		
	private:
		// Member variables
		CSpriteRenderer* m_pSpriteRenderer{};
		EntityCollision* m_pEntityCollision{};
		DelegateHandle m_SpriteRestrartHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnSpriteRestart() const;
		void FlipGameObject(bool flip) const;
		
	};
}

