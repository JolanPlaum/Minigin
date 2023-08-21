//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Score.h"
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "Item.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void Score::Init()
{
	m_CollisionHandle = GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.AddFunction(
		std::bind(&Score::OnCollisionNotify, this, std::placeholders::_1));
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void Score::OnDestroy()
{
	if (m_CollisionHandle.IsValid())
		GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.Remove(m_CollisionHandle);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void Score::OnCollisionNotify(GameObject* pOther)
{
	if (pOther->GetTag() == "Item")
	{
		Item* item = pOther->GetComponent<Item>();

		if (item->GetName() == "Watermelon") AddScore(100);
		else if (item->GetName() == "FrenchFries") AddScore(200);

		pOther->Destroy();
	}
}

void Score::AddScore(int score)
{
	m_Score += score;

	ScoreChanged.Notify(score);
}

