#pragma once
// Includes
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Transform final : public Component
	{
	public:
		// Constructors and Destructor
		explicit Transform() = default;
		~Transform() = default;
		
		// Copy and Move semantics
		Transform(const Transform& other)					= default;
		Transform& operator=(const Transform& other)		= default;
		Transform(Transform&& other) noexcept				= default;
		Transform& operator=(Transform&& other) noexcept	= default;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void SetPosition(const glm::vec3& pos);
		void SetPosition(float x, float y, float z);
		void SetRotation(const glm::vec3& rot);
		void SetRotation(float x, float y, float z);
		void SetScale(const glm::vec3& s);
		void SetScale(float x, float y, float z);
		void SetScale(float s);

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetPosition() const { return m_Position; }
	
	
	private:
		// Member variables
		glm::vec3 m_Position, m_Rotation, m_Scale;
	
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

