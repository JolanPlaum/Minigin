#pragma once
// Includes
#include "Component.h"
#include <glm/gtc/constants.hpp>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class RotationMovement : public Component
	{
	public:
		// Constructors and Destructor
		RotationMovement(GameObject* pGameObject) :Component(pGameObject) {};
		virtual ~RotationMovement() = default;
		
		// Copy and Move semantics
		RotationMovement(const RotationMovement& other)					= delete;
		RotationMovement& operator=(const RotationMovement& other)		= delete;
		RotationMovement(RotationMovement&& other) noexcept				= delete;
		RotationMovement& operator=(RotationMovement&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update() override;

		void SetRadius(float radius);
		void SetSpeedRadians(float rotationSpeed);
		void SetSpeedDegrees(float rotationSpeed);


	private:
		// Member variables
		float m_RotationSpeed{ glm::pi<float>() };
		float m_Radius{ 1.f };
		float m_CurrentAngle{ 0.f };
	
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

