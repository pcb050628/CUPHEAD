#pragma once
#include "meResource.h"

namespace me
{	
	class Sound : public Resource
	{
	public:
		Sound(const std::wstring& _name);
		virtual ~Sound() override;

		virtual bool Load(const std::wstring& path) override;
		bool LoadWavFile(const std::wstring& path);
		void Play(bool loop);
		void Stop(bool reset);
		void SetPosition(float position, bool loop);
		void SetVolume(float volume);
		int GetDecibel(float volume);

	private:
		LPDIRECTSOUNDBUFFER		mSoundBuffer;
		DSBUFFERDESC			mBufferDesc;
		int mVolume;

	};
}

