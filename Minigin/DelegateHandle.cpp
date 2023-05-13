//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "DelegateHandle.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
DelegateHandle::DelegateHandle()
	: DelegateHandle(false)
{
}

DelegateHandle::DelegateHandle(bool generateNewID)
	: m_ID{ 0 }
{
	m_ID = generateNewID ? GenerateNewID() : 0;
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void DelegateHandle::Reset()
{
	m_ID = 0;
}

bool DelegateHandle::IsValid() const
{
	return m_ID != 0;
}

bool DelegateHandle::operator==(const DelegateHandle& rh)
{
	return m_ID == rh.m_ID;
}
bool DelegateHandle::operator!=(const DelegateHandle& rh)
{
	return m_ID != rh.m_ID;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
unsigned long long DelegateHandle::GenerateNewID()
{
	static unsigned long long nextID = 0;

	return ++nextID;
}

