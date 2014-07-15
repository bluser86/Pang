#pragma once
#include "Include.h"
#include "IAudioProvider.h"

class AudioServiceLocator
{
public:
	static IAudioProvider* GetAudioProvider() { return _audioProvider; } const

	static void RegisterService(IAudioProvider *provider)
	{
		_audioProvider = provider;
	}

private:
	static IAudioProvider* _audioProvider;
};