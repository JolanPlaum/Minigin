#pragma once
// Includes
#include "Component.h"
#include <glm/vec2.hpp>
#include "Event.h"
#include "Rectangle.h"

namespace dae
{
	// Class Forward Declarations
	class GameObject;
	
	// Class Declaration
	class BoxCollider2D final : public Component
	{
	public:
		// Constructors and Destructor
		BoxCollider2D(GameObject* pGameObject) :Component(pGameObject) {};
		~BoxCollider2D() = default;
		
		// Copy and Move semantics
		BoxCollider2D(const BoxCollider2D& other)					= delete;
		BoxCollider2D& operator=(const BoxCollider2D& other)		= delete;
		BoxCollider2D(BoxCollider2D&& other) noexcept				= delete;
		BoxCollider2D& operator=(BoxCollider2D&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;

		void SetOffset(glm::vec2 offset);
		void SetSize(glm::vec2 size);

		const Boundaries& GetBoxBoundaries();

		Event<GameObject*> OnCollision;


	private:
		// Member variables
		bool m_IsDirty{ false };
		glm::vec2 m_Offset{};
		glm::vec2 m_Size{};
		Boundaries m_BoxBoundaries{};
		DelegateHandle m_SetDirtyHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void SetDirty();

		friend class CollisionManager;
		void CollisionNotify(GameObject* pOther);
		
	};
}

