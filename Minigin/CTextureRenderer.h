#pragma once
// Includes
#include "Component.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	class Transform;
	class Texture2D;
	
	// Class Declaration
	class CTextureRenderer : public Component
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

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		
		
	private:
		// Member variables
		std::weak_ptr<Transform> m_Transform{};
		std::shared_ptr<Texture2D> m_pTexture{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

