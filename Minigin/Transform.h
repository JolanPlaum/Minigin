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
		Transform() = default;
		~Transform() = default;
		
		// Copy and Move semantics
		Transform(const Transform& other)					= default;
		Transform& operator=(const Transform& other)		= default;
		Transform(Transform&& other) noexcept				= default;
		Transform& operator=(Transform&& other) noexcept	= default;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void ClearDirtyFlags();

		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z);
		void SetLocalRotation(const glm::vec3& rot);
		void SetLocalRotation(float x, float y, float z);
		void SetLocalScale(const glm::vec3& s);
		void SetLocalScale(float x, float y, float z);
		void SetLocalScale(float s);

		void SetWorldPosition(const glm::vec3& pos);
		void SetWorldPosition(float x, float y, float z);
		void SetWorldRotation(const glm::vec3& rot);
		void SetWorldRotation(float x, float y, float z);
		void SetWorldScale(const glm::vec3& s);
		void SetWorldScale(float x, float y, float z);
		void SetWorldScale(float s);

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetWorldRotation();
		const glm::vec3& GetWorldScale();
		//todo: currently world position is not affected by owner rotation/scale
		//		make it so that it does take that into mind
	
	
	private:
		// Member variables
		bool m_IsPositionDirty{ false }, m_IsRotationDirty{ false }, m_IsScaleDirty{ false };
		glm::vec3 m_LocalPosition{}, m_LocalRotation{}, m_LocalScale{};
		glm::vec3 m_WorldPosition{}, m_WorldRotation{}, m_WorldScale{};
	
		//---------------------------
		// Private Member Functions
		//---------------------------
		void SetPositionDirty();
		void SetRotationDirty();
		void SetScaleDirty();

		void ClearDirtyPosition();
		void ClearDirtyRotation();
		void ClearDirtyScale();
	
	};
}

