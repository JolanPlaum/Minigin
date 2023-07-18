//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "SoundSystem.h"
#include "ServiceLocator.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdexcept>
#include <unordered_map>
#include <glm/glm.hpp>
#include "RingBuffer.h"
#include "AudioChunk.h"
#include "ResourceManager.h"

using namespace dae;

std::unique_ptr<ISoundSystem> Locator::m_pSoundSystem{ std::make_unique<NullSoundSystem>() };


class SDLSoundSystem::SDLSoundSystemImpl final
{
	struct Sound
	{
		Sound() {}
		Sound(unsigned int id, float volume) : Id{ id }, Volume { volume } {}
		Sound(const std::string& path, float volume) : Volume { volume }, Path{ path } {}

		unsigned int Id = UINT_MAX;
		float Volume = 0.f;
		std::string Path = "";
	};

	RingBuffer<Sound> m_SoundQueue{ MIX_CHANNELS };
	std::unordered_map<unsigned int, std::shared_ptr<AudioChunk>> m_AudioClips{};
	std::vector<std::shared_ptr<AudioChunk>> m_ActiveAudio{ static_cast<size_t>(MIX_CHANNELS), nullptr };

public:
	SDLSoundSystemImpl()
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096) < 0)
		{
			throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + Mix_GetError());
		}
	}
	~SDLSoundSystemImpl()
	{
		Mix_CloseAudio();
		Mix_Quit();
	}

	void Play(unsigned int id, float volume)
	{
		// Check if ID is valid
		if (!m_AudioClips.contains(id)) return;

		// Add sound to queue
		m_SoundQueue.PushBack({ id, volume });
	}

	void Play(const std::string& path, float volume)
	{
		// Add sound to queue
		m_SoundQueue.PushBack({ path, volume });
	}

	void MasterVolume(float volume)
	{
		Mix_MasterVolume(static_cast<int>(glm::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME));
	}

	void Update()
	{
		// Exit early if queue is empty
		if (m_SoundQueue.Pending() == 0) return;
		Sound sound{ m_SoundQueue.Front() };

		// Get sound and set volume
		std::shared_ptr<AudioChunk> pChunk{ nullptr };
		if (sound.Id == UINT_MAX)
		{
			pChunk = ResourceManager::GetInstance().LoadAudio(sound.Path);
		}
		else
		{
			pChunk = m_AudioClips[sound.Id];
		}
		pChunk->GetMixChunk()->volume = static_cast<Uint8>(glm::clamp(sound.Volume, 0.f, 1.f) * MIX_MAX_VOLUME);

		// Try playing sound and exit if none are available
		int channel = Mix_PlayChannel(-1, pChunk->GetMixChunk(), 0);
		if (channel == -1) return;

		// Keep shared pointer alive while sound is playing
		m_ActiveAudio[channel] = pChunk;

		// Remove front item from queue
		m_SoundQueue.PullFront();
	}

	void Load(const std::string& path, unsigned int id)
	{
		if (id == UINT_MAX) return;

		m_AudioClips[id] = ResourceManager::GetInstance().LoadAudio(path);
	}
};

SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = std::make_unique<SDLSoundSystemImpl>();
}

SDLSoundSystem::~SDLSoundSystem()
{
}

void SDLSoundSystem::Play(const unsigned int id, const float volume)
{
	m_pImpl->Play(id, volume);
}

void SDLSoundSystem::Play(const std::string& path, float volume)
{
	m_pImpl->Play(path, volume);
}

void SDLSoundSystem::MasterVolume(float volume)
{
	m_pImpl->MasterVolume(volume);
}

void SDLSoundSystem::Update()
{
	m_pImpl->Update();
}

void SDLSoundSystem::Load(const std::string& path, unsigned int id)
{
	m_pImpl->Load(path, id);
}
