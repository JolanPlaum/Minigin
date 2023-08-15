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
SetSpriteIdxCommand::SetSpriteIdxCommand(GameObject* pGameObject, Index indexType, int idx)
	: GameObjectCommand(pGameObject)
	, m_IsUsingName{ false }
	, m_IndexType{ indexType }
	, m_Idx{ idx }
	, m_Name{}
{
}
SetSpriteIdxCommand::SetSpriteIdxCommand(GameObject* pGameObject, Index indexType, const std::string& name)
	: GameObjectCommand(pGameObject)
	, m_IsUsingName{ true }
	, m_IndexType{ indexType }
	, m_Idx{}
	, m_Name{ name }
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

	switch (m_IndexType)
	{
	case Index::col:
		if (m_IsUsingName) pSpriteRenderer->SetColIdx(m_Name);
		else pSpriteRenderer->SetColIdx(m_Idx);
		break;

	case Index::row:
		if (m_IsUsingName) pSpriteRenderer->SetRowIdx(m_Name);
		else pSpriteRenderer->SetRowIdx(m_Idx);
		break;

	case Index::tile:
		if (m_IsUsingName) pSpriteRenderer->SetTileIdx(m_Name);
		else pSpriteRenderer->SetTileIdx(m_Idx);
		break;
	}
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

