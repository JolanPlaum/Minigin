//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "KeepSpriteSheetCentered.h"
#include "GameObject.h"
#include "Transform.h"
#include "CSpriteRenderer.h"
#include "EntityCollision.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void KeepSpriteSheetCentered::Init()
{
	m_pSpriteRenderer = GetGameObject()->GetComponent<CSpriteRenderer>();
	m_pEntityCollision = GetGameObject()->GetComponentInParent<EntityCollision>();

	m_SpriteRestrartHandle = m_pSpriteRenderer->Restarted.AddFunction(
		std::bind(&KeepSpriteSheetCentered::OnSpriteRestart, this));

	OnSpriteRestart();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void KeepSpriteSheetCentered::OnDestroy()
{
	if (m_SpriteRestrartHandle.IsValid())
		m_pSpriteRenderer->Restarted.Remove(m_SpriteRestrartHandle);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void KeepSpriteSheetCentered::Update()
{
	if (m_pEntityCollision == nullptr) return;

	if (m_pEntityCollision->IsGoingLeft()) FlipGameObject(false);
	if (m_pEntityCollision->IsGoingRight()) FlipGameObject(true);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void KeepSpriteSheetCentered::OnSpriteRestart() const
{
	GetGameObject()->GetTransform().SetLocalPosition({ -m_pSpriteRenderer->GetSize().x / 2.f, 0 });
}

void KeepSpriteSheetCentered::FlipGameObject(bool flip) const
{
	auto scale = GetGameObject()->GetTransform().GetLocalScale();

	if (flip) scale.x = -abs(scale.x);
	else scale.x = abs(scale.x);

	GetGameObject()->GetTransform().SetLocalScale(scale);
}
