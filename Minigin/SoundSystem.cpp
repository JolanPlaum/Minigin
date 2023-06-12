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
	RingBuffer<Mix_Chunk*> m_ClipsQueue{ MIX_CHANNELS };
	std::unordered_map<unsigned int, std::shared_ptr<AudioChunk>> m_AudioClips{};

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
		if (m_AudioClips.find(id) == m_AudioClips.end()) return;

		// Add chunk to queue with altered volume
		Mix_Chunk* pChunk = m_AudioClips[id]->GetMixChunk();
		pChunk->volume = static_cast<Uint8>(glm::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME);
		m_ClipsQueue.PushBack(pChunk);
	}

	void MasterVolume(float volume)
	{
		Mix_MasterVolume(static_cast<int>(glm::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME));
	}

	void Update()
	{
		// Exit early if queue is empty
		if (m_ClipsQueue.Pending() == 0) return;

		// Try playing sound and exit if none are available
		int channel = Mix_PlayChannel(-1, m_ClipsQueue.Front(), 0);
		if (channel == -1) return;

		// Remove front item from queue
		m_ClipsQueue.PullFront();
	}

	void Load(const std::string& path, unsigned int id)
	{
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
