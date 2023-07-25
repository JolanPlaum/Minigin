#pragma once
// Includes
#include "Component.h"
#include <glm/glm.hpp>
#include "Event.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class BoxCollider2D final : public Component
	{
	public:
		// Constructors and Destructor
		BoxCollider2D(GameObject* pGameObject) :Component(pGameObject) {};
		~BoxCollider2D();
		
		// Copy and Move semantics
		BoxCollider2D(const BoxCollider2D& other)					= delete;
		BoxCollider2D& operator=(const BoxCollider2D& other)		= delete;
		BoxCollider2D(BoxCollider2D&& other) noexcept				= delete;
		BoxCollider2D& operator=(BoxCollider2D&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;

		void SetOffset(const glm::vec2& offset);
		void SetSize(const glm::vec2& size);

		const glm::vec4& GetBoxBoundaries();

		Event<BoxCollider2D*> OnCollision;


	private:
		// Member variables
		bool m_IsDirty{ false };
		glm::vec2 m_Offset{};
		glm::vec2 m_Size{};
		glm::vec4 m_BoxBoundaries{};
		DelegateHandle m_SetDirtyHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void SetDirty();

		friend class CollisionManager;
		void Collision(BoxCollider2D* pOther);
		
	};
}

