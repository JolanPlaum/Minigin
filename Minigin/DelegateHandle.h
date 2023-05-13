#pragma once
// Includes

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class DelegateHandle final
	{
	public:
		// Constructors and Destructor
		explicit DelegateHandle();
		explicit DelegateHandle(bool generateNewID); // should only be called by Delegate, not by user
		~DelegateHandle() = default;
		
		// Copy and Move semantics
		DelegateHandle(const DelegateHandle& other)					= default;
		DelegateHandle& operator=(const DelegateHandle& other)		= default;
		DelegateHandle(DelegateHandle&& other) noexcept				= default;
		DelegateHandle& operator=(DelegateHandle&& other) noexcept	= default;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Reset();
		bool IsValid() const;

		bool operator==(const DelegateHandle& rh);
		bool operator!=(const DelegateHandle& rh);
		
		
	private:
		// Member variables
		unsigned long long m_ID;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		unsigned long long GenerateNewID();
		
	};
}

