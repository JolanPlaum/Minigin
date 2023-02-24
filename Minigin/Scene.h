#pragma once
// Includes
#include "SceneManager.h"

namespace dae
{
	// Class Forward Declarations
	class GameObject;

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
		void Update();
		void Render() const;

		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();


	private:
		// Member variables
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 

		//---------------------------
		// Private Member Functions
		//---------------------------
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(const std::string& name);

	};

}
