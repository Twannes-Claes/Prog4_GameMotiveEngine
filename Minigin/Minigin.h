#pragma once
#include <string>
#include <functional>

namespace Monke
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, const float width, const float heigth);
		~Minigin();
		void Run(const std::function<void()>& initiliaze) const;

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		float GetWindowW() const { return m_WindowW; }
		float GetWindowH() const { return m_WindowH; }

	private:

		const float m_WindowW{};
		const float m_WindowH{};

	};
}