//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "LivesDisplay.h"
#include <functional>
#include "GameObject.h"
#include "CTextTexture.h"
#include "Lives.h"

using namespace dae;
using namespace std::placeholders;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void LivesDisplay::Init()
{
	m_pText = GetGameObject()->GetComponent<CTextTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void LivesDisplay::OnDestroy()
{
	SetLivesComponent(nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void LivesDisplay::SetLivesComponent(Lives* pLives)
{
	if (m_pLives && m_PlayerDiedHandle.IsValid())
		m_pLives->Died.Remove(m_PlayerDiedHandle);

	m_pLives = pLives;

	if (m_pLives)
		m_PlayerDiedHandle = m_pLives->Died.AddFunction(
			std::bind(&LivesDisplay::OnPlayerDied, this, _1)
		);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void LivesDisplay::OnPlayerDied(int lives)
{
	if (m_pText) m_pText->SetText("Lives: " + std::to_string(lives));
}

