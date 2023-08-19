//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "BoxCollider2D.h"
#include <functional>
#include <algorithm>
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "CTextureRenderer.h"
#include "CSpriteRenderer.h"
#include "Renderer.h"

using namespace dae;
using namespace std::placeholders;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void BoxCollider2D::Init()
{
	if (!m_IsDirty)
	{
		if (CTextureRenderer* pTexture{ GetGameObject()->GetComponent<CTextureRenderer>() }; pTexture)
		{
			m_Size = pTexture->GetSize();
		}
		else if (CSpriteRenderer* pSprite{ GetGameObject()->GetComponent<CSpriteRenderer>() }; pSprite)
		{
			m_Size = pSprite->GetSize();
		}
	}

	m_SetDirtyHandle = GetGameObject()->GetTransform().GotDirty.AddFunction(
		std::bind(&BoxCollider2D::SetDirty, this)
	);

	CollisionManager::GetInstance().AddCollider(this);

	SetDirty();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void BoxCollider2D::OnDestroy()
{
	if (m_SetDirtyHandle.IsValid())
		GetGameObject()->GetTransform().GotDirty.Remove(m_SetDirtyHandle);

	CollisionManager::GetInstance().RemoveCollider(this);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void BoxCollider2D::Render() const
{
	//Renderer::GetInstance().DrawRect(Rectangle(m_BoxBoundaries));
}

void BoxCollider2D::SetOffset(glm::vec2 offset)
{
	m_Offset = offset;
	SetDirty();
}

void BoxCollider2D::SetSize(glm::vec2 size)
{
	m_Size = size;
	SetDirty();
}

const Boundaries& BoxCollider2D::GetBoxBoundaries()
{
	if (m_IsDirty)
	{
		const auto& pos = GetGameObject()->GetTransform().GetWorldPosition();
		const auto& scale = GetGameObject()->GetTransform().GetWorldScale();
		
		float x1 = pos.x + m_Offset.x * scale.x;
		float y1 = pos.y + m_Offset.y * scale.y;
		float x2 = x1 + m_Size.x * scale.x;
		float y2 = y1 + m_Size.y * scale.y;

		m_BoxBoundaries.x1 = std::min(x1, x2);
		m_BoxBoundaries.y1 = std::min(y1, y2);
		m_BoxBoundaries.x2 = std::max(x1, x2);
		m_BoxBoundaries.y2 = std::max(y1, y2);

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

void BoxCollider2D::CollisionNotify(GameObject* pOther)
{
	OnCollision.Notify(pOther);
}

