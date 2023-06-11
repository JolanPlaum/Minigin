#pragma once
// Includes
#include <vector>
#include <cassert>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	template <typename T>
	class RingBuffer final
	{
	public:
		// Constructors and Destructor
		explicit RingBuffer() = default;
		explicit RingBuffer(int size) { m_Array.resize(size); }
		~RingBuffer() = default;
		
		// Copy and Move semantics
		RingBuffer(const RingBuffer& other)					= delete;
		RingBuffer& operator=(const RingBuffer& other)		= delete;
		RingBuffer(RingBuffer&& other) noexcept				= delete;
		RingBuffer& operator=(RingBuffer&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		const T& Front();
		const T& PullFront();
		T& PushBack();
		void PushBack(const T& value);
		
		size_t Pending() { return (m_Head > m_Tail) ? (MaxPending() - m_Head + m_Tail) : (m_Tail - m_Head); }
		size_t MaxPending() { return m_Array.size(); }

		
	private:
		// Member variables
		std::vector<T> m_Array{};
		size_t m_Head{ 0 };
		size_t m_Tail{ 0 };
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	template<typename T>
	inline const T& RingBuffer<T>::Front()
	{
		// Check if there is anything pending
		assert(m_Head != m_Tail && "Make sure that the buffer isn't empty");

		return m_Array[m_Head];
	}

	template<typename T>
	const T& RingBuffer<T>::PullFront()
	{
		// Check if there is anything pending
		assert(m_Head != m_Tail && "Make sure to only pull when the buffer isn't empty");

		// Temporarily store the returned value
		const T& value = m_Array[m_Head];

		// Update the head to the next spot
		++m_Head %= MaxPending();

		return value;
	}

	template<typename T>
	inline T& RingBuffer<T>::PushBack()
	{
		// Resize if max pending is reached
		if (((m_Tail + 1) % MaxPending()) == m_Head)
		{
			std::vector<T> tempArray{ m_Array.begin() + m_Head, m_Array.end() };
			if (m_Head != 0)
			{
				tempArray.insert(tempArray.end(), m_Array.begin(), m_Array.begin() + m_Tail);
				m_Head = 0;
				m_Tail = tempArray.size();
			}

			tempArray.resize(m_Array.size() * 2);
			m_Array = tempArray;
		}

		// Temporarily store the value to the buffer
		T& value = m_Array[m_Tail];

		// Update the tail
		++m_Tail %= MaxPending();

		return value;
	}

	template<typename T>
	void RingBuffer<T>::PushBack(const T& value)
	{
		// Add the value to the buffer
		PushBack() = value;
	}
}

