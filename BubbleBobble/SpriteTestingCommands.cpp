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

PauseSpriteCommand::PauseSpriteCommand(GameObject* pGameObject, float time)
	: PauseSpriteCommand(pGameObject, false, time)
{
}

PauseSpriteCommand::PauseSpriteCommand(GameObject* pGameObject, bool isPlayCommand, float time)
	: GameObjectCommand(pGameObject)
	, m_IsPlayCommand{ isPlayCommand }
	, m_Time{ time }
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

void PauseSpriteCommand::Execute()
{
	CSpriteRenderer* pSpriteRenderer = GetGameObject()->GetComponent<CSpriteRenderer>();

	if (m_IsPlayCommand) pSpriteRenderer->Play();
	else pSpriteRenderer->Pause(m_Time);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

