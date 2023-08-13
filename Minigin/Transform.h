#pragma once
// Includes
#include "Component.h"
#include <glm/vec2.hpp>
#include "Event.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Transform final : public Component
	{
	public:
		// Constructors and Destructor
		Transform(GameObject* pGameObject) :Component(pGameObject) {};
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

		void SetLocalPosition(glm::vec2 pos);
		void SetLocalPosition(float x, float y);
		void SetLocalRotation(double rot);
		void SetLocalScale(glm::vec2 s);
		void SetLocalScale(float x, float y);
		void SetLocalScale(float s);

		void SetWorldPosition(glm::vec2 pos);
		void SetWorldPosition(float x, float y);
		void SetWorldRotation(double rot);
		void SetWorldScale(glm::vec2 s);
		void SetWorldScale(float x, float y);
		void SetWorldScale(float s);

		glm::vec2 GetLocalPosition();
		double GetLocalRotation();
		glm::vec2 GetLocalScale();

		glm::vec2 GetWorldPosition();
		double GetWorldRotation();
		glm::vec2 GetWorldScale();

		Event<> GotDirty;
	
	
	private:
		// Member variables
		bool m_IsPositionDirty{ false }, m_IsRotationDirty{ false }, m_IsScaleDirty{ false };
		glm::vec2 m_LocalPosition{}, m_WorldPosition{};
		glm::vec2 m_LocalScale{1}, m_WorldScale{1};
		double m_LocalRotation{}, m_WorldRotation{};

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

