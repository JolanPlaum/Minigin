//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CTextureRenderer.h"
#include "Renderer.h"
#include "Transform.h"
#include "CTexture.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void CTextureRenderer::Init()
{
	m_Transform = GetGameObject()->GetComponent<Transform>();
	m_TextureComponent = GetGameObject()->GetComponent<CTexture>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void CTextureRenderer::Render() const
{
	if (!m_TextureComponent.expired())
	{
		const auto& pos = m_Transform.lock()->GetPosition();
		Renderer::GetInstance().RenderTexture(m_TextureComponent.lock()->GetTexture(), pos.x, pos.y);
	}
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

