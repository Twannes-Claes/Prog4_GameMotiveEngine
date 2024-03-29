#pragma once

#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <vector>

#include "AudioSystem.h"

struct Mix_Chunk;

namespace Monke
{

	class SDL_Audio final : public AudioSystem
	{
	public:

		SDL_Audio();
		virtual ~SDL_Audio() override;

		virtual void Play(const SoundID id, const float volume) override;
		virtual void Play(const SoundID id, const std::string& path, const float volume) override;

		virtual void LoadSound(const SoundID id ,const std::string& path) override;

		virtual void Stop(const SoundID ) override {};
		virtual void StopAll() override;

		virtual void Pause(const SoundID ) override{};
		virtual void PauseAll() override;

		virtual void Resume(const SoundID ) override{};
		virtual void ResumeAll() override;

		void Mute(bool mute);

	private:

		void Run();

		enum SDL_AudioEventType
		{
			play,
			play_name,

			stop,
			stop_all,

			pause,
			pause_all,

			resume,
			resume_all,

			load
		};

		struct AudioEvent
		{
			SDL_AudioEventType type{};

			SoundID ID{};
			float volume{};

			std::string path;
		};

		struct SoundData
		{
			Mix_Chunk* pData{};

			std::string path{};
		};

		std::unordered_map<SoundID ,SoundData> m_Sounds;

		std::jthread m_Thread{};
		std::mutex m_Mutex{};
		std::condition_variable m_Condition{};

		std::queue<AudioEvent> m_SoundQueue{};
	};

}
