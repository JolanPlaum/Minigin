#pragma once
// Includes
#include "Singleton.h"
#include <vector>
#include <glm/glm.hpp>
#include "Rectangle.h"

namespace dae
{
	// Class Forward Declarations
	class BoxCollider2D;
	
	// Class Declaration
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		// Constructors and Destructor
		~CollisionManager() = default;
		
		// Copy and Move semantics
		CollisionManager(const CollisionManager& other)					= delete;
		CollisionManager& operator=(const CollisionManager& other)		= delete;
		CollisionManager(CollisionManager&& other) noexcept				= delete;
		CollisionManager& operator=(CollisionManager&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update();

		void AddCollider(BoxCollider2D* pCollider);
		void RemoveCollider(BoxCollider2D* pCollider);
		
		
	private:
		// Member variables
		std::vector<BoxCollider2D*> m_Colliders;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<CollisionManager>;
		explicit CollisionManager();

		bool IsCollision(const Boundaries& bounds1, const Boundaries& bounds2) const;
		
	};
}

