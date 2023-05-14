#pragma once
// Includes
#include "Component.h"
#include <chrono>
#include <numeric>

namespace dae
{
	// Class Forward Declarations
	struct Transform3D
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};
	class GameObject3D
	{
	public:
		Transform3D transform{};
		int ID{ 1 };
		GameObject3D& operator*=(int id) {
			ID *= id;
			return *this;
		}
	};
	class GameObject3DAlt
	{
	public:
		Transform3D* pTransform{};
		int ID{ 1 };
		GameObject3DAlt& operator*=(int id) {
			ID *= id;
			return *this;
		}
	};
	
	// Class Declaration
	class TrashTheCache final : public Component
	{
	public:
		// Constructors and Destructor
		TrashTheCache(GameObject* pGameObject) :Component(pGameObject) {};
		~TrashTheCache() = default;
		
		// Copy and Move semantics
		TrashTheCache(const TrashTheCache& other)					= delete;
		TrashTheCache& operator=(const TrashTheCache& other)		= delete;
		TrashTheCache(TrashTheCache&& other) noexcept				= delete;
		TrashTheCache& operator=(TrashTheCache&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void Update() override;
		void UpdateGui() override;

		
	private:
		// Member variables
		const int m_MaxStepSize{ 1024 };
		const int m_BufferSize{ 10'000'000 };
		std::vector<float> m_TimeSteps{};
		//todo: if you have time left, make struct that holds data for each exercise
		//		for example: struct for button and struct for window

		//exercise 1
		std::string m_Ex1Name{ "Exercise 1" };
		int m_Ex1SampleCount{ 10 };

		int m_StepSizeInt{ 0 };
		std::string m_ButtonTextInt{ "Trash the cache" };
		std::vector<float> m_AveragesInt{};

		//exercise 2
		std::string m_Ex2Name{ "Exercise 2" };
		int m_Ex2SampleCount{ 100 };

		int m_StepSizeGameObject3D{ 0 };
		std::string m_ButtonTextGameObject3D{ "Trash the cache with GameObject3D" };
		std::vector<float> m_AveragesGameObject3D{};

		int m_StepSizeGameObject3DAlt{ 0 };
		std::string m_ButtonTextGameObject3DAlt{ "Trash the cache with GameObject3DAlt" };
		std::vector<float> m_AveragesGameObject3DAlt{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		template <typename T> void UpdateSample(int& currentStepSize, std::vector<float>& averages, int nrSamples);

		void GuiExercise1();
		void GuiExercise2();

	};

	template<typename T>
	inline void TrashTheCache::UpdateSample(int& currentStepSize, std::vector<float>& averages, int nrSamples)
	{
		// Skip if not sampling
		if (currentStepSize == 0)
			return;
		else if (currentStepSize == 1)
			averages.clear();

		// Iterate over the buffer in steps
		for (currentStepSize; currentStepSize <= m_MaxStepSize; currentStepSize)
		{
			// Allocate a large buffer
			std::vector<T> numbers{};
			numbers.resize(m_BufferSize);

			// Take multiple time samples
			std::vector<long long> tempTimes{};
			tempTimes.reserve(nrSamples);
			for (int count{}; count < nrSamples; ++count)
			{
				auto start = std::chrono::high_resolution_clock::now();

				for (unsigned int i{}; i < numbers.size(); i += currentStepSize) numbers[i] *= 2;

				auto end = std::chrono::high_resolution_clock::now();

				// Add sampled elapsed time to the list
				tempTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
			}

			// Remove 10% of the higest and 10% of the lowest values
			const int amountToRemove{ nrSamples / 10 };
			std::sort(tempTimes.begin(), tempTimes.end());
			long long totalTime = std::accumulate(tempTimes.begin() + amountToRemove, tempTimes.end() - amountToRemove, static_cast<long long>(0));

			// Caluclate average time it took
			float average{ totalTime / static_cast<float>(nrSamples - amountToRemove - amountToRemove) };

			// Add result
			averages.push_back(average / 1000.f);
			currentStepSize *= 2;
			return;
		}

		// Reset some values
		currentStepSize = 0;
	}
}

