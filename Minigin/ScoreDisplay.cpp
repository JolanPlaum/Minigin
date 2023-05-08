//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "CTextTexture.h"
#include "Observer.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
ScoreDisplay::ScoreDisplay(GameObject* pGameObject)
	: Component(pGameObject)
	, m_pObserver{ std::make_unique<Observer>() }
{
	m_pObserver->AddEventFunction<int>(EventType::SCORE_CHANGED,
		std::bind(&ScoreDisplay::OnScoreChanged, this, std::placeholders::_1));
}

void ScoreDisplay::Init()
{
	m_pText = GetGameObject()->GetComponent<CTextTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void ScoreDisplay::OnScoreChanged(int score)
{
	if (m_pText) m_pText->SetText("Score: " + std::to_string(score));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

