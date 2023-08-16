#pragma once
// Includes
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	// Class Forward Declarations
	class Texture2D;
	class Font;
	class AudioChunk;

	// Class Declaration
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		// Constructors and Destructor
		~ResourceManager() = default;

		// Copy and Move semantics
		ResourceManager(const ResourceManager& other)					= delete;
		ResourceManager& operator=(const ResourceManager& other)		= delete;
		ResourceManager(ResourceManager&& other) noexcept				= delete;
		ResourceManager& operator=(ResourceManager&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init(const std::string& data);

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::shared_ptr<AudioChunk> LoadAudio(const std::string& file) const;


	private:
		// Member variables
		std::string m_DataPath{};

		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	};
}
