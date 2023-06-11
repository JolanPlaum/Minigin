#pragma once
// Includes
#include <string>

struct Mix_Chunk;
namespace dae
{
	/**
	 * Simple RAII wrapper for an Mix_Chunk
	 */
	class AudioChunk final
	{
	public:
		// Constructors and Destructor
		explicit AudioChunk(const std::string& fullPath);
		~AudioChunk();
		
		// Copy and Move semantics
		AudioChunk(const AudioChunk& other)					= delete;
		AudioChunk& operator=(const AudioChunk& other)		= delete;
		AudioChunk(AudioChunk&& other) noexcept				= delete;
		AudioChunk& operator=(AudioChunk&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		Mix_Chunk* GetMixChunk() const;
		
		
	private:
		// Member variables
		Mix_Chunk* m_pChunk;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

