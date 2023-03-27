#pragma once
// Includes
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class MoveCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed);
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
		
		
	private:
		// Member variables
		glm::vec3 m_Direction;
		float m_Speed;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

