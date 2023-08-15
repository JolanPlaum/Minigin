#pragma once
// Includes
#include "Command.h"
#include <glm/vec2.hpp>
#include <string>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class SetSpriteIdxCommand final : public GameObjectCommand
	{
	public:
		enum class Index
		{
			col,
			row,
			tile,
		};

		// Constructors and Destructor
		explicit SetSpriteIdxCommand(GameObject* pGameObject, Index indexType, int idx);
		explicit SetSpriteIdxCommand(GameObject* pGameObject, Index indexType, const std::string& name);
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
		bool m_IsUsingName;
		Index m_IndexType;
		int m_Idx;
		std::string m_Name;
		
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

