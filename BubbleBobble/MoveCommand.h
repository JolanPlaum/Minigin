#pragma once
// Includes
#include "Command.h"
#include <glm/vec2.hpp>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class MoveCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit MoveCommand(GameObject* pGameObject, glm::vec2 direction, float speed);
		~MoveCommand() = default;
		
		// Copy and Move semantics
		MoveCommand(const MoveCommand& other)					= delete;
		MoveCommand& operator=(const MoveCommand& other)		= delete;
		MoveCommand(MoveCommand&& other) noexcept				= delete;
		MoveCommand& operator=(MoveCommand&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override;

		glm::vec2 GetDirection() const { return m_Direction; }
		float GetSpeed() const { return m_Speed; }
		
		
	private:
		// Member variables
		glm::vec2 m_Direction;
		float m_Speed;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

