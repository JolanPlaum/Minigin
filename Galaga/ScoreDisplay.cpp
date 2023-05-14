//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "CTextTexture.h"
#include "Score.h"

using namespace dae;
using namespace std::placeholders;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
ScoreDisplay::ScoreDisplay(GameObject* pGameObject)
	: Component(pGameObject)
{
}

void ScoreDisplay::Init()
{
	m_pText = GetGameObject()->GetComponent<CTextTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
ScoreDisplay::~ScoreDisplay()
{
	SetScoreComponent(nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void ScoreDisplay::SetScoreComponent(Score* pScore)
{
	if (m_pScore && m_ScoreChangedHandle.IsValid())
		m_pScore->ScoreChanged.Remove(m_ScoreChangedHandle);

	m_pScore = pScore;

	if (m_pScore)
		m_ScoreChangedHandle = m_pScore->ScoreChanged.AddFunction(
			std::bind(&ScoreDisplay::OnScoreChanged, this, _1)
		);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void ScoreDisplay::OnScoreChanged(int score)
{
	if (m_pText) m_pText->SetText("Score: " + std::to_string(score));
}

