#pragma once
// Includes
#include "Component.h"
#include <memory>
#include <string>
#include "Event.h"

namespace dae
{
	// Class Forward Declarations
	class Sprite2D;
	enum class SpriteRenderSettings : unsigned char
	{
		IterateNone		= 0x00,
		IterateColumn	= 0x01,
		IterateRow		= 0x02,
		
		PrioritizeRow	= 0x04,
	};
	
	// Class Declaration
	class CSpriteRenderer final : public Component
	{
	public:
		// Constructors and Destructor
		CSpriteRenderer(GameObject* pGameObject) :Component(pGameObject) {};
		~CSpriteRenderer() = default;
		
		// Copy and Move semantics
		CSpriteRenderer(const CSpriteRenderer& other)					= delete;
		CSpriteRenderer& operator=(const CSpriteRenderer& other)		= delete;
		CSpriteRenderer(CSpriteRenderer&& other) noexcept				= delete;
		CSpriteRenderer& operator=(CSpriteRenderer&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update() override;
		void Render() const override;

		void Lock();
		void Unlock();
		void Pause(float time = FLT_MAX);
		void Play();
		void Restart();

		void SetSprite(std::shared_ptr<Sprite2D> pSprite, float secondsPerFrame);
		void SetSettings(SpriteRenderSettings settings);
		void SetColIdx(unsigned int idx);
		void SetColIdx(const std::string& name);
		void SetRowIdx(unsigned int idx);
		void SetRowIdx(const std::string& name);

		Event<> Restarted{};
		Event<> AnimationLooped{}; //todo: add the amount of loops as a parameter
		
		
	private:
		// Member variables
		bool m_IsLocked{};
		bool m_IsPaused{};
		SpriteRenderSettings m_Settings{ DefaultSettings()};

		unsigned int m_ColIdx{};
		unsigned int m_RowIdx{};

		float m_AccuSec{};
		float m_SecPerFrame{};
		float m_LockedSecPerFrame{};

		std::shared_ptr<Sprite2D> m_pSprite{};
		std::shared_ptr<Sprite2D> m_pLockedSprite{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		constexpr SpriteRenderSettings DefaultSettings() const;

		void UpdateFrame();
		bool UpdateCol();
		bool UpdateRow();
		
	};
}

