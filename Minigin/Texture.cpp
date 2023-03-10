#include "Texture.h"

#include <glm/vec3.hpp>
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Errors.h"

namespace Monke
{
	Texture::Texture(std::weak_ptr<GameObject> parent)
	:RenderComponent(parent)
	{
	}

	void Texture::Initialize()
	{
		m_pTransform = GetOwner().lock()->GetComponent<Transform>();
		
		if (m_pTransform.expired())
		{
			const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No transform component to draw on a given position");
		}

		//GetComponentCheck(m_pTransform, "No transform component to draw on a given position");
	}

	void Texture::Render() const
	{
		RenderTexture(m_pTransform, m_pTexture);
	}

	void Texture::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
	{
		m_pTexture = pTexture;
	}
}
