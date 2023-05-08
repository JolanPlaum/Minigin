#pragma once
// Includes
#include <vector>
#include <memory>
#include <functional>
#include "Events.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Observer final
	{
	public:
		// Constructors and Destructor
		explicit Observer() = default;
		~Observer() = default;
		
		// Copy and Move semantics
		Observer(const Observer& other)					= delete;
		Observer& operator=(const Observer& other)		= delete;
		Observer(Observer&& other) noexcept				= delete;
		Observer& operator=(Observer&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		template<typename DataType> void Notify(EventType e, DataType d);
		template<typename DataType> void AddEventFunction(EventType e, const std::function<void(DataType)>& fn);
		
		
	private:
		// Member variables
		class IFunctionField;
		using EventFunction = std::pair<EventType, std::unique_ptr<IFunctionField>>;
		std::vector<EventFunction> m_EventFunction;

		class IFunctionField
		{
		public:
			IFunctionField() = default;
			virtual ~IFunctionField() = default;
		};

		template<typename DataType>
		class FunctionField final : public IFunctionField
		{
		public:
			explicit FunctionField(const std::function<void(DataType)>& fn) 
				: m_Function(fn) 
			{
			}

			void operator()(DataType data) { if (m_Function) m_Function(data); }

		private:
			std::function<void(DataType)> m_Function;
		};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	template<typename DataType>
	inline void Observer::Notify(EventType e, DataType d)
	{
		for (const EventFunction& eventFunction : m_EventFunction)
		{
			if (eventFunction.first == e)
			{
				auto funcPtr = dynamic_cast<FunctionField<DataType>*>(eventFunction.second.get());
				if (funcPtr != nullptr)
				{
					(*funcPtr)(d);
				}
			}
		}
	}

	template<typename DataType>
	inline void Observer::AddEventFunction(EventType e, const std::function<void(DataType)>& fn)
	{
		m_EventFunction.emplace_back(e, std::make_unique<FunctionField<DataType>>(fn));
	}
}

