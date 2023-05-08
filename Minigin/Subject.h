#pragma once
// Includes
#include <vector>
#include "Observer.h"
#include "Events.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Subject final
	{
	public:
		// Constructors and Destructor
		explicit Subject() = default;
		~Subject() = default;
		
		// Copy and Move semantics
		Subject(const Subject& other)					= delete;
		Subject& operator=(const Subject& other)		= delete;
		Subject(Subject&& other) noexcept				= delete;
		Subject& operator=(Subject&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void AddObserver(Observer* pObserver) { m_Observers.push_back(pObserver); }
		void RemoveObserver(Observer* pObserver) { std::erase(m_Observers, pObserver); }

		template<typename DataType> void NotifyObservers(EventType e, DataType d);
		
		
	private:
		// Member variables
		std::vector<Observer*> m_Observers{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	template<typename DataType>
	inline void Subject::NotifyObservers(EventType e, DataType d)
	{
		for (Observer* pObserver : m_Observers)
		{
			pObserver->Notify<DataType>(e, d);
		}
	}
}

