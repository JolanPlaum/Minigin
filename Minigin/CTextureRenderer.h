#pragma once
// Includes
#include "Component.h"
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	// Class Forward Declarations
	class Texture2D;
	
	// Class Declaration
	class CTextureRenderer final : public Component
	{
	public:
		// Constructors and Destructor
		CTextureRenderer(GameObject* pGameObject) :Component(pGameObject) {};
		~CTextureRenderer() = default;
		
		// Copy and Move semantics
		CTextureRenderer(const CTextureRenderer& other)					= delete;
		CTextureRenderer& operator=(const CTextureRenderer& other)		= delete;
		CTextureRenderer(CTextureRenderer&& other) noexcept				= delete;
		CTextureRenderer& operator=(CTextureRenderer&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);

		glm::ivec2 GetSize() const;
		
		
	private:
		// Member variables
		std::shared_ptr<Texture2D> m_pTexture{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

