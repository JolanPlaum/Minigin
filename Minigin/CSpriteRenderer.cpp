//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CSpriteRenderer.h"
#include "GameObject.h"
#include "Sprite2D.h"
#include "TimeManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "Texture2D.h"
#include "Rectangle.h"

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
void CSpriteRenderer::Update()
{
	float dt{ TimeManager::GetInstance().GetDeltaTime() };

	if (m_IsPaused)
	{
		m_AccuSec -= dt;

		if (m_AccuSec < 0.f) Play();
	}
	else if (m_pSprite && m_Settings != SpriteRenderSettings::IterateNone)
	{
		m_AccuSec += dt;

		if (m_AccuSec >= m_SecPerFrame)
		{
			m_AccuSec -= m_SecPerFrame;
			UpdateFrame();
		}
	}
}

void CSpriteRenderer::Render() const
{
	if (m_pSprite == nullptr) return;

	glm::vec2 pos = GetGameObject()->GetTransform().GetWorldPosition();
	glm::vec2 scale = GetGameObject()->GetTransform().GetWorldScale();
	glm::vec2 size = m_pSprite->GetTileSize();

	Rectangle dstRect{ pos.x, pos.y, size.x * scale.x, size.y * scale.y };
	Rectangle srcRect{ m_pSprite->GetSrcRect(m_ColIdx, m_RowIdx) };

	Renderer::GetInstance().RenderTexture(*m_pSprite->GetTexture(), dstRect, srcRect);
}

void CSpriteRenderer::Lock()
{
	m_IsLocked = true;
}
void CSpriteRenderer::Unlock()
{
	if (m_pLockedSprite)
	{
		m_pSprite = std::move(m_pLockedSprite);
		m_SecPerFrame = m_LockedSecPerFrame;

		Restart();
	}
	
	m_IsLocked = false;
}
void CSpriteRenderer::Pause(float time)
{
	m_IsPaused = true;
	m_AccuSec = time;
}
void CSpriteRenderer::Play()
{
	m_IsPaused = false;
	m_AccuSec = 0.f;

	UpdateFrame();

	Unpaused.Notify();
}
void CSpriteRenderer::Restart()
{
	if (!m_IsPaused) m_AccuSec = 0.f;

	if (static_cast<unsigned char>(m_Settings) & static_cast<unsigned char>(SpriteRenderSettings::IterateColumn))
	{
		m_ColIdx = 0;
	}

	if (static_cast<unsigned char>(m_Settings) & static_cast<unsigned char>(SpriteRenderSettings::IterateRow))
	{
		m_RowIdx = 0;
	}

	Restarted.Notify();
}

void CSpriteRenderer::SetSprite(std::shared_ptr<Sprite2D> pSprite, float secondsPerFrame)
{
	// Only lock the new sprite if there is an active sprite
	if (m_IsLocked && m_pSprite)
	{
		m_pLockedSprite = pSprite;
		m_LockedSecPerFrame = secondsPerFrame;
	}
	else
	{
		m_pLockedSprite = m_pSprite;
		m_LockedSecPerFrame = m_SecPerFrame;

		m_pSprite = pSprite;
		m_SecPerFrame = secondsPerFrame;

		Restart();
	}
}
void CSpriteRenderer::SetSettings(SpriteRenderSettings settings)
{
	m_Settings = settings;
}
void CSpriteRenderer::SetColIdx(unsigned int idx)
{
	m_ColIdx = idx;
}
void CSpriteRenderer::SetColIdx(const std::string& name)
{
	if (m_pSprite) SetColIdx(m_pSprite->GetColIdx(name));
}
void CSpriteRenderer::SetRowIdx(unsigned int idx)
{
	m_RowIdx = idx;
}
void CSpriteRenderer::SetRowIdx(const std::string& name)
{
	if (m_pSprite) SetRowIdx(m_pSprite->GetRowIdx(name));
}
void CSpriteRenderer::SetTileIdx(unsigned int idx)
{
	if (m_pSprite == nullptr) return;

	SetColIdx(m_pSprite->TileToCol(idx));
	SetRowIdx(m_pSprite->TileToRow(idx));
}
void CSpriteRenderer::SetTileIdx(const std::string& name)
{
	if (m_pSprite) SetTileIdx(m_pSprite->GetTileIdx(name));
}

glm::ivec2 CSpriteRenderer::GetSize() const
{
	if (m_pSprite) return m_pSprite->GetTileSize();
	else return {};
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void CSpriteRenderer::UpdateFrame()
{
	if (m_Settings == SpriteRenderSettings::IterateNone || m_pSprite == nullptr) return;

	if (static_cast<unsigned char>(m_Settings) & static_cast<unsigned char>(SpriteRenderSettings::PrioritizeRow))
	{
		if (UpdateRow())
		{
			if (UpdateCol())
			{
				AnimationLooped.Notify();
			}
		}
	}
	else
	{
		if (UpdateCol())
		{
			if (UpdateRow())
			{
				AnimationLooped.Notify();
			}
		}
	}
}
bool CSpriteRenderer::UpdateCol()
{
	// Return value indicates whether or not row has to update
	if (static_cast<unsigned char>(m_Settings) & static_cast<unsigned char>(SpriteRenderSettings::IterateColumn))
	{
		++m_ColIdx %= m_pSprite->GetNrCols();
		return m_ColIdx == 0;
	}
	return true;
}
bool CSpriteRenderer::UpdateRow()
{
	// Return value indicates whether or not column has to update
	if (static_cast<unsigned char>(m_Settings) & static_cast<unsigned char>(SpriteRenderSettings::IterateRow))
	{
		++m_RowIdx %= m_pSprite->GetNrRows();
		return m_RowIdx == 0;
	}
	return true;
}

