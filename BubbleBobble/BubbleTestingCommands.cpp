//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "BubbleTestingCommands.h"
#include "BubblesPrefab.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
LaunchBubbleCommand::LaunchBubbleCommand(GameObject* pGameObject, std::string color)
	: GameObjectCommand(pGameObject)
	, m_Color{ color }
{
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void LaunchBubbleCommand::Execute()
{
	GameObject* pPlayerVisuals{ GetGameObject()->GetComponentInChildren<CSpriteRenderer>()->GetGameObject() };
	float xDirection{ pPlayerVisuals->GetTransform().GetWorldScale().x };

	LaunchedBubble(GetGameObject()->GetScene(),
		pPlayerVisuals->GetTransform(),
		glm::vec2{ -xDirection, 0.f },
		m_Color);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

