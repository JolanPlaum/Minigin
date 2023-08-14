//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CTextureRenderer.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Texture2D.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void CTextureRenderer::Render() const
{
	if (m_pTexture == nullptr) return;

	const auto& pos = GetGameObject()->GetTransform().GetWorldPosition();
	const auto& scale = GetGameObject()->GetTransform().GetWorldScale();
	const auto& size = m_pTexture->GetSize();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, size.x * scale.x, size.y * scale.y);
}

void CTextureRenderer::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

glm::ivec2 CTextureRenderer::GetSize() const
{
	if (m_pTexture) return m_pTexture->GetSize();
	else return {};
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

