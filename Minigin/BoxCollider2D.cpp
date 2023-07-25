//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "BoxCollider2D.h"
#include <functional>
#include <algorithm>
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"

using namespace dae;
using namespace std::placeholders;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void BoxCollider2D::Init()
{
	m_SetDirtyHandle = GetGameObject()->GetTransform().GotDirty.AddFunction(
		std::bind(&BoxCollider2D::SetDirty, this)
	);

	CollisionManager::GetInstance().AddCollider(this);
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
BoxCollider2D::~BoxCollider2D()
{
	if (m_SetDirtyHandle.IsValid())
		GetGameObject()->GetTransform().GotDirty.Remove(m_SetDirtyHandle);

	CollisionManager::GetInstance().RemoveCollider(this);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void BoxCollider2D::SetOffset(const glm::vec2& offset)
{
	m_Offset = offset;
	SetDirty();
}

void BoxCollider2D::SetSize(const glm::vec2& size)
{
	m_Size = size;
	SetDirty();
}

const glm::vec4& BoxCollider2D::GetBoxBoundaries()
{
	if (m_IsDirty)
	{
		const auto& pos = GetGameObject()->GetTransform().GetWorldPosition();
		const auto& scale = GetGameObject()->GetTransform().GetWorldScale();
		
		float x1 = pos.x + m_Offset.x * scale.x;
		float y1 = pos.y + m_Offset.y * scale.y;
		float x2 = m_BoxBoundaries.x + m_Size.x * scale.x;
		float y2 = m_BoxBoundaries.y + m_Size.y * scale.y;

		m_BoxBoundaries.x = std::min(x1, x2);
		m_BoxBoundaries.y = std::min(y1, y2);
		m_BoxBoundaries.z = std::max(x1, x2);
		m_BoxBoundaries.w = std::max(y1, y2);

		m_IsDirty = false;
	}

	return m_BoxBoundaries;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void BoxCollider2D::SetDirty()
{
	m_IsDirty = true;
}

void BoxCollider2D::Collision(GameObject* pOther)
{
	OnCollision.Notify(pOther);
}

