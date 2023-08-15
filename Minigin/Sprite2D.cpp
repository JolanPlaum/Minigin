//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Sprite2D.h"
#include "Texture2D.h"

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

	for (unsigned int i{}; i < m_RowNames.size(); ++i)
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
	m_TileSize.x = textureSize.x / GetNrCols();
	m_TileSize.y = textureSize.y / GetNrRows();
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

void Sprite2D::SetRowName(unsigned int idx, const std::string& name)
{
	if (idx >= GetNrRows()) return;
	if (std::find(m_RowNames.begin(), m_RowNames.end(), name) != m_RowNames.end()) return;

	m_RowNames[idx] = name;
}

void Sprite2D::SetTileName(unsigned int idx, const std::string& name)
{
	if (idx >= GetNrCols() * GetNrRows()) return;
	if (m_TileNames.find(name) != m_TileNames.end()) return;

	auto it = std::find_if(m_TileNames.begin(), m_TileNames.end(), [idx](const std::pair<std::string, unsigned int>& tileName)
		{
			return tileName.second == idx;
		});
	if (it != m_TileNames.end()) m_TileNames.erase(it);
	m_TileNames[name] = idx;
}

void Sprite2D::SetTileName(unsigned int colIdx, unsigned int rowIdx, const std::string& name)
{
	if (colIdx >= GetNrCols() || rowIdx >= GetNrRows()) return;

	SetTileName(ColRowToTile(colIdx, rowIdx) , name);
}

unsigned int Sprite2D::GetColIdx(const std::string& name) const
{
	for (unsigned int i{}; i < m_ColNames.size(); ++i)
	{
		if (m_ColNames[i] == name) return i;
	}

	return UINT_MAX;
}

unsigned int Sprite2D::GetRowIdx(const std::string& name) const
{
	for (unsigned int i{}; i < m_RowNames.size(); ++i)
	{
		if (m_RowNames[i] == name) return i;
	}

	return UINT_MAX;
}

unsigned int Sprite2D::GetTileIdx(const std::string& name) const
{
	auto it = m_TileNames.find(name);

	if (it == m_TileNames.end()) return UINT_MAX;
	else return it->second;
}

Rectangle Sprite2D::GetSrcRect(unsigned int colIdx, unsigned int rowIdx) const
{
	if (colIdx == UINT_MAX || rowIdx == UINT_MAX) return {};

	colIdx %= GetNrCols();
	rowIdx %= GetNrRows();

	Rectangle srcRect{};
	srcRect.x = static_cast<float>(colIdx * m_TileSize.x);
	srcRect.y = static_cast<float>(rowIdx * m_TileSize.y);
	srcRect.w = static_cast<float>(m_TileSize.x);
	srcRect.h = static_cast<float>(m_TileSize.y);

	return srcRect;
}

Rectangle Sprite2D::GetSrcRect(unsigned int idx) const
{
	return GetSrcRect(TileToCol(idx), TileToRow(idx));
}

Rectangle Sprite2D::GetSrcRect(const std::string& colName, const std::string& rowName) const
{
	return GetSrcRect(GetColIdx(colName), GetRowIdx(rowName));
}

Rectangle Sprite2D::GetSrcRect(const std::string& tileName) const
{
	return GetSrcRect(GetTileIdx(tileName));
}

unsigned int Sprite2D::TileToCol(unsigned int idx) const
{
	if (idx == UINT_MAX) return idx;
	return idx % GetNrCols();
}

unsigned int Sprite2D::TileToRow(unsigned int idx) const
{
	if (idx == UINT_MAX) return idx;
	return idx / GetNrCols();
}

unsigned int Sprite2D::ColRowToTile(unsigned int colIdx, unsigned int rowIdx) const
{
	if (colIdx == UINT_MAX || rowIdx >= UINT_MAX) return UINT_MAX;
	return colIdx + rowIdx * GetNrCols();
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

