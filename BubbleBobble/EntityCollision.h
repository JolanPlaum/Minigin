#pragma once
// Includes
#include "Component.h"
#include <glm/vec2.hpp>
#include "DelegateHandle.h"
#include "Rectangle.h"

namespace dae
{
	// Class Forward Declarations
	class BoxCollider2D;
	
	// Class Declaration
	class EntityCollision final : public Component
	{
	public:
		// Constructors and Destructor
		EntityCollision(GameObject* pGameObject) :Component(pGameObject) {};
		~EntityCollision() = default;
		
		// Copy and Move semantics
		EntityCollision(const EntityCollision& other)					= delete;
		EntityCollision& operator=(const EntityCollision& other)		= delete;
		EntityCollision(EntityCollision&& other) noexcept				= delete;
		EntityCollision& operator=(EntityCollision&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;
		void Update() override;

		void SetStaticLevelCollision(bool isCollision = true);
		void SetPlatformCollision(bool isCollision = true);

		bool IsGoingLeft() const { return m_IsGoingLeft; }
		bool IsGoingRight() const { return m_IsGoingRight; }
		bool IsGoingUp() const { return m_IsGoingUp; }
		bool IsGoingDown() const { return m_IsGoingDown; }
		
		
	private:
		// Member variables
		bool m_IsCollisionStatic{ true };
		bool m_IsCollisionPlatform{ true };

		bool m_IsInPlatform{};
		bool m_WasInPlatform{};

		bool m_IsGoingLeft{};
		bool m_IsGoingRight{};
		bool m_IsGoingUp{};
		bool m_IsGoingDown{};

		glm::vec2 m_CurrentPosition{};
		glm::vec2 m_PreviousPosition{};

		BoxCollider2D* m_pCollider{};

		DelegateHandle m_CollisionHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnCollisionNotify(GameObject* pOther);

	};
}

