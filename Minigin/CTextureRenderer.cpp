//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CTextureRenderer.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void CTextureRenderer::Init()
{
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void CTextureRenderer::Render() const
{
	const auto& pos = GetGameObject()->GetTransform().GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void CTextureRenderer::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

