#pragma once
// Includes
#include "Command.h"
#include <glm/vec2.hpp>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class SetSpriteIdxCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit SetSpriteIdxCommand(GameObject* pGameObject, bool isColIdx, int idx);
		~SetSpriteIdxCommand() = default;
		
		// Copy and Move semantics
		SetSpriteIdxCommand(const SetSpriteIdxCommand& other)					= delete;
		SetSpriteIdxCommand& operator=(const SetSpriteIdxCommand& other)		= delete;
		SetSpriteIdxCommand(SetSpriteIdxCommand&& other) noexcept				= delete;
		SetSpriteIdxCommand& operator=(SetSpriteIdxCommand&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override;
		
		
	private:
		// Member variables
		bool m_IsColIdx;
		int m_Idx;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};

	// Class Declaration
	class PauseSpriteCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit PauseSpriteCommand(GameObject* pGameObject, float time = FLT_MAX);
		explicit PauseSpriteCommand(GameObject* pGameObject, bool isPlayCommand, float time = FLT_MAX);
		~PauseSpriteCommand() = default;

		// Copy and Move semantics
		PauseSpriteCommand(const PauseSpriteCommand& other)					= delete;
		PauseSpriteCommand& operator=(const PauseSpriteCommand& other)		= delete;
		PauseSpriteCommand(PauseSpriteCommand&& other) noexcept				= delete;
		PauseSpriteCommand& operator=(PauseSpriteCommand&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override;


	private:
		// Member variables
		bool m_IsPlayCommand;
		float m_Time;

		//---------------------------
		// Private Member Functions
		//---------------------------

	};
}

