#pragma once
// Includes
#include "Component.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	class Transform;
	class CTexture;
	
	// Class Declaration
	class CTextureRenderer : public RenderComponent
	{
	public:
		// Constructors and Destructor
		CTextureRenderer() = default;
		virtual ~CTextureRenderer() = default;
		
		// Copy and Move semantics
		CTextureRenderer(const CTextureRenderer& other)					= delete;
		CTextureRenderer& operator=(const CTextureRenderer& other)		= delete;
		CTextureRenderer(CTextureRenderer&& other) noexcept				= delete;
		CTextureRenderer& operator=(CTextureRenderer&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void Render() const override;
	
	
	private:
		// Member variables
		std::weak_ptr<Transform> m_Transform{};
		std::weak_ptr<CTexture> m_TextureComponent{};
	
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

