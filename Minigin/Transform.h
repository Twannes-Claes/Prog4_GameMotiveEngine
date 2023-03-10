#pragma once
#include "DataComponent.h"
#include <glm/glm.hpp>

namespace Monke
{
	class Transform final : public DataComponent
	{
	public:

		explicit Transform(std::weak_ptr<GameObject> parent);
		virtual ~Transform() override = default;


		virtual void Initialize() override;


		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition();

		//void SetWorldPosition(const glm::vec3& pos) { m_WorldPosition = pos; }
		//void SetWorldPosition(const float x, const float y, const float z = 0) { m_WorldPosition = { x,y,z }; }

		void SetPosition(const glm::vec3& pos) { m_LocalPosition = pos; SetTransformDirty(); }
		void SetPosition(const float x, const float y, const float z = 0) { m_LocalPosition = { x,y,z }; SetTransformDirty(); }

		void SetLocalPosition(const glm::vec3& pos) { m_LocalPosition = pos; SetTransformDirty(); }
		void SetLocalPosition(const float x, const float y, const float z = 0) { m_LocalPosition = { x,y,z }; SetTransformDirty(); }

		void SetTransformDirty();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:

		void UpdateWorldPosition();

		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

		//Dirty flag
		bool m_IsDirty{ true };

	};
}