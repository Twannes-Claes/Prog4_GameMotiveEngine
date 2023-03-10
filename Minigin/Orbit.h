#pragma once

#include <glm/vec3.hpp>

#include "UpdateComponent.h"

namespace Monke
{
	class Transform;

	class Orbit final : public UpdateComponent
	{

	public:

		explicit Orbit(std::weak_ptr<GameObject> parent);
		virtual ~Orbit() override = default;

		virtual void Initialize() override;
		virtual void Update() override;

		void SetRadius(const float radius) { m_Radius = radius; }
		void SetRotationSpeed(const float speed) { m_RotSpeed = speed; }
		void SetCenter(const glm::vec3& center) { m_Center = center; }

		Orbit(const Orbit& other) = delete;
		Orbit(Orbit&& other) = delete;
		Orbit& operator=(const Orbit& other) = delete;
		Orbit& operator=(Orbit&& other) = delete;


		std::weak_ptr<Transform> m_pTransform;

		float m_Rotation{};

		float m_Radius;
		float m_RotSpeed;

		glm::vec3 m_Center{};

	};

}

