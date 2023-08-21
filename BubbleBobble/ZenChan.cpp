//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "ZenChan.h"
#include "GameObject.h"
#include "Transform.h"
#include "ZenChanStates.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void ZenChan::Init()
{
	SetName("ZenChan");
	SetEnemyState(std::make_unique<ZenChanWalk>(GetGameObject()));
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void ZenChan::OnDestroy()
{
	SetEnemyState(nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void ZenChan::SetTrapped()
{
	SetEnemyState(std::make_unique<ZenChanTrapped>(GetGameObject()));
}

void ZenChan::FreeTrapped(glm::vec2 position)
{
	SetEnemyState(std::make_unique<ZenChanFall>(GetGameObject()));

	GetGameObject()->GetTransform().SetWorldPosition(position);
}

void ZenChan::SetDead(glm::vec2 position)
{
	SetEnemyState(std::make_unique<ZenChanDeath>(GetGameObject()));

	GetGameObject()->GetTransform().SetWorldPosition(position);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

