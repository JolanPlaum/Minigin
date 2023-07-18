#pragma once
// Includes
#include <memory>
#include <string>

namespace dae
{
	// Class Forward Declarations
	class AudioChunk;
	
	// Class Declaration
	class ISoundSystem
	{
	public:
		// Constructors and Destructor
		explicit ISoundSystem() = default;
		virtual ~ISoundSystem() = default;
		
		// Copy and Move semantics
		ISoundSystem(const ISoundSystem& other)					= delete;
		ISoundSystem& operator=(const ISoundSystem& other)		= delete;
		ISoundSystem(ISoundSystem&& other) noexcept				= delete;
		ISoundSystem& operator=(ISoundSystem&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		virtual void Play(unsigned int id, float volume) = 0;
		virtual void Play(const std::string& path, float volume) = 0;
		virtual void MasterVolume(float volume) = 0;
		virtual void Update() = 0;
		virtual void Load(const std::string& path, unsigned int id) = 0;
		
		
	private:
		// Member variables
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	class NullSoundSystem final : public ISoundSystem
	{
	public:
		void Play(unsigned int, float) override {};
		void Play(const std::string&, float) override {};
		void MasterVolume(float) override {};
		void Update() override {};
		void Load(const std::string&, unsigned int) override {};
	};

	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(unsigned int id, float volume) override;
		void Play(const std::string& path, float volume) override;
		void MasterVolume(float volume) override;
		void Update() override;
		void Load(const std::string& path, unsigned int id) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}

