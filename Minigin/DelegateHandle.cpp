//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "DelegateHandle.h"
#include <cassert>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
DelegateHandle::DelegateHandle()
	: DelegateHandle(false)
{
}

DelegateHandle::DelegateHandle(bool generateNewID)
	: m_pID{ std::make_shared<unsigned long long>() }
{
	(*m_pID) = generateNewID ? GenerateNewID() : 0;
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void DelegateHandle::Reset()
{
	(*m_pID) = 0;
}

bool DelegateHandle::IsValid() const
{
	return (*m_pID) != 0;
}

bool DelegateHandle::operator==(const DelegateHandle& rh)
{
	assert(!(m_pID != rh.m_pID && (*m_pID) == (*rh.m_pID)) && "ID's match up but they're not the same pointer.");
	return m_pID == rh.m_pID;
}
bool DelegateHandle::operator!=(const DelegateHandle& rh)
{
	assert(!(m_pID != rh.m_pID && (*m_pID) == (*rh.m_pID)) && "ID's match up but they're not the same pointer.");
	return m_pID != rh.m_pID;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
unsigned long long DelegateHandle::GenerateNewID()
{
	static unsigned long long nextID = 0;

	return ++nextID;
}

