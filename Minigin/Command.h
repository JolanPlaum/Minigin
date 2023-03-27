#pragma once

namespace dae
{
	//=============================
	// Base Command Class
	//=============================
	class Command
	{
	public:
		// Constructors and Destructor
		explicit Command() = default;
		virtual ~Command() = default;
		
		// Copy and Move semantics
		Command(const Command& other)					= delete;
		Command& operator=(const Command& other)		= delete;
		Command(Command&& other) noexcept				= delete;
		Command& operator=(Command&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Execute() = 0;
	};


	//=============================
	// GameObject Command Class
	//=============================
	class GameObject;
	class GameObjectCommand : public Command
	{
	public:
		// Constructors and Destructor
		explicit GameObjectCommand(GameObject* pGameObject) :m_pGameObject{ pGameObject } {}
		virtual ~GameObjectCommand() = default;
		
		// Copy and Move semantics
		GameObjectCommand(const GameObjectCommand& other)					= delete;
		GameObjectCommand& operator=(const GameObjectCommand& other)		= delete;
		GameObjectCommand(GameObjectCommand&& other) noexcept				= delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Execute() override = 0;


	private:
		// Member variables
		GameObject* m_pGameObject;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	};
}