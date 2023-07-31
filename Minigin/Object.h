#pragma once
// Includes

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Object
	{
	public:
		// Constructors and Destructor
		Object() = default;
		virtual ~Object() = default;
		
		// Copy and Move semantics
		Object(const Object& other)					= delete;
		Object& operator=(const Object& other)		= delete;
		Object(Object&& other) noexcept				= delete;
		Object& operator=(Object&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Destroy();
		virtual void OnDestroy() = 0;

		bool IsDestroyed() const { return m_IsDestroyed; }
		
		
	private:
		// Member variables
		bool m_IsDestroyed{ false };
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

