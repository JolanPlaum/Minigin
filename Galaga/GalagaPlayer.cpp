//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "GalagaPlayer.h"
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "Lives.h"
#include <iostream>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void GalagaPlayer::Init()
{
	m_CollisionHandle = GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.AddFunction(
		std::bind(&GalagaPlayer::OnCollisionNotify, this, std::placeholders::_1)
	);

	m_pLivesComp = GetGameObject()->GetComponent<Lives>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void GalagaPlayer::OnDestroy()
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
void GalagaPlayer::OnCollisionNotify(GameObject* pOther) const
{
	if (pOther->GetTag() == "Enemy")
	{
		if (m_pLivesComp)
		{
			m_pLivesComp->Kill();
		}

		pOther->Destroy();
	}
}

