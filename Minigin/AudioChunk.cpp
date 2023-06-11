//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "AudioChunk.h"
#include <SDL_mixer.h>
#include <stdexcept>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
AudioChunk::AudioChunk(const std::string& fullPath)
{
	m_pChunk = Mix_LoadWAV(fullPath.c_str());
	if (m_pChunk == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load WAV: ") + SDL_GetError());
	}
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
AudioChunk::~AudioChunk()
{
	Mix_FreeChunk(m_pChunk);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
Mix_Chunk* AudioChunk::GetMixChunk() const
{
	return m_pChunk;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

