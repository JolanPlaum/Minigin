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
	if (m_Colliders.size() < 2) return;

	for (int idx1{ 0 }; idx1 < static_cast<int>(m_Colliders.size()) - 1; ++idx1)
	{
		const auto& boundaries = m_Colliders[idx1]->GetBoxBoundaries();

		for (int idx2{ idx1 + 1 }; idx2 < static_cast<int>(m_Colliders.size()); ++idx2)
		{
			if (IsCollision(boundaries, m_Colliders[idx2]->GetBoxBoundaries()))
			{
				m_Colliders[idx1]->CollisionNotify(m_Colliders[idx2]->GetGameObject());
				m_Colliders[idx2]->CollisionNotify(m_Colliders[idx1]->GetGameObject());
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
	if (m_Colliders.empty()) return;

	std::erase(m_Colliders, pCollider);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
bool CollisionManager::IsCollision(const Boundaries& bounds1, const Boundaries& bounds2) const
{
	// If one rectangle is on left side of the other
	if (bounds1.x2 < bounds2.x1 || bounds2.x2 < bounds1.x1)
	{
		return false;
	}

	// If one rectangle is under the other
	if (bounds1.y2 < bounds2.y1 || bounds2.y2 < bounds1.y1)
	{
		return false;
	}

	return true;
}

