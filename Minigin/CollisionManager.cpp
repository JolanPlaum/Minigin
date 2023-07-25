//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CollisionManager.h"
#include "BoxCollider2D.h"
#include <algorithm>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
CollisionManager::CollisionManager()
{
}



//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void CollisionManager::Update()
{
	for (int idx1{ 0 }; idx1 < m_Colliders.size() - 1; ++idx1)
	{
		const auto& boundaries = m_Colliders[idx1]->GetBoxBoundaries();

		for (int idx2{ idx1 + 1 }; idx2 < m_Colliders.size(); ++idx2)
		{
			if (IsCollision(boundaries, m_Colliders[idx2]->GetBoxBoundaries()))
			{
				m_Colliders[idx1]->Collision(m_Colliders[idx2]);
				m_Colliders[idx2]->Collision(m_Colliders[idx1]);
			}
		}
	}
}

void CollisionManager::AddCollider(BoxCollider2D* pCollider)
{
	if (m_Colliders.end() != std::find(m_Colliders.begin(), m_Colliders.end(), pCollider)) return;

	m_Colliders.push_back(pCollider);
}

void CollisionManager::RemoveCollider(BoxCollider2D* pCollider)
{
	std::erase(m_Colliders, pCollider);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
bool CollisionManager::IsCollision(const glm::vec4& bounds1, const glm::vec4& bounds2) const
{
	// If one rectangle is on left side of the other
	if (bounds1.z < bounds2.x || bounds2.z < bounds1.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (bounds1.w < bounds2.y || bounds2.w < bounds1.y)
	{
		return false;
	}

	return true;
}

