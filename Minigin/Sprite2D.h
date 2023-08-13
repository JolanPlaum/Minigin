#pragma once
// Includes
#include <memory>
#include <string>
#include <vector>
#include "Rectangle.h"

namespace dae
{
	// Class Forward Declarations
	class Texture2D;
	
	// Class Declaration
	class Sprite2D final
	{
	public:
		// Constructors and Destructor
		explicit Sprite2D(std::shared_ptr<Texture2D> pTexture, unsigned int cols, unsigned int rows);
		explicit Sprite2D(std::shared_ptr<Texture2D> pTexture, std::vector<std::string> colNames, std::vector<std::string> rowNames);
		~Sprite2D() = default;
		
		// Copy and Move semantics
		Sprite2D(const Sprite2D& other)					= default;
		Sprite2D& operator=(const Sprite2D& other)		= default;
		Sprite2D(Sprite2D&& other) noexcept				= default;
		Sprite2D& operator=(Sprite2D&& other) noexcept	= default;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void SetColName(unsigned int idx, const std::string& name);
		void SetRowNames(unsigned int idx, const std::string& name);

		Texture2D* GetTexture() const { return m_pTexture.get(); }
		unsigned int GetNrCols() const { return static_cast<unsigned int>(m_ColNames.size()); }
		unsigned int GetNrRows() const { return static_cast<unsigned int>(m_RowNames.size()); }

		int GetColIdx(const std::string& name) const;
		int GetRowIdx(const std::string& name) const;

		Rectangle GetSrcRect(unsigned int colIdx, unsigned int rowIdx) const;
		Rectangle GetSrcRect(unsigned int idx) const;
		Rectangle GetSrcRect(const std::string& colName, const std::string& rowName) const;
		
		
	private:
		// Member variables
		int m_TileWidth{};
		int m_TileHeight{};
		std::shared_ptr<Texture2D> m_pTexture{};

		std::vector<std::string> m_ColNames{};
		std::vector<std::string> m_RowNames{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

