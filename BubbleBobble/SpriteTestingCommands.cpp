//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "SpriteTestingCommands.h"
#include "GameObject.h"
#include "Transform.h"
#include "CSpriteRenderer.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
SetSpriteIdxCommand::SetSpriteIdxCommand(GameObject* pGameObject, bool isColIdx, int idx)
	: GameObjectCommand(pGameObject)
	, m_IsColIdx{ isColIdx }
	, m_Idx{ idx }
{
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void SetSpriteIdxCommand::Execute()
{
	CSpriteRenderer* pSpriteRenderer = GetGameObject()->GetComponent<CSpriteRenderer>();

	if (m_IsColIdx) pSpriteRenderer->SetColIdx(m_Idx);
	else pSpriteRenderer->SetRowIdx(m_Idx);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

