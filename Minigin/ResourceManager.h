#pragma once
#include <string>
#include <memory>
#include <glm/vec2.hpp>

#include "Singleton.h"

namespace Monke
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:

		void Init(const std::string& filename);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

		const std::string& GetPath() { return m_dataPath; }

	private:

		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
