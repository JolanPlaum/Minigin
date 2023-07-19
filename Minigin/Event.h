#pragma once
// Includes
#include <vector>
#include <functional>
#include "Delegate.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	template<typename... Args>
	class Event final
	{
	public:
		// Constructors and Destructor
		explicit Event() = default;
		~Event() { Clear(); }
		
		// Copy and Move semantics
		Event(const Event& other)					= delete;
		Event& operator=(const Event& other)		= delete;
		Event(Event&& other) noexcept				= delete;
		Event& operator=(Event&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		DelegateHandle Add(const Delegate<Args...>& delegate); // Temporarily not usable outside of event class
		DelegateHandle AddFunction(const std::function<void(Args...)>& fn);
		void Remove(DelegateHandle handle);

		void Notify(Args... args);
		void Clear();
		
	private:
		// Member variables
		std::vector<Delegate<Args...>> m_Delegates{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	template<typename... Args>
	inline DelegateHandle Event<Args...>::Add(const Delegate<Args...>& delegate)
	{
		DelegateHandle temp{};
		if (delegate.IsBound())
		{
			m_Delegates.push_back(delegate);
			temp = delegate.GetHandle();
		}
		return temp;
	}

	template<typename... Args>
	inline DelegateHandle Event<Args...>::AddFunction(const std::function<void(Args...)>& fn)
	{
		Delegate<Args...> temp{};
		temp.BindFunction(fn);
		return Add(temp);
	}

	template<typename... Args>
	inline void Event<Args...>::Remove(DelegateHandle handle)
	{
		if (!handle.IsValid()) return;

		std::erase_if(m_Delegates, [handle](const Delegate<Args...>& d) {
			return d.GetHandle() == handle;
			});
	}

	template<typename... Args>
	inline void Event<Args...>::Notify(Args... args)
	{
		for (const Delegate<Args...>& delg : m_Delegates)
		{
			delg.ExecuteIfBound(args...);
		}
	}

	template<typename... Args>
	inline void Event<Args...>::Clear()
	{
		for (Delegate<Args...>& delg : m_Delegates)
		{
			delg.Unbind();
		}

		m_Delegates.clear();
	}
}

