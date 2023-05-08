//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "LivesDisplay.h"
#include "GameObject.h"
#include "CTextTexture.h"
#include "Observer.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
LivesDisplay::LivesDisplay(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pObserver{ std::make_unique<Observer>() }
{
	m_pObserver->AddEventFunction<int>(EventType::PLAYER_DIED,
		std::bind(&LivesDisplay::OnPlayerDied, this, std::placeholders::_1));
}

void LivesDisplay::Init()
{
	m_pText = GetGameObject()->GetComponent<CTextTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void LivesDisplay::OnPlayerDied(int lives)
{
	if (m_pText) m_pText->SetText("Lives: " + std::to_string(lives));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

