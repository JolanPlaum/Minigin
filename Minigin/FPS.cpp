//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "FPS.h"
#include "CTextTexture.h"
#include "TimeManager.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void FPS::Init()
{
	m_TextComponent = GetGameObject()->GetComponent<CTextTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void FPS::Update()
{
	m_TextComponent.lock()->SetText(std::to_string(int(TimeManager::GetInstance().GetFPS())) + " FPS");
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

