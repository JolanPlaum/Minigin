#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class Locator final
	{
	public:
		static ISoundSystem& GetSoundSystem() { return *m_pSoundSystem; }
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pService) {
			m_pSoundSystem = (pService == nullptr) ? std::make_unique<NullSoundSystem>() : std::move(pService);
		}

	private:
		static std::unique_ptr<ISoundSystem> m_pSoundSystem;

		Locator() = default;
		~Locator() = default;

		Locator(const Locator& other) = delete;
		Locator(Locator&& other) = delete;
		Locator& operator=(const Locator& other) = delete;
		Locator& operator=(Locator&& other) = delete;
	};
}