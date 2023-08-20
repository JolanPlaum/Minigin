#pragma once
// Includes
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	// Class Forward Declarations

	// Class Declaration
	class Scene final
	{
	public:
		// Constructors and Destructor
		~Scene() = default;

		// Copy and Move semantics
		Scene(const Scene& other)					= delete;
		Scene& operator=(const Scene& other)		= delete;
		Scene(Scene&& other) noexcept				= delete;
		Scene& operator=(Scene&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init();
		void UpdateGui();
		void Update();
		void Render() const;
		void Cleanup();

		GameObject* CreateObject();
		GameObject* Add(std::unique_ptr<GameObject> pObject);
		std::unique_ptr<GameObject> Remove(GameObject* pObject);
		void RemoveAll();


	private:
		// Member variables
		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_Objects{};
		std::vector<GameObject*> m_NewObjects{};
		std::vector<GameObject*> m_ActiveObjects{};

		static unsigned int m_IdCounter;

		//---------------------------
		// Private Member Functions
		//---------------------------
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

	};

}
