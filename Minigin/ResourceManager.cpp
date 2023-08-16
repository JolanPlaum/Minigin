//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "AudioChunk.h"
#include "Sprite2D.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
std::shared_ptr<Sprite2D> ResourceManager::LoadSprite(const std::string& file)
{
	if (auto it = m_Sprites.find(file); it != m_Sprites.end()) return it->second;

	unsigned int cols{ UINT_MAX }, rows{ UINT_MAX };
	std::vector<std::pair<unsigned int, std::string>> colNames, rowNames, tileNames;
	if (std::ifstream input{ m_DataPath + file + ".sprite" }; input.is_open())
	{
		while (!input.eof())
		{
			std::string str{};
			std::getline(input >> std::ws, str, ':');
			input >> std::ws;
			
			if (str == "nrCols")
			{
				input >> cols;
			}
			else if (str == "nrRows")
			{
				input >> rows;
			}
			else if (str == "columns")
			{
				colNames = ReadIdxNameArray(input);
			}
			else if (str == "rows")
			{
				rowNames = ReadIdxNameArray(input);
			}
			else if (str == "tiles")
			{
				tileNames = ReadIdxNameArray(input);
			}
			else
			{
				input.ignore();
			}

			// Make sure to start at new line
			input >> std::ws;
		}

		input.close();
	}

	if (cols == UINT_MAX || rows == UINT_MAX)
	{
		throw std::runtime_error(std::string("Failed to load sprite: Data was not correctly read in from .sprite file"));
	}

	auto pSprite = std::make_shared<Sprite2D>(LoadTexture(file), cols, rows);
	for (const auto& idxName : colNames) pSprite->SetColName(idxName.first, idxName.second);
	for (const auto& idxName : rowNames) pSprite->SetRowName(idxName.first, idxName.second);
	for (const auto& idxName : tileNames) pSprite->SetTileName(idxName.first, idxName.second);
	m_Sprites[file] = pSprite;

	return pSprite;
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

std::shared_ptr<AudioChunk> ResourceManager::LoadAudio(const std::string& file) const
{
	return std::make_shared<AudioChunk>(m_DataPath + file);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
std::vector<std::pair<unsigned int, std::string>> ResourceManager::ReadIdxNameArray(std::ifstream& input) const
{
	std::vector<std::pair<unsigned int, std::string>> idxNames{};

	if (input.peek() == '[')
	{
		std::string str{};
		std::getline(input, str, '\n');
	}
	else
	{
		while (input.peek() == '-')
		{
			input.ignore();

			std::string str{};
			std::pair<unsigned int, std::string> idxName{ UINT_MAX, "" };

			if (std::getline(input >> std::ws, str, ':'); str == "index") input >> idxName.first;
			if (std::getline(input >> std::ws, str, ':'); str == "name") input >> idxName.second;

			if (idxName.first != UINT_MAX && !idxName.second.empty())
			{
				idxNames.emplace_back(std::move(idxName));
			}

			input >> std::ws;
		}
	}

	return idxNames;
}

