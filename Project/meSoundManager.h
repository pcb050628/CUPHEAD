#pragma once
#include "DEFAULT.h"

namespace me
{	
	class SoundManager
	{
	public:
		static bool Init();
		static LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

	private:
		static LPDIRECTSOUND8 mSoundDevice;
	};
}

