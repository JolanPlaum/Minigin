//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Sprite2D.h"
#include "Texture2D.h"
#include <glm/vec2.hpp>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
Sprite2D::Sprite2D(std::shared_ptr<Texture2D> pTexture, unsigned int cols, unsigned int rows)
	: Sprite2D(pTexture, std::vector<std::string>{cols}, std::vector<std::string>{rows})
{
	for (unsigned int i{}; i < m_ColNames.size(); ++i)
	{
		m_ColNames[i] = std::to_string(i);
	}

	for (unsigned int i{}; i < m_ColNames.size(); ++i)
	{
		m_RowNames[i] = std::to_string(i);
	}
}

Sprite2D::Sprite2D(std::shared_ptr<Texture2D> pTexture, std::vector<std::string> colNames, std::vector<std::string> rowNames)
	: m_pTexture{ pTexture }
	, m_ColNames{ colNames }
	, m_RowNames{ rowNames }
{
	const glm::ivec2& textureSize{ m_pTexture->GetSize() };
	m_TileWidth = textureSize.x / GetNrCols();
	m_TileHeight = textureSize.y / GetNrRows();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Sprite2D::SetColName(unsigned int idx, const std::string& name)
{
	if (idx >= GetNrCols()) return;
	if (std::find(m_ColNames.begin(), m_ColNames.end(), name) != m_ColNames.end()) return;

	m_ColNames[idx] = name;
}

void Sprite2D::SetRowNames(unsigned int idx, const std::string& name)
{
	if (idx >= GetNrRows()) return;
	if (std::find(m_RowNames.begin(), m_RowNames.end(), name) != m_RowNames.end()) return;

	m_RowNames[idx] = name;
}

int Sprite2D::GetColIdx(const std::string& name) const
{
	for (int i{}; i < m_ColNames.size(); ++i)
	{
		if (m_ColNames[i] == name) return i;
	}

	return -1;
}

int Sprite2D::GetRowIdx(const std::string& name) const
{
	for (int i{}; i < m_RowNames.size(); ++i)
	{
		if (m_RowNames[i] == name) return i;
	}

	return -1;
}

Rectangle Sprite2D::GetSrcRect(unsigned int colIdx, unsigned int rowIdx) const
{
	if (colIdx < 0 || rowIdx < 0) return {};

	Rectangle srcRect{};
	srcRect.x = static_cast<float>(colIdx * m_TileWidth);
	srcRect.y = static_cast<float>(rowIdx * m_TileHeight);
	srcRect.w = static_cast<float>(m_TileWidth);
	srcRect.h = static_cast<float>(m_TileHeight);

	return srcRect;
}

Rectangle Sprite2D::GetSrcRect(unsigned int idx) const
{
	return GetSrcRect(idx % GetNrCols(), idx / GetNrCols());
}

Rectangle Sprite2D::GetSrcRect(const std::string& colName, const std::string& rowName) const
{
	return GetSrcRect(GetColIdx(colName), GetRowIdx(rowName));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

