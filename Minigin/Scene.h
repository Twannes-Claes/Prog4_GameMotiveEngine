#pragma once
#include "SceneManager.h"

namespace Monke
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:

		std::shared_ptr<GameObject> MakeGameObject();

		void Add(std::shared_ptr<GameObject> object);
		void Remove(const std::shared_ptr<GameObject>& object);
		void RemoveAll();

		void Initialize() const;
		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(std::string name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
