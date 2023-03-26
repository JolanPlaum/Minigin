#pragma once

namespace dae
{
	class GameObject;

	//=============================
	// Base Command Class
	//=============================
	class Command
	{
	public:
		// Constructors and Destructor
		explicit Command(GameObject* pGameObject) :m_pGameObject{ pGameObject } {}
		virtual ~Command() = default;
		
		// Copy and Move semantics
		Command(const Command& other)					= delete;
		Command& operator=(const Command& other)		= delete;
		Command(Command&& other) noexcept				= delete;
		Command& operator=(Command&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Execute() = 0;


	private:
		// Member variables
		GameObject* m_pGameObject;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	};
}