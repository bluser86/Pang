#include "Include.h"
#include "SFMLSoundProvider.h"

SFMLSoundProvider::SFMLSoundProvider() :
	_currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
	// Set first available channel number
	int availableChannel = -1;
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availableChannel = i;
			break;
		}
	}

	if(availableChannel != -1)
	{
		try
		{
			_currentSounds[availableChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availableChannel].play();
		}
		catch (SoundNotFoundException e)
		{
			// File was not found, but lets just continue.
			std::cout << e.what() << std::endl;
		}
	}
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	sf::Music* currentSong;
	try
	{
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException e)
	{
		// File was not found, exit
		std::cout << e.what() << std::endl;
		return;
	}

	if (_currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() == sf::Music::Playing)
			{
				priorSong->stop();
			}
		}
		catch (SoundNotFoundException e)
		{
			// File was not found, but lets just continue.
			std::cout << e.what() << std::endl;
		}
	}

	_currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::StopAllSounds()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].stop();
	}

	if (_currentSongName != "")
	{
		sf::Music * currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Music::Playing)
		{
			currentSong->stop();
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if(_currentSounds[i].getStatus() == sf::Sound::Playing)
		{
			return true;
		}
	}
	return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
	if (_currentSongName != "")
	{
		return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
	}

	return false;
}
