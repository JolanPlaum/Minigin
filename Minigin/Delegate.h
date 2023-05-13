#pragma once
// Includes
#include <memory>
#include <functional>
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	template<typename... Args>
	class Delegate final
	{
		using DelegateFunction = std::function<void(Args...)>;
	public:
		// Constructors and Destructor
		explicit Delegate() = default;
		~Delegate() = default;
		
		// Copy and Move semantics
		Delegate(const Delegate& other)					;
		Delegate& operator=(const Delegate& other)		;
		Delegate(Delegate&& other) noexcept				= default;
		Delegate& operator=(Delegate&& other) noexcept	= default;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void BindFunction(const DelegateFunction& fn);
		void Unbind();

		void Execute(Args... args) const;
		void ExecuteIfBound(Args... args) const;
		bool IsBound() const;

		DelegateHandle GetHandle() const { return m_Handle; }
		
		
	private:
		// Member variables
		std::unique_ptr<DelegateFunction> m_pFunction{};
		DelegateHandle m_Handle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};


	//-----------------------------------------------------------------
	// Constructors
	//-----------------------------------------------------------------
	template<typename ...Args>
	inline Delegate<Args...>::Delegate(const Delegate& other)
		: m_pFunction{ std::make_unique<DelegateFunction>(*other.m_pFunction) }
		, m_Handle{ other.m_Handle }
	{
	}

	template<typename ...Args>
	inline Delegate<Args...>& Delegate<Args...>::operator=(const Delegate& other)
	{
		if (this == &other) return *this;

		m_pFunction = std::make_unique<DelegateFunction>(*other.m_pFunction);
		m_Handle = other.m_Handle;

		return *this;
	}


	//-----------------------------------------------------------------
	// Public Member Functions
	//-----------------------------------------------------------------
	template<typename... Args>
	inline void Delegate<Args...>::BindFunction(const DelegateFunction& fn)
	{
		if (fn)
		{
			m_pFunction = std::make_unique<DelegateFunction>(fn);
			m_Handle = DelegateHandle(true);
		}
		else
		{
			Unbind();
		}
	}

	template<typename... Args>
	inline void Delegate<Args...>::Unbind()
	{
		m_pFunction = nullptr;
		m_Handle.Reset();
	}

	template<typename... Args>
	inline void Delegate<Args...>::Execute(Args... args) const
	{
		(*m_pFunction)(args...);
	}

	template<typename... Args>
	inline void Delegate<Args...>::ExecuteIfBound(Args... args) const
	{
		if (IsBound())
		{
			Execute(args...);
		}
	}

	template<typename... Args>
	inline bool Delegate<Args...>::IsBound() const
	{
		return (m_Handle.IsValid() && m_pFunction && (*m_pFunction));
	}
}

