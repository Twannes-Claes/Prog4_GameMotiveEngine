#pragma once
#include <memory>
#include <vector>
#include <string>

#include "UpdateComponent.h"
#include "RenderComponent.h"
#include "BaseComponent.h"
#include "DataComponent.h"

namespace Monke
{
	class Texture2D;

	//class BaseComponent;
	//class RenderComponent;
	//class UpdateComponent;
	//class DataComponent;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{

	public:

		//scene manager functions
		void Initialize() const;
		void Update();
		void Render() const;

		//scenegraph functions
		void SetParent(const std::weak_ptr<GameObject>& newParent, const bool keepWorldPosition = false);
		void AddChild(const std::weak_ptr<GameObject>& child);
		void RemoveChild(std::weak_ptr<GameObject> child);

		std::weak_ptr<GameObject> GetParent() const { return m_pParent; }
		const std::vector<std::weak_ptr<GameObject>>& GetAllChildren() const { return m_pChildren; }

		void Destroy();
		bool IsMarkedDead() const { return m_IsMarkedDead; }

		//THE BIG SIX
		GameObject() = default;

		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Template_Component_Classes

		template <class T>
		std::weak_ptr<T> GetComponent() const;

		template <class T>
		std::shared_ptr<T> AddComponent();

		template <class T>
		bool HasComponent() const;

		template <class T>
		bool RemoveComponent();

#pragma endregion

	private:

#pragma region Template_ComponentCheck_Functions
		//private functions to make less code
		//template<typename T, typename V>
		//bool GetComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	for (const std::shared_ptr<V>& pComponent : vector)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool AddComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	if constexpr (std::is_base_of_v<V, T>)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		auto pVComponent = std::dynamic_pointer_cast<V>(derivedComponent);
		//
		//		vector.push_back(pVComponent);
		//		return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool HasComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	for (const std::shared_ptr<V>& component : vector)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		if ((derivedComponent = std::dynamic_pointer_cast<T>(component))) return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool RemoveComponentCheck(std::vector<std::shared_ptr<V>>& vector)
		//{
		//	if constexpr (std::is_base_of_v<V, T>)
		//	{
		//		//find the first component that matches the component in the vector
		//		auto it = std::remove_if(vector.begin(), vector.end(), []
		//		(const std::shared_ptr<BaseComponent>& component)
		//			{
		//				//check if the component can be casted to the template type
		//				return std::dynamic_pointer_cast<T>(component) != nullptr;
		//			});
		//		//if i components has been found erase it and turn the remove flag to true
		//		if (it != vector.end())
		//		{
		//			vector.erase(it);
		//			return true;
		//		}
		//	}
		//
		//	return false;
		//}
#pragma endregion

		template <class T>
		void CleanUpVector(std::vector<std::shared_ptr<T>>& v)
		{

			static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

			//auto it = std::remove_if(v.begin(), v.end(),
			//[]
			//(const std::shared_ptr<BaseComponent>& component)
			//{
			//	//check if the component can be casted to the template type
			//	return component->IsMarkedDead();
			//});
			////if i components has been found erase it and turn the remove flag to true
			//if (it != v.end())
			//{
			//	v.erase(it);
			//}

			//remove all elements from the vector if is marked as dead

			v.erase(std::remove_if(begin(v), end(v), [](auto pComponent)
			{
				return pComponent->IsMarkedDead();
			}), end(v));

		}

		//parent and children for scenegraph
		std::weak_ptr<GameObject> m_pParent{};
		std::vector< std::weak_ptr<GameObject> > m_pChildren{};

		//component vectors
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
		std::vector<std::shared_ptr<DataComponent>> m_pDataComponents{};

		bool m_IsMarkedDead{ false };
	};

#pragma region Template_Component_Logic

	template <class T>
	std::weak_ptr<T> GameObject::GetComponent() const
	{

		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		//make shared of class
		std::shared_ptr<T> derivedComponent{ nullptr };

		//bool gettedComponent{ false };

		//gettedComponent = GetComponentCheck(derivedComponent, m_pUpdateComponents);
		for (const std::shared_ptr<UpdateComponent>& pComponent : m_pUpdateComponents)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return derivedComponent;
		}
		//if (gettedComponent) return derivedComponent;
		//
		//gettedComponent = GetComponentCheck(derivedComponent, m_pRenderComponents);
		for (const std::shared_ptr<RenderComponent>& pComponent : m_pRenderComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return derivedComponent;
		}
		//if (gettedComponent) return derivedComponent;
		//
		//gettedComponent = GetComponentCheck(derivedComponent, m_pDataComponents);
		for (const std::shared_ptr<DataComponent>& pComponent : m_pDataComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return derivedComponent;
		}
		//if (gettedComponent) return derivedComponent;

		return derivedComponent;
	}

	template<class T>
	std::shared_ptr<T> GameObject::AddComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v

		static_assert(std::is_base_of_v<BaseComponent, T> , "The given class must be inherited from BaseComponent");

		//make the component
		//https://en.cppreference.com/w/cpp/memory/enable_shared_from_this

		auto pComponent{ std::make_shared<T>(weak_from_this()) };

		//bool hasAdded{ false };

		//check if component is an updatable or render component, if so add them to the vector
		//hasAdded = AddComponentCheck(pComponent, m_pUpdateComponents);
		if constexpr (std::is_base_of_v<UpdateComponent, T>)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			auto pUpdateComponent = std::dynamic_pointer_cast<UpdateComponent>(pComponent);
		
			m_pUpdateComponents.push_back(pUpdateComponent);
			return pComponent;
		}
		//if (hasAdded) return pComponent;

		//hasAdded = AddComponentCheck(pComponent, m_pRenderComponents);
		else if constexpr (std::is_base_of_v<RenderComponent, T>)
		{
			auto pRenderComponent = std::dynamic_pointer_cast<RenderComponent>(pComponent);
		
			m_pRenderComponents.push_back(pRenderComponent);
			return pComponent;
		}
		//if (hasAdded) return pComponent;

		//hasAdded = AddComponentCheck(pComponent, m_pDataComponents);
		else if constexpr (std::is_base_of_v<DataComponent, T>)
		{
			auto pDataComponent = std::dynamic_pointer_cast<DataComponent>(pComponent);
		
			m_pDataComponents.push_back(pDataComponent);
			return pComponent;
		}
		//if (hasAdded) return pComponent;

		//return the component
		return pComponent;
	}

	template <class T>
	bool GameObject::HasComponent() const
	{
		std::shared_ptr<T> derivedComponent{ nullptr };

		//bool hasComponent{ false };

		//hasComponent = HasComponentCheck(derivedComponent, m_pUpdateComponents);
		for (const std::shared_ptr<UpdateComponent>& pComponent : m_pUpdateComponents)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		}
		//loop over all render components and check if it has the given one
		//if (hasComponent) return hasComponent;

		//hasComponent = HasComponentCheck(derivedComponent, m_pRenderComponents);
		for (const std::shared_ptr<RenderComponent>& pComponent : m_pRenderComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		}
		//loop over all data components and check if it has the given one
		//if (hasComponent) return hasComponent;

		//hasComponent = HasComponentCheck(derivedComponent, m_pDataComponents);
		for (const std::shared_ptr<DataComponent>& pComponent : m_pDataComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		}
		//if (hasComponent) return hasComponent;

		return false;
	}

	template <class T>
	bool GameObject::RemoveComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v
		
		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		////save bool to check if component has been deleted
		//bool removed = false;

		//removed = RemoveComponentCheck<T>(m_pUpdateComponents);

		//if (removed) return removed;
		if constexpr (std::is_base_of_v<UpdateComponent, T>)
		{
			//find the first component that matches the component in the vector
			auto it = std::remove_if(m_pUpdateComponents.begin(), m_pUpdateComponents.end(), 
			[]
			(const std::shared_ptr<BaseComponent>& component)
			{
				//check if the component can be casted to the template type
				return std::dynamic_pointer_cast<T>(component) != nullptr;
			});
			//if i components has been found erase it and turn the remove flag to true
			if (it != m_pUpdateComponents.end())
			{
				//m_pUpdateComponents.erase(it);
				(*it)->Destroy();
				return true;
			}
		}
		//check if it is a render component

		//removed = RemoveComponentCheck<T>(m_pRenderComponents);

		//if (removed) return removed;
		else if constexpr (std::is_base_of_v<RenderComponent, T>)
		{
			auto it = std::remove_if(m_pRenderComponents.begin(), m_pRenderComponents.end(), []
			(const std::shared_ptr<BaseComponent>& component)
			{
				return std::dynamic_pointer_cast<T>(component) != nullptr;
			});
			if (it != m_pRenderComponents.end())
			{
				(*it)->Destroy();
				return true;
			}
		}
		//check if it is a data component

		//removed = RemoveComponentCheck<T>(m_pDataComponents);

		//if (removed) return removed;
		else if constexpr (std::is_base_of_v<DataComponent, T>)
		{
			auto it = std::remove_if(m_pDataComponents.begin(), m_pDataComponents.end(), []
			(const std::shared_ptr<BaseComponent>& component)
				{
					return std::dynamic_pointer_cast<T>(component) != nullptr;
				});
			if (it != m_pDataComponents.end())
			{
				(*it)->Destroy();
				return true;
			}
		}

		//return if the component has been removed
		return false;
	}

#pragma endregion

}
